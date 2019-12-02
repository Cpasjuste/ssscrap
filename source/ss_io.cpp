//
// Created by cpasjuste on 16/09/2019.
//

#include <dirent.h>
#include <sys/stat.h>
#include "ss_io.h"

using namespace ss_api;

std::vector<std::string> Io::getDirList(const std::string &path, const std::string &ext) {

    std::vector<std::string> files;
    struct dirent *ent;
    DIR *dir;

    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            // skip "."
            if (ent->d_name[0] == '.' || ent->d_type != DT_REG) {
                continue;
            }
            std::string file = ent->d_name;
            if (!ext.empty()) {
                if (file.rfind('.') != std::string::npos
                    && file.substr(file.find_last_of('.') + 1) == ext) {
                    files.emplace_back(file);
                }
            } else {
                files.emplace_back(file);
            }
        }
        closedir(dir);
    }
    return files;
}

void Io::makedir(const std::string &path) {
    mkdir(path.c_str(), 0755);
}

bool Io::exist(const std::string &file) {
    struct stat st{};
    return (stat(file.c_str(), &st) == 0);
}
