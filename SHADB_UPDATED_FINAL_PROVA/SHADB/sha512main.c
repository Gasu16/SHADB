/*******************************************************************************
 * File:        sha512main.c                                                   *
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

unsigned int funzioneSHA512(SHA512 *sha512, char *pathInp) {
    printf("\n\n************ SHA-512 *************\n");    
    sha512_set(sha512);
    char *p_inp = pathInp;
    char *real_p = realpath(p_inp, NULL);
    unsigned char * msg = (char *)malloc(sizeof(UCHAR_MAX));
    msg = SHA512_read_file(p_inp);

    unsigned int digest;
    digest = sha512_exe(sha512, msg);

    printf("\n\n");
    free(real_p);
    free(msg);
    real_p = NULL;
    msg = NULL;
    return digest;
}

