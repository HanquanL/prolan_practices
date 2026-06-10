#include <iostream>

class Graph{
    private:
        int** adj;      // V X V matrix: adj[u][v] == 1 means edge
        int numVertices;

        void dfsHelper(int u, bool* visited) const{
            visited[u] = true;
            std::cout << u << " ";
            for(int v = 0; v < numVertices; ++v){
                if(adj[u][v] == 1 && !visited[v]){
                    dfsHelper(v, visited);    // recurse = use the call stack
                }
            }
        }

    public:
        Graph(int vertices) : numVertices(vertices){
            adj = new int*[numVertices];
            for(int i = 0; i < numVertices; ++i){
                adj[i] = new int[numVertices];
                for(int j = 0; j < numVertices; ++j){
                    adj[i][j] = 0;    // 0 = no edge
                }
            }
        }

        ~Graph(){
            for(int i = 0; i < numVertices; ++i){
                delete[] adj[i];
            }
            delete[] adj;
        }

        void addEdge(int u, int v){
            adj[u][v] = 1;
            adj[v][u] = 1;
        }

        bool hasEdge(int u, int v) const{
            return adj[u][v] == 1;
        }

        void bfs(int start) const{
            bool* visited = new bool[numVertices];
            for(int i = 0; i < numVertices; ++i){
                visited[i] = false;
            }

            int* queue = new int[numVertices];    // array-backed queue
            int head = 0; 
            int tail = 0;

            visited[start] = true;
            queue[tail] = start;
            ++tail;

            std::cout << "BFS from " << start <<": ";
            while(head < tail){
                int u = queue[head];
                ++head;
                std::cout << u << " ";

                for(int v = 0; v < numVertices; ++v){
                    if(adj[u][v] == 1 && !visited[v]){
                        visited[v] = true;
                        queue[tail] = v;
                        ++tail;
                    }
                }
            }
            std::cout << "\n";
            delete[] visited;
            delete[] queue;
        }

        void dfs(int start) const{
            bool* visited = new bool[numVertices];
            for(int i = 0; i < numVertices; ++i){
                visited[i] = false;
            }
            std::cout << "DFS from " << start << ": ";
            dfsHelper(start, visited);
            std::cout << "\n";
            delete[] visited;
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