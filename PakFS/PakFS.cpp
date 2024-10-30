#include "PakFS.hpp"
#include <iomanip>
#include <filesystem>

PakFS::PakFS(const std::string& baseDir, bool paksOnly) {
    base = baseDir;

    for(int i = 0; i < MAX_PAKS; i++) {
        std::string path = baseDir + "/pak" + std::to_string(i) + ".pak";

        if(!std::ifstream  (path)) {
            pakFiles[i] = NULL;
            continue;
        }

        pakFiles[i] = new PakFile(path);

        for (const auto& file : pakFiles[i]->getFileNames()) {
            files[file] = i;
        }
    }

    if (!paksOnly) {
        ParseDirectory("");
    }
}

PakFS::PakFS(const std::string& baseDir) : PakFS(baseDir, true) {}

PakFS::~PakFS() {
    for (int i = 0; i < MAX_PAKS; i++) {
        if (pakFiles[i]) {
            delete pakFiles[i];
        }
    }
}

int PakFS::getFileSize(const std::string& t_filename) {
    if(files[t_filename] == -1) {
        std::ifstream file(base + "/" + t_filename, std::ios::binary | std::ios::ate);
        return file.tellg();
    }else{
        return pakFiles[files[t_filename]]->getFileSize(t_filename);
    }
}

void PakFS::getFile(const std::string& t_filename, uint8_t* buffer) {
    if(files[t_filename] == -1) {
    std::string filename = base + "/" + t_filename;
        std::ifstream file(filename, std::ios::binary);
        file.read(reinterpret_cast<char*>(buffer), getFileSize(t_filename));
        return;
    }else{
        pakFiles[files[t_filename]]->getFile(t_filename, buffer);
    }
}

std::string PakFS::getFileString(const std::string& t_filename) {
    int size = getFileSize(t_filename);
    uint8_t* ByteArray;
    ByteArray = new uint8_t[size + 1];
    getFile(t_filename, ByteArray);
    ByteArray[size] = 0;
    std::string str(reinterpret_cast<char*>(ByteArray));
    delete [] ByteArray;
    return str;
}

void PakFS::listFiles() {
    std::cout << "--------------" << std::endl << "PAK | Filename" <<  std::endl << "--------------" << std::endl;
    for (const auto& file : files) {
        std::cout << std::setw(3) << std::setfill(' ') << file.second << " | " << file.first << std::endl;
    }
    std::cout << std::endl;
}

void PakFS::ParseDirectory(const std::string& t_path) {
    std::string path = t_path;

    if(!path.empty()) {
        path += "/";
    }

    for (const auto& entry : std::filesystem::directory_iterator(base + "/" + t_path)) {
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".pak") {
                continue;
            }
            files[path + entry.path().filename().string()] = -1;
        }else if(entry.is_directory()){
            ParseDirectory(entry.path().string().substr(base.size() + 1));
        }
    }
}