#include <iostream>
#include <vector>
#include <queue>

class Graph{
    private:
        std::vector<std::vector<int>> adj;
        int numVertices;

        void dfsHelper(int u, std::vector<bool>& visited) const {
            visited[u] = true;
            std::cout << u << " ";
            for(int v : adj[u]){
                if(! visited[v]){
                    dfsHelper(v, visited);
                }
            }
        }
    public:
        Graph(int vertices) : adj(vertices), numVertices(vertices){}

        void addEdge(int u, int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        void bfs(int start) const{
            std::vector<bool> visited(numVertices, false);
            std::queue<int> q;

            visited[start] = true;
            q.push(start);

            std::cout << "BFS from " << start << ": ";
            while(!q.empty()){
                int u = q.front();
                q.pop();
                std::cout << u << " ";

                for(int v : adj[u]){
                    if(!visited[v]){
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            std::cout << "\n";
        }

        void dfs(int start) const{
            std::vector<bool> visited(numVertices, false);
            std::cout << "DFS from " << start << ": ";
            dfsHelper(start, visited);
            std::cout << "\n";
        }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.bfs(0);    // BFS from 0: 0 1 2 3 4
    g.dfs(0);    // DFS from 0: 0 1 3 2 4
}