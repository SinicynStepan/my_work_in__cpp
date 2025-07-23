#include <locale.h>
#include <iostream>

struct Graph
{
    int n;
    bool **adj_matrix;

    Graph(int num_vertices)
    {
        this->n = num_vertices;
        this->adj_matrix = new bool *[this->n];

        for (int i = 0; i < this->n; i++)
        {
            this->adj_matrix[i] = new bool[this->n];
            for (unsigned int j = 0; j < this->n; j++)
                this->adj_matrix[i][j] = false;
        }
    }
    Graph(const Graph &other)
    {
        this->n = other.n;
        this->adj_matrix = new bool *[this->n];

        for (unsigned int i = 0; i < this->n; i++)
        {
            this->adj_matrix[i] = new bool[this->n];
            for (unsigned int j = 0; j < this->n; j++)
                this->adj_matrix[i][j] = other.adj_matrix[i][j];
        }
    }
    ~Graph()
    {
        for (int i = 0; i < this->n; i++)
            delete[] this->adj_matrix[i];
        delete this->adj_matrix;
    }
};

void dfs(int node, Graph g, bool *visited)
{
    visited[node] = true;
    for (int k = 0; k < g.n; k++)
        if (g.adj_matrix[node][k] == true && !visited[k])
            dfs(k, g, visited);
}

int count_components_complement(Graph G)
{
    Graph complement_graph(G);

    for (int i = 0; i < G.n; i++)
        for (int j = 0; j < G.n; j++)
        {
            if (i == j)
                continue;
            else if (G.adj_matrix[i][j] == false)
            {
                complement_graph.adj_matrix[i][j] = true;
                complement_graph.adj_matrix[j][i] = true;
            }
            else
            {
                complement_graph.adj_matrix[i][j] = false;
                complement_graph.adj_matrix[j][i] = false;
            }
        }

    bool *visited = new bool[G.n];
    for (int i = 0; i < G.n; i++)
        visited[i] = false;
    int count = 0;
    for (int i = 0; i < G.n; i++)
        if (!visited[i])
        {
            dfs(i, complement_graph, visited);
            count++;
        }

    delete[] visited;

    return count;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n, m;
    std::cout << "Введите количество вершин (n): ";
    std::cin >> n;
    std::cout << std::endl
              << "Введите количество ребер (m): ";
    std::cin >> m;
    if (n <= 0 || m < 0)
        std::cout << "Некорректное количество вершин или рёбер." << std::endl;

    Graph graph(n);

    std::cout << "Введите ребра (u v), где u и v - номера вершин (от 0 до n-1):" << std::endl;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        if (u >= 0 && u < n && v >= 0 && v < n)
        {
            graph.adj_matrix[u][v] = true;
            graph.adj_matrix[v][u] = true;
        }
        else
        {
            std::cout << "Некорректный ввод ребра. Номера вершин должны быть от 0 до " << n - 1;
            i--;
        }
    }

    int components = count_components_complement(graph);
    std::cout << "Количество компонент связности в дополнении графа: " << components;

    return 0;
}
