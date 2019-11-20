/*******************************************************************************
 * File:        sha512.c                                                       *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>

#include "sha512.h"

#define R_RIGHT(x,n) ((x>>n) | (x<<(64-n)))
#define RIGHT_SHIFT(x, n) (x>>n)


// TABLE OF CONSTANTS K
static const unsigned long k[80] = {
              0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 
              0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 
              0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 
              0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
              0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 
              0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 
              0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 
              0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
              0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 
              0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
              0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 
              0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
              0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 
              0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
              0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 
              0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

/*** VARIABLES DEFINITION ***/

void sha512_set(SHA512 *sha512) {
    sha512->original_len = 0;
    sha512->current_len = 0;
    sha512->num_chunks = 0;
    
    sha512->h[0] = 0x6a09e667f3bcc908;
    sha512->h[1] = 0xbb67ae8584caa73b;
    sha512->h[2] = 0x3c6ef372fe94f82b;
    sha512->h[3] = 0xa54ff53a5f1d36f1;
    sha512->h[4] = 0x510e527fade682d1;
    sha512->h[5] = 0x9b05688c2b3e6c1f;
    sha512->h[6] = 0x1f83d9abfb41bd6b;
    sha512->h[7] = 0x5be0cd19137e2179;

}

/*
 * Reading input file specified by user
 */
unsigned char * SHA512_read_file(char *path){
    FILE *fp;
    char testo[CHAR_MAX];
    unsigned char * msg = (char *)malloc(strlen(testo)+1);
    fp = fopen(path, "r");
    /* Cambia il path di fopen a seconda del file che vuoi leggere */
    if(fp == NULL){
        printf("File non trovato");
    }
    while(fscanf(fp, "%s", testo) != EOF){
        /* Quello che andiamo a leggere da file lo metto in "testo" 
         fin quando arrivo a EOF (end of file) */
        //printf(" %s", testo);
    }
    strcpy(msg, testo);
    fclose(fp);
    free(fp);
    fp = NULL;
    return msg;
}

/*
 * Function used to pad the message to respect the standards of SHA-512 algorithm
 */

SHA512 *sha512_pad(SHA512 *sha512, unsigned char * mex) {
    /*          ******** PADDING [APPENDING 896 BITS '0'] ********
     * We append k bits '0' where k is 896 mod 1024, so 896 bits = 112 bytes
     * And then we are going to append 16 bytes (128 bits) more to the message
     * which represent the original length of the message
     */
    //printf("current len: %ld\n", sha512->current_len);
    int bit_padding = sha512->current_len % 128; // 128 bytes = 1024 bits
    
    
    if (bit_padding < 112) { 
        bit_padding = 112 - bit_padding;
    } else {
        bit_padding = 240 - bit_padding; // [1920 bits mod 1024 bits = 896 bits] - [240 bytes mod 128 bytes = 112 bytes]
    }
    int i = 0;
    while (i < bit_padding) {
        mex[sha512->current_len] = 0x00;
        sha512->current_len++;
        i++;
    }
    

    mex[sha512->current_len + 1] = '\0';
    int j;

    /*** APPEND THE LENGTH OF MESSAGE IN 128-BITS FORMAT AT THE END OF THE MESSAGE  ***/
    for (j = 0; j < 6; j++) {

        mex[sha512->current_len] = 0x00; 
        sha512->current_len++;
    }
    

    mex[sha512->current_len] = (sha512->original_len * 8) / 0x100;
    sha512->current_len++;
    mex[sha512->current_len] = (sha512->original_len * 8) % 0x100;
    sha512->current_len++;

    mex[sha512->current_len + j] = '\0';
    sha512->num_chunks = sha512->current_len / 128;
   // printf("num chunks: %d\n", sha512->num_chunks);
   // printf("current len: %ld\n", sha512->current_len);
    return sha512;
}

/*
 * Function used for processing the message and calculate the digest
 * This is where the most important part happens, the real process of digest elaboration
 */

