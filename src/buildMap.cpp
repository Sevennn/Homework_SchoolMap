#include "buildMap.hpp"
#include <cstring>

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
