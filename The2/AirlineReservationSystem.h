#ifndef AIRLINERESERVATIONSYSTEM_H
#define AIRLINERESERVATIONSYSTEM_H

#include "BST.h"
#include "Queue.h"
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"

class AirlineReservationSystem {
public: // DO NOT CHANGE THIS PART.
    AirlineReservationSystem() {}

    void addPassenger(const std::string &firstname, const std::string &lastname);

    Passenger *searchPassenger(const std::string &firstname, const std::string &lastname);

    void addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity);

    std::vector<Flight *> searchFlight(const std::string &departureCity, const std::string &arrivalCity);

    void issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void executeTheFlight(const std::string &flightCode);

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    std::vector<Flight*> searchFlight(std::vector<Flight*> p, BSTNode<Flight>* f, const std::string& departureCity, const std::string& arrivalCity) {
        /* TODO */
        if (f != NULL) {
            if (f->data.getDepartureCity() == departureCity && f->data.getArrivalCity() == arrivalCity) {
                p.push_back(&(f->data));
            }


            p = searchFlight(p, f->left, departureCity, arrivalCity);
            p = searchFlight(p, f->right, departureCity, arrivalCity);
        }
        return p;
    }
    bool containss(BSTNode<Flight>* f, const std::string& flightCode) {
        if (f==NULL) {
            return false;
        }
        else {
            if (f->data.getFlightCode() == flightCode) {
                return true;
            }
            else if (f->data.getFlightCode() < flightCode) {
                containss(f->right, flightCode);
            }
            else if (f->data.getFlightCode() > flightCode)
            {
                containss(f->left, flightCode);
            }
        }
    }
    
    Flight* findFlight(BSTNode<Flight>* f, const std::string& flightCode) {
        if (f == NULL) {
            return NULL;
        }
        else {
            if (f->data.getFlightCode() == flightCode) {
                return &(f->data);
            }
            else if (f->data.getFlightCode() < flightCode) {
                findFlight(f->right, flightCode);
            }
            else {
                findFlight(f->left, flightCode);
            }
        }
    }
    int findBusiness(Flight f) {
        f.
    }
    
private: // DO NOT CHANGE THIS PART.
    BST<Passenger> passengers;
    BST<Flight> flights;

    Queue<Ticket> freeTicketRequests;
};

#endif //AIRLINERESERVATIONSYSTEM_H
