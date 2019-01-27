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

#pragma once

#include "NetworkParameters.hpp"

#include <vector>

using namespace std;

struct TopologyDimmensions
{
    int m;
    int n;
};

struct Neighbors {
    int up;
    int down;
    int left;
    int right;
};

class Topology
{
  public:
    Topology(NetworkParameters *netParams);
    void Init();
    void Broadcast(int *data, int size);
    void Load(vector<int> data);
    void Scatter(vector<int> data);
    void Send(int* data, int dataCount, int target);
    void Receive(int *data, int dataCount, int source);
    void Barrier();
    Neighbors GetNeighbors();
    void GetCoords(int* coords);
    int getLocalData();
    NetworkParameters *netParams;
    TopologyDimmensions dimmensions;
    Neighbors neighbors;
    ~Topology();
};