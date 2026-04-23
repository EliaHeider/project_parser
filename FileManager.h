#ifndef PROJECT_PARSER_FILEMANAGER_H
#define PROJECT_PARSER_FILEMANAGER_H
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
class FileManager {
public:
    FileManager() {
        _path = std::filesystem::current_path();
    }
    explicit FileManager(const std::filesystem::path &path) {
        _path = path;
    }
    static void
    WriteFiles(const std::vector<std::filesystem::path> &paths, const std::filesystem::path &o_path = "o_file.txt") {
        std::ofstream o_fileStream(o_path);
        if (!o_fileStream.is_open()) {
            std::cerr << "Cannt open the output file:" << '\n';
        }
        for (const auto &file: paths) {
            std::ifstream f_inputFile(file);
            if (!f_inputFile.is_open()) {
                std::cerr << "Cannt open the file: " << file << '\n';
            }
            std::string line;
            while (std::getline(f_inputFile, line)) {
                o_fileStream << line << '\n';
            }
        }
    }
    [[nodiscard]] std::vector<std::filesystem::path>
    FileInDir() const {
        std::vector<std::filesystem::path> paths;
        for (const auto &entry: std::filesystem::recursive_directory_iterator(_path)) {
            if (!entry.is_directory()) paths.push_back(entry.path());
        }
        return paths;
    }
private:
    std::filesystem::path _path;
};
#endif //PROJECT_PARSER_FILEMANAGER_H
