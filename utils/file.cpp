#include <streambuf>
#include <filesystem>
#include <fstream>

#include "file.h"

namespace file {
    FileReader::FileReader(const std::string &file_name) : file_name{file_name} {
        //
    }

    bool FileReader::read_file() {
        if (this->file_name == "") {
            return false;
        }

        if (!std::filesystem::exists(this->file_name)) {
            return false;
        }

        std::ifstream file{this->file_name};
        file.seekg(0, std::ios::end);
        this->buffer.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        this->buffer.assign(std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{});

        return true;
    }

    std::string FileReader::get_buffer() {
        return this->buffer;
    }

    FileWriter::FileWriter(const std::string &file_name) : file_name{file_name} {
        //
    }

    bool FileWriter::write_file() {
        if (this->file_name == "") {
            return false;
        }

        std::ofstream file{this->file_name};
        file.write(this->buffer.data(), this->buffer.size());

        return true;
    }

    void FileWriter::set_buffer(const std::string &buffer) {
        this->buffer = buffer;
    }
}
