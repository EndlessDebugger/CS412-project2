#include "requestqueue.h"
#include "webserver.h"
#include <vector>

using std::vector;

class loadbalancer{

    int clock_len, num_servers;
    RequestQueue workload;
    webserver* servers;

    public:
    loadbalancer(int clock_len, int num_servers);
    ~loadbalancer();

    void simulation();
};

loadbalancer::loadbalancer(int time_len, int serv_count){
    clock_len = time_len;
    num_servers = serv_count;

    servers = new webserver[num_servers];

    for(int i = 0; i <num_servers*2; i++){
        // len is the random amount of time each request would take
        int len = rand() % 50 +5;
        workload.add(Request(len));
    }

}


loadbalancer::~loadbalancer(){

    delete servers;
}

void loadbalancer::simulation(){

    
}
