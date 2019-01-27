/**
 * @file main.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief Project entry point
 * @version 0.1
 * @date 2019-01-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "NetworkParameters.hpp"
#include "Topology.hpp"
#include "SumCartesian2DSendRecv.hpp"
#include "IO.hpp"
#include "utils.hpp"

#include "mpi.h"

#include <vector>

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    // Initialize MPI and get rank and number of processes
    NetworkParameters *netParams = new NetworkParameters(argc, argv);
    Topology *topology = new Topology(netParams);

    topology->Init();

    // Read data
    vector<int> data;
    ifRoot(netParams->getCurrentRank(), {
        ReadData(&data, argc, argv);
    });

    // Scatter the data across the topology processes
    topology->Load(data);

    // Initialize an object that calculates the sum using the MPI_Send/MPI_Recv methods
    SumCartesian2DSendRecv calculation1 = new SumCartesian2DSendRecv(topology);

    // Calculate the sum using MPI_Send/MPI_Recv
    int sum1 = calculation1.Compute();

    // Print first result
    // PrintResult(sum1, "MPI_Send/MPI_Recv");

    //accumulateTop();
    //accumulateLeft();
    //PrintResult();

    delete netParams;
    delete topology;

    // MPI_Finalize();
    return 0;
}
