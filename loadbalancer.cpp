#include "webserver.h"
#include <vector>

using std::vector;

/**
 * \file loadbalancer.cpp
 * @brief 
 * This file contains the class for the loadbalancer object. Meant to simulate a loadbalancer handling and dispatching requests to a number a servers from a number of users.
 * 
 */

/*! \class loadbalancer
    \brief A class object used to represent a loadbalancer handling requests and servers.
*/
class loadbalancer{

    int clock_len;/**< an integer variable meant to represent how long should the loadbalancer be running*/
    int num_servers;/**< an integer variable meant to represent the number of servers the loadbalancer has to balance with.*/
    RequestQueue workload;/**< a RequestQueue variable meant to represent the incoming requests ready to be assigned to a server */
    vector<WebServer> servers;/**< a vector of Webservers to hold all the servers the loadbalancer has to managed*/
    int rand_len;/**<an integer variable to dictate the upper limit of time a request would take to complete.*/

    public:
    loadbalancer(int clock_len, int num_servers);

    void main_loop();
};

//! Default constructor
/*!
    This constructor initliazes all the loadbalancer data members, creates all the servers and fills the request queue with requests equal to 2 times the number of servers.

    \param time_len an integer representing the user input for how long the loadbalancer should run.
    \param serv_count an integer representing the user input for how many servers the loadbalancer has
*/
loadbalancer::loadbalancer(int time_len, int serv_count){
    clock_len = time_len;
    num_servers = serv_count;
    rand_len = time_len / 50;

    char name = 'a';
    for(int i=0; i<num_servers;i++){
        servers.push_back(WebServer(name));
        name++;
    }

    for(int i = 0; i < num_servers*2; i++){
        // len is the random amount of time each request would take
        int len = rand() % rand_len +5;
        workload.add(Request(len));
    }

    cout<<"Requests have a range of 5 to "<<rand_len<<" clock cycles"<<endl;

}

//! This runs the simulation and assigns each server with its request onces it's avaialble
/*!
   After beginning the clock, the function runs an endless loop until either the clock length has been reached or the requestqeue has become empty. The first condition is to ensure the loop is ends within a reasonable amount of time of the inputted time.
   The second condition is to ensure every request is handled before ending the loadbalancer. After the loop has begun, we randomly generate a number of requests to add to the queue, representing actual traffic.
   After which, the function iterates through all the servers and checks if they're available for a new request, if not then continue, otherwise assign the server the request and move to the next server.
*/
void loadbalancer::main_loop(){

    int clock = 0;
    int rand_requests = 0;
    int total = workload.size();
    while(clock <= clock_len || !workload.empty()){


        if(rand()%213+1 == 4){
            int num = rand()%5+1;
            for(int i =0; i< num;i++){
                int len = rand() % rand_len + 5;
                workload.add(Request(len));
            }
            rand_requests += num;
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

    cout<<"Initial Queue size: "<<total<<endl;
    cout<<"Final number of requests handled: "<<rand_requests<<endl;

}
