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

#include <iostream>

using namespace std;

void readTopologyDimmensions(int *m, int *n)
{
    cout << "Define topology dimmensions:" << endl;
    cout << "M: ";
    cin >> *m;
    cout << "N: ";
    cin >> *n;
}