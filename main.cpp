#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std::chrono;


#include "dominolinebuilder.h"

int main()
{
    //Ensure that datasetSize is the same as the number of examples in the file
    const unsigned long int datasetSize = 3000;

    //const std::string filepath = "../Dominoes/dominoes-test_data/example/example-input.txt";

    //const std::string filepath = "../Dominoes/dominoes-test_data/10/10-input.txt";
    //const std::string filepath = "../Dominoes/dominoes-test_data/1000/1000-input.txt";
    const std::string filepath = "../Dominoes/dominoes-test_data/3000/3000-input.txt";
    long long totalDuration = 0;
    const int runs = 5;

    //Check the user has inputted the correct datasetSize to prevent program from crashing
    std::string equal;
    std::cout << "Is the number of examples the same as datasetSize? Y/N " << datasetSize << "\n" << filepath;
    std::cin >> equal;

    if (equal == "y" || equal == "Y") {
        for (int i = 0; i <= runs; i++) {
            std::ifstream theInputStream(filepath);
            if (! theInputStream.good()) throw std::invalid_argument("Cannot read from specified file.");

//            auto start = high_resolution_clock::now();
            DominoLineBuilder theDominoLine(datasetSize,theInputStream);
//            auto stop = high_resolution_clock::now();

            double total_single_call_time = 0.0; //Total time for single calls
            int call_count = 0; //Count no. of calls

//            auto start = std::chrono::high_resolution_clock::now();

//            while (theDominoLine.nextRight()) {
//                auto single_call_start = std::chrono::high_resolution_clock::now();

//                //Call nextRight() and measure its performance
//                theDominoLine.nextRight();

//                auto single_call_stop = std::chrono::high_resolution_clock::now();
//                double duration = std::chrono::duration<double, std::micro>(single_call_stop - single_call_start).count(); // Microseconds
//                total_single_call_time += duration; //Accumulate the time
//                call_count++; //Increment the call count
//            }

//            auto stop = std::chrono::high_resolution_clock::now();
//            double total_duration = std::chrono::duration<double, std::micro>(stop - start).count(); // Microseconds

            // Calculate the average time for single calls
//            double average_single_call_time = (call_count > 0) ? total_single_call_time / call_count : 0.0;

            // Output the results
//            std::cout << "Total time: "
//                      << std::fixed << std::setprecision(6)
//                      << total_duration
//                      << " microseconds" << std::endl;

//            std::cout << "Average time taken for single call: "
//                      << std::fixed << std::setprecision(6)
//                      << average_single_call_time
//                      << " microseconds" << std::endl;


            auto start = high_resolution_clock::now();
            while (theDominoLine.nextRight());
            auto stop = high_resolution_clock::now();

            theDominoLine.display(std::cout);

            auto duration = duration_cast<microseconds>(stop - start);

              //Skip the first run and start adding from the second run
              //This is done because the first run is a significant outlier
              if (i > 0) {
                  totalDuration += duration.count();
              }
              //Display current runs duration
              std::cout << "\nTime taken to run: " << duration.count() << " microseconds \n";
        }

        //Calculate and print the average time (excluding the first trial)
        long long avgTime = totalDuration / runs;
        std::cout << "\nAverage time for " << runs << " runs: " << avgTime << " microseconds\n";
    }
}
