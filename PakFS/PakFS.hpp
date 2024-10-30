#ifndef PAKFS_HPP
#define PAKFS_HPP

#include "PakFile.hpp"
#include <map>

#define MAX_PAKS 10

class PakFS {
public:
    PakFS(const std::string& baseDir, bool paksOnly);
    PakFS(const std::string& baseDir);
    ~PakFS();

    int getFileSize(const std::string& filename);
    void getFile(const std::string& filename, uint8_t* buffer);
    std::string getFileString(const std::string& filename);
    void listFiles();

private:
    std::map<std::string, int> files;
    PakFile* pakFiles[MAX_PAKS];
    std::string base {""};

    void ParseDirectory(const std::string& path);

};

#endif // PAKFS_HPP