/**
 * @file NetworkParameters.hpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief Header file fro NetworkParameters.cpp
 * @version 0.1
 * @date 2019-01-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

class NetworkParameters
{
  public:
    NetworkParameters(int argc, char **argv);
    ~NetworkParameters();
    int getCurrentRank();
    int getProcessesNumber();
};