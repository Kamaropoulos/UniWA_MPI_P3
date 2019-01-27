#include "Topology.hpp"

#include "mpi.h"

#include <iostream>

using namespace std;

class SumCartesian2DSendRecv
{
  private:
    Topology *topology;
    int result;

  public:
    SumCartesian2DSendRecv(Topology *topology);
    void Compute();
    ~SumCartesian2DSendRecv();
};

SumCartesian2DSendRecv::SumCartesian2DSendRecv(Topology *topology)
{
    this->topology = topology;
}

void SumCartesian2DSendRecv::Compute()
{
    // Get Local Data
    int localData = this->topology->getLocalData();

    // For more than one data per process, sum them here.
    // For now we only have one.
    int localSum = localData;
    int next = localSum;

    Neighbors neighbors = this->topology->GetNeighbors();

    if (neighbors.down >= 0)
    {
        this->topology->Receive(&next, 1, neighbors.down);
        next += localSum;
        localSum = next;
    }

    if (neighbors.up >= 0)
    {
        this->topology->Send(&next, 1, neighbors.up);
    }
    else
    {
        if (neighbors.right >= 0)
        {
            this->topology->Receive(&next, 1, neighbors.right);
            next += localSum;
            localSum = next;
        }
        if (neighbors.left >= 0)
        {
            this->topology->Send(&next, 1, neighbors.left);
        }
        else
        {
            cout << next << endl;
        }
    }
}

SumCartesian2DSendRecv::~SumCartesian2DSendRecv()
{
}
