#include "loadbalancer.cpp"

using std::cin;
/*! \mainpage CSCE 412: Project 2: LoadBalancer
 * \subsection By Daniel Ortiz-Chaves, 128009829
 *
 * \section intro_sec Introduction
 *
 * This Project models a simulation of a large company load balancing web requests using a load balancer.   
 * The project uses a variety of data structures to process and handle the requests for the load balancer.
 * 
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Download the code Git repo
 * \subsection step2 Step 2: Compile the project in a approiate environment. e.g. g++ -std=c++17 main.cpp
 * \subsection step3 Step 3: Run the project. e.g. ./a.out
 * \subsection step4 Step 4: Input the variables for runtime and number of servers
 * 
 *
 */
int main(){
    cout << "--------Load Balancer Sim--------" <<endl;
    cout << "Enter number of servers: ";
    int num_servers = 0;
    cin >> num_servers;

    cout << "Enter runtime of Sim: ";
    int runtime  = 0;
    cin >> runtime;

    char cont = 'y';
    cout << "Begin (y/n)? : ";
    cin >> cont;

    if(cont == 'y'){
        loadbalancer test(runtime,num_servers);
        test.main_loop();
    }

    cout << "--------Have a nice day--------" << endl;
}