/***************************************************************************
                          configuration.c  -  configuration file
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "configuration.h"

#include "audio.h"
#include "mixer.h"
#include "preprocess.h"

#include "cvoicecontrol.h"

/********************************************************************************
 * is the string empty? (i.e. does it only contain spaces, tabs and newline?)
 ********************************************************************************/

int isEmpty(char *s)
{
  if (strlen(s) == 0 || s[0] == '\n')
    return 1;
  
  while (*s != '\0')
  {
    if (*s != ' ' && *s != '\t' && *s != '\n')
      return 0;
    s++;
  }

  return 1;
}

/********************************************************************************
 * used to find out which parameter is in the current config line
 ********************************************************************************/

int isParameter(char *s, char *param)
{
  if (strncmp(s, param, strlen(param)) == 0)
    return 1;
  else
    return 0;
}

/********************************************************************************
 * find beginning of data part in a line loaded from the config file
 ********************************************************************************/

char *dataStart(char *s)
{
  while (*s != '=')
  {
    if (*s == '\0')
    {
      fprintf(stderr, "Invalid line in configuration file!\n");
      exit(-1);
    }
    s++;
  }
  s++;
  while (*s == ' ') s++;
  return s;
}

/********************************************************************************
 * load configuration
 ********************************************************************************/

int loadConfiguration()
{
  /***** load configuration */

  char *home = getenv("HOME");
  char *config_file;
  FILE *f;
  char *config_file_tail = "/.cvoicecontrol/config";

  if (home == NULL)
  {
    fprintf(stderr, "The environment variable HOME is not set!\n");
    return 0;
  }

  config_file = malloc(strlen(home) + strlen(config_file_tail) + 1);
  strcpy(config_file, home);
  strcat(config_file, config_file_tail);

  if ((f = fopen(config_file, "r")) == NULL)
  {
    fprintf(stderr, "Failed to read config file: %s\n", config_file);
    fprintf(stderr, "Please run 'cvoicecontrol_microphone_config' first!\n");
    return 0;
  }
  else
  {
    int mic_level = 0, igain_level = 0;
    int l = 500;
    char s[l];
    char tmp_dev_audio[80];
    char tmp_dev_mixer[80];

    /* set default values here! */

    score_threshold = 18;
    rec_level = stop_level = silence_level = 0;
    
    while ( fgets(s, l, f) != NULL )
    {
      if (s[0] == '#' || isEmpty(s))
	/* comment or empty line skipped */;
      else if (isParameter(s, "Mixer Device"))
	sscanf(dataStart(s), "%s\n", tmp_dev_mixer);
      else if (isParameter(s, "Audio Device"))
	sscanf(dataStart(s), "%s\n", tmp_dev_audio);
      else if (isParameter(s, "Mic Level"))
	sscanf(dataStart(s), "%d\n", &mic_level);
      else if (isParameter(s, "IGain Level"))
	sscanf(dataStart(s), "%d\n", &igain_level);
      else if (isParameter(s, "Record Level"))
	sscanf(dataStart(s), "%hd\n", &rec_level);
      else if (isParameter(s, "Stop Level"))
	sscanf(dataStart(s), "%hd\n", &stop_level);
      else if (isParameter(s, "Silence Level"))
	sscanf(dataStart(s), "%hd\n", &silence_level);
      else if (isParameter(s, "Score Threshold"))
	sscanf(dataStart(s), "%f\n", &score_threshold);
      else if (isParameter(s, "Channel Mean"))
	sscanf(dataStart(s), "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
	       channel_mean+ 0, channel_mean+ 1, channel_mean+ 2,
	       channel_mean+ 3, channel_mean+ 4, channel_mean+ 5,
	       channel_mean+ 6, channel_mean+ 7, channel_mean+ 8,
	       channel_mean+ 9, channel_mean+10, channel_mean+11,
	       channel_mean+12, channel_mean+13, channel_mean+14,
	       channel_mean+15);
      else
	fprintf(stderr, "Invalid line in configuration file (ignored): %s", s);
    }
    
    fclose(f);

    if (rec_level == 0)
    {
      fprintf(stderr, "Invalid 'Record Level' in configuration file!\n");
      exit(-1);
    }
    if (stop_level == 0)
    {
      fprintf(stderr, "Invalid 'Stop Level' in configuration file!\n");
      exit(-1);
    }
    if (silence_level == 0)
    {
      fprintf(stderr, "Invalid 'Silence Level' in configuration file!\n");
      exit(-1);
    }
    
    /***** init mixer device */

    setMixer(tmp_dev_mixer);
    if (initMixer() == MIXER_ERR)
    {
      fprintf(stderr, "Failed to initialize mixer device!!\n");
      return 0;
    }
    if (igain_level > 0)
      setIGainLevel(igain_level);
    setMicLevel(mic_level);

    /***** open and initialize audio device for recording */
    setAudio(tmp_dev_audio);
    if (initAudio() == AUDIO_ERR)
    {
      fprintf(stderr, "Failed to initialize audio device!!\n");
      return 0;
    }

    /*****
     * after a suspend/resume cycle on a
     * Dell Inspiron 3500 (+ OSS sound system)
     * sound recording doesn't work properly the FIRST time.
     *
     * => workaround: open the audio device, read one block of data
     *                and close the audio device
     *****/

    openAudio();
    getBlockMax();
    closeAudio();
  }

  return 1;
}
