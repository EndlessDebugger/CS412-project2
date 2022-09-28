#include <queue>
#include <string>
#include <exception>
#include <stdlib.h>

using std::string, std::queue, std::rand, std::to_string;

struct Request{
    string ip_in;
    string ip_out;
    int time;

    Request(): ip_in(gen_ip()), ip_out(gen_ip()),time(gen_time()){};
    Request(string in, string out, int t): ip_in(in), ip_out(out),time(t){};

    string gen_ip(){
        return to_string(rand()%256)+"."+to_string(rand()%256)+"."+to_string(rand()%256)+"."+to_string(rand()%256);
    };

    int gen_time(){ return rand(); };
};


class RequestQueue{
    private:
    queue<Request> holder;

    public:

    bool add(Request x){
        try{
            holder.push(x);
        }
        catch(std::exception e){
            return false;
        }
        
        return true;
    }

    Request pop(){
        if(!empty()){
            Request temp = holder.front();
            holder.pop();
            return temp;
        }
        
        throw "Queue is empty";
    }

    bool empty(){
        return holder.empty();
    }
};
