/*******************************************************************************
 * File:        sha384.h                                                       *
 *                                                                             *
 *                                                                             *
 * To change this license header, choose License Headers in Project Properties.*
 * To change this template file, choose Tools | Templates                      *
 * and open the template in the editor.                                        *
 *                                                                             *
 *                                                                             *
 * Author: Grammatico - Sammarco - Virgili                                     *
 *                                                                             *
 *                                                                             *
 ******************************************************************************/

#ifndef SHA384_H
#define SHA384_H

#include <stdio.h>
#include <stddef.h>

typedef struct {

    unsigned long w[80];
    unsigned long h[8];                                 // Variables from h0 to h7
    unsigned long a, b, c, d, e, f, g, hs;              // Variables where we will store the hash values
    unsigned long s0, s1, ch, maj, t1, t2;              // Variable used for the digest calculation
    long current_len;                                   // Current length of the message
    long original_len;                                  // Original length of the message
    int num_chunks;                                     // Number of chunks in the message

} SHA384;

void sha384_set(SHA384 *sha384);
unsigned char * SHA384_read_file(char *path);
SHA384 *sha384_pad(SHA384 *sha384, unsigned char * mex);
unsigned int sha384_exe(SHA384 *sha384, unsigned char * message);
unsigned int funzioneSHA384(SHA384 *sha384, char *pathInp);

#endif /* SHA384_H */

