#include <iostream>
#include <cstring>

#include "PakFS/PakFS.hpp"

#define PAKFS_BASE          "base"
#define PAKFS_PAKS_ONLY     false

int main() {
    try {
        PakFS pakfs(PAKFS_BASE, PAKFS_PAKS_ONLY);

        pakfs.listFiles();

        std::vector<std::string> filenames{ "testfile", "testfile2", "folder/testfile3" , "folder2/testfile4", "folder2/subfolder1/testfile5" };

        for (const auto& filename : filenames) {
            int filesize = pakfs.getFileSize(filename);
            if(filesize >= 0)
            {
                std::cout << "File found: " << filename << " Size: " << filesize << std::endl << "----" << std::endl;
                uint8_t* ByteArray;
                ByteArray = new uint8_t[filesize + 1];
                pakfs.getFile(filename, ByteArray);
                ByteArray[filesize] = 0;
                std::cout << ByteArray << std::endl << "----"<< std::endl;
                delete [] ByteArray;
            }else{
                std::cout << "File not found: " << filename << std::endl << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
