/*******************************************************************************
 * File:        conf.c                                                         *
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
 * Last: 01 settembre 2019 - 01:07                                             *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>

#include "conf.h"


void writeDigest(node_t *node, FILE *f){
    int i;
    int len = 0;

    if(strcmp(node->sha_name, "sha1")==0){
        len = SHA1_SIZE;
    }

    if(strcmp(node->sha_name, "sha224")==0){
        len = SHA224_SIZE;
    }

    if(strcmp(node->sha_name, "sha256")==0){
        len = SHA256_SIZE;
    }
    
    if(strcmp(node->sha_name, "sha384")==0){
        len = SHA384_SIZE;
    }
    
    if(strcmp(node->sha_name, "sha512")==0){
        len = SHA512_SIZE;
    }
    //printf("%d len\n", len);

    for(i = 0; i < len; i++){
       // printf(" digest %X ", node->arrayDig[i]);
        fprintf(f, "%X", node->arrayDig[i]);
    }
    fprintf(f, "\n");
}


void WriteListFile(node_t *node, char *out_path){
    FILE *f;
    f = fopen(out_path, "a");
    fprintf(f, "\n\n");
    if(f == NULL){
        NO_FILE;
        return;
    }
    node_t *currentNode = node;

    while(currentNode != NULL){

        currentNode->next = NULL;
        fseek(f, 0, SEEK_END);
        fprintf(f, "%s\n", currentNode->path); 
        fprintf(f, "%s\n", currentNode->sha_name);
        writeDigest(node, f);        // Scriviamo qui il digest sul file puntato da f come parametro
        
        currentNode = currentNode->next;
    }
    
    fclose(f);
    f = NULL;
}
