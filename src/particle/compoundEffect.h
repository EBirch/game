#ifndef COMPOUND_EFFECT_H
#define COMPOUND_EFFECT_H

#include <unordered_map>
#include <vector>
#include <tuple>
#include <memory>
#include "./particleEffect.h"

class CompoundEffect{
	public:
		CompoundEffect(Json::Value &json);
		int end;
		std::unordered_map<int, std::vector<std::tuple<std::shared_ptr<ParticleEffect>, float, float, float>>> effectMap;
};

#endif
