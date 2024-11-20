#ifndef BUFFER_H
#define BUFFER_H

#include <string.h>
#include <iostream>
#include <stdio.h>

class Buffer{ //works like a circular queue
    private:
        std::string *values;
        int buffer_length;
        int first_position;
        int last_position;
        int busy_positions;
    
    public:
        Buffer(int buffer_length); //constructor
        void push(std::string str); 
        std::string pop();
        void show_status();
        void show_buffer();
        bool is_full();
        bool is_empty();
        int busy_spaces();
        void set_new_length(int);
};

#endif
