#include <thread>
#include "buffer.hpp"
#include "writer.hpp"
#include "omp.h"

using namespace std;

Buffer buffer(100000);
unsigned int readed_data = 0;
bool finish = false;

void read_procedure(){
    ifstream file("dataset_00_sem_virg.csv");
    //ifstream file("dataset_00_1000_sem_virg.csv");
    string line_data;
    getline(file, line_data); //ignoring the first line (title)
    
    while (getline(file, line_data)){
        while(buffer.is_full()) continue;

        #pragma omp critical
        buffer.push(line_data);

        readed_data++;

    }
    finish = true;
}

void monitoring(){
    int i = 1;
    while(!finish){
        sleep(5);
        cout << "READED LINES: " << readed_data << " in " << i*5 << " seconds" << endl;
        cout << "======================================" << endl;
        i++;
    }
}

int main(){
    Writer writer(&buffer, &finish);

    thread monitor(monitoring);

    #pragma omp parallel
    {        
        #pragma omp single nowait
        read_procedure();

        #pragma omp single nowait
        writer.write_procedure();
    }

    monitor.join();

    return 0;
}


