#ifndef PAKFILE_HPP
#define PAKFILE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

class PakFile {
public:
    PakFile(const std::string& filename);
    ~PakFile();

    std::vector<std::string> getFileNames();

    int getFileSize(const std::string& filename);
    void getFile(const std::string& filename, uint8_t* buffer);

private:
    struct PakHeader {
        char id[4];
        uint32_t dirOffset;
        uint32_t dirLength;
    };

    struct PakEntry {
        char name[56];
        uint32_t offset;
        uint32_t length;
    };

    std::ifstream file;
    PakHeader header;
    std::vector<PakEntry> entries;

    void readHeader();
    void readDirectory();
};

#endif // PAKFILE_HPP