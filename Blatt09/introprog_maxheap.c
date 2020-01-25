#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "introprog_heap.h"

/* Reserviere Speicher für einen Heap
 *
 * Der Heap soll dabei Platz für capacity Elemente bieten.
 *
 * Um konsistent mit den Parametern für malloc zu sein, ist
 * capacity als size_t (entspricht unsigned long auf x86/64)
 * deklariert.
 * Da es sauberer ist, sind auch alle Indizes in dieser Aufgabe
 * als size_t deklariert. Ob man size_t oder int als Index für
 * ein Array verwendet, macht in der Praxis (auf x86/64) nur
 * bei Arrays mit mehr als 2.147.483.647 Elementen einen
 * Unterschied.
 */
heap* heap_create(size_t capacity) {
    // Declaring and Initializing heap structure
    heap *new_heap = (heap *) malloc(sizeof(heap));
    new_heap->elements = (int *) malloc(sizeof(int) * capacity);
    new_heap->size = 0;
    new_heap->capacity = capacity;

    return new_heap;
}

// void printHeap(heap* h)
// {
//     for(int i = 0; i < h->size; i++)
//         printf("%d ", h->elements[i]);
//     printf("\n");
// }

/* Stellt die Heap Bedingung an Index i wieder her
 *
 * Vorraussetzung: Der linke und rechte Unterbaum von i
 * erfüllen die Heap-Bedingung bereits.
 */
void heapify(heap* h, size_t i) {
    // Get left and right children Indexes
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    // Find the largest value from the set {left, right, i}
    size_t largest;
    if(left < h->size && h->elements[left] > h->elements[i])
        largest = left;
    else 
        largest = i;
    if(right < h->size && h->elements[right] > h->elements[largest])
        largest = right;

    // If there is a change that needs to be made, switch largest with i and
    // continue recursively
    if(largest != i){
        size_t aux = h->elements[i];
        h->elements[i] = h->elements[largest];
        h->elements[largest] = aux;
        heapify(h, largest);
    }
}

/* Holt einen Wert aus dem Heap
 *
 * Wenn der Heap nicht leer ist, wird die größte Zahl
 * zurückgegeben. Wenn der Heap leer ist, wird -1 zurückgegeben.
 */
int heap_extract_max(heap* h) {
    if(h->size == 0){
        // If the heap is empty, return an error
        return -1;
    } else {
        int max = h->elements[0];
        h->elements[0] = h->elements[h->size - 1];
        h->size--;
        // printHeap(h);
        heapify(h, 0);
        // printHeap(h);
        return max;
    }
}

/* Fügt einen Wert in den Heap ein
 *
 * Wenn der Heap bereits voll ist, wird -1 zurückgegeben.
 */
int heap_insert(heap* h, int key) {
    if(h->size == h->capacity){
        // If the heap is full, return an error
        return -1;
    } else {
        h->size++;
        //printf("size: %zu  array:", h->size);
        size_t index = h->size - 1;

        while(index > 0 && h->elements[(index - 1)/ 2] < key)
        {
            h->elements[index] = h->elements[(index - 1) / 2];
            index = (index - 1) / 2;
        }

        h->elements[index] = key;

        // printHeap(h);
        // Print heap function used for debugging
        

        return 1;
    }
}

/* Gibt den Speicher von einem Heap wieder frei
 */
void heap_free(heap* h) {
    free(h->elements);
    free(h);
}
