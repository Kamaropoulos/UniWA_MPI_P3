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

#include "mpi.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    // Initialize MPI and get rank and number of processes
    NetworkParameters *netParams = new NetworkParameters(argc, argv);

    Topology *topology = new Topology(netParams);

    //GetNetworkParameters();
    //GenerateTopology();
    //ReadData();
    //ScatterData();
    //accumulateTop();
    //accumulateLeft();
    //PrintResult();
    //accumulateTop();
    //accumulateLeft();
    //PrintResult();

    delete netParams;

    MPI_Finalize();
    return 0;
}
