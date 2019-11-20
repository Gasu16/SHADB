/*******************************************************************************
 * File:        rwfile.c                                                       *
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
 * Last: 01 settembre 2019 - 01:07                                                 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rwfile.h"
#include "linked_list.h"

/********************    BEGIN OF ReadFile FUNCTION  **************************/

void ReadFile(char *path) {
    FILE *file = fopen(path, "r");          // Open the input file in read mode
    if (file == NULL) {
        //printf("\nFILE NON PRESENTE\n");
        NO_FILE;
    }
    
    char read;
    while ((read = fgetc(file)) != EOF) {   // Read until the end of the file (EOF)
        printf("%c", read);                 // Print contents of the file
    }
    fclose(file);
}

/********************    END OF ReadFile FUNCTION  ****************************/

/********************    BEGIN OF WriteOutFile FUNCTION  **********************/
void WriteOutFile(char *out_path){
    FILE *fout = fopen(out_path, "a");      // Open the output file in append mode
/*
    prova *p;
    p->d = 3;
    printf("p->d: %d\n", p->d);
*/
    fprintf(fout, "%s", "STO SCRIVENDO SU FILE...\n");
    fclose(fout);
}

/********************    END OF WriteOutFile FUNCTION  ************************/