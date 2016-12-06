#include <iostream>
#include <fstream>
#include "buildMap.hpp"
#include "Path.hpp"

using std::string;
using std::ifstream;

int main() {
  Digraph walkMap;
  Digraph carMap;
  string walkString;
  string carString;
  ifstream walkMapRoot(Path::walkPath);
  ifstream carMapRoot(Path::carPath);
  if (!walkMapRoot.is_open() || !carMapRoot.is_open()) { return false; }
  json walkJson;
  json carJson;
  walkMapRoot >> walkJson;
  carMapRoot >> carJson;
  walkMap.createMap(walkJson);
  carMap.createMap(carJson);
  // walkMap.listAllVertexes();
  return 0;
}
