#include <iostream>
#include <stdio.h>
#include <fstream>
#include "buildMap.hpp"
#include "Path.hpp"

#define CONSOLE_VERSION   // This is for Ta
#define SERVER_VERSION
/*
  json command
  {"startpoint":1,"endpoint":10,"passpoint":[2,3,4,5,6],"by":"foot"}

*/

using std::string;
using std::endl;
using std::cin;
using std::cout;
using std::vector;
using std::ifstream;
Digraph walkMap;
Digraph carMap;

void Print(json r, Digraph* temp) {
  json passpoints = r["passpoint"];
  json passways = r["passway"];
  cout << "Started from " << temp->searchVertexByID(r["startpoint"])->siteName << endl;
  json::iterator it1 = passpoints.begin();
  ++it1;
  while (it1 != passpoints.end()) {
    cout << "Next, you should go to " << temp->searchVertexByID(*it1)->siteName << endl;
    it1++;
  }
}
void ListAll() {
  walkMap.listAllVertexes();
}
void Guidance() {
  cout << "Onfoot or Take cars ? [1/0]" << endl;
  bool isOnfoot;
  cin >> isOnfoot;
  Digraph* temp = NULL;

  if (isOnfoot)
    temp = &walkMap;
  else
    temp = &carMap;

    cout << "Input names of Your start point and end point." << endl;
    string start;
    string end;
    cin >> start >> end;
    cout << "Input the points that you want to travel (except for start point and end point)." << endl
    << "[End with eof] : " << endl;
    vector<string>points;
    char* t;
    while (scanf("%s", t) != EOF) {
      //if (t[0] == 'q') break;
      string tmp(t);
      points.push_back(tmp);
    }
    json res = temp->ManageWays(start, points, end);
    Print(res, temp);
}




int main() {
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
#ifdef CONSOLE_VERSION
  while (true) {
    cout << "input one of the following command: " << endl;
    cout << "g : guidance\na : list all vertex \nq : quit\n";
    char c;
    cin >> c;
    if (c == 'q')
      break;
    switch(c) {
      case 'g' :
        Guidance();
        break;
      case 'a' :
        ListAll();
      default:
        break;
    }
  }
#endif

#ifdef SERVER_VERSION
  while (true) {
    string temp;
    cin >> temp;

    json tmp = json::parse(temp);
    Digraph* t = NULL;

    if (tmp["by"] == "foot")
      t = &walkMap;
    else
      t = &carMap;
    vector<string>points;
    json passpoint_vec = tmp["passpoint"];
    string start = t->searchVertexByID(tmp["startpoint"])->siteName;
    string end = t->searchVertexByID(tmp["endpoint"])->siteName;
    json::iterator it1 = passpoint_vec.begin();
    while (it1 != passpoint_vec.end()) {
      points.push_back(t->searchVertexByID(*it1)->siteName);
      it1++;
    }
    cout << t->ManageWays(start, points, end).dump() << endl;
  }
#endif
  return 0;
}



