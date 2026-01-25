#pragma once
#include <string>

class ILogSinker {
public:
  virtual ~ILogSinker() = default;
  virtual void Log(const std::string &category, const std::string &message) = 0;
};