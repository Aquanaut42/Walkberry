
#pragma once  // simplest way
#include "ReadMusic.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Song {
    std::string title;
    std::string artist;
    std::string album;
    std::string path;
};

std::vector<Song> songs;
namespace fs = std::filesystem;

void scanFolder(const std::string& folder);
void printSongs();