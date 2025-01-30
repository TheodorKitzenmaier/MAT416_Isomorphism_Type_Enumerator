#include <string>

class SimpleGraph {
private:
	// Number of verticies in G.
	int vertexCount;

	// Edges of G.
	bool** edges;

	// Labels for verticies in G. Optional.
	std::string* vertexLabels;



	// Returns if the given vertex index is valid.
	bool indexValid(int v);

	// Returns a pointer to the boolean representing the edge between vertices <u> and <v>.
	bool* getEdge(int u, int v);



	// Returns a decoded set of edges. Edges decoded assuming a graph of size <V>.
	static bool** decode_edges(bool* edges, int V);

	// Returns an encoded set of edges. Edges encoded assuming a graph of size <V>
	static bool* encode_edges(bool** edges, int V);

public:
	// Creates an empty graph with no verticies and no edges.
	SimpleGraph();

	// Creates a graph with <V> vertices and no edges.
	SimpleGraph(int V);

	// Creates a graph with <V> vertices and edges encoded in <E>.
	SimpleGraph(int V, bool* E);

	// Creates a graph with <V> vertices and edges in <E>
	SimpleGraph(int V, bool** E);

	// Creates a graph with <V> verticies, edges encoded in <E>, and vertex names given by <V_names>.
	SimpleGraph(int V, bool* E, std::string* V_names);

	// Creates a graph with <V> verticies, edges in <E>, and vertex names given by <V_names>.
	SimpleGraph(int V, bool** E, std::string* V_names);

	~SimpleGraph();



	// Resizes the graph. If additional vertices are added, they will have no adjacencies. If vertices are removed, any incident edges will also be removed.
	void resize(int V);



	// Adds an edge between vertices at indicies u and v. Returns if the vertices were already adjacent.
	bool addEdge(int u, int v);

	// Removes the edge between u and v. Returns if the vertices were adjacent before removal.
	bool removeEdge(int u, int v);

	// Returns if the two vertices are adjacent.
	bool isAdjacent(int u, int v);



	// Sets the edges of G using the given edge data.
	void setEdges(bool** E);

	// Sets the edges of G using the given edge encoding.
	void setEncodedEdges(bool* E);

	// Removes all edges from G.
	void removeEdges();



	// Returns a copy of the edges of G.
	bool** getEdges();

	// Returns an encoding of the edges of G.
	bool* encodeEdges();

	// Returns the length of the array which encodes the edges of G.
	int getEncodingLength();



	// Returns a string representation of the graph. Format of "V = {<verticesThe #define directives define the identifier as macro, that is instruct the compiler to replace most successive occurrences of identifier with replacement-list, which will be additionally processed. Exceptions arise from the rules of scanning and replacement. If the identifier is already defined as any type of macro, the program is ill-formed unless the definitions are identical. >}, E = {<edges>}".
	std::string toString();



	// Returns the name of the given vertex, <v>.
	std::string getName(int v);

	// Sets the name of the given vertex, <v>
	void setName(int v, std::string name);
};
