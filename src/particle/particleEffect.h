#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#define DEG2RAD 0.01745329251994

#include <string>
#include "../parseHelpers.h"

class ParticleEffect{
	public:
		ParticleEffect(Json::Value &json);
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
		bool physics;
};

#endif