unsigned int sha512_exe(SHA512 *sha512, unsigned char * message) {
    unsigned char *mex = (unsigned char *) malloc(strlen((const char *) message) + 100);
    strcpy((unsigned char *) mex, (const char *) message);
    sha512->current_len = strlen((const char *) mex);
    sha512->original_len = sha512->current_len;
    
    // Append the bit '1' to the message

    mex[sha512->current_len] = 0x80;
    
    mex[sha512->current_len + 1] = '\0'; // NULL terminator
    sha512->current_len++;

    sha512_pad(sha512, mex);
    
    /*** MAIN OPERATION OF THE SHA-512 ALGORITHM (search for the pseudo-code) ***/
    int index;
    int j;

    for(j = 0; j < sha512->num_chunks; j++){
        
        for(index = 0; index < 16; index++){
            //  break chunk into sixteen 32-bit big-endian words w[index]
            sha512->w[index] = mex[j * 64 + index * 4 + 0] * 0x1000000 + mex[j * 64 + index * 4 + 1] * 0x10000 + mex[j * 64 + index * 4 + 2] * 0x100 + mex[j * 64 + index * 4 + 3];            
        }
        
        for(index = 16; index < 80; index++){
            /*
             s0 := (w[i-15] rightrotate 7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift 3)
             s1 := (w[i-2] rightrotate 17) xor (w[i-2] rightrotate 19) xor (w[i-2] rightshift 10)
             w[i] := w[i-16] + s0 + w[i-7] + s1
             */
            sha512->s0 = ((R_RIGHT(sha512->w[index - 15], 1)) ^ (R_RIGHT(sha512->w[index - 15], 8)) ^ (RIGHT_SHIFT(sha512->w[index - 15], 7)));
            sha512->s1 = ((R_RIGHT(sha512->w[index - 2], 14)) ^ (R_RIGHT(sha512->w[index - 2], 18)) ^ (RIGHT_SHIFT(sha512->w[index - 2], 41)));
            sha512->w[index] = sha512->w[index - 16] + sha512->s0 + sha512->w[index - 7] + sha512->s1;
        }
        
        sha512->a = sha512->h[0];
        sha512->b = sha512->h[1];
        sha512->c = sha512->h[2];
        sha512->d = sha512->h[3];
        sha512->e = sha512->h[4];
        sha512->f = sha512->h[5];
        sha512->g = sha512->h[6];
        sha512->hs = sha512->h[7];
        
        for(int i = 0; i < 80; i++){
            
            sha512->s0 = ((R_RIGHT(sha512->a, 28)) ^ (R_RIGHT(sha512->a, 34)) ^ (R_RIGHT(sha512->a, 39)));
            sha512->maj = ((sha512->a & sha512->b) ^ (sha512->a & sha512->c) ^ (sha512->b & sha512->c));
            sha512->t2 = sha512->s0 + sha512->maj;
            sha512->s1 = ((R_RIGHT(sha512->e, 14)) ^ (R_RIGHT(sha512->e, 18)) ^ (R_RIGHT(sha512->e, 41)));
            sha512->ch = ((sha512->e & sha512->f) ^ ((~sha512->e) & sha512->g));
            sha512->t1 = sha512->hs + sha512->s1 + sha512->ch + k[i] + sha512->w[i];
            
            sha512->hs = sha512->g;
            sha512->g = sha512->f;
            sha512->f = sha512->e;
            sha512->e = sha512->d + sha512->t1;
            sha512->d = sha512->c;
            sha512->c = sha512->b;
            sha512->b = sha512->a;
            sha512->a = sha512->t1 + sha512->t2;
        }
        
        sha512->h[0] += sha512->a;
        sha512->h[1] += sha512->b;
        sha512->h[2] += sha512->c;
        sha512->h[3] += sha512->d;
        sha512->h[4] += sha512->e;
        sha512->h[5] += sha512->f;
        sha512->h[6] += sha512->g;
        sha512->h[7] += sha512->hs;
        
        
    }
    printf("DIGEST: %lX %lX %lX %lX %lX %lX %lX %lX \n", sha512->h[0], sha512->h[1], sha512->h[2], sha512->h[3], sha512->h[4], sha512->h[5], sha512->h[6], sha512->h[7]);
    free(mex);
    mex = NULL;
    return *sha512->h;
}
