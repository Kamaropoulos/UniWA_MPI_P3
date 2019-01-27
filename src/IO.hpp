/**
 * @file io.hpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief Header file for io.cpp
 * @version 0.1
 * @date 2019-01-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

/**
 * @file io.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief Methods for data I/O (files, stdin/stdout)
 * @version 0.1
 * @date 2019-01-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define DEFAULT_FILENAME "matrix.in"

#include <vector>
#include <string>

using namespace std;

void readTopologyDimmensions(int *m, int *n);

inline bool fileExists(const string &name);

string inputFileName(int argc, char **argv);

void ReadData(vector<int> *data, int argc, char **argv);