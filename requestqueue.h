#include <queue>
#include <string>
#include <exception>

using std::string, std::queue, std::rand, std::to_string;
/**
 * \file requestqueue.h
 * @brief 
 * This file contains the class for the request queue. 
 *  And the struct for Request objects and its attributes
 * 
 */

/*! \struct Request
    \brief A struct holding the incoming and outgoing ip adresses, the time length of a simulated request.

    This object is used for a webserver object to hold onto while running to simulate a server handling requests.
*/
struct Request{
    string ip_in;/**< String IPV4 address meant to represent the address the request came from.*/
    string ip_out;/**< String IPV4 address, meant to represent the address the request goes to.*/
    int time;/**<  unsigned int32, meant to represent the time it will take to complete the request by the server.*/

    //! Default constructor, used for debugging and program initlization.
    /*!
        This constructor will used "default" and 0 for time_len in the request creation. It is meant for the webserver to differinate when a request has been completed versus in progress. 
    */
    Request(): ip_in("default"), ip_out("default"),time(0){};

    //! Creation Constructor, used for request generation
    /*!
        This is the main constructor used for the program. It will take in the time needed to complete the request and generate 2 randomized IP addresses via <gen_ip>"()"".
        The majority of requests will be made from this constructor.
        \param limit an integer argument representing the time the request takes
    */ 
    Request(int limit): ip_in(gen_ip()), ip_out(gen_ip()),time(limit){};

    //! Debugging Constructor, This constructor will have all its given arguements to create that exact request.
    /*!
        \param in a String argument the incoming IPV4 address.
        \param out a String argument the outgoing IPV4 address.
        \param t an integer argument representing the time the request takes
    */ 
    Request(string in, string out, int t): ip_in(in), ip_out(out),time(t){};

    //! IPV4 Address generation
    /*!

        When called it will call rand()%256 (0 to 255) to generate one part of an IPV4 address.
        Thus it's structure is: 'rand()%256'.'rand()%256'.'rand()%256'.'rand()%256'
        Each part is converted and merged into one string.
        \return a String parameter holding a randomized IPV4 Address.
    */
    string gen_ip(){
        return to_string(rand()%256)+"."+to_string(rand()%256)+"."+to_string(rand()%256)+"."+to_string(rand()%256);
    };

};

/*! \class RequestQueue
    \brief A class using the standard library queue data structure to hold requests for the webserver to pull from.
*/
class RequestQueue{
    private:
    queue<Request> holder;/**< Queue to hold requests for the loadbalancer to insert requests into web-servers.*/

    public:

    //! Add new requests to the queue
    /*!
        \param x a Request argument for the queue to hold on until the next available server
        \return a bool parameter for debugging and verifcation of successful push
    */
    bool add(Request x){
        try{
            holder.push(x);
        }
        catch(std::exception e){
            return false;
        }
        
        return true;
    }
    //! Remove and return a request from the queue
    /*!
        Checks if queue is empty, then stores the top request into a temporay variable and removes its from the queue. Throws error if queue is empty.
        \return a Request parameter that represents the topmost request
    */
    Request pop(){
        if(!empty()){
            Request temp = holder.front();
            holder.pop();
            return temp;
        }
        
        throw "Queue is empty";
    }

    //!Checks if the queue is empty
    /*!
        Accomplished via the built-in empty variable
        \return a bool parameter, true if the queue is empty. False otherwise.
    */
    bool empty(){
        return holder.empty();
    }
};
