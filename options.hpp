#pragma once
#include <iostream>
#include <vector>
#include <optional>

class lSoptions{
public:
	static inline std::string filename = "qlayoutSwitcher.json";
	static inline std::string baseCommand;
	static inline std::optional<std::string> hotkey = std::nullopt;
	static inline std::vector<std::pair<std::string, std::string>> layouts;
	static int load();
};
