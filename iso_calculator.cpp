#include "graph.h"
#include "isomorphism.h"

#include <iostream>
#include <string>
#include <string.h>

//#define DEBUG(v) std::clog << v << std::endl;
#define DEBUG(v) 

// Simple linked list node.
class GraphSet {
public:
	SimpleGraph* data;
	GraphSet* next;
	int count;

	GraphSet() {
		data = nullptr;
		next = nullptr;
		count = 0;
	}

	~GraphSet() {
		if (data)
			delete data;
		if (next)
			delete next;
	}
};

// Steps to the next configuration, and returns if it is valid.
bool step_configuration(bool* config, int len) {
	// Walk from the back.
	bool* walk = config + len - 1;

	// Walk until a 0 is encounterd.
	DEBUG("Walking back for 0")
	int count = 0;	
	while (*walk) {
		count++;
		walk--;

		// Exit case.
		if (walk < config) {
			DEBUG("Failing config due to no false encounters.")
			return false;
		}
	}

	// If there are no 1's followed by a 0, then all 1's are on the right, and the configuration is terminal.
	DEBUG("Walking back for 1")
	while (!*walk) {
		walk--;
		if (walk < config) {
			DEBUG("Failing config due to config terminality.")
			return false;
		}
	}

	// A 1 has been found. Move it to right, then follow it with count 1s.
	DEBUG("Walking forward with 1s.")
	*walk = false;
	walk++;
	for (int i = 0; i <= count; i++) {
		if (walk > config + len - 1) {
			DEBUG("Failing config due to overrunning end of array.")
			return false;
		}
		*walk = true;
		walk++;
	}

	// Assign rest as 0s.
	DEBUG("Walking forward with 0s")
	while (walk < config + len) {
		*walk = false;
		walk++;
	}

	return true;
}

// Returns graphs for all the isomorphism types with the given vertex and edge counts.
GraphSet* get_isomorphism_types(int vertexCount, int edgeCount) {
	// Initial variables.
	SimpleGraph G(vertexCount);
	int encodingLength = G.getEncodingLength();
	bool* config = new bool[encodingLength];
	GraphSet* set = nullptr;

	// Initialize config with edge count.
	bool* asn = config;
	for (int i = 0; i < edgeCount; i++) {
		*asn = true;
		asn++;
	}
	for (int i = 0; i < encodingLength - edgeCount; i++) {
		*asn = false;
		asn++;
	}

	// Itterate over all graph configurations.
	do {

		// Apply config.
		G.setEncodedEdges(config);
		DEBUG("Testing configuration: " << G.toString())

		// Compare with existing types.
		GraphSet* compare = set;
		bool isNew = true;
		while (compare) {
			DEBUG("Comparing configurations: (" << G.toString() << "), (" << compare->data->toString() << ")")

			if (are_isomorphic(G, *(compare->data))) {
				compare->count++;
				isNew = false;
				break;
			}

			compare = compare->next;
		}
		if (!isNew)
			continue;

		// If the graph does not fit into any existing types, add to set of types.
		GraphSet* newType = new GraphSet();
		newType->data = new SimpleGraph(vertexCount, config);
		newType->next = set;
		newType->count++;
		set = newType;

	// Step configuration, and repeat loop if the encoding is still valid.
	} while(step_configuration(config, encodingLength));

	// Clean up.
	delete[] config;

	return set;
}

int main(int argc, char** argv) {
	// Configuration variables.
	int vertexCount = -1;
	int minEdges = -1;
	int maxEdges = -1;

	// Process arguements.
	for (int arg = 0; arg < argc; arg++) {
		// Vertex count.
		if (!strcmp(argv[arg], "-v")) {
			arg++;
			if (!(arg < argc)) {
				std::cout << "Error: \"-v\" argument must be followed by an integer vertex count." << std::endl;
				return 1;
			}
			try {
				vertexCount = std::stoi(argv[arg]);
			}
			catch (std::exception& e) {
				std::cout << "Error: \"-v\" argument must be followed by an integer vertex count." << std::endl;
				return 1;
			}
		}

		// Edge min.
		if (!strcmp(argv[arg], "-min")) {
			arg++;
			if (!(arg < argc)) {
				std::cout << "Error: \"-min\" argument must be followed by an integer edge count." << std::endl;
				return 1;
			}
			try {
				minEdges = std::stoi(argv[arg]);
			}
			catch (std::exception& e) {
				std::cout << "Error: \"-min\" argument must be followed by an integer edge count." << std::endl;
				return 1;
			}
		}

		// Edge max.
		if (!strcmp(argv[arg], "-max")) {
			arg++;
			if (!(arg < argc)) {
				std::cout << "Error: \"-max\" argument must be followed by an integer edge count." << std::endl;
				return 1;
			}
			try {
				maxEdges = std::stoi(argv[arg]);
			}
			catch (std::exception& e) {
				std::cout << "Error: \"-max\" argument must be followed by an integer edge count." << std::endl;
				return 1;
			}
		}

		// Edge configuration
		if (!strcmp(argv[arg], "-e")) {
			arg++;
			if (!(arg < argc)) {
				std::cout << "Error: \"-e\" argument must be followed by two integer values." << std::endl;
				return 1;
			}
			try {
				minEdges = std::stoi(argv[arg]);
			}
			catch (std::exception& e) {
				std::cout << "Error: \"-e\" argument must be followed by two integer values." << std::endl;
				return 1;
			}

			arg++;
			if (!(arg < argc)) {
				std::cout << "Error: \"-e\" argument must be followed by two integer values." << std::endl;
				return 1;
			}
			try {
				maxEdges = std::stoi(argv[arg]);
			}
			catch (std::exception& e) {
				std::cout << "Error: \"-e\" argument must be followed by two integer values." << std::endl;
				return 1;
			}
		}
	}

	// Followup configuration.
	if (vertexCount <= 0) {
		std::cout << "Error: Positive vertex count must be specified. Passed using \"-v\" parameter." << std::endl << "See README.md for more information." << std::endl;
		return 1;
	}

	if (minEdges <= 0) {
		std::cout << "No minimum edge cout specified, assuming 0." << std::endl;
		minEdges = 0;
	}

	if (maxEdges <= 0) {
		std::cout << "No maximum edge count specified, assuming " << vertexCount * (vertexCount -1) / 2 << "." << std::endl;
		maxEdges = vertexCount * (vertexCount -1) / 2;
	}

	if (minEdges > maxEdges) {
		std::cout << "Error: Minimum edge count must be greater than maximum edge count." << std::endl;
		return 1;
	}

	if (maxEdges > vertexCount * (vertexCount -1) / 2) {
		std::cout << "Error: Invalid edge count. Can be at most " << vertexCount * (vertexCount -1) / 2 << "." << std::endl;
	}

	// For each edge count, enumerate isomorphism types.
	for (int i = minEdges; i <= maxEdges; i++) {
		GraphSet* set = get_isomorphism_types(vertexCount, i);

		// Print.
		std::cout << "Isomorphism types with " << vertexCount << " vertices and " << i << " edges:" << std::endl;
		GraphSet* printer = set;
		while (printer) {
			std::cout << "(" << printer->count << ")\t" << printer->data->toString() << std::endl;
			printer = printer->next;
		}

		// Clean up.
		delete set;
	}

	return 0;
}
