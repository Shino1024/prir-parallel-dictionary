#ifndef PRIR_FILE_H
#define PRIR_FILE_H

#include <iostream>
#include <fstream>
#include <string>

namespace file {
    class FileReader {
        std::string file_name;
        std::string buffer;

    public:
        FileReader(const std::string &file_name);
        bool read_file();
        std::string get_buffer();
    };

    class FileWriter {
        std::string file_name;
        std::string buffer;

    public:
        FileWriter(const std::string &file_name);
        bool write_file();
        void set_buffer(const std::string &buffer);
    };
}

#endif // PRIR_FILE_H
