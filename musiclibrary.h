#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include "song.h"
#include <stddef.h>

typedef struct {
    Song *songs;
    size_t count;
    size_t capacity;
} MusicLibrary;

void init_library(MusicLibrary *lib);
void free_library(MusicLibrary *lib);
void scan_folder(MusicLibrary *lib, const char *path);
void print_songs(const MusicLibrary *lib);

#endif
