/***************************************************************************
                          model_editor.h  -  tool to edit speaker models
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

#ifndef CVC_MODEL_EDITOR_H
#define CVC_MODEL_EDITOR_H

#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "configuration.h"
#include "model.h"
#include "mixer.h"
#include "audio.h"
#include "preprocess.h"
#include "ncurses_tools.h"

enum state {inactive, active};

#define MIN2(a,b) ((a<b)?(a):(b))

#define MIN_NR_SAMPLES_PER_ITEM 4

#endif //CVC_MODEL_EDITOR_H//
