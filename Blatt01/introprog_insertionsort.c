#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"


//Adrian Munteanu 13:02 09.11.2019
int MAX_LAENGE = 1000;

void insertion_sort(int array[], int len) {
    for(int j = 1; j < len; j++)
    {
        int currentElement = array[j];
        int sortedArrayIndex = j - 1;
        while(sortedArrayIndex > -1 && currentElement < array[sortedArrayIndex]){
            array[sortedArrayIndex + 1] = array[sortedArrayIndex];
            sortedArrayIndex--;
        }
        array[sortedArrayIndex + 1] = currentElement;
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int array[MAX_LAENGE];
    int len = read_array_from_file(array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(array, len);

    /* Aufruf Insertionsort */
    insertion_sort(array, len);

    printf("Sortiertes Array:");
    print_array(array, len);

    return 0;
}
