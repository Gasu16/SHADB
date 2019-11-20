/*******************************************************************************
 * File:        shadb.c                                                        *
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
#include "shadb.h"


int Function(int argc, char **argv) {
    SHA1config s;
    SHA224 sha224;
    SHA256 sha256;
    SHA384 sha384;
    SHA512 sha512;
    node_t *node1 = NULL;
    char *s_name;
    char *path_input;
    char *file_output = DEFAULT_OUTPUT_FILE; // shadb.out
    if (argc != 5){
	fprintf(stderr, "\n\nNumero di argomenti errato, riprovare\n\n");
	return 1;
    }

    s_name = argv[3];
    path_input = argv[4];
    file_output = argv[1];
    char *real_input = realpath(path_input, NULL);
    //printf("real path: %s\n", real_input);

    
    int i;
    if(strcmp(s_name, "sha1")==0){
        funzioneSHA1(&s, real_input);
        node1 = CreateNode(node1);

        for (i = 0; i < SHA1_SIZE; i++) {
            node1->arrayDig[i] = s.h[i];
            //    printf("%X ", node1->arrayDig[i]);
        }
    }
    
    if(strcmp(s_name, "sha224")==0){
        funzioneSHA224(&sha224, real_input);
        node1 = CreateNode(node1);
        for (i = 0; i < SHA224_SIZE; i++) {
            node1->arrayDig[i] = sha224.h[i];
            //    printf("%X ", node->arrayDig[i]);
        }
    }
    
    if(strcmp(s_name, "sha256")==0){
        funzioneSHA256(&sha256, real_input);
        node1 = CreateNode(node1);
        for (i = 0; i < SHA256_SIZE; i++) {
            node1->arrayDig[i] = sha256.h[i];
            //    printf("%X\n ", node1->arrayDig[i]);
        }
    }
    
    if(strcmp(s_name, "sha384")==0){
        funzioneSHA384(&sha384, real_input);
        node1 = CreateNode(node1);
        for (i = 0; i < SHA384_SIZE; i++) {
            node1->arrayDig[i] = sha384.h[i];
            //    printf("%X ", node->arrayDig[i]);
        }
    }
    
    if(strcmp(s_name, "sha512")==0){
        funzioneSHA512(&sha512, real_input);
        node1 = CreateNode(node1);
        for (i = 0; i < SHA512_SIZE; i++) {
            node1->arrayDig[i] = sha512.h[i];
            //    printf("%X ", node->arrayDig[i]);
        }
    }
    
    node1->path = real_input;
    node1->sha_name = s_name;
    
    if (strcmp(argv[2], "add") == 0) {
        
        printf("/*******FUNZIONE ADD********/\n");
        if(Find(node1)==false){ // Se non lo trova lo aggiungiamo...
            
            node1 = Append(node1);
            WriteListFile(node1, file_output);
        }
        else{ // Se lo trova ritorniamo un messaggio su stderr
            
            return STDERR_ADD;
        }
        PrintList(node1);
    }

    if (strcmp(argv[2], "find") == 0) {
        if(Find(node1)==false){
           return STDERR_FIND;
        }
        else{
            printf("RISULTATO DELLA RICERCA: TROVATO\n");
        }
    }
    
    return 0;

}
