#include "buildMap.hpp"
#include <cstring>

using std::endl;
using std::cout;

Digraph::Digraph() : firstVertex(nullptr), vertexSize(0), edgeSize(0) {
  memset(digraghMatrix, 0, sizeof(digraghMatrix));
}

Digraph::~Digraph() { this->clearDigraph(); }

bool Digraph::createVertex(const int& vertexID, const string& name, const string& information) {
  Vertex *tempVertex = this->firstVertex;
  while (tempVertex) {
    if (vertexID == tempVertex->siteID) { return false; }  // check ID
    tempVertex = tempVertex->nextVertex;
  }
  if (this->searchVertexByName(name) != nullptr) { return false; }
  ++(this->vertexSize);
  Vertex *currentVertex = new Vertex(nullptr, nullptr, vertexID, name, information);
  if (this->firstVertex == nullptr) {  // create the first vertex
    this->firstVertex = currentVertex;
  } else {  // create the other vertex
    Vertex *tempVertex = this->firstVertex;
    while (tempVertex->nextVertex != nullptr) {
      tempVertex = tempVertex->nextVertex;
    }
    tempVertex->nextVertex = currentVertex;
  }
  return true;
}

bool Digraph::createEdge(const int& edgeID, const string& start, const string& end, const int& length) {
  Vertex *tempVertex = this->firstVertex;
  Edge *tempEdge = nullptr;
  while (tempVertex != nullptr) {
    tempEdge = tempVertex->firstEdge;
    while(tempEdge != nullptr) {
      if (edgeID == tempEdge->pathID) { return false; }  // check ID
      tempEdge = tempEdge->nextEdge;
    }
    tempVertex = tempVertex->nextVertex;
  }
  if (start == end || length <= 0) { return false; }  // check some error
  Vertex *startVertex = searchVertexByName(start);
  Vertex *endVertex = searchVertexByName(end);
  if (startVertex == nullptr || endVertex == nullptr) { return false; }  // check whether the two vectexs have been created
  Edge *checkEdge = startVertex->firstEdge;
  while (checkEdge != nullptr) {  // check whether the edge has been created
    if (checkEdge->endPoint->siteName == end) { return false; }
    checkEdge = checkEdge->nextEdge;
  }

  // build DigraghList
  ++(this->edgeSize);
  Edge *startToEnd = new Edge(endVertex, nullptr, edgeID, length);
  Edge *endToStart = new Edge(startVertex, nullptr, edgeID, length);
  if (startVertex->firstEdge == nullptr) {  // startToEnd
    startVertex->firstEdge = startToEnd;
  } else {
    tempEdge = startVertex->firstEdge;
    while (tempEdge->nextEdge != nullptr) {
      tempEdge = tempEdge->nextEdge;
    }
    tempEdge->nextEdge = startToEnd;
  }
  if (endVertex->firstEdge == nullptr) {  // endToStart
    endVertex->firstEdge = endToStart;
  } else {
    tempEdge = endVertex->firstEdge;
    while (tempEdge->nextEdge != nullptr) {
      tempEdge = tempEdge->nextEdge;
    }
    tempEdge->nextEdge = endToStart;
  }

  // build DigraghMatrix
  this->digraghMatrix[startVertex->siteID][endVertex->siteID]
  = this->digraghMatrix[endVertex->siteID][startVertex->siteID] = length;
  return true;
}

Vertex* Digraph::searchVertexByID(const int& ID) {
  Vertex *currentVertex = this->firstVertex;
  while (currentVertex != nullptr) {
    if (currentVertex->siteID == ID) { return currentVertex; }
    currentVertex = currentVertex->nextVertex;
  }
  return nullptr;
}

Vertex* Digraph::searchVertexByName(const string& name) {
  Vertex *currentVertex = this->firstVertex;
  while (currentVertex != nullptr) {
    if (currentVertex->siteName == name) { return currentVertex; }
    currentVertex = currentVertex->nextVertex;
  }
  return nullptr;
}

void Digraph::listAllVertexes() {
  Vertex *currentVertex = this->firstVertex;
  while (currentVertex != nullptr) {
    cout << "Name: " << currentVertex->siteName << endl;
    cout << "Info: " << currentVertex->siteInformation << endl << endl;
    currentVertex = currentVertex->nextVertex;
  }
}

