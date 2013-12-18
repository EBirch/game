#include "./particleEffect.h"
#include <json/json.h>

ParticleEffect::ParticleEffect(Json::Value json){
	try{
		minParticles = json.get("minParticles", 0).asInt();
		maxParticles = json.get("maxParticles", 50).asInt();
		minSpeed = json.get("minSpeed", 0).asDouble();
		maxSpeed = json.get("maxSpeed", 1).asDouble();
		minLifespan = json.get("minLifespan", 0).asInt();
		maxLifespan = json.get("maxLifespan", 10).asInt();
		minAngle = 0.01745329251994 * json.get("minAngle", 0).asDouble();
		maxAngle = 0.01745329251994 * json.get("maxAngle", 360).asDouble();
		minHue = json.get("minHue", 0).asInt();
		maxHue = json.get("maxHue", 360).asInt();
		minSat = json.get("minSat", 0).asDouble();
		maxSat = json.get("maxSat", 1).asDouble();
		minVal = json.get("minVal", 0).asDouble();
		maxVal = json.get("maxVal", 1).asDouble();
		minRotation = 0.01745329251994 * json.get("minRotation", 0).asDouble();
		maxRotation = 0.01745329251994 * json.get("maxRotation", 0).asDouble();
		minXScale = json.get("minXScale", 1).asDouble();
		maxXScale = json.get("maxXScale", 1).asDouble();
		minYScale = json.get("minYScale", 1).asDouble();
		maxYScale = json.get("maxYScale", 1).asDouble();
	}
	catch(const std::exception &error){
		std::cerr<<"ParticleEffect construction exception: "<<error.what()<<std::endl;
	}
}
