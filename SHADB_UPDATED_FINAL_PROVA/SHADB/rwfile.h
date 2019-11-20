/*******************************************************************************
 * File:        rwfile.h                                                       *
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
 * Last: 01 settembre 2019 - 01:07                                                *
 ******************************************************************************/

#ifndef RWFILE_H
#define RWFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "conf.h"

#define NO_FILE fprintf(stderr, "FILE NON PRESENTE\n");

void ReadFile(char *path);
void WriteOutFile(char *out_path);


#endif /* RWFILE_H */