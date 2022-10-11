#include "loadbalancer.cpp"

using std::cin;

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