#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Program2.h"

int main(int argc, char * argv[]) {
    // Check the validity of program call
    if (4 != argc) {
        std::cout << "Run with \'./program2 <filex.txt> <filey.txt>"
            << " <output2.txt>\'" << std::endl;
        return 0;
    }
    // Declare strings to hold what's read in from the files
    std::string linex;
    std::string liney;
    // Try to open files
    std::ifstream x_file(argv[1]);
    std::ifstream y_file(argv[2]);
    if (x_file.is_open() && y_file.is_open()) {
        std::getline(x_file, linex); // Initialize strings
        std::getline(y_file, liney);
	if (linex.length() == 0 || liney.length() == 0) {
		std::cout << "Warning: one of the files is blank." << std::endl;
	}
        // Close the files
        x_file.close();
        y_file.close();
    }
    else {
        std::cout << "Unable to open " << argv[1] << " or " << argv[2]
            << std::endl;
        return 0;
    }
    Program2 p(linex, liney); // Initialize an instance of Program2
    // Clock the run-time
    auto start = std::chrono::system_clock::now();
    int length = p.lengthLCS(0, 0); // Found the length of the LCS
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::ofstream outf(argv[3]);
    // Write the length of the resulting LCS to file
    if (outf.is_open()) {
        outf << length;
        // Write the run-time
        outf << std::endl << elapsed.count() << " nanoseconds" << std::endl;
        outf.close();
    }
    else {
        std::cout << "Unable to open " << argv[3] << " for writing."
            << std::endl; 
    }
    return 0;
}
