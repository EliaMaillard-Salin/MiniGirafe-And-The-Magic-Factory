#include "pch.h"
#include "Utils.h"


namespace Utils
{
	bool NormalizeQ(sf::Vector2f& vector)
	{
		float invmagnitude = Q_rsqrt(vector.x * vector.x + vector.y * vector.y);

		if (invmagnitude != 0)
		{
			vector.x *= invmagnitude;
			vector.y *= invmagnitude;

			return true;
		}

		return false;
	}

	bool Normalize(sf::Vector2f& vector)
	{
		float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude != 0)
		{
			vector.x /= magnitude;
			vector.y /= magnitude;

			return true;
		}

		return false;
	}

	float GetDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return std::sqrt(x * x + y * y);
	}

	float GetDistancesqrd(int x1, int y1, int x2, int y2)
	{
		int x = x2 - x1;
		int y = y2 - y1;

		return (x * x + y * y);
	}
	float Q_rsqrt(float number)
	{
		long i;
		float y;

		y = number;
		i = *(long*)&y; // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1); // what the fuck?
		y = *(float*)&i;

		return y;
	}

	sf::Vector2f GetVectorDistance(sf::Vector2f& v1, sf::Vector2f& v2) {

		sf::Vector2f t = { 0.f,0.f };

		t.x = v2.x - v1.x;
		t.y = v2.y - v1.y;

		return t;
	}

	sf::Vector2f rotate_pointCW(float cx, float cy, float angle, sf::Vector2f p)
	{
		float angleInRads = angle * 3.14159265359 / 180;
		float s = sin(angleInRads);
		float c = cos(angleInRads);

		// translate point back to origin:
		p.x -= cx;
		p.y -= cy;

		// rotate point
		float xnew = p.x * c - p.y * s;
		float ynew = p.x * s + p.y * c;

		// translate point back:
		p.x = xnew + cx;
		p.y = ynew + cy;

		return p;
	}

	float Getmagnitude(sf::Vector2f v) {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	sf::Vector2f Reflect(sf::Vector2f  Normal, sf::Vector2f  inDir) {
		sf::Vector2f tmp = (inDir - (Normal * (inDir.dot(Normal)) * 2.f));
		return tmp;
	}
}