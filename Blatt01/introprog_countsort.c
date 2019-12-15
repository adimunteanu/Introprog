#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"


//Adrian Munteanu 13:38 09.11.2019 
int MAX_LAENGE = 1000;
int MAX_VALUE = 100;

void count_sort_calculate_counts(int input_array[], int len, int count_array[]) {
    /* Hier Funktion implementieren */
    for(int i = 0; i < len; i++)
        count_array[input_array[i]]++;
    // for(int i = 0; i < MAX_VALUE; i++)
    //     printf("%d ", count_array[i]);
    // printf("\n");
}

void count_sort_write_output_array(int output_array[], int len, int count_array[]) {
    /* Hier Funktion implementieren */
    int size = 0;
    for(int i = 0; i < MAX_VALUE + 1; i++){
        // printf("%d ", count_array[i]);
        if(count_array[i])
            for(int j = 1; j <= count_array[i]; j++){
                output_array[size] = i;
                size++;
            }
        // printf("%d ", size);
    }
}



int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    /*
     * Hier alle nötigen Deklarationen und Funktionsaufrufe für
     * Countsort einfügen!
     */
    //Declaration and initialization of reccurenceArray with 0
    int recurrenceArray[MAX_VALUE + 1];
    for(int i = 0; i <= MAX_VALUE; i++)
        recurrenceArray[i] = 0;

    int output_array[MAX_LAENGE];
    count_sort_calculate_counts(input_array, len, recurrenceArray);
    count_sort_write_output_array(output_array, len, recurrenceArray);

    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    print_array(output_array, len);

    return 0;
}
