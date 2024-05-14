#pragma once
#include <iostream>
#include "graph.hpp"

namespace cs251 {

class color_walk {
public:
	static std::vector<std::pair<char, int>> calculate(const graph& g, handle startHandle);
};

}
