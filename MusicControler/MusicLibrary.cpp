
#include "MusicLibrary.hpp"
#include "ReadMusic.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class MusicLibrary {
public:
    
    void scanFolder(const std::string& folder) {
        for (auto& p : fs::recursive_directory_iterator(folder)) {
            if (p.is_regular_file()) {
                auto ext = p.path().extension().string();
                if (ext == ".mp3") {
                    songs.push_back(readID3v1(p.path().string()));
                }
                else if (ext == ".m4a") {
                    Song s;
                    s.path = p.path().string();
                    s.title = p.path().filename().string();
                    s.artist = "Unknown Artist";
                    s.album = "Unknown Album";
                    songs.push_back(s);
                }
            }
        }
    }

    void printSongs() {
        for (const auto& s : songs) {
            std::cout << s.artist << " - " << s.title << " [" << s.album << "]\n";
        }
    }
};
