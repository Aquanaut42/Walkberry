
#include "MusicLibrary.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

Song readID3v1(const std::string& filepath);
