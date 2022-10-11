#include "requestqueue.h"
#include <iostream>

using std::cout,std::endl;
/**
 * \file WebServer.h
 * @brief 
 * This file contains the class for the WebServer object. Meant to represent a server that handles HTTP requests, completes them and returns the results
 * 
 */

/*! \class WebServer
    \brief A class object used to represent a server handling tasks and annoucing when they're complete.
*/
class WebServer{

    bool occupied;/**< boolean variable meant to represent if this current server is currently occupied*/
    int start_time;/**< integer variable to hold when the server took its current Request, used in status()*/
    char name;/**< Character data-member to uniquely identify the current server, immutable after WebServer creation*/
    Request current;/**< Request variable holding the (primitive, not pointer) request.*/

    public:
    //! Default constructor
    /*!
        This constructor initliazes all the WebServer data members and fills the current variable with the default constuctor Request().
        \param kname a char representing the unique identifer for the server
    */
    WebServer(char kname){
        occupied = false;
        start_time = 0;
        name = kname;
        current = Request();
    }

    //! Indicates if the server is available to take on a new request.
    /*!
        This function checks two conditions to make the determine if the server is unoccupied, otherwise assume it's still processing a Request. occupied is set True via set_job().
        First condition is if the current request has a time length of 0, this would only be possible if was created via the default constructor thus the server has previously completed a request and is ready for a new one. 
        The second condition checks on if the current request has been completed. This is accomplished via time arithmetic, in which it calls endjob(curr_time).
        \param curr_time a integer variable representing the current clock cycle on the load balancer.
        \return occupied, a boolean variable representing server availabilty. True if currently dealing with a request, False if unoccupied.
    */
    bool status(int curr_time){
        if(current.time == 0){
            occupied = false;
        }
        else if(current.time + start_time == curr_time){
            end_job(curr_time);
        }

        return occupied;
    }

    //! Sets the server occupied with a new request
    /*!
        This function updates the server with a new request by updating the local data members with the new information.
        \param beg_time a integer variable representing the current clock cycle on the load balancer, doesn't change during request run and used for time arithmetic.
        \param incoming a Request variable representing the incoming request that will occupy the server.
    */
    void set_job(int beg_time, Request incoming){
        start_time = beg_time;
        current = incoming;
        occupied = true;
    }

    //! Removes current request and announces the end of processing
    /*!
        This function updates the server data-members with the default values to put it into a unoccupied state and prints out the completion of the request to the system output with its information.
        \param curr_time a integer variable representing the current clock cycle on the load balancer.
    */
    void end_job(int curr_time){
        cout<<"At " << curr_time << " Server "<<string(1,name) << " processed request from "<< current.ip_in << " to " << current.ip_out << endl;
        start_time = 0;
        occupied = false;
        current = Request();
    }
};