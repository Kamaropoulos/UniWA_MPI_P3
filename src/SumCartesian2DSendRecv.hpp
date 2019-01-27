#pragma once

#include "Topology.hpp"

class SumCartesian2DSendRecv
{
  public:
    SumCartesian2DSendRecv(Topology *topology);
    void Compute();
    ~SumCartesian2DSendRecv();
};
