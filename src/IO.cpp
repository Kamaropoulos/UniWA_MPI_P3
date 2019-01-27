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

#include <iostream>
#include <stdexcept>

#include <vector>
#include <string>

#include <sys/stat.h>

#include <sstream>
#include <fstream>

using namespace std;

void readTopologyDimmensions(int *m, int *n)
{
    cout << "Define topology dimmensions:" << endl;
    cout << "M: ";
    cin >> *m;
    cout << "N: ";
    cin >> *n;
}

/**
 * @brief Check if a file with the given name exists
 * 
 * @param name [in] The name of the file to check
 * @return true The file exists
 * @return false The file doesn't exist
 */
inline bool fileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

/**
 * @brief Decide which filename should be used to read the data from
 * 
 * @param argc [in] The number of command line arguments
 * @param argv [in] The command line arguments
 * @return std::string The filename to use for reading the data
 */
std::string inputFileName(int argc, char **argv)
{
    std::string filename;
    // Check if file name was passed
    switch (argc)
    {
    case 1:
        // No parameter passed, fallback to default filename
        return DEFAULT_FILENAME;
        break;

    case 2:
        // We got one parameter, check if it's an existing file
        filename = argv[1];
        if (fileExists(filename))
        {
            return filename;
        }
        else
        {
            throw std::runtime_error("Could not open file \"" + filename + "\"");
        }

    default:
        throw std::runtime_error("Incorrect command usage!");
        break;
    }
}

/**
 * @brief Determines the source to read from, reads and writes the data to a 2D vector
 * 
 * @param data [out] A pointer to an <std::vector<std::vector<int>> collection to write the data to
 * @param argc [in] The number of command line arguments
 * @param argv [in] The command line arguments
 */
void ReadData(std::vector<int> *data, int argc, char **argv)
{
    std::string filename;

    try
    {
        filename = inputFileName(argc, argv);
    }
    catch (std::exception &e)
    {
        std::cout << "\033[1;31m"
                  << "Error: " << e.what() << "\033[0m"
                  << std::endl;
    }

    // An input file stream used to read data from config.txt.
    std::ifstream inputFile(filename);

    // If the file is opened sucessfully
    if (inputFile.is_open())
    {
        std::string line;

        // While inputFile still has lines, put them on line.
        std::getline(inputFile, line);

        istringstream iss(line);
        
        // A temporary variable to store numbers from the input file.
        int tmpNumber;

        while (iss >> tmpNumber)
        {
            data->push_back(tmpNumber);
        }

        // We are at the end of the file, close it as we won't need it anymore.
        inputFile.close();
    }
}
