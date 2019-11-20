/*******************************************************************************
 * File:        sha512.h                                                       *
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

#ifndef SHA512_H
#define SHA512_H

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

} SHA512;

void sha512_set(SHA512 *sha512);
unsigned char * SHA512_read_file(char *path);
SHA512 *sha512_pad(SHA512 *sha512, unsigned char * mex);
unsigned int sha512_exe(SHA512 *sha512, unsigned char * message);
unsigned int funzioneSHA512(SHA512 *sha512, char *pathInp);

#endif /* SHA512_H */

