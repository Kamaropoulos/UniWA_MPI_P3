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

#include <iostream>

using namespace std;

struct TopologyDimmensions {
    int m;
    int n;
};

class Topology
{
private:
    TopologyDimmensions dimmensions;
    NetworkParameters *netParams;

public:
    Topology(NetworkParameters* netParams);
    ~Topology();
};

Topology::Topology(NetworkParameters* netParams)
{
    this->netParams = netParams;
    // Get dimmensions from the user
    ifRoot(netParams->getCurrentRank(), {
        readTopologyDimmensions(&(dimmensions.m), &(dimmensions.n));
        cout << "m: " << dimmensions.m << " n: " << dimmensions.n << endl;
    });
}

Topology::~Topology()
{
}
