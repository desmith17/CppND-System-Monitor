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
    std::vector<int> tf {216000,3600,60};
    std::vector<int> t {};
    long sec = seconds;
    while (sec > 0){
        for (int i = 0; i < tf.size(); i++){
            t[i] = floor(sec/tf[i]);
        }
        string tim = std::to_string(t[0]) + ":" + std::to_string(t[1]) + ":" + std::to_string(t[2]);
        return tim;
    }
}