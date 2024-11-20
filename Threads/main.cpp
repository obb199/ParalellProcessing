#include <thread>
#include "buffer.hpp"
#include "writer.hpp"

using namespace std;

Buffer buffer(100000);
mutex mtx;
unsigned int readed_data = 0;
bool finish = false;

void read_procedure(){
    ifstream file("dataset_00_sem_virg.csv");
    //ifstream file("dataset_00_1000_sem_virg.csv");
    string line_data;
    getline(file, line_data); //ignoring the first line (title)
    
    while (getline(file, line_data)){
        while(buffer.is_full()) continue;
        mtx.lock();
        buffer.push(line_data);
        readed_data++;
        mtx.unlock();
        
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
    std::thread reader_thread(read_procedure);
    Writer writer(&buffer, &mtx, &finish);
    std::thread monitor_thread(monitoring);
    writer.write_procedure();
    reader_thread.join();
    monitor_thread.join();
    return 0;
}


