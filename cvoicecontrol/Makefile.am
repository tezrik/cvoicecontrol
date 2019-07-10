####### kdevelop will overwrite this part!!! (begin)##########

bin_PROGRAMS =  cvoicecontrol cvoicecontrol_microphone_config cvoicecontrol_model_editor

cvoicecontrol_SOURCES = audio.c bb_queue.c configuration.c keypressed.c mixer.c model.c preprocess.c realfftf.c score.c semaphore.c cvoicecontrol.c
cvoicecontrol_LDADD   = -lm ${LIBPTHREAD}

cvoicecontrol_microphone_config_SOURCES = audio.c keypressed.c mixer.c ncurses_tools.c preprocess.c realfftf.c microphone_config.c
cvoicecontrol_microphone_config_LDADD   = -lm ${LIBNCURSES}

cvoicecontrol_model_editor_SOURCES = audio.c configuration.c keypressed.c mixer.c model.c ncurses_tools.c preprocess.c realfftf.c model_editor.c
cvoicecontrol_model_editor_LDADD   = -lm ${LIBNCURSES}

SUBDIRS = docs

EXTRA_DIST = audio.c audio.h bb_queue.c bb_queue.h configuration.c configuration.h keypressed.c keypressed.h microphone_config.c microphone_config.h mixer.c mixer.h model.c model.h model_editor.c model_editor.h ncurses_tools.c ncurses_tools.h preprocess.c preprocess.h queue.h realfftf.c realfftf.h score.c score.h semaphore.c semaphore.h cvoicecontrol.c cvoicecontrol.h

####### kdevelop will overwrite this part!!! (end)############
