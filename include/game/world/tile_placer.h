#pragma once

#include <string>

namespace farmomatica {

class TilePlacer {
public:
  static void PlaceTile(const std::string &name, int x, int y, int z);
};

} // namespace farmomatica
