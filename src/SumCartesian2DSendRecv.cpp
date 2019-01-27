#include "Topology.hpp"

class SumCartesian2DSendRecv
{
  private:
    Topology *topology;

  public:
    SumCartesian2DSendRecv(Topology *topology);
    int Compute();
    ~SumCartesian2DSendRecv();
};

SumCartesian2DSendRecv::SumCartesian2DSendRecv(Topology *topology)
{
    this->topology = topology;
}

int SumCartesian2DSendRecv::Compute()
{
    // Get Local Data
    int localData = topology->getLocalData();

    // For more than one data per process, sum them here.
    // For now we only have one.
    int LocalSum = localData;
}

SumCartesian2DSendRecv::~SumCartesian2DSendRecv()
{
}
