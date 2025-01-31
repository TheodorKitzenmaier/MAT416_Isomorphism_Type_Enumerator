#pragma once

#include "graph.h"

// Returns if the <G> and <H> are isomorphic using the given mapping.
bool is_isomorphic_mapping(SimpleGraph& G, SimpleGraph& H, int* mapping);

// Choses the given values, storing them into the buffer.
// <tmp> stores which values have already been chosen. Passed in to save on allocation overhead.
void apply_mapping(int* choices, int* buffer, bool* tmp, int len);

// Returns if the graphs G and H are isomorphic.
bool are_isomorphic(SimpleGraph& G, SimpleGraph& H);
