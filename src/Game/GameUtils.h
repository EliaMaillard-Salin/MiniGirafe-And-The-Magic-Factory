#pragma once

#include "pch.h"

class EnumConverter
{
	std::map <std::string, RESSOURCES_TYPES> m_stringToEnumTypes;
	std::map <std::string, RESSOURCES_BIOMES> m_stringToEnumBiomes;
	std::map <std::string, RESSOURCES_RANK> m_stringToEnumRank;
	std::map <std::string, RESSOURCES_PROPS> m_stringToEnumProps;

public:
	EnumConverter();
	~EnumConverter();

	RESSOURCES_TYPES ConvertStringToEnumTypes(std::string str);
	RESSOURCES_BIOMES ConvertStringToEnumBiomes(std::string str);
	RESSOURCES_RANK ConvertStringToEnumRank(std::string str);
	RESSOURCES_PROPS ConvertStringToEnumProps(std::string str);
};

