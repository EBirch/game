#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include <string>
#include <json/json.h>

class ParticleEffect{
	public:
		ParticleEffect(Json::Value json);
		int minParticles;
		int maxParticles;
		int minLifespan;
		int maxLifespan;
		int minHue;
		int maxHue;
		float minSat;
		float maxSat;
		float minVal;
		float maxVal;
		float minSpeed;
		float maxSpeed;
		float minAngle;
		float maxAngle;
		float minRotation;
		float maxRotation;
		float minXScale;
		float maxXScale;
		float minYScale;
		float maxYScale;
};

#endif
