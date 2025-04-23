#include "pch.h"
#include "SceneTest.h"
#include "MovingItem.h"
#include "Pipe.h"

MovingItem::MovingItem()
{
	m_collider = Entity::Circle;
	m_tag = SceneTest::MOVINGITEM;

	SetLayer(1);
	m_isDrawable = true;
	m_hasCollision = true;

	m_width = 8;
	m_height = 8;
}



void MovingItem::Init(const char* texturepath,int x,int y, Pipe* pipetogoto)
{
	m_pPipeToGoTo = pipetogoto;
	SetSpriteTexture(texturepath);
	SetPosition(x, y);
}

void MovingItem::OnFixedUpdate()
{
	if (m_pPipeToGoTo != nullptr) {
		sf::Vector2f pipepos = m_pPipeToGoTo->GetPosition();

		switch (m_pPipeToGoTo->GetOutPos())
		{
		case Pipe::UP:
			AttractToPosition(pipepos.x, pipepos.y-32, 1.f);
			break;
		case Pipe::RIGHT:
			AttractToPosition(pipepos.x + 32 , pipepos.y, 1.f);
			break;
		case Pipe::DOWN:
			AttractToPosition(pipepos.x, pipepos.y + 32, 1.f);
			break;
		case Pipe::LEFT:
			AttractToPosition(pipepos.x - 32, pipepos.y, 1.f);
			break;
		}
	}
		
		
}

void MovingItem::OnUpdate()
{
	if (m_pSprite != nullptr) {
		m_pSprite->setPosition(m_pos);
	}
}

void MovingItem::OnCollision(Entity* collidedWith)
{
	if (collidedWith->GetTag() == SceneTest::MOVINGITEM) {

		sf::Vector2f mpos = GetPosition();
		sf::Vector2f otherpos = collidedWith->GetPosition();

		float distanceMin = m_width*0.5f + collidedWith->GetWidth()*0.5f;
		float distanceMinsquared = distanceMin * distanceMin;
		float distancesquared = (otherpos.x -mpos.x) * (otherpos.x - mpos.x) + (otherpos.y - mpos.y) * (otherpos.y - mpos.y);

		if (distancesquared > distanceMinsquared)
			return;

		float overlapDistance = (distanceMin - std::sqrt(distancesquared)) * 0.5f;

		sf::Vector2f distVec = Utils::GetVectorDistance(mpos,otherpos);
		Utils::NormalizeQ(distVec);

		SetPosition(mpos.x - distVec.x * overlapDistance, mpos.y - distVec.y * overlapDistance);
		collidedWith->SetPosition(otherpos.x + distVec.x * overlapDistance, otherpos.y + distVec.y * overlapDistance);

		sf::Vector2f m_vel = GetVelocity();
		float magmvel = Utils::Getmagnitude(m_vel);

		sf::Vector2f othervel = collidedWith->GetVelocity();
		float magothermvel = Utils::Getmagnitude(othervel);

		float moyennemag = (magmvel + magothermvel) * 0.5f;

		sf::Vector2f accelerationtoadd = -distVec * moyennemag * 0.4f;
		AddAcceleration(accelerationtoadd);

		sf::Vector2f otheraccelerationtoadd = distVec * moyennemag * 0.4f;
		collidedWith->AddAcceleration(otheraccelerationtoadd);
	}

	bool behavelikewall = false;

	if (collidedWith->GetTag() == SceneTest::PIPEENDCHECK) {
		for (int i = 0; i < doorpassed.size(); i++) {
			if (collidedWith == doorpassed[i]) {
				return;
			}
		}
		Pipe* newPipeToGoTo = m_pPipeToGoTo->GetpOut();
		if (newPipeToGoTo == m_pPipeToGoTo) {
			behavelikewall = true;
		}
		else {
			doorpassed.push_back(collidedWith);
			m_pPipeToGoTo = newPipeToGoTo;
		}
	}

	if (collidedWith->GetTag() == SceneTest::PIPEWALL || behavelikewall) {

		sf::Vector2f segA = collidedWith->GetPosition(0, 0);
		sf::Vector2f segB = collidedWith->GetPosition(1, 1);

		if (collidedWith->GetWidth() == 1) {
			sf::Vector2f segB = collidedWith->GetPosition(0, 1);
		}
		else if(collidedWith->GetHeight() == 1) {
			sf::Vector2f segB = collidedWith->GetPosition(1, 0);
		}
		else {
			return;
		}

		

		float radius = m_width * 0.5f;
		sf::Vector2f circleCenter = GetPosition();
		sf::Vector2f segment = segB - segA;
		sf::Vector2f toCircle = circleCenter - segA;

		float segmentLengthSquared = (segB.x - segA.x) * (segB.x - segA.x) + (segB.y - segA.y) * (segB.y - segA.y);
		float t = std::max(0.f, std::min(1.f, (toCircle.x * segment.x + toCircle.y * segment.y) / segmentLengthSquared));

		sf::Vector2f closestPoint = segA + t * segment;
		float distFloat = (closestPoint.x - circleCenter.x) * (closestPoint.x - circleCenter.x) + (closestPoint.y - circleCenter.y) * (closestPoint.y - circleCenter.y);
		if (distFloat <= radius * radius) {
			float overlap = std::sqrt(radius * radius - distFloat);
			if (overlap > 0) {
				sf::Vector2f closestPointVec2(closestPoint.x, closestPoint.y);
				sf::Vector2f distVec = Utils::GetVectorDistance(circleCenter, closestPointVec2);

				sf::Vector2f ReflectedVec;
				Utils::Normalize(distVec);

				m_pos.x -= (distVec.x * overlap);
				m_pos.y -= (distVec.y * overlap);

				sf::Vector2f t = Utils::Reflect(distVec, this->GetVelocity());
				SetVelocity(t*0.4f);
			}
		}
	}
}
