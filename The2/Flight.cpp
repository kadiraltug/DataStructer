#include "Flight.h"

Flight::Flight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    this->flightCode = flightCode;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->departureCity = departureCity;
    this->arrivalCity = arrivalCity;
    this->economyCapacity = economyCapacity;
    this->businessCapacity = businessCapacity;
    this->completed = false;
}

const std::string &Flight::getFlightCode() const {
    return flightCode;
}

const std::string &Flight::getDepartureTime() const {
    return departureTime;
}

const std::string &Flight::getArrivalTime() const {
    return arrivalTime;
}

const std::string &Flight::getDepartureCity() const {
    return departureCity;
}

const std::string &Flight::getArrivalCity() const {
    return arrivalCity;
}

int Flight::getEconomyCapacity() const {
    return economyCapacity;
}

int Flight::getBusinessCapacity() const {
    return businessCapacity;
}

bool Flight::isCompleted() const {
    return completed;
}

void Flight::setCompleted(bool completed) {
    this->completed = completed;
}

bool Flight::addTicket(const Ticket &ticket) {
    int bus = 0, ec = 0;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].getTicketType() == business) {
            bus++;
        }
        else {
            ec++;
        }
    }
    if (ticket.getTicketType() == business && getBusinessCapacity() <=bus) {
        return false;
    }
    else if (ticket.getTicketType() == business && getBusinessCapacity() >bus) {
        tickets.push_back(ticket);
        return true;
    }
    else if (ticket.getTicketType() == economy && getEconomyCapacity() <=ec) {
        return false;
    }
    else {
        tickets.push_back(ticket);
        return true;
    }
}
if(ticket.getTicketType() == business && getBusinessCapacity() !=0){
	tickets.push_back(ticket);
	return true;
}
else if(ticket.getTicketType() == economy && getEconomyCapacity() !=0){
	tickets.push_back(ticket);
	return true;
}
else{
	return false;
}
bool Flight::operator<(const Flight &rhs) const {
   
    if (rhs.flightCode < this->flightCode) {
        return false;
    }
    else {
        return true;
    }
    
}

bool Flight::operator>(const Flight &rhs) const {
    return rhs < *this;
}

bool Flight::operator==(const Flight &rhs) const {
    return flightCode == rhs.flightCode;
}

bool Flight::operator!=(const Flight &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << "Flight(flightCode: " << flight.flightCode;
    os << ", departureTime: " << flight.departureTime;
    os << ", arrivalTime: " << flight.arrivalTime;
    os << ", departureCity: " << flight.departureCity;
    os << ", arrivalCity: " << flight.arrivalCity;
    os << ", economyCapacity: " << flight.economyCapacity;
    os << ", businessCapacity: " << flight.businessCapacity;
    os << ", completed: " << (flight.completed ? "yes" : "no");
    os << ", tickets: [";
    for (int i = 0 ; i < flight.tickets.size() ; ++i) {
        os << flight.tickets[i];
        if (i != (flight.tickets.size() - 1)) os << ", ";
    }
    os << "])";
    return os;
}

