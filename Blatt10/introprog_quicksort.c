#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

/*****************************************************
 * Die benoetigten structs findet Ihr in quicksort.h *
 *****************************************************/

void init_list(list* mylist)
{
// HIER Liste initialisieren
    mylist->first = NULL;
    mylist->last = NULL;
}



// Diese Funktion fügt Listenelemente an die Liste an
void insert_list(list_element* le, list* mylist)
{
    // HIER Code einfügen
    // If we have an empty list
    if(!mylist->first){
        mylist->first = le;
        mylist->last = le;
        mylist->last->next = NULL;
        mylist->first->next = NULL;
    } else {
        // If we have at least one element
        list_element *currentElement = mylist->first;
        while(currentElement->next != NULL)
            currentElement = currentElement->next;
        currentElement->next = le;
        mylist->last = le;
        mylist->last->next = NULL;
        // printf("%s %d\n", le->password, le->count);
        // printf("%s %d\n", mylist->first->password, mylist->first->count);
    }
}

// Speicher für Listenelemente wieder freigeben
void free_list(list* mylist)
{
    // HIER Code einfügen
    while(mylist->first)
    {
        list_element *temp = mylist->first;
        mylist->first = mylist->first->next;
        free(temp);
    }
}


// Namen, Zahlen Paare in Liste einlesen
void read_data(char* filename, list* mylist)
{
    // HIER Code einfügen:
    // * Speicher allozieren
    // * Daten in list_element einlesen
    // * insert_list benutzen, um list_element in Liste einzufügen

    // This aufgabe was badly organized
    FILE *fp = fopen(filename, "r");
    char *password = (char *) malloc(sizeof(char *));
    int count;
    while(fscanf(fp,"%s %d\n", password, &count) != EOF)
    {
        // printf("%s %d\n", password, count);
        list_element *newElement = (list_element *) malloc(sizeof(list_element));
        newElement->password = (char *) malloc(sizeof(char *));
        newElement->count = count;
        strncpy(newElement->password, password, strlen(password));
        newElement->next = NULL;

        insert_list(newElement, mylist);

    }
    fclose(fp);
}

// Liste teilen. Teillisten werden in left und right zurück gegeben
list_element* partition( list* input, list* left, list* right )
{
    // HIER Code einfügen:
    // parition() Funktion implementieren
    list_element* pivot = input->first;
    list_element* currentElement = pivot->next;
    
    while(currentElement)
    {
        // printf("%d\n", currentElement->count);
        list_element* tmp = currentElement->next;
        if(currentElement->count < pivot->count)
        {
            // Add to left
            insert_list(currentElement, left);
        } else {
            // Add to right
            insert_list(currentElement, right);
        }
        currentElement = tmp;
    }
    return pivot;
}

// Hauptfunktion des quicksort Algorithmus
void qsort_list(list* mylist)
{
    // HIER Code einfügen
    if(mylist->first != mylist->last)
    {
        list left, right;
        init_list(&left);
        init_list(&right);
        list_element* pivot = partition(mylist, &left, &right);

        qsort_list(&left);
        qsort_list(&right);

        if(left.first == NULL){
            mylist->first = pivot;
        } else {
            mylist->first = left.first;
            left.last->next = pivot;
        }

        if(right.first == NULL){
            pivot->next = NULL;
            mylist->last = pivot;
        } else {
            pivot->next = right.first;
            mylist->last = right.last;
        }
    }

}

// Liste ausgeben
void print_list(list* mylist)
{
    // HIER Code einfügen:
    // * Laufe über die list_element in mylist und gebe sie aus.
    list_element* currentElement = mylist->first;
    while(currentElement)
    {
        printf("%s %d\n", currentElement->password, currentElement->count);
        currentElement = currentElement->next;
    }
}

