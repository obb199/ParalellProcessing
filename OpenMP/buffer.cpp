#include "buffer.hpp"

Buffer::Buffer(int buffer_length){
    this->buffer_length = buffer_length;
    this->first_position = 0;
    this->last_position = 0;
    this->values = new std::string[buffer_length];
    this->busy_positions = 0;
}

void Buffer::push(std::string str){
    if (this->busy_positions != this->buffer_length){
        this->values[this->last_position] = str;
        this->last_position = ++this->last_position % this->buffer_length;
        this->busy_positions++;
    }
} 

std::string Buffer::pop(){
    if (busy_positions != 0){
        int pos = first_position;
        this->first_position = (this->first_position+1) % this->buffer_length;
        this->busy_positions--;
        return this->values[pos];
    }
    return "";
}

void Buffer::show_status(){
    std::cout << "LENGTH: " << this->buffer_length << std::endl;
    std::cout << "FIRST POSITION: " << this->first_position << std::endl;
    std::cout << "LAST POSITION: " << this->last_position << std::endl;
    std::cout << "BUSY POSITIONS: " << this->busy_positions << std::endl;
}

void Buffer::show_buffer(){
    if (this->busy_positions > 0){
        int i = this->first_position;
        do{
            std::cout << i << ":";
            std::cout << this->values[i] << " ";

            i = ++i % this->buffer_length;
        }while (i != this->last_position);
        }
    std::cout << std::endl;
}

bool Buffer::is_full(){
    return this->busy_positions == this->buffer_length;
}

bool Buffer::is_empty(){
    return this->busy_positions == 0;
}

int Buffer::busy_spaces(){
    return this->busy_positions;
}

void Buffer::set_new_length(int length){
    this->buffer_length = length;
}