#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using std::string;
using std::vector;

struct Vertex;

struct Edge {
  Vertex *endPoint;
  Edge *nextEdge;
  int pathLength;
  int pathID;
  Edge(Vertex *endpoint = nullptr, Edge *nextedge = nullptr, int ID = 0, int length = 0)
       : endPoint(endpoint), nextEdge(nextedge), pathLength(length), pathID(ID) {}
};

struct Vertex {
  Edge *firstEdge;
  Vertex *nextVertex;
  int siteID;
  string siteName;
  string siteInformation;
  Vertex(Edge *firstedge = nullptr, Vertex *nextvertex = nullptr,
         int ID = 0, string name = "", string information = "")
         : firstEdge(firstedge), nextVertex(nextvertex),
           siteID(ID), siteName(name), siteInformation(information) {}
};

class Digraph {
  private:
    Vertex *firstVertex;
    int digraghMatrix[20][20];
    vector<vector<int> >path;
    vector<vector<int> >dismap;
    int vertexSize;
    int edgeSize;
  public:
    Digraph();
    ~Digraph();
    bool createVertex(const int& vertexID, const string& name, const string& information);
    bool createEdge(const int& edgeID, const string& start, const string& end, const int& length);
    Vertex* searchVertexByID(const int& ID);
    Vertex* searchVertexByName(const string& name);
    void createMap(const json& myJson);
    void clearDigraph();
    void BuildSmallestMap();
    void FindWays(int beg, int end, vector<int> &way);
    void ManageWays(string start, vector<string>points, string end, bool isOnfoot);
    void CreateOrder(int start, int end, vector<int> &passpoint, vector<int> des);
    void CreateWay(vector<int>p, vector<int> &way);
};
