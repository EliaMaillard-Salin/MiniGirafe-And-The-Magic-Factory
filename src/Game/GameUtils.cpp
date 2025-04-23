#include "pch.h"
#include "GameUtils.h"

EnumConverter::EnumConverter()
{
	m_stringToEnumTypes.insert(std::pair<std::string, RESSOURCES_TYPES>("PLANT", RESSOURCES_TYPES::PLANT));
	m_stringToEnumTypes.insert(std::pair<std::string, RESSOURCES_TYPES>("TREE", RESSOURCES_TYPES::TREE));
	m_stringToEnumTypes.insert(std::pair<std::string, RESSOURCES_TYPES>("ROCK", RESSOURCES_TYPES::ROCK));

	m_stringToEnumBiomes.insert(std::pair<std::string, RESSOURCES_BIOMES>("PLAINS", RESSOURCES_BIOMES::PLAINS));
	m_stringToEnumBiomes.insert(std::pair<std::string, RESSOURCES_BIOMES>("FOREST", RESSOURCES_BIOMES::FOREST));
	m_stringToEnumBiomes.insert(std::pair<std::string, RESSOURCES_BIOMES>("MOUTAINS", RESSOURCES_BIOMES::MOUTAINS));
	m_stringToEnumBiomes.insert(std::pair<std::string, RESSOURCES_BIOMES>("VOLCAN", RESSOURCES_BIOMES::VOLCAN));

	m_stringToEnumRank.insert(std::pair<std::string, RESSOURCES_RANK>("RANK_1", RESSOURCES_RANK::RANK_1));
	m_stringToEnumRank.insert(std::pair<std::string, RESSOURCES_RANK>("RANK_2", RESSOURCES_RANK::RANK_2));
	m_stringToEnumRank.insert(std::pair<std::string, RESSOURCES_RANK>("RANK_3", RESSOURCES_RANK::RANK_3));

	//Plants
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("TREFLE", RESSOURCES_PROPS::TREFLE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("MILLEPERTUIS", RESSOURCES_PROPS::MILLEPERTUIS));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("MUSHROOM", RESSOURCES_PROPS::MUSHROOM));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("DATURA", RESSOURCES_PROPS::DATURA));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("ACONIT", RESSOURCES_PROPS::ACONIT));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("AUBEPINE", RESSOURCES_PROPS::AUBEPINE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("EDELWEISS", RESSOURCES_PROPS::EDELWEISS));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("PEYOTL", RESSOURCES_PROPS::PEYOTL));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("NUYTSIA_FLORIBUNDA", RESSOURCES_PROPS::NUYTSIA_FLORIBUNDA));

	//Trees
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("CHENE", RESSOURCES_PROPS::CHENE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("SAULE", RESSOURCES_PROPS::SAULE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("NOISETIER", RESSOURCES_PROPS::NOISETIER));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("AULNE", RESSOURCES_PROPS::AULNE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("SUREAU", RESSOURCES_PROPS::SUREAU));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("ERABLE", RESSOURCES_PROPS::ERABLE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("IF", RESSOURCES_PROPS::IF));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("SAPIN", RESSOURCES_PROPS::SAPIN));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("HOUX", RESSOURCES_PROPS::HOUX));

	// Rock
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("SILICE", RESSOURCES_PROPS::SILICE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("ROCK_PROP", RESSOURCES_PROPS::ROCK_PROP));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("AVENTURINE", RESSOURCES_PROPS::AVENTURINE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("CITRINE", RESSOURCES_PROPS::CITRINE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("AMETHYSTE", RESSOURCES_PROPS::AMETHYSTE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("AIGUE_MARINE", RESSOURCES_PROPS::AIGUE_MARINE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("JASPE", RESSOURCES_PROPS::JASPE));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("QUARTZ", RESSOURCES_PROPS::QUARTZ));
	m_stringToEnumProps.insert(std::pair<std::string, RESSOURCES_PROPS>("HELIOLITE", RESSOURCES_PROPS::HELIOLITE));
}

EnumConverter::~EnumConverter()
{
	m_stringToEnumTypes.clear();
	m_stringToEnumBiomes.clear();
	m_stringToEnumRank.clear();
	m_stringToEnumProps.clear();
}

RESSOURCES_TYPES EnumConverter::ConvertStringToEnumTypes(std::string str)
{
	return m_stringToEnumTypes[str];
}

RESSOURCES_BIOMES EnumConverter::ConvertStringToEnumBiomes(std::string str)
{
	return m_stringToEnumBiomes[str];
}

RESSOURCES_RANK EnumConverter::ConvertStringToEnumRank(std::string str)
{
	return m_stringToEnumRank[str];
}

RESSOURCES_PROPS EnumConverter::ConvertStringToEnumProps(std::string str)
{
	return m_stringToEnumProps[str];
}
