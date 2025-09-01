#ifndef SONG_H
#define SONG_H

#define FIELD_SIZE 128

typedef struct {
    char title[FIELD_SIZE];   // song title (from filename)
    char artist[FIELD_SIZE];  // artist folder name
    char album[FIELD_SIZE];   // album folder name
    char path[512];           // full path to file
} Song;

#endif
