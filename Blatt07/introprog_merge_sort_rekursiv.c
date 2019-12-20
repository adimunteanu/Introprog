#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des letzten Elements(Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last)
{
  // HIER Funktion merge() implementieren
  int *auxArray = (int *) malloc(sizeof(int) * (last - first + 1)); //Initialize auxiliary array
  int len = 0; //Initialize length of auxArray

  int leftIndex = first; //Initialize index for left side of array
  int rightIndex = middle + 1; //Initialize index for right side of array

  
  //While we can find values in both sides of the array
  while(leftIndex <= middle && rightIndex <= last)
  {
    if(array[leftIndex] < array[rightIndex]){
      auxArray[len] = array[leftIndex]; //Insert the element from the left side
      leftIndex++;
    } else {
      auxArray[len] = array[rightIndex]; //Insert the element from the right side
      rightIndex++;
    }
    len++; // Increase size of auxArray
  }

  // While we still have elements in the left side, keep adding them to auxArray
  while(leftIndex <= middle)
  {
    auxArray[len] = array[leftIndex];
    len++;
    leftIndex++;
  }

  // While we still have elements in the right side, keep adding them to auxArray
  while(rightIndex <= last)
  {
    auxArray[len] = array[rightIndex];
    len++;
    rightIndex++;
  }
  
  int copyIndex = 0; // Initialize index to copy back values into array from auxArray

  while(copyIndex < len)
  {
    array[first + copyIndex] = auxArray[copyIndex];
    copyIndex++;
  }
  free(auxArray); // Free dynamic allocated memory
}

/*
 * Diese Funktion implementiert den rekursiven Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode in
 * Listing 1 implementiert werden.
 *
 * array: Pointer auf das Array
 * first: Index des ersten Elements des (Teil-)Array
 * last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last)
{
  // HIER Funktion merge_sort() implementieren
  if(first < last){
    int middle = (first + last)/2; //Calculate Middle
    merge_sort(array, first, middle); //Divide left side of array
    merge_sort(array, middle + 1, last); //Divide right side of array
    merge(array, first, middle, last); //Add two sorted arrays to one in sortered order
  }
}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl> \
 *         <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    // Hier array initialisieren
    int *array = (int *) malloc(sizeof(int) * atoi(argv[1]));

    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    // HIER Aufruf von "merge_sort()"
    merge_sort(array, 0, len - 1);

    printf("Sortiert:\n");
    print_array(array, len);
    
    free(array);

    return 0;
}
