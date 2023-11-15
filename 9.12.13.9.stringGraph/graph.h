#include <string>
#define SIZE 20

class Graph {
 public:    
    Graph();
    
    void addPerson(const std::string& person);
    void addLink(const std::string& p1, const std::string& p2, int weight = 1);
    void depth(std::string& start_name);
    void width(const std::string& start_name);  
    void width(const std::string& start_name, int linkcount);  
    void PrintVertexex();
    void FindPairs(int handshake);
    int findMinWayDFS(int from, int to);
    
    
 private:
    void inner(int current,int to, bool visited[], int& min, int currentDistance);
 
    void depthInner(std::string& current, bool visited[]);
    bool edgeExists(int index1, int index2);
    
    int find(const std::string& person);
 
 
    std::string persons[SIZE]; //хранилище вершин
    int matrix[SIZE][SIZE];
    
    int persons_count;
    
};

