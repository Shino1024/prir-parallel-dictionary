#ifndef PRIR_FILE_H
#define PRIR_FILE_H

#include <iostream>
#include <fstream>
#include <string>

class FileReader {
    std::string file_name;
    std::string buffer;

    public:
    FileReader(const std::string &file_name);
    void read_file();
    std::string get_buffer();
};

class FileWriter {
    std::string file_name;
    std::string buffer;

    public:
    FileWriter(const std::string &file_name);
    void write_file();
    void set_buffer(const std::string &buffer);
};

#endif // PRIR_FILE_H
