#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if (line.empty()) continue;
        // Comment Skip
        if (line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while (stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if (i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if (i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if (!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                    << tokens[0] << "-"
                    << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    // TODO
    bool control = true;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i].name == vertexName) {
            control = false;
            break;
        }
    }
    if (control) {
        GraphVertex p;
        p.name = vertexName;
        p.edgeCount = 0;
        vertexList.push_back(p);
    }
    else {
        throw DuplicateVertexNameException();
    }
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
    const std::string& toVertexName,
    int weight)
{
    // TODO
    bool control1 = false;
    bool control2 = false;
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i].name == fromVertexName) {
            control1 = true;
            index1 = i;
        }
        else if (vertexList[i].name == toVertexName) {
            control2 = true;
            index2 = i;
        }
    }

    if (control1 && control2 && toVertexName != fromVertexName) {
        if (vertexList[index1].edgeCount >= MAX_EDGE_PER_VERTEX || vertexList[index2].edgeCount >= MAX_EDGE_PER_VERTEX) {
            throw TooManyEdgeOnVertexExecption();
        }
        else {


            GraphEdge p1;
            p1.vertexId0 = index1;
            p1.vertexId1 = index2;
            p1.masked = false;
            p1.weight = weight;

            bool control3 = true;
            for (int i = 0; i < vertexList[index1].edgeCount; i++) {
                if ((edgeList[vertexList[index1].edgeIds[i]].vertexId0 == index1 && edgeList[vertexList[index1].edgeIds[i]].vertexId1 == index2) ||
                    (edgeList[vertexList[index1].edgeIds[i]].vertexId0 == index2 && edgeList[vertexList[index1].edgeIds[i]].vertexId1 == index1)) {
                    control3 = false;
                }
            }
            if (control3) {
                edgeList.push_back(p1);

                vertexList[index1].edgeIds[vertexList[index1].edgeCount] = edgeList.size() - 1;
                vertexList[index1].edgeCount++;
                vertexList[index2].edgeIds[vertexList[index2].edgeCount] = edgeList.size() - 1;
                vertexList[index2].edgeCount++;
                return true;
            }
        }

    }
    else if (toVertexName == fromVertexName) {
        if (vertexList[index1].edgeCount >= MAX_EDGE_PER_VERTEX || vertexList[index2].edgeCount >= MAX_EDGE_PER_VERTEX) {
            throw TooManyEdgeOnVertexExecption();
        }
    }
    else {
        throw VertexNotFoundException();
    }
    return false;
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
    const std::string& from,
    const std::string& to) const
{
    // TODO
    bool control1 = false;
    bool control2 = false;
    int index1 = -3;
    int index2 = -3;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i].name == from) {
            control1 = true;
            index1 = i;
        }
        else if (vertexList[i].name == to) {
            control2 = true;
            index2 = i;
        }
    }
    if (!control1 || !control2) {
        throw VertexNotFoundException();
    }
    else if (control1 && control2 && index1 != index2) {
        std::priority_queue<DistanceVertexIdPair> pq;
        std::vector<int> previous;
        previous.resize(vertexList.size(), INVALID_INDEX);
        std::vector<int> distance;
        distance.resize(vertexList.size(), LARGE_NUMBER);
        distance[index1] = 0;
        DistanceVertexIdPair p(index1, 0);
        pq.push(p);
        while (!pq.empty()) {
            int a = pq.top().vId;
            pq.pop();
            for (int i = 0; i < vertexList[a].edgeCount; i++) {
                if (edgeList[vertexList[a].edgeIds[i]].masked) continue;
                int v;
                if (edgeList[vertexList[a].edgeIds[i]].vertexId0 == a) {
                    v = edgeList[vertexList[a].edgeIds[i]].vertexId1;
                }
                else {
                    v = edgeList[vertexList[a].edgeIds[i]].vertexId0;
                }
                int weight = edgeList[vertexList[a].edgeIds[i]].weight;
                if (distance[a] + weight < distance[v]) {
                    distance[v] = distance[a] + weight;
                    previous[v] = a;
                    pq.push(DistanceVertexIdPair(v, distance[v]));
                }
            }
        }
        std::vector<int> last;
        if (previous[index2] == INVALID_INDEX) {
            return false;
        }
        else {
            int z = index2;
            int x = -2;
            last.push_back(z);
            while (x != index1) {
                x = previous[z];
                last.push_back(x);
                z = x;
            }
            for (int i = last.size() - 1; i > -1; i--) {
                orderedVertexIdList.push_back(last[i]);
            }


        }
        return true;
    }
    else if (index1 == index2) {
        orderedVertexIdList.push_back(index1);
        return true;
    }
    return false;
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
    const std::string& from,
    const std::string& to,
    int numberOfShortestPaths)
{
    // TODO
    UnMaskAllEdges();
    bool control1 = false;
    bool control2 = false;
    int index1 = -3;
    int index2 = -3;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i].name == from) {
            control1 = true;
            index1 = i;
        }
        else if (vertexList[i].name == to) {
            control2 = true;
            index2 = i;
        }
    }
    if (!control1 || !control2) {
        throw VertexNotFoundException();
        return 0;
    }
    else if (control1 && control2 && index1 != index2) {


        for (int k = 0; k < numberOfShortestPaths; k++) {
            std::vector<int> last2;
            bool a = ShortestPath(last2, from, to);
            if (a) {
                orderedVertexIdList.push_back(last2);
                int maxedge = -2;
                int maxindex;
                for (int i = 0; i < last2.size() - 1; i++) {
                    int z;
                    int maxindex2;
                    for (int j = 0; j < vertexList[last2[i]].edgeCount; j++) {
                        if ((edgeList[vertexList[last2[i]].edgeIds[j]].vertexId0 == last2[i] && edgeList[vertexList[last2[i]].edgeIds[j]].vertexId1 == last2[i + 1]) ||
                            (edgeList[vertexList[last2[i]].edgeIds[j]].vertexId0 == last2[i + 1] && edgeList[vertexList[last2[i]].edgeIds[j]].vertexId1 == last2[i])) {
                            z = edgeList[vertexList[last2[i]].edgeIds[j]].weight;
                            maxindex2 = vertexList[last2[i]].edgeIds[j];
                            break;
                        }
                    }
                    if (z > maxedge) {
                        maxedge = z;
                        maxindex = maxindex2;
                    }

                }
                edgeList[maxindex].masked = true;
            }
            else {
                break;
            }
        }


        UnMaskAllEdges();
        return orderedVertexIdList.size();
    }
    else if (index1 == index2) {
        std::vector<int> last2;
        last2.push_back(index1);
        orderedVertexIdList.push_back(last2);
        UnMaskAllEdges();
        return 1;
    }
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
    for (int i = 0; i < vertexNames.size(); i++) {
        bool control1 = false;
        bool control2 = false;
        int index1 = 0;
        int index2 = 0;
        for (int j = 0; j < vertexList.size(); j++) {
            if (vertexList[j].name == vertexNames[i].s0) {
                index1 = j;
                control1 = true;
            }
            else if (vertexList[j].name == vertexNames[i].s1) {
                index2 = j;
                control2 = true;
            }
        }
        if (control1 && control2 && index1 != index2) {
            for (int k = 0; k < vertexList[index1].edgeCount; k++) {
                if ((edgeList[vertexList[index1].edgeIds[k]].vertexId1 == index1 && edgeList[vertexList[index1].edgeIds[k]].vertexId0 == index2) ||
                    (edgeList[vertexList[index1].edgeIds[k]].vertexId1 == index2 && edgeList[vertexList[index1].edgeIds[k]].vertexId0 == index1)) {

                    edgeList[vertexList[index1].edgeIds[k]].masked = true;
                    break;
                }

            }
        }
        else if (index1 == index2) {

        }
        else {
            throw VertexNotFoundException();
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
    for (int i = 0; i < vertexNames.size(); i++) {
        bool control1 = false;
        bool control2 = false;
        int index1 = 0;
        int index2 = 0;
        for (int j = 0; j < vertexList.size(); j++) {
            if (vertexList[j].name == vertexNames[i].s0) {
                index1 = j;
                control1 = true;
            }
            else if (vertexList[j].name == vertexNames[i].s1) {
                index2 = j;
                control2 = true;
            }
        }
        if (control1 && control2 && index1 != index2) {
            for (int k = 0; k < vertexList[index1].edgeCount; k++) {
                if ((edgeList[vertexList[index1].edgeIds[k]].vertexId0 == index1 && edgeList[vertexList[index1].edgeIds[k]].vertexId1 == index2) ||
                    (edgeList[vertexList[index1].edgeIds[k]].vertexId0 == index2 && edgeList[vertexList[index1].edgeIds[k]].vertexId1 == index1)) {

                    edgeList[vertexList[index1].edgeIds[k]].masked = false;
                    break;
                }


            }
        }
        else if (index1 == index2) {

        }
        else {
            throw VertexNotFoundException();
        }
    }
}

void Graph::UnMaskAllEdges()
{
    // TODO
    for (int i = 0; i < edgeList.size(); i++) {
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    // TODO
    bool control = false;
    int index = 0;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i].name == name) {
            control = true;
            index = i;
            break;
        }
    }
    if (control) {
        for (int i = 0; i < vertexList[index].edgeCount; i++) {
            edgeList[vertexList[index].edgeIds[i]].masked = true;

        }
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    // TODO
    bool control = false;
    int index = 0;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i].name == name) {
            control = true;
            index = i;
            break;
        }
    }
    if (control) {
        for (int i = 0; i < vertexList[index].edgeCount; i++) {
            edgeList[vertexList[index].edgeIds[i]].masked = false;

        }
    }
}

