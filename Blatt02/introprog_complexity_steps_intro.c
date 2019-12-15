#include <stdio.h>
#include "introprog_complexity_steps_input.h"

long for_linear(int n, int* befehle)
{ 
    // TODO: Die Befehle müssen richtig gezählt werden

    long sum = 0;
    *befehle += 1; // Initialisierung von sum
    *befehle += 1; // Initialisierung von i
    for(int i = 1; i <= n; ++i) {
        *befehle += 1; //Vergleichung von i mit n (passiert n+1 mal)
        *befehle += 1; //Zuweisung für i (passiert n mal)
        // Zähle die folgende Zeile als genau ein Befehl!
        sum += get_value_one();
        *befehle += 1; //Die obere Zuweisung
    }
    *befehle += 1; //die letzte Vergleichung von i mit n
    *befehle += 1; //die Return Statement
    return sum;
}

long for_quadratisch(int n, int* befehle)
{
    // TODO: Die Befehle müssen richtig gezählt werden

    long sum = 0;   
    *befehle += 1; //Initialisierung von sum
    *befehle += 1; //Initialisierung von i                                                1
    for(int i = 1; i <= n; ++i) {
        *befehle += 1;//Vergleichung von i mit n (passiert n+1 mal)
        *befehle += 1;//Zuweisung für i (passiert n mal)   
        *befehle += 1;//Initialisierung von j (passiert n mal)                            1 + (n + 1) + n
        for(int j = 1; j <= n; ++j) {   
            *befehle += 1;//Vergleichung von j mit n (passiert n*(n+1) mal)  
            *befehle += 1;//Zuweisung fur j (passiert n^2 mal)                       n * (1 + (n + 1) + n)
            // Zähle die folgende Zeile als genau ein Befehl!       
            sum += get_value_one();                           
            *befehle += 1;//Die obere zuweisung      n^2
        }
        *befehle += 1;//letzte Vergleichung von j mit n
    }
    *befehle += 1; // Lezte Vergleichung von i mit n
    *befehle += 1; // Die Return Statement
    return sum;                                                       
}

long for_kubisch(int n, int* befehle)
{
    // TODO: Die Befehle müssen richtig gezählt werden

    long sum = 0;                       
    *befehle += 1; // Initialisierung von sum
    *befehle += 1; // Initialisierung von i
    for(int i = 1; i <= n; ++i) {
        *befehle += 1; // Vergleichung von i mit n (passiert n+1 mal)
        *befehle += 1; // zuweisung i (passiert n mal)
        *befehle += 1; // Initialisierung j (passiert n mal)
        for(int j = 1; j <= n; ++j) {
            *befehle += 1; //Vergleichung von j mit n (passiert n*(n+1) mal)
            *befehle += 1; // zuweisung j (passiert n^2 mal)
            *befehle += 1; // initialisierung von k 
            for(int k = 1; k <= n; ++k) {
                *befehle += 1; //vergleicung von k mit n (passiert n^2*(n+1) mal)
                *befehle += 1;// zuweisung von k (passiert n^3)
                // Zähle die folgende Zeile als genau ein
                // Befehl!
                sum += get_value_one();
                *befehle += 1; //die obere zuweisung (passiert n^3 mal)
            }
            *befehle += 1; // letzte vergleichung von k mit n
        }
        *befehle += 1; //letzte vergleichung von j mit n
    }
    *befehle += 1; //letzte Vergleichung von i mit n
    *befehle += 1; //return statement
    return sum;
}


int main(int argc, char *argv[])
{
    const int WERTE[] = {5,6,7,8,9,10};
    const int LEN_WERTE = 6;
    const int LEN_ALGORITHMEN = 3;

    long befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    long werte_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("Starte Algorithmus %d mit Wert %d\n",
                (i+1), n);
            int anzahl_befehle = 0;
            int wert = 0;

            // Starte den Timer
            start_timer();

            // Aufruf der entsprechenden Funktion
            if(i==0) {
                wert = for_linear(n, &anzahl_befehle);
            }
            else if(i==1) {
                wert = for_quadratisch(n, &anzahl_befehle);
            }
            else if(i==2) {
                wert = for_kubisch(n, &anzahl_befehle);
            }

            // Speichere Laufzeit, Rückgabewert und Anzahl
            // ausgeführter Befehle ab
            laufzeit_array[i][j] = end_timer();
            werte_array[i][j] = wert;
            befehle_array[i][j] = anzahl_befehle;
        }
        printf("\n");
    }

    // Ausgabe der Rückgabewerte, Anzahl ausgeführter Befehle
    // sowie der gemessenen Laufzeiten (in Millisekunden)
    printf("%3s \t%-28s \t%-28s \t%-28s\n", "","linear", "quadratisch", "kubisch");
    printf("%3s \t %5s %10s %10s\t %5s %10s %10s\t %5s %10s %10s\n", "n","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%3d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%5ld %10ld %10.4f \t ", werte_array[i][j], befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
