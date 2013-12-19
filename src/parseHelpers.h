#ifndef PARSE_HELPERS_H
#define PARSE_HELPERS_H

#include <fstream>
#include <stdexcept>
#include <json/json.h>

void parse(std::string path, Json::Value &json);
int getAs(Json::Value &json, std::string val, int fallback);
bool getAs(Json::Value &json, std::string val, bool fallback);
float getAs(Json::Value &json, std::string val, float fallback);
std::string getAs(Json::Value &json, std::string val, std::string fallback);

template<class T>
T get(Json::Value &json, std::string val, T fallback){
	T temp;
	try{
		return getAs(json, val, fallback);
	}
	catch(const std::exception &error){
		std::cerr<<"Error reading value "<<val<<": "<<error.what()<<std::endl;
		return fallback;
	}
}

#endif
