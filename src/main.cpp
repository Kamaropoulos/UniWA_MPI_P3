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

    vector<int> data;
    
    // Read data
    ifRoot(netParams->getCurrentRank(), {
        ReadData(&data, argc, argv);
        for(int i = 0; i < data.size(); i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    });

    // Scatter the data across the topology processes
    Topology->LoadData(data);

    

    //ScatterData();
    //accumulateTop();
    //accumulateLeft();
    //PrintResult();
    //accumulateTop();
    //accumulateLeft();
    //PrintResult();

    delete netParams;
    delete topology;

    MPI_Finalize();
    return 0;
}
