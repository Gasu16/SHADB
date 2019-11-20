/*******************************************************************************
 * File:        linked_list.h                                                  *
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

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "sha1.h"
#include "sha224.h"
#include "sha256.h"
#include "sha384.h"
#include "sha512.h"
#include <limits.h>
#include <stdbool.h>

#define SET_SIZE 64

#define SHA1_SIZE 5
#define SHA384_SIZE 6
#define SHA224_SIZE 7
#define SHA256_SIZE 8
#define SHA512_SIZE 8

typedef struct Node {
    int data;
    unsigned int arrayDig[SET_SIZE]; // Array where we will save the digest calculated from SHA-1
    unsigned char *path;
    unsigned char *sha_name;
    struct Node *next; // Pointer to the next data
} node_t;


node_t *CreateNode(node_t *next);
node_t *Append(node_t *head);
bool Find(node_t *node);

void PrintList(node_t *head);
int Length(node_t *head);

#endif /* LINKED_LIST_H */