void Digraph::createMap(const json& myJson) {
  for (int i = 0; i < myJson["Vertexes"].size(); ++i) {
    createVertex(myJson["Vertexes"][i]["VertexID"], myJson["Vertexes"][i]["VertexName"], myJson["Vertexes"][i]["VertexInfo"]);
  }
  for (int i = 0; i < myJson["Edges"].size(); ++i) {
    createEdge(myJson["Edges"][i]["EdgeID"], myJson["Edges"][i]["Start"], myJson["Edges"][i]["End"], myJson["Edges"][i]["pathLength"]);
  }
}

void Digraph::clearDigraph() {
  Vertex *tempVertex = nullptr;
  Edge *tempEdge = nullptr;
  while (this->firstVertex != nullptr) {
    // delete edge
    while(this->firstVertex->firstEdge) {
      tempEdge = this->firstVertex->firstEdge;
      this->firstVertex->firstEdge = tempEdge->nextEdge;
      delete tempEdge;
    }
    // delete vertex
    tempVertex = this->firstVertex;
    this->firstVertex = tempVertex->nextVertex;
    delete tempVertex;
  }
}

void Digraph::BuildSmallestMap() {
  // these vector are private
  for (int i = 0; i < 20; i++) {
    vector<int> p1;
    vector<int> p2;
    dismap.push_back(p1);
    path.push_back(p2);
    for (int j = 0; j < 20; j++) {
      if (digraghMatrix[i][j] == 0)
        dismap[i].push_back(1000);
      else
        dismap[i].push_back(digraghMatrix[i][j]);
      path[i].push_back(-1);
    }
  }
  for (int k = 0; k < 20; k++)
    for (int i = 0; i < 20; i++)
      for (int j = 0; j < 20; j++) {
        if (dismap[i][j] > dismap[i][k]+dismap[k][j]) {
          dismap[i][j] = dismap[i][k]+dismap[k][j];
          path[i][j] = k;
        }
      }
}


void Digraph::FindWays(int beg, int end, vector<int> &way) {
  if (path[beg][end] >= 0) {
    FindWays(beg, path[beg][end], way);
    FindWays(path[beg][end], end, way);
  } else {
    way.push_back(end);
  }
}



void Digraph::ManageWays(string start, vector<string> points, string end, bool isOnfoot) {
  BuildSmallestMap();
  vector<int>destinations;
  Vertex* s = searchVertexByName(start);
  if (s == NULL) {
    cout << start <<" : No such a start!" << endl;
    return;
  }
  Vertex* e = searchVertexByName(end);
  if (e == NULL) {
    cout << end <<" : No such a end!" << endl;
    return;
  }
  int start_, end_;
  json result;
  start_ = s->siteID;
  end_ = e->siteID;
  result["startpoint"] = start_;
  result["endpoint"] = end_;
  for (int i = 0; i < points.size(); i++) {
    Vertex* temp = searchVertexByName(points[i]);
    if (temp == NULL) {
      cout << points[i] <<" : Is it really a right point ?" << endl;
      return;
    }
    destinations.push_back(temp->siteID);
  }
  vector<int>passpoint;
  passpoint.push_back(start_);
  CreateOrder(start_, end_, passpoint, destinations);
  vector<int>passway;
  CreateWay(passpoint, passway);
  json p_vec(passpoint);
  json w_vec(passway);
  result["passpoint"] = p_vec;
  result["passway"] = w_vec;
  cout << result.dump() << endl;;
}

void Digraph::CreateOrder(int start, int end, vector<int> &passpoint, vector<int> destinations) {
  int t_start = start;
  while (destinations.size() > 0) {
    int small = 1000;
    int small_index = -1;
    vector<int>::iterator era;
    for (auto i = destinations.begin(); i != destinations.end(); i++) {
      if (dismap[t_start][*i] < small) {
        small = dismap[t_start][*i];
        small_index = *i;
        era = i;
      }
    }
    FindWays(t_start, small_index, passpoint);
    destinations.erase(era);
    t_start = small_index;
  }
  FindWays(t_start, end, passpoint);
}


void Digraph::CreateWay(vector<int> p, vector<int> &way) {
  for (int i = 0; i < p.size()-1; i++) {
    Vertex* q = searchVertexByID(p[i]);
    Edge* t = q->firstEdge;
    while (t) {
      if (t->endPoint->siteID == p[i+1])
        way.push_back(t->pathID);
      t = t->nextEdge;
    }
  }
}
