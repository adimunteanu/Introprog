#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // definiert den speziellen Wert NaN für floats
#include "introprog_input_stacks-rpn.h"

typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};

/* 
 * Füge Element am Anfang des Stacks ein
 *
 * astack - Ein Pointer auf den Stack.
 * value  - Zahl, die als neues Element auf den Stack gelegt
 *          werden soll.
 */
void stack_push(stack* astack, float value)
{
    /* HIER implementieren */
    stack_element *new_stack_element = (stack_element *) malloc(sizeof(stack_element));
    new_stack_element->value = value;
    new_stack_element->next = NULL;
    if(astack->top){
        new_stack_element->next = astack->top;
    }
    astack->top = new_stack_element;
}

/* 
 * Nehme das letzte eingefügte Element vom Anfang des Stacks
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * astack - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack* astack)
{
    /* HIER implementieren */
    if(!isnan(astack->top->value))
    {
        float return_value = astack->top->value; //store value of element on top of stack
        stack_element *to_free = astack->top; //store adress of element we need to free in to_free
        astack->top = astack->top->next; //delete first element of the stack
        free(to_free);
        return return_value; //return value on top of stack
    } else {
        return NAN;
    }
}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf
 * dem Stack aus.  Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann konvertiere die Zahl mithilfe von
 *     atof() zu einem float und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack,
 *     führe die Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * astack - Ein Pointer auf den Stack
 * token  - Eine Zeichenkette
 */
void process(stack* astack, char* token)
{
    /* HIER implementieren */
    if(is_number(token))
    {
        float value = atof(token);
        stack_push(astack, value);
    }

    if(is_add(token))
    {
        float first_number = stack_pop(astack);
        float second_number = stack_pop(astack);
        stack_push(astack, first_number + second_number);
    }

    if(is_sub(token))
    {
        float first_number = stack_pop(astack);
        float second_number = stack_pop(astack);
        stack_push(astack, second_number - first_number);
    }

    if(is_mult(token))
    {
        float first_number = stack_pop(astack);
        float second_number = stack_pop(astack);
        stack_push(astack, first_number * second_number);
    }
    printf("\n<Logik fehlt!>\n");
    return;
    /* Du kannst zur Erkennung der Token folgende Hilfsfunktionen
     * benutzen:
     *
     * Funktion          Rückgabewert von 1 bedeutet
     * ---------------------------------------------
     * is_add(token)     Token ist ein Pluszeichen
     * is_sub(token)     Token ist ein Minuszeichen
     * is_mult(token)    Token ist ein Multiplikationszeichen
     * is_number(token)  Token ist eine Zahl
     */
}

/* 
 * Debugausgabe des Stack
 * Diese Funktion kannst du zum debugging des Stack verwenden.
 *
 * astack - Ein Pointer auf den Stack
 */
void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
    printf(" | Nr. | Adresse           | Next              | Wert    |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element* elem=astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %7.3f |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
}

/* 
 * Erstelle einen Stack mit dynamischem Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack* stack_erstellen() {
    /* HIER implementieren */
    stack *new_astack = (stack *) malloc(sizeof(stack));
    new_astack->top = NULL;
    return new_astack;
}

int main(int argc, char** args)
{
    stack* astack = stack_erstellen();
    char zeile[MAX_STR];
    char* token;

    intro();
    while (taschenrechner_input(zeile) == 0) {
        // Erstes Token einlesen
        token = strtok(zeile, " ");

        while (token != NULL) {
            printf("Token: %s\n", token);
            // Stackoperationen durchführen
            process(astack, token);
            // Nächstes Token einlesen
            token = strtok(NULL, " ");
            print_stack(astack);
        }

        printf("\nExtrahiere Resultat\n");
        float result = stack_pop(astack);
        print_stack(astack);

        if (astack->top != NULL) {
            while (astack->top != NULL) {
                stack_pop(astack);   //Räume Stack auf
            }
            printf("\nDoes not Compute: Stack nicht leer!\n");
        } else if (result != result) {
            printf("\nDoes not Compute: Berechnung fehlgeschlagen!\n");
        } else {
            printf("\nDein Ergebnis:\t%7.3f\n\n", result);
        }
    }
    free(astack);
}
