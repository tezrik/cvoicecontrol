/***************************************************************************
                          preprocess.h  -  Preprocessing of a wave file for
                                                         speech recognition
                             -------------------
    begin                : Sat Feb 12 2000
    copyright            : (C) 2000 by Daniel Kiecza
    email                : daniel@kiecza.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CVC_PREPROCESS_H
#define CVC_PREPROCESS_H

#include <math.h>

#include "realfftf.h"

/********************************************************************************
 * fft_size        Size of short-time window
 * fft_size_char   Size of short-time window (in number of char values)
 *
 * fft_size is size in number of 16-bit samples,
 * a 16-bit sample is a two-byte value, thus:
 * fft_size == 2 * fft_size_char
 *
 * as the power spectrum is symmetric, we have:
 *   power_spec_size = 0.5 * fft_size
 ********************************************************************************/

#define FFT_SIZE        256
#define POWER_SPEC_SIZE 128
#define FFT_SIZE_CHAR   512
#define HAMMING_SIZE    FFT_SIZE
#define VECSIZE         16
#define FEAT_VEC_SIZE   VECSIZE

/********************************************************************************
 * Offset = 10ms (160 16bit-values = 320 uchars)
 *
 * the distance that lies between two audio frames
 * generally, it is  offset < fft_size, and thus
 * subsequent frames do overlap!
 ********************************************************************************/

#define OFFSET          320

/*****
  used for reduction of short-time spectrum to mel scale coefficients
  *****/
int   filter_banks[17];

/*****
  contains the power spectrum
  *****/
float power_spec[POWER_SPEC_SIZE];

/********************************************************************************
 * Hamming window width = 16ms ! (256 Frames)
 * (hamming_size == fft_size)
 *
 * a window function that a frame of audio values is multiplied with.
 * This is done to smoothen the beginning and end of a frame,
 * i.e. to reduce discontinuities at the two ends and as a result
 * to reduce the number of artefacts in the power spectrum
 ********************************************************************************/

float hamming_window[HAMMING_SIZE];

/*****
  The characteristics of the recording channel
  This is substracted from each feature vector to reduce
  channel effects
  *****/
int   do_mean_sub;
float channel_mean[FEAT_VEC_SIZE];


int  initPreprocess();
int  preprocessFrame(float *frame, float *result);
void endPreprocess();

#endif //CVC_PREPROCESS_H//
