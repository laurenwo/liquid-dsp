/*
 * Copyright (c) 2007, 2008, 2009, 2010, 2011 Joseph Gaeddert
 * Copyright (c) 2007, 2008, 2009, 2010, 2011 Virginia Polytechnic
 *                                      Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// interleaver.c
//
// basic interleaver methods:
//  interleaver_print()
//  interleaver_debug_print()
//  interleaver_encode()
//  interleaver_decode()
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h> // debug_print

#include "liquid.internal.h"

// print interleaver internals
void interleaver_print(interleaver _q)
{
    printf("interleaver [%u] :\n", _q->n);
}

// print interleaver internals with debugging info
void interleaver_debug_print(interleaver _q)
{
    interleaver_print(_q);
    return;
    unsigned int n = (_q->n)*sizeof(unsigned char)*8;
    if (n>80) {
        printf("interleaver_debug_print(), too large to print debug info\n");
        return;
    }

    unsigned int t[n];
    interleaver_compute_bit_permutation(_q, t);

    unsigned int i,j,k;

    // compute permutation metrics: distance between bits
    float dtmp, dki, dmin=(float)n, dmean=0.0f;
    j = 0;
    for (k=1; k<3; k++) {
        //printf("==== k : %d\n", k);
        for (i=0; i<(n-k); i++) {
            dki = fabsf((float)(t[i]) - (float)(t[i+k]));
            dtmp = dki + (float)(k-1);
            //printf("    d(%u,%u) : %f\n", i, i+k, dki);

            dmean += dki;
            dmin = (dtmp < dmin) ? dki : dmin;
            j++;
        }
    }
    dmean /= j;

    printf("   ");
    j=0;
    for (i=0; i<n; i++) {
        if ((i%10)==0)  printf("%1u", j++);
        else            printf(" ");
    }
    printf("\n");

    for (i=0; i<n; i++) {
        printf("%2u ", i);
        for (j=0; j<n; j++) {
            if (j==t[i])
                printf("*");
            else if ((j%10)==0 && ((i%10)==0))
                printf("+");
            else if ((j%10)==0)
                printf("|");
            else if ((i%10)==0)
                printf("-");
            else if (j==i)
                printf("\\");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    printf("  dmin: %8.2f, dmean: %8.2f\n", dmin, dmean);
}

// execute forward interleaver (encoder)
//  _q          :   interleaver object
//  _msg_dec    :   decoded (un-interleaved) message
//  _msg_enc    :   encoded (interleaved) message
void interleaver_encode(interleaver _q,
                        unsigned char * _msg_dec,
                        unsigned char * _msg_enc)
{
    memcpy(_msg_enc, _msg_dec, _q->n);
}

// execute reverse interleaver (decoder)
//  _q          :   interleaver object
//  _msg_enc    :   encoded (interleaved) message
//  _msg_dec    :   decoded (un-interleaved) message
void interleaver_decode(interleaver _q,
                        unsigned char * _msg_enc,
                        unsigned char * _msg_dec)
{
    memcpy(_msg_dec, _msg_enc, _q->n);
}

