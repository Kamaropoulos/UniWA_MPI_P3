/**
 * @file Topology.hpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief Header file for Topology.hpp
 * @version 0.1
 * @date 2019-01-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "NetworkParameters.hpp"

struct TopologyDimmensions
{
    int m;
    int n;
};

class Topology
{
  public:
    Topology(NetworkParameters *netParams);
    void Init();
    int Broadcast(int* data, int size);
    ~Topology();
};
