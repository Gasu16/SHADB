/*******************************************************************************
 * File:        linked_list.c                                                  *
 *                                                                             *
 *                                                                             *
 * To change this license header, choose License Headers in Project Properties.*
 * To change this template file, choose Tools | Templates                      *
 * and open the template in the editor.                                        *
 *                                                                             *
 *                                                                             *
 * Author: Grammatico - Sammarco - Virgili                                     *
 *                                                                             *
 * Created on 3 agosto 2019, 17.13                                             *
 * Last: 01 settembre 2019 - 01:07                                                  *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "linked_list.h"
#include "conf.h"
#include <math.h>

// We check if the list is empty
bool isEmpty(node_t *head);

bool isEmpty(node_t *head) {
    return head;
}

/********************    BEGIN OF PrintList FUNCTION **************************/
// Print the nodes of the list  

void PrintList(node_t *head) {
    //printf("********PRINT LIST********\n\n");
    node_t *current = head;
    int i;

    int size = 0;
    if(strcmp(current->sha_name, "sha1")==0){
        size = SHA1_SIZE;
    }
    if(strcmp(current->sha_name, "sha224")==0){
        size = SHA224_SIZE;
    }
    if(strcmp(current->sha_name, "sha256")==0){
        size = SHA256_SIZE;
    }
    if(strcmp(current->sha_name, "sha384")==0){
        size = SHA384_SIZE;
    }
    if(strcmp(current->sha_name, "sha512")==0){
        size = SHA512_SIZE;
    }

    
    while (current != NULL) {
        printf("\nPATH: %s\n", current->path);
        printf("\nSHA NAME: %s\n", current->sha_name);
        printf("\nDIGEST: ");
        for (i = 0; i < size; i++) {
            printf("%X ", current->arrayDig[i]);
        }

        current = current->next; // Go to the next node in the list
    }
    printf("\n\n");
    free(current);
    current = NULL;
    return;
}

/********************    END OF PrintList FUNCTION  ***************************/

/********************    BEGIN OF CreateNode FUNCTION  ************************/
// Create a new node



node_t *CreateNode(node_t *next) {
    node_t *node = (node_t*) malloc(sizeof (node_t));
    if (node == NULL) {
        printf("IMPOSSIBILE CREARE UN NUOVO NODO\n");
        return NULL;
    }

    node->next = next;
    return node;
}


/********************    END OF CreateNode FUNCTION  **************************/


/********************    BEGIN OF Append FUNCTION  ****************************/
// Add a new node at the end of the list

node_t *Append(node_t *head) {
    if (head == NULL) {
        printf("head e' null\n");
    }
    node_t *cursor = head;
    
    while (cursor->next != NULL) {
        cursor = cursor->next;
    }
    // After this while we arrived at the end of the list
    //printf("*****FUNZIONE APPEND INIZIO******\n\n");
    node_t *node = CreateNode(cursor);
    //printf("*****FUNZIONE APPEND FINE*******\n");
    cursor->next = node;
    return head;
}

/********************    END OF Append FUNCTION  ******************************/


/********************    BEGIN OF Find FUNCTION  ******************************/
// To search and find a node with a specific data

bool Find(node_t *node) {
    FILE *f = fopen("shadb.out", "a+");
    if (f == NULL) {
        printf("File output non trovato\n");
    }

    char line[64];
    char *newPath = node->path;

    while (fgets(line, sizeof (line), f) != NULL) {
        // read line by line
        if(strncmp(newPath, line, strlen(newPath))==0){
            //printf("File gia' presente\n");
            return true;
        }
    }
    fclose(f);
    f = NULL;
    return false;
}

/********************    END OF Find FUNCTION  ********************************/


/********************    BEGIN OF Length FUNCTION  ************************/
// Return the size of list

int Length(node_t *head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    printf("SIZE: %d\n", len);
    return len;
}

/********************    END OF Length FUNCTION  ************************/