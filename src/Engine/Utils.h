#pragma once
#include <SFML/System/Vector2.hpp>

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	bool NormalizeQ(sf::Vector2f& vector);
	float GetDistance(float x1, float y1, float x2, float y2);
	float Getmagnitude(sf::Vector2f v);
	float GetDistancesqrd(int x1, int y1, int x2, int y2);
	float Q_rsqrt(float number);
	sf::Vector2f GetVectorDistance(sf::Vector2f& v1, sf::Vector2f& v2);
	sf::Vector2f rotate_pointCW(float cx, float cy, float angle, sf::Vector2f p);
	sf::Vector2f Reflect(sf::Vector2f  Normal, sf::Vector2f  inDir);
}