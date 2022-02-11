#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
    const std::string& location1) const
{
    std::cout << "Route between \""
        << location0 << "\" and \""
        << location1 << "\" is in cache, using that..."
        << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
    const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
        << location0 << "\" and \""
        << location1 << "\"..."
        << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
    const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
    const std::string& mapFilePath)
{
    // TODO
    map = Graph(mapFilePath);
    this->potentialPathCount = potentialPathCount;
    inJourney = false;
    cachedPaths = KeyedHashTable(map.TotalVertexCount() * potentialPathCount);
}

void METUMaps::SetDestination(const std::string& name)
{
    // TODO
    if (inJourney) {
        PrintUnableToChangeDestination();
    }
    else {
        destination = name;
    }
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    // TODO
    if (inJourney) {
        PrintUnableToChangeStartingLoc();
    }
    else {
        startingLoc = name;
    }
}

void METUMaps::StartJourney()
{
    // TODO
    if (inJourney) {
        PrintAlreadyInJourney();
    }
    else {
        std::vector<std::vector<int> > p;
        PrintCalculatingRoutes(startingLoc, destination);
        int x;
        try {
            x = map.MultipleShortPaths(p, startingLoc, destination, potentialPathCount);
        }
        catch (const VertexNotFoundException& a)
        {
            PrintLocationNotFound();
            return;
        }
        if (x) {
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < p[i].size() - 1; j++) {
                    std::vector<int> temp;
                    for (int k = j; k < p[i].size(); k++) {
                        temp.push_back(p[i][k]);
                    }
                    cachedPaths.Insert(GenerateKey(map.VertexName(p[i][j]), map.VertexName(p[i][p[i].size() - 1])), temp);

                }
            }
            currentLoc = startingLoc;
            currentRoute = p[0];
            inJourney = true;
        }
        else {
            PrintLocationNotFound();
        }
    }
}

void METUMaps::EndJourney()
{
    // TODO
    if (inJourney) {
        cachedPaths.ClearTable();
        destination.clear();
        startingLoc.clear();
        currentLoc.clear();
        inJourney = false;
    }
    else {
        PrintJourneyIsAlreadFinished();
    }
}

void METUMaps::UpdateLocation(const std::string& name)
{
    // TODO
    if (!inJourney) {
        PrintNotInJourney();
    }
    else if (name == destination) {
        PrintJourneyCompleted();
    }
    else {
        std::vector<int> p;
        cachedPaths.Find(p, GenerateKey(name, destination));
        if (p.size() == 0) {
            PrintCalculatingRoutes(name, destination);
            cachedPaths.ClearTable();
            std::vector<std::vector<int> > q;
            int x;
            try {
                x = map.MultipleShortPaths(q, name, destination, potentialPathCount);
            }
            catch (const VertexNotFoundException& a)
            {
                PrintLocationNotFound();
                return;
            }
            if (x) {
                for (int i = 0; i < x; i++) {
                    for (int j = 0; j < q[i].size() - 1; j++) {
                        std::vector<int> temp;
                        for (int k = j; k < q[i].size(); k++) {
                            temp.push_back(q[i][k]);
                        }
                        cachedPaths.Insert(GenerateKey(map.VertexName(q[i][j]), map.VertexName(q[i][q[i].size() - 1])), temp);
                        temp.clear();
                    }
                }

            }
            currentLoc = name;
            currentRoute = q[0];
        }
        else {

            PrintCachedLocationFound(name, destination);
            currentRoute = p;
            currentLoc = name;

        }

    }

}
void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if (!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
        << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}