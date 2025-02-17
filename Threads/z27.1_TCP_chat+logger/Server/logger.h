#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <shared_mutex>

class Logger {
 public:
   Logger();
   ~Logger();

  void inputToLog(const std::string& text);
  std::string getLastString();

 private:
  std::fstream log_;
  std::shared_mutex m_;
};

