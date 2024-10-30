#include "PakFile.hpp"

PakFile::PakFile(const std::string& filename) {
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open PAK file");
    }
    readHeader();
    readDirectory();
}

PakFile::~PakFile() {
    if (file.is_open()) {
        file.close();
    }
}

std::vector<std::string> PakFile::getFileNames() {
    std::vector<std::string> names;
    for (const auto& entry : entries) {
        names.push_back(entry.name);
    }
    return names;
}

int PakFile::getFileSize(const std::string& filename) {
    for (const auto& entry : entries) {
        if (filename == entry.name) {
            return entry.length;
        }
    }
    return -1;
}

void PakFile::getFile(const std::string& filename, uint8_t* buffer) {
    for (const auto& entry : entries) {
        if (filename == entry.name) {
            file.seekg(entry.offset, std::ios::beg);
            file.read(reinterpret_cast<char*>(buffer), entry.length);
            return;
        }
    }
}

void PakFile::readHeader() {
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (std::string(header.id, 4) != "PACK") {
        throw std::runtime_error("Invalid PAK file");
    }
}

void PakFile::readDirectory() {
    file.seekg(header.dirOffset, std::ios::beg);
    int numEntries = header.dirLength / sizeof(PakEntry);
    entries.resize(numEntries);
    file.read(reinterpret_cast<char*>(entries.data()), header.dirLength);
}