#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
//MemUtil = ((memtot - (memfree + buffer + cached))/memtot)*100
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  long memtot, memfree, buffers, cached, shmem, sreclaimable;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':',' ');
      //std::replace(line.begin(), line.end(), 'kB',' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          memtot = stoi(value);
        }
        if (key == "MemFree") {
          //std::replace(value.begin(), value.end(), 'kb', ' ');
          memfree = stoi(value);
        }
        if (key == "Buffers") {
          //std::replace(value.begin(), value.end(), 'kB', ' ');
          buffers = stoi(value);
        }
        if (key == "Cached") {
          //std::replace(value.begin(), value.end(), 'kB', ' ');
          cached = stoi(value);
        }
        if (key == "Shmem") {
          //std::replace(value.begin(), value.end(), 'kB', ' ');
          shmem = stoi(value);
        }
        if (key == "SReclaimable") {
          //std::replace(value.begin(), value.end(), 'kB', ' ');
          sreclaimable = stoi(value);
        }
      }
    }
  }
  return ((memtot-(memfree + buffers + (cached + sreclaimable - shmem)))/memtot)*100; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime, idletime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
  }
  return stol(uptime); 
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string line;
  string kType,kUser,kNice,kSystem,kIdle,kIOwait,kIRQ,kSoftIRQ,kSteal,kGuest,kGuestNice;
  std::ifstream stream(kProcDirectory + kStatFilename);
  std::getline(stream, line);
  std::istringstream linestream(line);
  linestream >> kType >> kUser >> kNice >> kSystem >> kIdle>> kIOwait >> kIRQ >> kSoftIRQ >> kSteal >> kGuest>> kGuestNice;

  return stol(kUser)+stol(kNice)+stol(kSystem)+stol(kIdle)+stol(kIOwait)+stol(kIRQ)+stol(kSoftIRQ)+stol(kSteal)+stol(kGuest)+stol(kGuest); 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key;
  string value;
  string line;
  long tproc;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          tproc = stoi(value);
        }
      }
    }
  }
  return tproc; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key;
  string value;
  string line;
  long rproc;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          rproc = stoi(value);
        }
      }
    }
  }
  return rproc; 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
