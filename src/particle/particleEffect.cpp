#include "./particleEffect.h"

ParticleEffect::ParticleEffect(Json::Value &json){
	minParticles = get(json, "minParticles", 0);
	maxParticles = get(json, "maxParticles", 0);
	minSpeed = get(json, "minSpeed", 0.0f);
	maxSpeed = get(json, "maxSpeed", 0.0f);
	minLifespan = get(json, "minLifespan", 0);
	maxLifespan = get(json, "maxLifespan", 0);
	minAngle = DEG2RAD * get(json, "minAngle", 0.0f);
	maxAngle = DEG2RAD * get(json, "maxAngle", 0.0f);
	minHue = get(json, "minHue", 0);
	maxHue = get(json, "maxHue", 0);
	minSat = get(json, "minSat", 0.0f);
	maxSat = get(json, "maxSat", 0.0f);
	minVal = get(json, "minVal", 0.0f);
	maxVal = get(json, "maxVal", 0.0f);
	minRotation = DEG2RAD * get(json, "minRotation", 0.0f);
	maxRotation = DEG2RAD * get(json, "maxRotation", 0.0f);
	minXScale = get(json, "minXScale", 0.0f);
	maxXScale = get(json, "maxXScale", 0.0f);
	minYScale = get(json, "minYScale", 0.0f);
	maxYScale = get(json, "maxYScale", 0.0f);
}
