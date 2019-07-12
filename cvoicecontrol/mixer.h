/***************************************************************************
                          mixer.h  -  handle mixer device
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

#ifndef CVC_MIXER_H
#define CVC_MIXER_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <glob.h>

typedef struct
{
    int    count;  /***** number of available devices */
    char **name;   /***** list of device names */
} MixerDevices;

void noMixer();
void setMixer(char *dev);
int  mixerOK();
const char *getMixer();
int  initMixer(int automix);
MixerDevices *scanMixerDevices(int automix);

int setIGainLevel(int level);
int setMicLevel(int level);

#define MIXER_ERR -1
#define MIXER_OK  1

int mic_level;
int igain_level;

#endif //CVC_MIXER_H//
