
// Copyright Leatherman

#include <iostream>
#include <fstream>
#include <ctime>

#include "textgen.h"

int main() {
    MarkovGenerator gen;

    std::ifstream file("input.txt");
    Prefix start = gen.ReadState(file);

    unsigned state = time(nullptr);

    gen.write(std::cout, start, &state);
}
