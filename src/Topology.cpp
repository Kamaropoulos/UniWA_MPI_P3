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

#include <iostream>

using namespace std;

struct TopologyDimmensions
{
    int m;
    int n;
};

class Topology
{
  private:
    TopologyDimmensions dimmensions;
    NetworkParameters *netParams;
    MPI_Comm topologyCommunicator;

    bool isValid();

  public:
    Topology(NetworkParameters *netParams);
    void Init();
    void Broadcast(int *data, int size);
    ~Topology();
};

void Topology::Broadcast(int *data, int size)
{
    MPI_Bcast(data, size, MPI_INT, 0, MPI_COMM_WORLD);
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
}

Topology::~Topology()
{
}
