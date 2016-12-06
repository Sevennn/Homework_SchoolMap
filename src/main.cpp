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
  walkMap.BuildSmallestMap();
  carMap.BuildSmallestMap();
  while (true) {
    cout << "input one of the following command: " << endl;
    cout << "f : find vertex\ng : guidance\n a : list all vertex \n";
    char c;
    cin >> c;
    switch(c) {
      case 'a':
        ListAll();
        break;
      case 'g':
        Guidance();
        break;
      case 'f':
        SearchFor();
        break;
      default:
        break;
    }
  }
  return 0;
}



