#include <iostream>
#include <cstring>

#include "PakFS/PakFS.hpp"

#define PAKFS_BASE          "base"

int main() {
    try {
        PakFS pakfs(PAKFS_BASE);

        std::string filename = "testfile";

        int filesize = pakfs.getFileSize(filename);

        if(filesize >= 0)
        {
            std::cout << "Size: " << filesize << std::endl << "----" << std::endl;
            std::cout << pakfs.getFileString(filename);
        }else{
            std::cout << "File not found: " << filename << std::endl << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
