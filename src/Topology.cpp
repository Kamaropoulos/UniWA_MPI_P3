/**
 * @file Topology.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief Methods for managing the network topology
 * @version 0.1
 * @date 2019-01-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "NetworkParameters.hpp"
#include "IO.hpp"
#include "utils.hpp"

#include "mpi.h"

#include <vector>

#include <iostream>

using namespace std;

struct TopologyDimmensions
{
    int m;
    int n;
};

struct Neighbors
{
    int up;
    int down;
    int left;
    int right;
};

class Topology
{
  private:
    int localData;
    MPI_Comm topologyCommunicator;

    bool isValid();

  public:
    Topology(NetworkParameters *netParams);
    void Init();
    void Broadcast(int *data, int size);
    void Load(vector<int> data);
    void Scatter(vector<int> data);
    void Send(int *data, int dataCount, int target);
    void Receive(int *data, int dataCount, int source);
    void GetCoords(int* coords);
    void Barrier();
    Neighbors GetNeighbors();
    int getLocalData();
    ~Topology();
    NetworkParameters *netParams;
    TopologyDimmensions dimmensions;
    Neighbors neighbors;
};

Neighbors Topology::GetNeighbors(){
    return neighbors;
}

void Topology::Broadcast(int *data, int size)
{
    MPI_Bcast(data, size, MPI_INT, 0, MPI_COMM_WORLD);
}

void Topology::Barrier()
{
    MPI_Barrier(MPI_COMM_WORLD);
}

void Topology::GetCoords(int* coords){
    MPI_Cart_coords(this->topologyCommunicator, this->netParams->getCurrentRank(), 2, coords);
}

int Topology::getLocalData()
{
    // cout << "Process " << this->netParams->getCurrentRank() << ": " << "U=" << this->neighbors.up << " D=" << this->neighbors.down << " L=" << this->neighbors.left << " R=" << this->neighbors.right << endl;
    return this->localData;
}

/**
 * @brief Reads the topology dimmensions from stdin and constructs a new Topology object
 * 
 * @param netParams 
 */
Topology::Topology(NetworkParameters *netParams)
{
    this->netParams = netParams;
    int *tempDimmensions = new int[2];
    // Get dimmensions from the user
    ifRoot(this->netParams->getCurrentRank(), {
        readTopologyDimmensions(&(dimmensions.m), &(dimmensions.n));
        tempDimmensions[0] = this->dimmensions.m;
        tempDimmensions[1] = this->dimmensions.n;
    });
    // Broadcast the dimmensions to the other processes
    this->Broadcast(tempDimmensions, 2);
    this->dimmensions.m = tempDimmensions[0];
    this->dimmensions.n = tempDimmensions[1];
    delete[] tempDimmensions;
}

/**
 * @brief Check if the dimmensions and the number of processes match
 * 
 * @return true 
 * @return false 
 */
bool Topology::isValid()
{
    return (this->netParams->getProcessesNumber() == (this->dimmensions.m * this->dimmensions.n));
}

void Topology::Scatter(vector<int> data)
{
    // Get array from vector
    int *dataArray;

    ifRoot(this->netParams->getCurrentRank(), {
        dataArray = &data[0];
    });

    int tempData;

    MPI_Scatter(dataArray, 1, MPI_INT, &tempData, 1, MPI_INT, 0, MPI_COMM_WORLD);

    this->Barrier();

    this->localData = tempData;

    // cout << "Process " << this->netParams->getCurrentRank() << " got: " << this->localData << endl;
}

void Topology::Send(int *data, int dataCount, int target)
{
    // cout << this->netParams->getCurrentRank() << " sends to " << target << endl;
    MPI_Send(data, dataCount, MPI_INT, target, 10, this->topologyCommunicator);
}

void Topology::Receive(int *data, int dataCount, int source)
{
    MPI_Status status;
    // cout << this->netParams->getCurrentRank() << " receives from " << source << endl;
    MPI_Recv(data, dataCount, MPI_INT, source, 10, this->topologyCommunicator, &status);
}

void Topology::Init()
{
    ifRoot(this->netParams->getCurrentRank(), {
        if (!(this->isValid()))
        {
            std::cout << "\033[1;31m"
                      << "Error: Invalid number of processes or topology dimmensions!"
                      << "\033[0m"
                      << std::endl;

            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    });

    int dims[2] = {this->dimmensions.m, this->dimmensions.n};
    int periods[2] = {0, 0};

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &(this->topologyCommunicator));

    // Find Neighbors
    MPI_Cart_shift(topologyCommunicator, 0, 1, &(this->neighbors.up), &(this->neighbors.down));
    MPI_Cart_shift(topologyCommunicator, 1, 1, &(this->neighbors.left), &(this->neighbors.right));

    // cout << "Process " << this->netParams->getCurrentRank() << ": " << "U=" << this->neighbors.up << " D=" << this->neighbors.down << " L=" << this->neighbors.left << " R=" << this->neighbors.right << endl;
}

void Topology::Load(vector<int> data)
{
    this->Barrier();
    // // Check if data is integer multiple of p
    if (data.size() % this->netParams->getProcessesNumber())
    {
        // If it's not, print an error and abort
        std::cout << "\033[1;31m"
                  << "Error: The number of elements is not an integer multiple of the number of processes!"
                  << "\033[0m"
                  << std::endl;

        MPI_Abort(MPI_COMM_WORLD, 1);

        return;
    }

    // Barrier to ensure input is valid before letting the other processes continue
    this->Barrier();

    // Broadcast number of data
    int dataCount;

    ifRoot(this->netParams->getCurrentRank(), {
        dataCount = data.size();
    });

    this->Broadcast(&dataCount, 1);

    this->Barrier();

    // Scatter Data
    this->Scatter(data);
}

Topology::~Topology()
{
}
