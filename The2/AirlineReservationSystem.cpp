#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    
    Passenger pass(firstname,lastname);
    if(searchPassenger(firstname,lastname)){
        
    }
    else{
        passengers.insert(pass);
    }
    
    
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    
    Passenger p(firstname,lastname);
    if(passengers.search(p)){
        return &(passengers.search(p)->data);
    }
    else{
        return NULL;
    }
    
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
     
    
    if (containss(flights.getRoot(), flightCode)) {

    }
    else {
        Flight f(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
        flights.insert(f);
    }
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    std::vector<Flight*> same;
    return searchFlight(same, flights.getRoot(), departureCity, arrivalCity);
}



void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger* p=searchPassenger(firstname,lastname);
    Flight* f=findFlight(flights.getRoot(),flightCode);
    if(!p||!f){
        
        
    }
    else{
        Ticket t(p,f,ticketType);
        (*f).addTicket(t);
    }
    
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger* p = searchPassenger(firstname, lastname);
    Flight* f = findFlight(flights.getRoot(), flightCode);
    if (!p || !f) {


    }
    else {
        Ticket t(p, f, ticketType);
        
        freeTicketRequests.enqueue(t);
        
    }
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    
    Queue<Ticket> q;
    Flight* f = findFlight(flights.getRoot(), flightCode);
    
    
    if (!f) {

    }
    else {
        while (!freeTicketRequests.isEmpty()) {
            Ticket t = freeTicketRequests.dequeue();
            if (t.getFlight()->getFlightCode() == flightCode) {
                if (f->getBusinessCapacity() == 0 && t.getTicketType() == business) {
                    q.enqueue(t);
                }
                else if(f->getEconomyCapacity() == 0 && t.getTicketType() == economy){
                    q.enqueue(t);
                }   
                else {
                    
                    if((*f).addTicket(t)){
                        
                    }
                    else{
                        q.enqueue(t);
                    }
                }
                
            }
            else {
                q.enqueue(t);
            }
        }
        while (!q.isEmpty()) {
            freeTicketRequests.enqueue(q.dequeue());
        }
        f->setCompleted(true);
        
    }
    
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}

