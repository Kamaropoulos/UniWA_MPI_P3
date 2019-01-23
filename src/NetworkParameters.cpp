/**
 * @file NetworkParameters.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief Getting and storing the MPI parameters
 * @version 0.1
 * @date 2019-01-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "mpi.h"

class NetworkParameters
{
  private:
    int processesNumber;
    int currentProcessRank;
    int currentProcessArgc;
    char **currentProcessArgv;

  public:
    NetworkParameters(int argc, char **argv);
    ~NetworkParameters();
    int getCurrentRank();
    int getProcessesNumber();
};

NetworkParameters::NetworkParameters(int argc, char **argv)
{
    this->currentProcessArgc = argc;
    this->currentProcessArgv = argv;
    MPI_Init(&(this->currentProcessArgc), &(this->currentProcessArgv));
    MPI_Comm_rank(MPI_COMM_WORLD, &(this->currentProcessRank));
    MPI_Comm_size(MPI_COMM_WORLD, &(this->processesNumber));
}

int NetworkParameters::getCurrentRank()
{
    return this->currentProcessRank;
}

int NetworkParameters::getProcessesNumber()
{
    return this->processesNumber;
}

NetworkParameters::~NetworkParameters()
{
}