void Graph::ModifyEdge(const std::string& vName0,
    const std::string& vName1,
    float newWeight)
{
    // TODO
    bool control1 = false;
    bool control2 = false;
    int index1 = 0;
    int index2 = 0;
    for (int j = 0; j < vertexList.size(); j++) {
        if (vertexList[j].name == vName0) {
            index1 = j;
            control1 = true;
        }
        else if (vertexList[j].name == vName1) {
            index2 = j;
            control2 = true;
        }
    }
    if (!control1 || !control2) {
        throw VertexNotFoundException();
    }
    else if (control1 && control2 && index1 != index2) {
        for (int i = 0; i < vertexList[index1].edgeCount; i++) {
            if ((edgeList[vertexList[index1].edgeIds[i]].vertexId1 == index2 && edgeList[vertexList[index1].edgeIds[i]].vertexId0 == index1) ||
                (edgeList[vertexList[index1].edgeIds[i]].vertexId0 == index2 && edgeList[vertexList[index1].edgeIds[i]].vertexId1 == index1)) {
                edgeList[vertexList[index1].edgeIds[i]].weight = newWeight;
            }
        }
    }
    else if (index1 == index2) {

    }
    else {

    }
}

void Graph::ModifyEdge(int vId0, int vId1,
    float newWeight)
{
    // TODO
    if (vId0 >= vertexList.size() || vId0 >= vertexList.size()) {

    }
    else {
        for (int i = 0; i < vertexList[vId0].edgeCount; i++) {
            if ((edgeList[vertexList[vId0].edgeIds[i]].vertexId1 == vId1 && edgeList[vertexList[vId0].edgeIds[i]].vertexId0 == vId0) ||
                (edgeList[vertexList[vId0].edgeIds[i]].vertexId0 == vId1 && edgeList[vertexList[vId0].edgeIds[i]].vertexId1 == vId0)) {
                edgeList[vertexList[vId0].edgeIds[i]].weight = newWeight;
            }
        }


    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for (size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for (int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if (edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                << std::setw(2) << edge.weight
                << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                ? edge.vertexId1
                : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
    bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for (size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if (vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if (!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if (i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if (nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if (vertexId < static_cast<int>(vertexList.size()) &&
            nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for (int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if ((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                    ||
                    (edgeList[eId].vertexId0 == nextVertexId &&
                        edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if (edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                << std::setw(2)
                << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if (sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    // TODO
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    // TODO
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    // TODO
    return vertexList[vertexId].name;
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    // TODO
    int sum = 0;
    for (int i = 0; i < orderedVertexIdList.size() - 1; i++) {
        for (int j = 0; j < vertexList[orderedVertexIdList[i]].edgeCount; j++) {
            if ((edgeList[vertexList[orderedVertexIdList[i]].edgeIds[j]].vertexId1 == orderedVertexIdList[i + 1] && edgeList[vertexList[orderedVertexIdList[i]].edgeIds[j]].vertexId0 == orderedVertexIdList[i]) ||
                (edgeList[vertexList[orderedVertexIdList[i]].edgeIds[j]].vertexId0 == orderedVertexIdList[i + 1] && edgeList[vertexList[orderedVertexIdList[i]].edgeIds[j]].vertexId1 == orderedVertexIdList[i])) {
                sum += edgeList[vertexList[orderedVertexIdList[i]].edgeIds[j]].weight;
                break;
            }

        }
    }
    return sum;
}