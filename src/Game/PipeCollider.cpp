#include "pch.h"
#include "PipeCollider.h"
#include "SceneTest.h"
#include "Pipe.h"
#include "Utils.h"

PipeCollider::PipeCollider()
{
	m_collider = Entity::AABB;
	m_tag = SceneTest::PIPEWALL;

	SetSpriteTexture("cunpx");

	m_layer = 5;
	m_width = 0.f;
	m_height = 0.f;
	m_hasCollision = true;
	m_isDrawable = true;
	m_relativex = 0.f;
	m_relativey = 0.f;
}

void PipeCollider::Init(Pipe* mpipe, float relativex, float relativey, float w, float h, bool IsWall)
{
	m_pipe = mpipe;
	m_relativex = relativex;
	m_relativey = relativey;

	m_width = w;
	m_height = h;

	m_pSprite->scale({ w,h });


	if (!IsWall) {
		m_tag = SceneTest::PIPEENDCHECK;
	}
}

void PipeCollider::OnUpdate()
{
	SetPosition(m_pipe->GetPosition().x + m_relativex, m_pipe->GetPosition().y + m_relativey);

	m_pSprite->setScale({ m_width,m_height });

	m_pSprite->setOrigin({ 0,0 });

}


void PipeCollider::RotateCW(float angle)
{	
	float w = GetWidth();
	float h = GetHeight();

	SetWidth(h);
	SetHeight(w);

	sf::Vector2f newpos = Utils::rotate_pointCW(0,0,angle,{ m_relativex,m_relativey});
	m_relativex = newpos.x;
	m_relativey = newpos.y;
}


