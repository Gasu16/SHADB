/*******************************************************************************
 * File:        conf.h                                                         *
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
#ifndef CONF_H
#define CONF_H

#define DEFAULT_INPUT_FILE "input.txt"
#define DEFAULT_OUTPUT_FILE "shadb.out" // Poi si cambierà in shadb.out
#define DEFAULT_SHA_OPTION "SHA1"
#define STDERR_ADD fprintf(stderr, "FILE GIÀ PRESENTE IN ARCHIVIO\n"); // Scriviamo su stderr se un file e' gia' presente nel repository
#define STDERR_FIND fprintf(stderr, "FILE NON ESISTE NEL REPOSITORY\n"); // Scriviamo su stderr se un file non viene trovato nel repository
#define PARAM_ERR fprintf(stderr, "PARAMETRI ERRATI\n");


#include "linked_list.h"
#include "rwfile.h"

void writeDigest(node_t *node, FILE *f);

void WriteListFile(node_t *node, char *out_path);



#endif /* CONF_H */