#include "musiclibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Make sure there's room for one more song
static void ensure_capacity(MusicLibrary *lib) {
    if (lib->count >= lib->capacity) {
        size_t new_capacity = lib->capacity == 0 ? 10 : lib->capacity * 2;
        Song *new_songs = realloc(lib->songs, new_capacity * sizeof(Song));
        if (!new_songs) {
            perror("realloc");
            exit(1);
        }
        lib->songs = new_songs;
        lib->capacity = new_capacity;
    }
}

#include <libgen.h>  // for dirname, basename

static void add_song(MusicLibrary *lib, const char *fullpath, const char *filename) {
    ensure_capacity(lib);

    Song *song = &lib->songs[lib->count++];

    // store full path
    strncpy(song->path, fullpath, sizeof(song->path) - 1);
    song->path[sizeof(song->path) - 1] = '\0';

    // ----- Extract album and artist -----
    char path_copy[512];
    strncpy(path_copy, fullpath, sizeof(path_copy) - 1);
    path_copy[sizeof(path_copy) - 1] = '\0';

    char *file_dir = dirname(path_copy);       // /Music/Artist/Album
    char dir_copy[512];
    strncpy(dir_copy, file_dir, sizeof(dir_copy) - 1);
    dir_copy[sizeof(dir_copy) - 1] = '\0';

    char *album = basename(dir_copy);          // Album
    strncpy(song->album, album, sizeof(song->album) - 1);
    song->album[sizeof(song->album) - 1] = '\0';

    char *artist_dir = dirname(dir_copy);      // /Music/Artist
    char artist_copy[512];
    strncpy(artist_copy, artist_dir, sizeof(artist_copy) - 1);
    artist_copy[sizeof(artist_copy) - 1] = '\0';

    char *artist = basename(artist_copy);      // Artist
    strncpy(song->artist, artist, sizeof(song->artist) - 1);
    song->artist[sizeof(song->artist) - 1] = '\0';

    // ----- Extract title (filename minus extension & track number) -----
    char namebuf[256];
    strncpy(namebuf, filename, sizeof(namebuf) - 1);
    namebuf[sizeof(namebuf) - 1] = '\0';
    char *ext = strrchr(namebuf, '.');
    if (ext) *ext = '\0';

    char *title_start = namebuf;
    while (*title_start && isdigit((unsigned char)*title_start)) {
        title_start++;
    }
    while (*title_start == '-' || *title_start == '_' || *title_start == ' ') {
        title_start++;
    }

    strncpy(song->title, title_start, sizeof(song->title) - 1);
    song->title[sizeof(song->title) - 1] = '\0';
}



static void scan_folder_recursive(MusicLibrary *lib, const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode)) {
            scan_folder_recursive(lib, fullpath);
        } else {
            const char *ext = strrchr(entry->d_name, '.');
            if (ext && (strcasecmp(ext, ".mp3") == 0 || strcasecmp(ext, ".m4a") == 0)) {
                add_song(lib, fullpath, entry->d_name);
            }
        }
    }

    closedir(dir);
}

void init_library(MusicLibrary *lib) {
    lib->songs = NULL;
    lib->count = 0;
    lib->capacity = 0;
}

void free_library(MusicLibrary *lib) {
    free(lib->songs);
    lib->songs = NULL;
    lib->count = 0;
    lib->capacity = 0;
}

void scan_folder(MusicLibrary *lib, const char *path) {
    scan_folder_recursive(lib, path);
}

void print_songs(const MusicLibrary *lib) {
    for (size_t i = 0; i < lib->count; i++) {
        printf("%zu. %s\n", i + 1, lib->songs[i].title);
    }
}
