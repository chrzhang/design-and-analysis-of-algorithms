#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Program1.h"

int main(int argc, char *argv[]) {
    std::stringstream sps; // Stream to hold LCS for file or console output
    // Check validity of program call
    if (4 != argc) {
        std::cout << "Run with \'./program1 <filex.txt> <filey.txt>"
            << " <output1.txt>\'" << std::endl;
        return 0;
    }
    // Declare strings to hold what will be read in from the two files
    std::string linex;
    std::string liney;
    // Attempt to open files
    std::ifstream x_file(argv[1]);
    std::ifstream y_file(argv[2]);
    if (x_file.is_open() && y_file.is_open()) {
        std::getline(x_file, linex); // Initialize strings
        std::getline(y_file, liney);
        // Close the files
        x_file.close();
        y_file.close();
    }
    else {
        std::cout << "Unable to open " << argv[1] << " or " << argv[2]
            << std::endl;
        return 0;
    }
    Program1 p(linex, liney); // Initialize an instance of Program1
    // Clock the run-time
    auto start = std::chrono::system_clock::now();
    p.getSubsequence(sps);
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::ofstream outf(argv[3]); // Prepare writing to the output file
    // Write the resulting LCS to file
    if (outf.is_open()) {
	if (linex.length() == 0 || liney.length() == 0) {
		std::cout << "Warning: one of the files is blank." << std::endl;
		outf << "0" << std::endl;
            	// Write the run-time of the algorithm
            	outf << elapsed.count() << " nanoseconds" << std::endl;
	}
        else if ((linex.length() <= 10) && (liney.length() <= 10)) {
            // Write the rows of the matrix
            std::stringstream sms;
            p.writeMatrix(sms);
            outf << sms.str();
            // Write the LCS
            outf << sps.str();
            // Write the run-time of the algorithm
            outf << elapsed.count() << " nanoseconds" << std::endl;
        }
        else {
            // Write the length of the LCS
            outf << p.getLengthLCS() << std::endl;
            // Write the run-time of the algorithm
            outf << elapsed.count() << " nanoseconds" << std::endl;
        }
        outf.close(); // Close the file
    }
    else {
        std::cout << "Unable to open " << argv[3] << " for writing."
            << std::endl;
    }
    return 0;
}
