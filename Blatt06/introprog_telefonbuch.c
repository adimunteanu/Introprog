#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

/*
 * Fügt einen Knoten mit der Telefonnummer phone und dem Namen name
 * in den Binären Suchbaum bst ein.  Für den Suchbaum soll die
 * Eigenschaft gelten, dass alle linken Kinder einen Wert kleiner
 * gleich (<=) und alle rechten Kinder einen Wert größer (>) haben.
 */
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
    if(find_node(bst, phone)){
        //if we try to add a phone number that already exists, give an error msg and exit function
        printf("Number already exists in our phonebook!\n");
        return;
    } else {
        //Declaration and initialization of new node 
        bst_node *new_node = (bst_node *) malloc(sizeof(bst_node));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        new_node->phone = phone;
        new_node->name = malloc(sizeof(char) * (strlen(name) + 1));
        strncpy(new_node->name, name, strlen(name) + 1);

        //Increasing amount of nodes in the tree
        bst->count++;

        //Initialization of the node we use to find the place to add our new element
        bst_node *search_node = bst->root;

        //Initialization of the father of our new node
        bst_node *new_node_father = NULL;

        //While the search node exists
        while(search_node)
        {
            new_node_father = search_node;
            if(new_node->phone < search_node->phone)
                //if then number to be added is smaller than the number of the current node, start looking to the left
                search_node = search_node->left;
            else 
                //if the number to be added is greater than the number of the current node, start looking to the right
                search_node = search_node->right;
        }

        //Set the parent of our new node (it can also be NULL)
        new_node->parent = new_node_father;
        
        if(new_node_father == NULL){
            //if we found no parent, then this new node becomes our root node
            bst->root = new_node;
        } else {
            if(new_node->phone < new_node_father->phone){
                //if the number is smaller than the father, add the child to the left
                new_node_father->left = new_node;
            } else {
                //if the number is greater than the father, add the child to the right
                new_node_father->right = new_node;
            }
        }
    }
}

/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
    //Initialize the node we search with
    bst_node *search_node = bst->root;
    //while our search node exists, we search for the right node
    while(search_node)
    {   
        //if we found it, we return it
        if(phone == search_node->phone)
            return search_node;
        if(phone < search_node->phone)
            //if it's to the left, go to the left
            search_node = search_node->left;
        else
            //if it's to the right, go to the right
            search_node = search_node->right;
    }
    //if it's not there at all, just return the NULL pointer
    return NULL;
}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {
    if(node){
        bst_in_order_walk_node(node->left);
        print_node(node);
        bst_in_order_walk_node(node->right);
    }
}

/* 
 * Gibt den gesamten Baum bst in "in-order" Reihenfolge aus.  Die
 * Ausgabe dieser Funktion muss aufsteigend soriert sein.
 */
void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

/*
 * Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
 * "post-order" Traversierung, d.h. zurerst wird der linke und dann
 * der rechte Teilbaum gelöscht.  Anschließend wird der übergebene
 * Knoten gelöscht.
 */
void bst_free_subtree(bst_node* node) {
    if(node)
    {
        bst_free_subtree(node->left);
        bst_free_subtree(node->right);
        free(node->name);
        free(node);
    }
}

/* 
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
