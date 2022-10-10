#include "requestqueue.h"
#include <iostream>

using std::cout,std::endl;


class webserver{
    bool occupied;
    int start_time;
    char name;
    Request current;

    public:

    webserver(char kname){
        occupied = false;
        start_time = 0;
        name = kname;
        current = Request();
    }

    bool status(int curr_time){
        if(current.time == 0){
            occupied = false;
        }
        else if(current.time + start_time == curr_time){
            end_job(curr_time);
        }

        return occupied;
    }

    void set_job(int beg_time, Request incoming){
        start_time = beg_time;
        current = incoming;
        occupied = true;
    }

    void end_job(int curr_time){
        cout<<"At " << curr_time << " Server "<<string(1,name) << " processed request from "<< current.ip_in << " to " << current.ip_out << endl;
        start_time = 0;
        occupied = false;
        current = Request();
    }

    char get_name(){
        return name;
    }
};