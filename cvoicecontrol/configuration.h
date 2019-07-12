/***************************************************************************
                          configuration.h  -  configuration file
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

#ifndef CVC_CONFIGURATION_H
#define CVC_CONFIGURATION_H

#define CVC_CONFIG_PATH "/.config/"
#define CVC_CONFIG_FILE "cvoicecontrol.conf"
#define CVC_CONFIG_PATHFILE "/.config/cvoicecontrol.conf"
#define CVC_CONFIG_HOMEPATH "~/.config/"
#define CVC_CONFIG_HOMEPATHFILE "~/.config/cvoicecontrol.conf"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio.h"
#include "mixer.h"
#include "preprocess.h"
#include "cvoicecontrol.h"

int loadConfiguration();
int saveConfiguration(int autohome);

#endif //CVC_CONFIGURATION_H//
