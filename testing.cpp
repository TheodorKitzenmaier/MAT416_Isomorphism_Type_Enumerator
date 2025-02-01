#include "graph.h"
#include "isomorphism.h"
#include <string>
#include <iostream>

std::string array_to_string(int* array, int len) {
	std::string str = "{";
	for (int i = 0; i < len; i++) {
		str += std::to_string(array[i]);
		if (i != len - 1)
			str += ", ";
	}
	str += "}";
	return str;
}


// Tests mapping application. Returns number of failed tests.
int test_apply_mapping() {
	int failures = 0;
	bool failure;

	// Testing of known cases.
	int* buffer = new int[10];
	bool* tmp = new bool[10];
	int len = 10;

	failure = false;
	int choices_1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int expected_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	apply_mapping(choices_1, buffer, tmp, len);
	for (int i = 0; i < len; i++) {
		if (expected_1[i] != buffer[i])
			failure = true;
	}
	if (failure) {
		failures++;
		std::cout << "Expected " << array_to_string(expected_1, len) << ", got " << array_to_string(buffer, len) << std::endl;
	}

	failure = false;
	int choices_2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int expected_2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	apply_mapping(choices_2, buffer, tmp, len);
	for (int i = 0; i < len; i++) {
		if (expected_2[i] != buffer[i])
			failure = true;
	}
	if (failure) {
		failures++;
		std::cout << "Expected " << array_to_string(expected_2, len) << ", got " << array_to_string(buffer, len) << std::endl;
	}

	failure = false;
	int choices_3[] = {7, 2, 3, 1, 4, 0, 2, 0, 0, 0};
	int expected_3[] = {7, 2, 4, 1, 8, 0, 6, 3, 5, 9};
	apply_mapping(choices_3, buffer, tmp, len);
	for (int i = 0; i < len; i++) {
		if (expected_3[i] != buffer[i])
			failure = true;
	}
	if (failure) {
		failures++;
		std::cout << "Expected " << array_to_string(expected_3, len) << ", got " << array_to_string(buffer, len) << std::endl;
	}

	failure = false;
	int choices_4[] = {4, 6, 1, 0, 0, 4, 2, 1, 1, 0};
	int expected_4[] = {4, 7, 1, 0, 2, 9, 6, 5, 8, 3};
	apply_mapping(choices_4, buffer, tmp, len);
	for (int i = 0; i < len; i++) {
		if (expected_4[i] != buffer[i])
			failure = true;
	}
	if (failure) {
		failures++;
		std::cout << "Expected " << array_to_string(expected_4, len) << ", got " << array_to_string(buffer, len) << std::endl;
	}

	failure = false;
	int choices_5[] = {2, 3, 4, 5, 4, 3, 2, 1, 0, 0};
	int expected_5[] = {2, 4, 6, 8, 7, 5, 3, 1, 0, 9};
	apply_mapping(choices_5, buffer, tmp, len);
	for (int i = 0; i < len; i++) {
		if (expected_5[i] != buffer[i])
			failure = true;
	}
	if (failure) {
		failures++;
		std::cout << "Expected " << array_to_string(expected_5, len) << ", got " << array_to_string(buffer, len) << std::endl;
	}

	failure = false;
	int choices_6[] = {0, 1, 2, 3, 4, 4, 3, 2, 1, 0};
	int expected_6[] = {0, 2, 4, 6, 8, 9, 7, 5, 3, 1};
	apply_mapping(choices_6, buffer, tmp, len);
	for (int i = 0; i < len; i++) {
		if (expected_6[i] != buffer[i])
			failure = true;
	}
	if (failure) {
		failures++;
		std::cout << "Expected " << array_to_string(expected_6, len) << ", got " << array_to_string(buffer, len) << std::endl;
	}

	failure = false;
	int choices_7[] = {6, 2, 0, 0, 0, 2, 3, 1, 0, 0};
	int expected_7[] = {6, 2, 0, 1, 3, 7, 9, 5, 4, 8};
	apply_mapping(choices_7, buffer, tmp, len);
	for (int i = 0; i < len; i++) {
		if (expected_7[i] != buffer[i])
			failure = true;
	}
	if (failure) {
		failures++;
		std::cout << "Expected " << array_to_string(expected_7, len) << ", got " << array_to_string(buffer, len) << std::endl;
	}

	delete[] buffer;
	delete[] tmp;

	return failures;
}

int main(int argc, char** argv) {
	std::cout << "Testing \"apply_mapping\" function:" << std::endl;
	int failures = test_apply_mapping();
	std::cout << "Failed " << failures << " tests." << std::endl;
}
