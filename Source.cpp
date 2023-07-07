#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Edge
{
public:
	int start;
	int end;
	int weight;

	Edge() {
		this->end = 0;
		this->start = 0;
		this->weight = 0;
	};
	Edge(int a, int b, int c) { 
		this->end = b;
		this->start = a;
		this->weight = c;
	}
	Edge(int& start, int& end, int &weight) 
	{
		this->start = start;
		this->end = end;
		this->weight = weight;
	}
	void print() 
	{
		cout << start << "\t" << end << "\t" << weight << endl;
	}
};

class Graph
{
    vector<Edge> graph;
    int num_edges;
    int num_vertices;
    vector<Edge>::iterator it;
public:
    
    Graph()
    {
        this->num_edges = 0;
        this->num_vertices = 0;
    }
    Graph(Graph& other)
    {
        this->num_edges = other.size();
        this->num_vertices = other.num_vertices;
        for (int i = 0; i < num_edges; i++)
        {
            this->graph.push_back(other.graph[i]);
        }
    }
    Graph& operator=(const Graph& other)
    {
        this->num_edges = other.num_edges;
        this->num_vertices = other.num_vertices;
        if (this != &other) 
        {
            num_vertices = other.num_vertices;
            graph.clear(); 
            for (const auto& edge : other.graph) {
                graph.push_back(edge);
            }
        }
        return *this;
    }
    Edge operator[](int i) const
    {
        return graph[i];
    }
    bool empty() const { return graph.empty(); }
    int size() const { return graph.size(); }
    void erase(size_t idx)
    {
        this->num_vertices--;
        this->num_edges--;
        it = graph.begin();
        advance(it, idx);
        graph.erase(it);
    }
    void add_edge(const Edge& e)
    {
        this->num_vertices++;
        this->num_edges++;
        graph.push_back(e);
    }
    void add_edge(Edge&& e)
    {
        this->num_vertices++;
        this->num_edges++;
        graph.push_back(move(e));
    }
    int NumOfVertices() const
    {
        int res = graph[0].start;
        for (size_t i = 0; i < this->size(); i++)
        {
            if (res < graph[i].start || res < graph[i].end) 
            {
                if (res < graph[i].start) res = this->graph[i].start;
                else if (res < graph[i].end) res = this->graph[i].end;
            }
        }
        return res;
    }
    Edge find_Min()
    {
        Edge res = graph[0];
        for (size_t i = 1; i < graph.size(); i++)
        {
            if (res.weight > graph[i].weight) res = graph[i];
        }
        return res;
    }
    void Print() const
    {
        for (size_t i = 0; i < graph.size(); i++)
        {
            cout << graph[i].start << " " << graph[i].end << " " << graph[i].weight << endl;
        }
    }
    int FindMinIndx() 
    {
        int j = 0;
        Edge res = graph[0];
        for (size_t i = 1; i < graph.size(); i++)
        {
            if (res.weight > graph[i].weight) {
                res = graph[i];
                j = i;
            }
        }
        return j;
    }
    void Prim()
    {
        Graph res;
        Graph g1;
        g1 = *this;
        Edge min_edge;
        min_edge = g1.find_Min();
        res.add_edge(min_edge);
        g1.erase(g1.FindMinIndx());
        while (!g1.empty())
        {
            bool adj_edge = true;
            min_edge = g1.find_Min();
            for (size_t i = 0; i < res.num_edges; i++)
            {
                if (res[i].end == min_edge.end || res[i].start == min_edge.end)
                {
                    for (size_t j = 0; j < res.num_edges; j++)
                    {
                        if (res[j].end == min_edge.start || res[j].start == min_edge.start && j != i)
                        {
                            adj_edge = false;
                        }
                    }
                }
            }
            if (adj_edge)
            {
                res.add_edge(min_edge);
            }
            g1.erase(g1.FindMinIndx());
        }
        this->graph = res.graph;
    }
    int find(int* parent, int i) const {
        if (parent[i] == i) {
            return i;
        }
        return find(parent, parent[i]);
    }
    void Kruskal() {
        Graph res;
        sort(graph.begin(), graph.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
            });
        int* parent = new int[num_vertices + 1];
        for (int i = 1; i <= num_vertices; i++) {
            parent[i] = i;
        }
        for (int i = 0; i < num_edges; i++) {
            int x = find(parent, graph[i].start);
            int y = find(parent, graph[i].end);
            if (x != y) {
                res.add_edge(graph[i]);
                parent[x] = y;
            }
        }
        delete[] parent;
        this->graph = res.graph;
    }
    friend istream& operator>>(istream& ustream, Graph& g);
    friend ostream& operator<<(ostream& os, const Graph& g);
};

ostream& operator<<(ostream& os, const Graph& g)
{
    os << "Количество вершин: " << g.NumOfVertices() << "\n";
    os << "Количество ребер: " << g.size() << "\n";
    os << "Список смежности: " << "\n";
    for (size_t i = 0; i < g.size(); i++)
    {
        os << g.graph[i].start << " " << g.graph[i].end << " " << g.graph[i].weight << "\n";
    }
    return os;
}

istream& operator>>(istream& ustream, Graph& g) {
	if (typeid(ustream) == typeid(ifstream)) {
		ustream >> g.num_edges;
		ustream >> g.num_vertices;
		g.graph.resize(g.size());
		for (int i = 0; i < g.size(); i++) {
			int u, v, w;
            ustream >> u >> v >> w;
            g.graph[i].start = u;
            g.graph[i].end = v;
            g.graph[i].weight = w;
		}
	}
	else {
		ustream >> g.num_vertices;
		ustream >> g.num_edges;
		g.graph.resize(g.num_edges);
		for (int i = 0; i < g.size(); i++) {
            int u, v, w;
            ustream >> u >> v >> w;
            g.graph[i].start = u;
            g.graph[i].end = v;
            g.graph[i].weight = w;
		}
	}
	return ustream;
}

int main()
{
    setlocale(LC_ALL, "russian");
    Graph test;
    fstream fs;
    fs.open("test1.txt", fstream::in | fstream::out);
    if (fs.is_open()) 
    {
        fs >> test;
    }
    cout << test;
    fs.close();
    test.Prim();
    cout << test;
    fs.open("res.txt", fstream::in | fstream::out);
    if (fs.is_open())
    {
        fs << test;
    }
    fs.close();
	return 0;
}