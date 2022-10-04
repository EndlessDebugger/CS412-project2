#include "requestqueue.h"


class webserver{
    bool occupied;
    int start_time;
    Request current;

    public:

    webserver(){
        occupied = false;
        start_time = 0;
    }

    bool status(int curr_time){

        if(curr_time - start_time >= current.time){
            occupied = false;
        }

        return occupied;
    }

    bool set_job(int beg_time, Request incoming){
        start_time = beg_time;
        current = incoming;
        occupied = true;
    }

    Request get_job(){
        start_time = 0;
        return current;
    }
};