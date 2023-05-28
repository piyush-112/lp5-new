//bfs
/*
#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;
const int max = 100000;
vector<vector<int>> graph;
void bfs(vector<vector<int>> &graph, int start, vector<bool> &visited) {
queue<int> q;
q.push(start);
visited[start] = true;
#pragma omp parallel
{
#pragma omp single
{
while (!q.empty()) {
int vertex = q.front();
q.pop();
cout<<vertex<<" ";
#pragma omp task firstprivate(vertex)
{
for (int neighbor : graph[vertex]) {
if (!visited[neighbor]) {
q.push(neighbor);
visited[neighbor] = true;
#pragma omp task
bfs(graph, neighbor, visited);
}
}
}
}
}
}
}
void parallel_bfs(vector<vector<int>> &graph, int start) {
vector<bool> visited(graph.size(), false);
bfs(graph, start, visited);
}
int main() {
int n, m, start_node;
cout << "Enter no. of Node, no. of Edges, and Starting Node of graph:\n";
cin >> n >> m >> start_node;
// Initialize graph vector
graph.resize(n + 1);
cout << "Enter pair of node and edges:\n";
for (int i = 0; i < m; i++) {
int u, v;
cin >> u >> v;
graph[u].push_back(v);
graph[v].push_back(u);
}
parallel_bfs(graph, start_node);
return 0;
}
*/


#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

// Structure to represent a graph
struct Graph
{
    int vertices;
    vector<vector<int>> adjList;
};

// Function to add an edge to the graph
void addEdge(Graph &graph, int src, int dest)
{
    graph.adjList[src].push_back(dest);
}

// Parallel DFS function
void parallelDFS(const Graph &graph, int startVertex, vector<bool> &visited)
{
    stack<int> stk;
    stk.push(startVertex);

    while (!stk.empty())
    {
        int currentVertex = stk.top();
        stk.pop();

        if (!visited[currentVertex])
        {
#pragma omp critical
            {
                if (!visited[currentVertex])
                {
                    visited[currentVertex] = true;
                    cout << "Visited vertex: " << currentVertex << endl;
                }
            }

#pragma omp parallel for
            for (int i = 0; i < graph.adjList[currentVertex].size(); ++i)
            {
                int neighbor = graph.adjList[currentVertex][i];
                stk.push(neighbor);
            }
        }
    }
}

// Driver program to test the parallel DFS
int main()
{
    int numVertices = 7;
    Graph graph;
    graph.vertices = numVertices;
    graph.adjList.resize(numVertices);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);

    vector<bool> visited(numVertices, false);

    parallelDFS(graph, 0, visited);

    return 0;
}