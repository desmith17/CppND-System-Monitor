#include <string>
#include <vector>
#include <cmath>

#include "format.h"

using std::string;


// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    std::vector<int> tf {3600,60,1};    //denominator values in seconds for hours, minutes, and seconds
    std::vector<int> t {};    //vector to store integer values for hour, minutes and seconds
    long sec = seconds;
    while (sec > 0){                          
        for (int i = 0; i <= 2; i++){             //parse through the tf vector
            t[i] = int(floor(sec/tf[i]));         //round down the hour/minute/second value and convert double to an integer
            sec -= t[i]*tf[i];                    //remove calculate time placement value from sec
        }        
    }
return std::to_string(t[0]) + ":" + std::to_string(t[1]) + ":" + std::to_string(t[2]); //return HH:MM:SS values in string format
}
