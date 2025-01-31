#include "graph.h"
#include "isomorphism.h"
#include <stdexcept>

bool is_isomorphic_mapping(SimpleGraph& G, SimpleGraph& H, int* mapping) {
	// Search for mismatched vertex pair.
	for (int i = 0; i < G.getVertexCount() - 1; i++) {
		for (int j = i + 1; j < G.getVertexCount(); j++) {
			if (G.isAdjacent(i, j) != H.isAdjacent(mapping[i], mapping[j]))
				return false;
		}
	}

	return true;
}

void apply_mapping(int* choices, int* buffer, bool* tmp, int len) {
	// Reset contents of tmp.
	for (int i = 0; i < len; i++) {
		tmp[i] = false;
	}

	// Do mapping.
	for (int i = 0; i < len; i++) {
		// Value to set the current buffer to.
		int set = -1;

		// Find correct value of set. (I barely understand what is happening here lol)
		int choice = -1;
		do {
			set++;
			choice++;

			if (tmp[set])
				choice--;
		} while (choice < choices[i]);

		tmp[set] = true;
		buffer[i] = set;
	}
}

bool are_isomorphic(SimpleGraph& G, SimpleGraph& H) {
	// Two graphs, G and H, are isomorphic iff there is a bijection f from V(G) to V(H)
	// Such that uv is in E(G) iff f(u)f(v) is in E(H).

	// In more "practical" terms, there is some mapping of the verticies in G such that
	// The edges are the same.

	// There are a LOT of mappings :D
	// For a graph |G| = n, There are n! mappings (I think).
	// This function will then, in the worst case, have a running time of O(n(n!)).
	// This is bad, but for small graphs, "good enough".

	// Check if the graphs are comparable.
	if (G.getVertexCount() != H.getVertexCount())
		throw std::runtime_error("Unable to compare graphs with different size");

	// Initial mapping.
	// Head pointer: Points to the head of the map array.
	int* head = new int[G.getVertexCount()];
	int* tail = head + G.getVertexCount() - 1;
	for (int i = 0; i < G.getVertexCount(); i++) {
		head[i] = 0;
	}

	// Select pointer: Points to the current index being incremented.
	int* select = head;

	// Select max counter: Stores the max value which can be stored at the select pointer.
	int selectMax = 0;
	bool returnToTail;

	// Array which stores applicable mappings.
	int* mapping = new int[G.getVertexCount()];
	bool* tmp = new bool[G.getVertexCount()];

	// The select pointer increments its value until it exceeds the max.
	// The select pointer then increments the value before it, and resets
	// all values to 1 walking back to the tail of the array.
	while (select >= head) {
		// Check if the current mapping shows that the two graphs are isomorphic.
		apply_mapping(head, mapping, tmp, G.getVertexCount());
		if (is_isomorphic_mapping(G, H, mapping)) {
			// Do cleanup before returning.
			delete[] head;
			delete[] mapping;
			delete[] tmp;
			return true;
		}

		// Increment and update the mapping.
		*select++;
		returnToTail = false;
		while (*select > selectMax) {
			// Head has exceeded max, all mappings checked.
			if (select == head)
				break;

			// Increment previous index, return to tail.
			select = select - 1;
			*select++;
			selectMax++;
			returnToTail = true;
		}

		// Reset to tail.
		if (returnToTail) {
			while (select > tail) {
				select++;
				*select = 0;
			}
			selectMax = 0;
		}
	}

	// Cleanup.
	delete[] head;
	delete[] mapping;
	delete[] tmp;

	// No mappings were found.
	return false;
}
