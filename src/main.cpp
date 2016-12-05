#include <iostream>
#include "buildMap.hpp"

using namespace std;

int main() {
	Digraph schoolMap;
	string name1 = "慎思园";
	string name2 = "至善园";
  string name3 = "明德园0";
  string name4 = "明德园1";
  string name5 = "明德园2";
  string name6 = "明德园3";
  string name7 = "明德园4";
  string name8 = "明德园5";
	string info1 = "宿舍";
	string info2 = "宿舍";
	schoolMap.createVertex(name1, info1);
  schoolMap.createVertex(name2, info2);
  schoolMap.createVertex(name3, info2);
  schoolMap.createVertex(name4, info2);
  schoolMap.createVertex(name5, info2);
  schoolMap.createVertex(name6, info2);
  schoolMap.createVertex(name7, info2);
  schoolMap.createVertex(name8, info2);
  schoolMap.createEdge(name1, name2, 3);
  schoolMap.createEdge(name1, name3, 5);
  schoolMap.createEdge(name2, name3, 7);
  schoolMap.createEdge(name2, name5, 9);
  schoolMap.createEdge(name3, name4, 2);
  schoolMap.createEdge(name5, name8, 7);
  schoolMap.createEdge(name4, name8, 11);
  schoolMap.createEdge(name1, name7, 15);
  schoolMap.createEdge(name6, name7, 15);
  vector<string>p;
  p.push_back("明德园0");
  p.push_back("明德园1");
  p.push_back("明德园2");
  p.push_back("明德园5");  
  schoolMap.ManageWays("慎思园", p, "至善园", 0);
	return 0;
}
