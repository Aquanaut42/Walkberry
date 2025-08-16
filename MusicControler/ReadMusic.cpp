
#include "ReadMusic.hpp"
#include "MusicLibrary.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// Read MP3 ID3v1 tags (last 128 bytes)
Song readID3v1(const std::string& filepath) {
    Song song;
    song.path = filepath;
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return song;

    file.seekg(-128, std::ios::end);
    char tag[128];
    file.read(tag, 128);

    if (tag[0] == 'T' && tag[1] == 'A' && tag[2] == 'G') {
        song.title  = std::string(tag + 3, 30);
        song.artist = std::string(tag + 33, 30);
        song.album  = std::string(tag + 63, 30);
    } else {
        song.title  = fs::path(filepath).filename().string();
        song.artist = "Unknown Artist";
        song.album  = "Unknown Album";
    }
    // Trim trailing nulls/spaces
    song.title.erase(song.title.find_last_not_of(" \0") + 1);
    song.artist.erase(song.artist.find_last_not_of(" \0") + 1);
    song.album.erase(song.album.find_last_not_of(" \0") + 1);

    return song;
}
