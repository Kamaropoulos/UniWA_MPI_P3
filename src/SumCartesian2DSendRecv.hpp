#include "Topology.hpp"

class SumCartesian2DSendRecv
{
  public:
    SumCartesian2DSendRecv(Topology *topology);
    int Compute();
    ~SumCartesian2DSendRecv();
};
