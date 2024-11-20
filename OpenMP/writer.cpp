#include "writer.hpp"

Writer::Writer(Buffer *buffer,  bool *end_flag){ //adapted
    this->buffer = buffer;
    this->end_flag = end_flag;
}

bool Writer::is_nominal_column(int column){
    for (int i = 0; i < 12; i++){
        if (this->nominal_columns[i] == column) return true;
    }
    return false;
}

void Writer::separe_rows(string str){
    unsigned int c = 0, i = 0;
    string sub_string = "";
    while (c < 25){
        while(str[i] != 44) sub_string += str[i++];
        if (is_nominal_column(c)){
            write_file(c, sub_string);
        }
        sub_string = "";
        i++;
        c++;
    }
}

void Writer::write_file(int c, string str){
    for(int i = 0; i < 12; i++){
        if (this->nominal_columns[i] == c){
            int res = this->nominal_encodings_maps.search_element_code(str, i);
            if (res == -1){
                this->files[12] << this->nominal_encodings_maps.map_length(i);
                this->nominal_encodings_maps.add_element(str, i);
            }else{
                this->files[12] << res;
            }

            if (i == 11) this->files[12] << "\n";
            else this->files[12] << ",";

            break;
        }
    }
}

void quicksort(int init, int end, int numbers[], string strings[]){ //Quicksort converted to work with the Population struct
    int i = init, j = end, x, aux_int;
    string aux_str;
    x = numbers[(i+j)/2];
    do{
        while (numbers[i] > x) i++;
        while (x > numbers[j]) j--;
        if(i <= j){
            aux_int = numbers[i];
            aux_str = strings[i];
            numbers[i++] = numbers[j];
            strings[i-1] = strings[j];
            numbers[j--] = aux_int;
            strings[j+1] = aux_str;    
        }
    }while (i <= j);

    if (init < j){
        quicksort(init, j, numbers, strings);
    }

    if (i < end){
        quicksort(i, end, numbers, strings);
    }
}


void Writer::write_codes_procedure(int idx){
    string strings[this->nominal_encodings_maps.maps_length[idx]];
    int numbers[this->nominal_encodings_maps.maps_length[idx]];

    int i = 0;

    for (auto& set: this->nominal_encodings_maps.maps[idx]){
        strings[i] = set.first;
        numbers[i] = set.second;
        i++;
    }

    quicksort(0, this->nominal_encodings_maps.maps_length[idx]-1, numbers, strings);

    for (int j = i-1; j >= 0; j--){
        this->files[idx] << strings[j] << ": " << numbers[j] << endl;
    }
}

void Writer::write_codes(){ //adapted
    #pragma omp parallel for
    for (int i = 0; i < 12; i++){
        write_codes_procedure(i);
    }
}

void Writer::open_files(){
    this->files[0].open("results/col01_info.txt");
    this->files[1].open("results/col02_info.txt");
    this->files[2].open("results/col04_info.txt");
    this->files[3].open("results/col06_info.txt");
    this->files[4].open("results/col07_info.txt");
    this->files[5].open("results/col08_info.txt");
    this->files[6].open("results/col09_info.txt");
    this->files[7].open("results/col17_info.txt");
    this->files[8].open("results/col18_info.txt");
    this->files[9].open("results/col19_info.txt");
    this->files[10].open("results/col21_info.txt");
    this->files[11].open("results/col24_info.txt");
    this->files[12].open("results/processed_dataset.txt");
}

void Writer::close_files(){ //adapted
    #pragma omp parallel for
    for (int i = 0; i < 13; i++){
        this->files[i].close();
    }
}

void Writer::write_procedure(){
    string str;
    open_files();
    while (!*this->end_flag || !this->buffer->is_empty()){
        if (!this->buffer->is_empty()){

            #pragma omp critical
            str = this->buffer->pop();

            separe_rows(str);
            this->processed_data++;
        }
    }
    
    write_codes();
    close_files();
}
