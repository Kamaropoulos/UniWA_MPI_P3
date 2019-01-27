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

    // int* coords = new int[2];
    // this->topology->GetCoords(coords);
    // int myRank = this->topology->netParams->getCurrentRank();
    // cout << "Process " << myRank << ": " << coords[0] << "," << coords[1] << endl;

    // cout << "U=" << this->topology->neighbors.up << " D=" << this->topology->neighbors.down << " L=" << this->topology->neighbors.left << " R=" << this->topology->neighbors.right << endl;

    Neighbors neighbors = this->topology->GetNeighbors();
    // cout << "U=" << neighbors.up << " D=" << neighbors.down << " L=" << neighbors.left << " R=" << neighbors.right << endl;



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

    // for (int i = 0; i < this->topology->dimmensions.m; i++)
    // {
    //     if (this->topology->neighbors.down == MPI_PROC_NULL)
    //     {
    //         this->topology->Send(&next, 1, this->topology->neighbors.up);
    //     }
    //     else if (this->topology->neighbors.up == MPI_PROC_NULL)
    //     {
    //         this->topology->Receive(&next, 1, this->topology->neighbors.down);
    //     }
    //     else
    //     {
    //         this->topology->Send(&next, 1, this->topology->neighbors.up);
    //         this->topology->Receive(&next, 1, this->topology->neighbors.down);
    //         next += localSum;
    //     }
    // }

    // // cout << "." << endl;
    // this->topology->Barrier();

    // localSum = next;

    // for (int i = 0; i < this->topology->dimmensions.n; i++)
    // {
    //     if (this->topology->neighbors.left >= 0)
    //     {
    //         this->topology->Send(&next, 1, this->topology->neighbors.left);
    //     }

    //     if (this->topology->neighbors.right >= 0)
    //     {
    //         this->topology->Receive(&next, 1, this->topology->neighbors.right);
    //         next += localSum;
    //     }
    // }

    // if (this->topology->netParams->getCurrentRank() == 0)
    // {
    //     cout << next << endl;
    // }

    // return 0;
}

SumCartesian2DSendRecv::~SumCartesian2DSendRecv()
{
}
