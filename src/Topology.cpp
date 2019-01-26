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

    bool isValid();

  public:
    Topology(NetworkParameters *netParams);
    int Init();
    int Broadcast(int *data, int size);
    ~Topology();
};

int Topology::Broadcast(int *data, int size)
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

    ifRoot(this->netParams->getCurrentRank(), {
        if (!(this->isValid()))
        {
            std::cout << "\033[1;31m"
                      << "Error: Invalid number of processes or topology dimmensions!"
                      << "\033[0m"
                      << std::endl;

            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    })
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

int Topology::Init()
{
}

Topology::~Topology()
{
}
