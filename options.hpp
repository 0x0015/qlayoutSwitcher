#pragma once
#include <iostream>
#include <vector>

class lSoptions{
public:
	static inline std::string filename = "qlayoutSwitcher.json";
	static inline std::string baseCommand;
	static inline std::vector<std::pair<std::string, std::string>> layouts;
	static int load();
};
