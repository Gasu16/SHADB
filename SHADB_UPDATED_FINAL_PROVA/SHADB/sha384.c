/*******************************************************************************
 * File:        sha384.c                                                       *
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

#include "sha384.h"

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

void sha384_set(SHA384 *sha384) {
    sha384->original_len = 0;
    sha384->current_len = 0;
    sha384->num_chunks = 0;
    
    sha384->h[0] = 0xcbbb9d5dc1059ed8;
    sha384->h[1] = 0x629a292a367cd507;
    sha384->h[2] = 0x9159015a3070dd17;
    sha384->h[3] = 0x152fecd8f70e5939;
    sha384->h[4] = 0x67332667ffc00b31;
    sha384->h[5] = 0x8eb44a8768581511;
    sha384->h[6] = 0xdb0c2e0d64f98fa7;
    sha384->h[7] = 0x47b5481dbefa4fa4;

}

/*
 * Reading input file specified by user
 */
unsigned char * SHA384_read_file(char *path){
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
        printf(" %s", testo);
    }
    strcpy(msg, testo);
    fclose(fp);
    free(fp);
    fp = NULL;
    return msg;
}

/*
 * Function used to pad the message to respect the standards of SHA-384 algorithm
 */

SHA384 *sha384_pad(SHA384 *sha384, unsigned char * mex) {
    /*          ******** PADDING [APPENDING 896 BITS '0'] ********
     * We append k bits '0' where k is 896 mod 1024, so 896 bits = 112 bytes
     * And then we are going to append 16 bytes (128 bits) more to the message
     * which represent the original length of the message
     */
    printf("current len: %ld\n", sha384->current_len);
    int bit_padding = sha384->current_len % 128; // 128 bytes = 1024 bits
    
    
    if (bit_padding < 112) { 
        bit_padding = 112 - bit_padding;
    } else {
        bit_padding = 240 - bit_padding; // [1920 bits mod 1024 bits = 896 bits] - [240 bytes mod 128 bytes = 112 bytes]
    }
    int i = 0;
    while (i < bit_padding) {
        mex[sha384->current_len] = 0x00;
        sha384->current_len++;
        i++;
    }
    

    mex[sha384->current_len + 1] = '\0';
    int j;

    /*** APPEND THE LENGTH OF MESSAGE IN 128-BITS FORMAT AT THE END OF THE MESSAGE  ***/
    for (j = 0; j < 6; j++) {

        mex[sha384->current_len] = 0x00; 
        sha384->current_len++;
    }
    

    mex[sha384->current_len] = (sha384->original_len * 8) / 0x100;
    sha384->current_len++;
    mex[sha384->current_len] = (sha384->original_len * 8) % 0x100;
    sha384->current_len++;

    mex[sha384->current_len + j] = '\0';
    sha384->num_chunks = sha384->current_len / 128;
    printf("num chunks: %d\n", sha384->num_chunks);
    printf("current len: %ld\n", sha384->current_len);
    return sha384;
}

/*
 * Function used for processing the message and calculate the digest
 * This is where the most important part happens, the real process of digest elaboration
 */

unsigned int sha384_exe(SHA384 *sha384, unsigned char * message) {
    unsigned char *mex = (unsigned char *) malloc(strlen((const char *) message) + 100);
    strcpy((unsigned char *) mex, (const char *) message);
    sha384->current_len = strlen((const char *) mex);
    sha384->original_len = sha384->current_len;
    
    // Append the bit '1' to the message

    mex[sha384->current_len] = 0x80;
    
    mex[sha384->current_len + 1] = '\0'; // NULL terminator
    sha384->current_len++;

    sha384_pad(sha384, mex);
    
    /*** MAIN OPERATION OF THE SHA-384 ALGORITHM (search for the pseudo-code) ***/
    int index;
    int j;
    printf("Numero di chunk: %d\n", sha384->num_chunks);
    for(j = 0; j < sha384->num_chunks; j++){
        
        for(index = 0; index < 16; index++){
            //  break chunk into sixteen 32-bit big-endian words w[index]
            sha384->w[index] = mex[j * 64 + index * 4 + 0] * 0x1000000 + mex[j * 64 + index * 4 + 1] * 0x10000 + mex[j * 64 + index * 4 + 2] * 0x100 + mex[j * 64 + index * 4 + 3];            
        }
        
        for(index = 16; index < 80; index++){
            /*
             s0 := (w[i-15] rightrotate 7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift 3)
             s1 := (w[i-2] rightrotate 17) xor (w[i-2] rightrotate 19) xor (w[i-2] rightshift 10)
             w[i] := w[i-16] + s0 + w[i-7] + s1
             */
            sha384->s0 = ((R_RIGHT(sha384->w[index - 15], 1)) ^ (R_RIGHT(sha384->w[index - 15], 8)) ^ (RIGHT_SHIFT(sha384->w[index - 15], 7)));
            sha384->s1 = ((R_RIGHT(sha384->w[index - 2], 14)) ^ (R_RIGHT(sha384->w[index - 2], 18)) ^ (RIGHT_SHIFT(sha384->w[index - 2], 41)));
            sha384->w[index] = sha384->w[index - 16] + sha384->s0 + sha384->w[index - 7] + sha384->s1;
        }
        
        sha384->a = sha384->h[0];
        sha384->b = sha384->h[1];
        sha384->c = sha384->h[2];
        sha384->d = sha384->h[3];
        sha384->e = sha384->h[4];
        sha384->f = sha384->h[5];
        sha384->g = sha384->h[6];
        sha384->hs = sha384->h[7];
        
        for(int i = 0; i < 80; i++){
            
            sha384->s0 = ((R_RIGHT(sha384->a, 28)) ^ (R_RIGHT(sha384->a, 34)) ^ (R_RIGHT(sha384->a, 39)));
            sha384->maj = ((sha384->a & sha384->b) ^ (sha384->a & sha384->c) ^ (sha384->b & sha384->c));
            sha384->t2 = sha384->s0 + sha384->maj;
            sha384->s1 = ((R_RIGHT(sha384->e, 14)) ^ (R_RIGHT(sha384->e, 18)) ^ (R_RIGHT(sha384->e, 41)));
            sha384->ch = ((sha384->e & sha384->f) ^ ((~sha384->e) & sha384->g));
            sha384->t1 = sha384->hs + sha384->s1 + sha384->ch + k[i] + sha384->w[i];
            
            sha384->hs = sha384->g;
            sha384->g = sha384->f;
            sha384->f = sha384->e;
            sha384->e = sha384->d + sha384->t1;
            sha384->d = sha384->c;
            sha384->c = sha384->b;
            sha384->b = sha384->a;
            sha384->a = sha384->t1 + sha384->t2;
        }
        
        sha384->h[0] += sha384->a;
        sha384->h[1] += sha384->b;
        sha384->h[2] += sha384->c;
        sha384->h[3] += sha384->d;
        sha384->h[4] += sha384->e;
        sha384->h[5] += sha384->f;
        sha384->h[6] += sha384->g;
        sha384->h[7] += sha384->hs;
        
        
    }
    printf("DIGEST: %lX %lX %lX %lX %lX %lX \n", sha384->h[0], sha384->h[1], sha384->h[2], sha384->h[3], sha384->h[4], sha384->h[5]);
    free(mex);
    mex = NULL;
    return *sha384->h;
}
