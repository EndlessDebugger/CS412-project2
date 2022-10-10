#include "webserver.h"
#include <vector>


using std::vector;

class loadbalancer{

    int clock_len, num_servers;
    RequestQueue workload;
    vector<webserver> servers;

    public:
    loadbalancer(int clock_len, int num_servers);

    void main_loop();
};

loadbalancer::loadbalancer(int time_len, int serv_count){
    clock_len = time_len;
    num_servers = serv_count;

    // servers = new webserver[num_servers];

    char name = 'a';
    for(int i=0; i<num_servers;i++){
        servers.push_back(webserver(name));
        name++;
    }

    for(int i = 0; i < num_servers*2; i++){
        // len is the random amount of time each request would take
        int len = rand() % 50 +5;
        workload.add(Request(len));
    }

}

void loadbalancer::main_loop(){

    int clock = 0;

    while(clock <= clock_len || !workload.empty()){


        if(rand()%213+1 == 4){
            int len = rand() % 50 + 5;
            workload.add(Request(len));
        }

        for(int i = 0; i <num_servers;i++){

            //     if(!i.status(clock)){
            // cout<<i.get_name()<<" "<< clock<<" "<< !i.status(clock)<<endl;
            try{
                if(!servers[i].status(clock)){
                    servers[i].set_job(clock, workload.pop());

                }
            }
            catch(...){
            // cout<<i.get_name()<<" "<< clock<<" "<< !i.status(clock)<<endl;
                continue;
            }
        }
        clock++;

    }

}
