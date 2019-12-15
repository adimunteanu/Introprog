#include <stdio.h>
#include <stdlib.h>
#include "introprog_complexity_steps_input.h"

const int MAX_VALUE = 100;

void count_sort_calculate_counts(int input_array[], int len, int count_array[], int* befehle) {
    // Muss implementiert werden
    *befehle += 1; // init i = 0
    for(int i = 0; i < len; i++){
        *befehle += 1; //vergleich
        *befehle += 1; //i++
        count_array[input_array[i]]++;
        *befehle += 1; // count_array[input_array[i]] ++
    }
    *befehle += 1; //letzte vergleich
}

void count_sort_write_output_array(int output_array[], int len, int count_array[], int* befehle) {
    // Muss implementiert werden
    int index = 0;
    *befehle += 1; // init index = 0;
    *befehle += 1; // init i = 0
    for(int i = 0; i <= MAX_VALUE; i++){
        *befehle += 1; // vergleich
        *befehle += 1; // i++

        *befehle += 1; // init j = 1
        for(int j = 1; j <= count_array[i]; j++)
        {
            *befehle += 1; // vergleich
            *befehle += 1; // j++

            output_array[index] = i;
            *befehle += 1; // output_array[index] = i

            index++;
            *befehle += 1; // index++;
        }
        *befehle += 1; //letzte vergleich
    }
    *befehle += 1; // letzte vergleich groß for
}

void count_sort(int array[], int len, int* befehle) {
    // Muss implementiert werden

    int *count_array = malloc(MAX_VALUE * sizeof(int) + 4);
    *befehle += 1; // malloc
    *befehle += 1; // init i = 0
    for(int i = 0; i <= MAX_VALUE; i++){
        *befehle += 1; //vergleich
        *befehle += 1; // i++
        count_array[i] = 0; //init with 0
        *befehle += 1; // count_array[i] = 0
    } 
    *befehle += 1; //letzte vergleich
    count_sort_calculate_counts(array, len, count_array, befehle);

    count_sort_write_output_array(array, len, count_array, befehle);
    free(count_array);
    *befehle += 1; // free(count_array)
}


void insertion_sort(int array[], int len, int* befehle) {
    *befehle += 2 * len; // for
    for(int j = 1; j < len; j++){

        int key = array[j];
        *befehle += 1; // key = array[j]

        int i = j - 1; 
        *befehle += 1; // i = j - 1

        while(i > -1 && key < array[i])
        {
            *befehle += 1; // erste vergleich
            *befehle += 1; // zweite vergleich

            array[i+1] = array[i];
            *befehle += 1; // array[i+1]=array[i]

            i--; 
            *befehle += 1; // i--
        }
        *befehle += 1; // lezte erste vergeleich while
        *befehle += 1; // letzte zweite vergleich while

        array[i+1] = key;
        *befehle += 1; // array[i+1] = key
    }
}


int main(int argc, char *argv[]) {

    const int WERTE[] = {100000,100000,100000,100000,100000};
    const int LEN_WERTE = 5;
    const int LEN_ALGORITHMEN = 2;

    int rc = 0;
    long befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j)
    {
        int n = WERTE[j];

        // Reserviere Speicher für  Arrays der Länge n
        int* array_countsort = malloc(sizeof(int) * n);
        int* array_insertionsort = malloc(sizeof(int) * n);

        // Fülle array_countsort mit Zufallswerten ..
        fill_array_randomly(array_countsort, n, MAX_VALUE);
        // ... und kopiere die erzeugten Werte in das Array
        // array_insertionsort
        copy_array_elements(array_insertionsort, array_countsort, n);

        // Teste ob beide Arrays auch wirklich die gleichen Werte
        // enthalten
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n))
        {
            printf("Die Eingaben für beide Algorithmen müssen für die Vergleichbarkeit gleich sein!\n");
            return -1;
        }

        for(int i = 0; i < LEN_ALGORITHMEN; ++i)
        {
            int anzahl_befehle = 0;

            start_timer();

            // Aufruf der entsprechenden Sortieralgorithmen
            if(i==0)
            {
                    count_sort(array_countsort, n, &anzahl_befehle);
            }
            else if(i==1)
            {
                    insertion_sort(array_insertionsort, n, &anzahl_befehle);
            }
            

            // Speichere die Laufzeit sowie die Anzahl benötigter
            // Befehle
            laufzeit_array[i][j] = end_timer();
            befehle_array[i][j] = anzahl_befehle;
        }

        //debugging
        // for(int i = 0; i < n; i++)
        //     printf("%d ", array_countsort[i]);
        // printf("\n");
        // for(int i = 0; i < n; i++)
        //     printf("%d ", array_insertionsort[i]);
        // printf("\n");


        // Teste, ob die Ausgabe beider Algorithmen gleich sind
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n))
        {
            printf("Die Arrays sind nicht gleich. Eines muss (falsch) sortiert worden sein!\n");
            rc = -1;
        }

        // Gib den Speicherplatz wieder frei
        free(array_countsort);
        free(array_insertionsort);
    }

    // Ausgabe der Anzahl ausgeführter Befehle sowie der gemessenen
    // Laufzeiten (in Millisekunden)
    printf("Parameter MAX_VALUE hat den Wert %d\n", MAX_VALUE);
    printf("\t %32s           %32s \n", "Countsort","Insertionsort");
    printf("%8s \t %16s %16s \t %16s %16s \n", "n","Befehle", "Laufzeit","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j)
    {
        printf("%8d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i)
        {
            printf("%16ld %16.4f \t ",  befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return rc;
}
