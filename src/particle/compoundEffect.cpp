#include <algorithm>
#include "./compoundEffect.h"

extern std::unordered_map<std::string, std::shared_ptr<ParticleEffect>> particleEffects;

CompoundEffect::CompoundEffect(Json::Value &json){
	auto effects = json.getMemberNames();
	int max = 0;
	std::for_each(effects.begin(), effects.end(), 
		[&](std::string name){
			std::vector<std::tuple<std::shared_ptr<ParticleEffect>, float, float, float>> effects;
			std::for_each(json[name].begin(), json[name].end(),
				[&](Json::Value val){
					effects.push_back(std::make_tuple(particleEffects.at(get(val, "effect", std::string(""))), get(val, "offsetX", 0.0f), get(val, "offsetY", 0.0f), get(val, "rotation", 0.0f)));
				});
			int timestep = std::stoi(name);
			if(timestep > max){
				max = timestep;
			}
			effectMap.insert(std::make_pair(timestep, effects));
		});
}
