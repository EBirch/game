#include "./parseHelpers.h"

void parse(std::string path, Json::Value &json){
	std::ifstream file(path);
	if(file.fail()){
		std::cerr<<"Error opening file "<<path<<std::endl;
	}
	Json::Reader reader;
	if(!reader.parse(file, json)){
		std::cout<<"Error parsing file "<<path<<": "<<reader.getFormatedErrorMessages()<<std::endl;
	}
}

int getAs(Json::Value &json, std::string val, int fallback){
	return json.get(val, fallback).asInt();
}

bool getAs(Json::Value &json, std::string val, bool fallback){
	return json.get(val, fallback).asBool();
}

float getAs(Json::Value &json, std::string val, float fallback){
	return json.get(val, fallback).asDouble();
}

std::string getAs(Json::Value &json, std::string val, std::string fallback){
	return json.get(val, fallback).asString();
}
