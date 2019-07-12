/***************************************************************************
                          keypressed.h  -  handle asynchronous keyboard
                                                         input
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

#ifndef CVC_KEYPRESSED_H
#define CVC_KEYPRESSED_H

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int  initKeyPressed();
int  keyPressed();
void endKeyPressed();

#endif //CVC_KEYPRESSED_H//
