#include "webserver.h"
#include <vector>


using std::vector;

class loadbalancer{

    int clock_len, num_servers;
    RequestQueue workload;
    vector<webserver> servers;
    int rand_len = 2000;

    public:
    loadbalancer(int clock_len, int num_servers);

    void main_loop();
};

loadbalancer::loadbalancer(int time_len, int serv_count){
    clock_len = time_len;
    num_servers = serv_count;
    rand_len = time_len / 50;

    char name = 'a';
    for(int i=0; i<num_servers;i++){
        servers.push_back(webserver(name));
        name++;
    }

    for(int i = 0; i < num_servers*2; i++){
        // len is the random amount of time each request would take
        int len = rand() % rand_len +5;
        workload.add(Request(len));
    }

}

void loadbalancer::main_loop(){

    int clock = 0;

    while(clock <= clock_len || !workload.empty()){


        if(rand()%213+1 == 4){
            int num = rand()%5+1;
            for(int i =0; i< num;i++){
                int len = rand() % rand_len + 5;
                workload.add(Request(len));
            }
        }

        for(int i = 0; i <num_servers;i++){
            try{
                if(!servers[i].status(clock)){
                    servers[i].set_job(clock, workload.pop());

                }
            }
            catch(...){
                continue;
            }
        }
        clock++;

    }

}
