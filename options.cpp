#include "options.hpp"
#include "json.hpp"
#include "SimpleCppTextFileHandler/file.hpp"

using json = nlohmann::json;

int lSoptions::load(){
	if(!fileExists(filename)){
		std::cerr<<"Error: layout file \""<<filename<<"\" could not be found!"<<std::endl;
		return -1;
	}
	std::string contents = readFile(filename);
	auto j = json::parse(contents);

	if(j.contains("command")){
		baseCommand = j["command"].get<std::string>();
	}else{
		std::cerr<<"Error: unable to find commmand in qlayoutSwitcher.json"<<std::endl;
		return -2;
	}

	if(j.contains("hotkey")){
		hotkey = j["hotkey"].get<std::string>();
	}

	if(!j.contains("layouts")){
		return -3;
	}
	
	auto jl = j["layouts"];
	for(auto& o : jl){
		if(!(o.contains("name") && o.contains("id"))){
			continue;
		}
		std::string name = o["name"];
		std::string id = o["id"];
		layouts.push_back(std::make_pair(name, id));
	}

	return 0;
}
