#ifndef WRITER_HPP
#define WRITER_HPP

#include "buffer.hpp"
#include "maps.hpp"

#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <unordered_map>

class Writer{
    private:
        int nominal_columns[12] = {1, 2, 3, 5, 6, 7, 8, 17, 18, 19, 20, 23};
        Maps nominal_encodings_maps;
        ofstream files[13];
        unsigned int processed_data = 0;

    public:
        Buffer *buffer;
        mutex *mtx;
        bool *end_flag;
        Writer(Buffer *, std::mutex *, bool *);
        bool is_nominal_column(int);
        void separe_rows(string);
        void write_file(int, string);
        void write_codes();
        void open_files();
        void close_files();
        void write_codes_procedure(int);
        void write_procedure();
};

#endif