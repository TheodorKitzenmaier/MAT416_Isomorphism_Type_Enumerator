#include "graph.h"
#include <string>
#include <exception>
#include <stdexcept>

// Macro to loop over edges in G.
#define FOR_EDGES(size, exec1, exec2) for (int i = 0; i < size - 1; i++) { exec1 for (int j = 0; j < size - 1 - i; j++) { exec2 } }

bool SimpleGraph::indexValid(int v) {
	return v < vertexCount && v >= 0;
}

bool* SimpleGraph::getEdge(int u, int v) {
	if (!indexValid(u))
		throw std::runtime_error(("Invalid index u = " + std::to_string(u)).c_str());

	if (!indexValid(v))
		throw std::runtime_error(("Invalid index v = " + std::to_string(v)).c_str());

	if (u == v)
		throw std::runtime_error("Vertices can not be adjacent to themselves");

	return edges[std::min(u, v)] + std::max(u, v) - std::min(u, v) - 1;
}



bool** SimpleGraph::decode_edges(bool* edges, int V) {
	bool** decoded = new bool*[V - 1];

	FOR_EDGES(V,
		decoded[i] = new bool[V - 1 - i];,
		decoded[i][j] = *edges;
		edges++;)

	return decoded;
}

bool* SimpleGraph::encode_edges(bool** edges, int V) {
	// Two pointers, one to track the head, other to traverse the array.
	int len = (V * V - V) / 2;
	bool* encoded = new bool[len];
	bool* cpy = encoded;

	FOR_EDGES(V,
		,
		*cpy = edges[i][j];
		cpy++;)

	return encoded;
}



SimpleGraph::SimpleGraph() {
	vertexCount = 0;
	edges = new bool*[0];
	vertexLabels = new std::string[0];
}

SimpleGraph::SimpleGraph(int V) {
	vertexCount = V;

	edges = new bool*[V - 1];
	for (int i = 0; i < V - 1; i++) {
		edges[i] = new bool[V - 1 - i];
	}
	removeEdges();

	vertexLabels = new std::string[V];
	for (int i = 0; i < V; i++)  {
		vertexLabels[i] = std::to_string(i);
	}
}

SimpleGraph::SimpleGraph(int V, bool* E) {
	vertexCount = V;

	edges = decode_edges(E, V);

	vertexLabels = new std::string[V];
	for (int i = 0; i < V; i++)  {
		vertexLabels[i] = std::to_string(i);
	}
}

SimpleGraph::SimpleGraph(int V, bool** E) {
	vertexCount = V;

	// Create personal copy of edges.
	edges = new bool*[V - 1];
	setEdges(E);
	for (int i = 0; i < V - 1; i++) {
		edges[i] = new bool[V - 1 - i];
	}

	vertexLabels = new std::string[V];
	for (int i = 0; i < V; i++)  {
		vertexLabels[i] = std::to_string(i);
	}
}

SimpleGraph::SimpleGraph(int V, bool* E, std::string* V_names) {
	vertexCount = V;

	edges = decode_edges(E, V);

	vertexLabels = new std::string[V];
	for (int i = 0; i < V; i++)  {
		vertexLabels[i] = V_names[i];
	}
}

SimpleGraph::SimpleGraph(int V, bool** E, std::string* V_names) {
	vertexCount = V;

	// Create personal copy of edges.
	edges = new bool*[V - 1];
	for (int i = 0; i < V - 1; i++) {
		edges[i] = new bool[V - 1 - i];
	}
	setEdges(E);

	vertexLabels = new std::string[V];
	for (int i = 0; i < V; i++)  {
		vertexLabels[i] = V_names[i];
	}
}

SimpleGraph::~SimpleGraph() {
	for (int i = 0; i < vertexCount - 1; i++) {
		delete[] edges[i];
	}
	delete[] edges;

	delete[] vertexLabels;
}



void SimpleGraph::resize(int V) {
	// If size is the same, abort.
	if (V == vertexCount)
		return;

	// Create new structures to store additional data.
	bool** new_edges = new bool*[V - 1];
	FOR_EDGES(
		V,
		new_edges[i] = new bool[V - 1 - i];,
		new_edges[i][j] = false;)

	std::string* new_vertexLabels = new std::string[V];

	// Copy data into new structures.
	FOR_EDGES(
		std::min(V, vertexCount),
		,
		new_edges[i][j] = edges[i][j];)

	for (int i = 0; i < V; i++) {
		new_vertexLabels[i] = i < vertexCount ? vertexLabels[i] : std::to_string(i);
	}

	// Destroy old structures.
	for (int i = 0; i < vertexCount - 1; i++) {
		delete[] edges[i];
	}
	delete[] edges;

	delete[] vertexLabels;

	// Assign new structures.
	vertexCount = V;
	edges = new_edges;
	vertexLabels = new_vertexLabels;
}



bool SimpleGraph::addEdge(int u, int v) {
	bool* edgePTR = getEdge(u, v);

	// Grab original value to return.
	bool original = *edgePTR;

	*edgePTR = true;

	return original;
}

bool SimpleGraph::removeEdge(int u, int v) {
	bool* edgePTR = getEdge(u, v);

	// Grab original value.
	bool original = *edgePTR;

	*edgePTR = false;

	return original;
}

bool SimpleGraph::isAdjacent(int u, int v) {
	return *getEdge(u, v);
}



void SimpleGraph::setEdges(bool** E) {
	FOR_EDGES(
		vertexCount,
		,
		edges[i][j] = E[i][j];)
}

void SimpleGraph::setEncodedEdges(bool* E) {
	FOR_EDGES(
		vertexCount,
		,
		edges[i][j] = *E;
		E++;)
}

void SimpleGraph::removeEdges() {
	FOR_EDGES(
		vertexCount,
		,
		edges[i][j] = false;)
}



bool** SimpleGraph::getEdges() {
	bool** copy = new bool*[vertexCount - 1];

	FOR_EDGES(
		vertexCount,
		copy[i] = new bool[vertexCount - 1 - i];,
		copy[i][j] = edges[i][j];)

	return copy;
}

bool* SimpleGraph::encodeEdges() {
	bool* encoding = new bool[getEncodingLength()];
	bool* encodePTR = encoding;

	FOR_EDGES(
		vertexCount,
		,
		*encodePTR = edges[i][j];
		encodePTR++;)

	return encoding;
}



std::string SimpleGraph::toString() {
	// Create string.
	std::string graphEncoding = "V = {";

	// Loop over vertices.
	for (int i = 0; i < vertexCount; i++) {
		graphEncoding += vertexLabels[i];
		if (i != vertexCount - 1)
			graphEncoding += ", ";
	}

	graphEncoding += "}, E = {";

	// For each pair of vertices, determine if they are adjacent. If they are, append.
	bool first = true;
	FOR_EDGES(
		vertexCount,
		,
		if (!isAdjacent(i, j))
			continue;

		if (!first)
			graphEncoding += ", ";
		else
			first = false;

		graphEncoding += vertexLabels[i] + "-" + vertexLabels[j];)

	graphEncoding += "}";

	return graphEncoding;
}



std::string SimpleGraph::getName(int v) {
	if (!indexValid(v))
		throw std::runtime_error(("Invalid index v = " + std::to_string(v)).c_str());

	return vertexLabels[v];
}

void SimpleGraph::setName(int v, std::string name) {
	if (!indexValid(v))
		throw std::runtime_error(("Invalid index v = " + std::to_string(v)).c_str());

	vertexLabels[v] = name;
}
