#include "pch.h"
#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "AssetManager.h"
#include "AnimationManager.h"

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (speed > 0) {
		m_speed = speed;
	}

	sf::Vector2f position = GetPosition(0.5f, 0.5f);
		
	m_target.position = { x, y };
	m_target.distance = Utils::GetDistancesqrd(position.x, position.y, x, y);
	m_target.isSet = true;

	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;
	m_velocity = direction * m_speed;

	return true;
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{

	x -= GetWidth() * ratioX;
	y -= GetHeight() * ratioY;

	m_pos.x = x;
	m_pos.y = y;

	if (m_pSprite != nullptr)

		m_pSprite->setPosition(GetPosition(0.0f,0.0f));
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position = m_pos; // Top Left pos

	position.x += m_width * ratioX;
	position.y += m_height * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	if (speed > 0) {
		m_speed = speed;
	}

	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);

	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	m_velocity = direction * m_speed;

	return true;
}

void Entity::SetVelocity(float x, float y)
{

	m_velocity = sf::Vector2f(x, y);
	m_target.isSet = false;
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void Entity::SetAcceleration(float x, float y)
{
	m_acceleration = sf::Vector2f(x, y);
	m_target.isSet = false;
}

void Entity::AddAcceleration(float x, float y)
{
	m_acceleration += sf::Vector2f(x, y);
	m_target.isSet = false;
}

void Entity::AddAcceleration(sf::Vector2f acceleration)
{
	m_acceleration += acceleration;
	m_target.isSet = false;
}

bool Entity::AttractToPosition(int x, int y, float speed)
{
	if (speed > 0) {
		m_speed = speed;
	}

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	m_target.position = { x, y };
	m_target.distance = Utils::GetDistancesqrd(position.x, position.y, x, y);
	m_target.isSet = true;

	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;
	m_acceleration += direction * m_speed;

	return true;
}

bool Entity::ReppelFromPosition(int x, int y, float speed)
{
	if (speed > 0) {
		m_speed = speed;
	}

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	m_target.position = { x, y };
	m_target.distance = Utils::GetDistancesqrd(position.x, position.y, x, y);
	m_target.isSet = true;

	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;
	m_acceleration += -direction * m_speed;

	return true;
}

void Entity::SetSpeed(float speed) { m_speed = speed; }

void Entity::SetTag(int tag) { m_tag = tag; }

int Entity::GetTag() { return m_tag; }

Entity::Collider Entity::GetCollider()
{
	return m_collider;
}

bool Entity::IsColliding(Entity* other) const
{
	float otherwidth = other->GetWidth();
	float otherheight = other->GetHeight();

	bool iscolliding = false;

	if (m_collider == Entity::Collider::AABB) {
		sf::Vector2f position = GetPosition(0,0);
		if (other->GetCollider() == Entity::Collider::AABB) {
			sf::Vector2f otherPosition = other->GetPosition(0, 0);
			return isAABBColliding(position.x, position.y, m_width, m_height, otherPosition.x, otherPosition.y, otherwidth, otherheight);
		}
		else if (other->GetCollider() == Entity::Collider::Circle) {
			sf::Vector2f otherPosition = other->GetPosition();
			return isAABBCircleColliding(position.x, position.y, m_width, m_height, otherPosition.x, otherPosition.y, otherwidth*0.5f);
		}
	}
	else if (m_collider == Entity::Collider::Circle) {
		sf::Vector2f position = GetPosition();
		if (other->GetCollider() == Entity::Collider::AABB) {
			sf::Vector2f otherPosition = other->GetPosition(0, 0);

			return isAABBCircleColliding(otherPosition.x, otherPosition.y, otherwidth, otherheight, position.x, position.y, m_width*0.5f);
		}
		else if (other->GetCollider() == Entity::Collider::Circle) {
			sf::Vector2f otherPosition = other->GetPosition();

			return isCircleColliding(position.x, position.y, m_width *0.5f, otherPosition.x, otherPosition.y, otherwidth *0.5f);
		}
	}

	return iscolliding;
}

bool Entity::isAABBColliding(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) const
{
	bool FromRight = x1 > x2 + w2;
	bool FromLeft = x1 + w1 < x2;
	bool FromTop = y1 + h1 < y2;
	bool FromBottom = y1 > y2 + h2;

	return !(FromRight || FromLeft || FromTop || FromBottom);
}

bool Entity::isCircleColliding(float x1, float y1, float r1, float x2, float y2, float r2) const
{
	float MinDist = r1 + r2;
	sf::Vector2f DistVec = { x1-x2, y1-y2 };
	float Dist = DistVec.dot(DistVec);

	return (MinDist * MinDist >= Dist);
}

bool Entity::isAABBCircleColliding(float x1, float y1, float w1, float h1, float x2, float y2, float r2) const
{
	float testX = x2;
	float testY = y2;

	if (x2 < x1)
		testX = x1;
	else if (x2 > x1 + w1)
		testX = x1 + w1;

	if (y2 < y1)
		testY = y1;    
	else if (y2 > y1 + h1)
		testY = y1 + h1;

	float distX = x2 - testX;
	float distY = y2 - testY;
	float distance = (distX * distX) + (distY * distY);

	return (distance <= r2 * r2);
}

bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.0f,0.0f);

	bool AisToTheRightOfB = position.x > x;
	bool AisToTheLeftOfB = position.x + GetWidth() < x;
	bool AisAboveB = position.y + GetHeight() < y;
	bool AisBelowB = position.y > y;

	return !(AisToTheRightOfB || AisToTheLeftOfB || AisAboveB || AisBelowB);

}

bool Entity::AllowedCollision(Entity* pEntity)
{
	for (int notAllowedTag : m_tagWithoutCollision)
	{
		if (notAllowedTag == pEntity->m_tag)
			return false;
	}
	return true;
}

Scene* Entity::GetScene() const
{
	return m_pScene;
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}

void Entity::SetLayer(int layer)
{
	if (m_pDrawIterator != nullptr)
		GetScene()->ChangeEntityLayer(this, layer);
	m_layer = layer;
}


const char* Entity::GetName()
{
	return m_name;
}
 
float Entity::GetWidth() const
{
	return m_width;
}

float Entity::GetHeight() const
{
	return m_height;
}

void Entity::SetSpriteTexture(const char* texturePath)
{
	sf::Texture* ptexture = AssetManager::GetTexture(texturePath);
	if (ptexture == nullptr)
		return;
	if (m_pSprite == nullptr)
		m_pSprite = new sf::Sprite(*ptexture);
	else
		m_pSprite->setTexture(*ptexture);
	m_width = m_pSprite->getTextureRect().size.x;
	m_height = m_pSprite->getTextureRect().size.y;
}

void Entity::SetSpriteTexture(sf::Texture* texture)
{
	if (texture == nullptr)
		return;
	if (m_pSprite == nullptr)
		m_pSprite = new sf::Sprite(*texture);
	else
		m_pSprite->setTexture(*texture);
	m_width = m_pSprite->getTextureRect().size.x;
	m_height = m_pSprite->getTextureRect().size.y;
}

void Entity::ChangeSprite(sf::Sprite* pSprite)
{
	m_pSprite = pSprite;
}

sf::Sprite* Entity::GetSprite()
{
	return m_pSprite;
}

void Entity::SetScale(float scaleX, float scaleY)
{
	m_pSprite->setScale(sf::Vector2f(scaleX, scaleY));
}

void Entity::SetWidth(float width)
{
	m_width = width;
}

void Entity::SetHeight(float height)
{
	m_height = height;
}

void Entity::SetSize(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

void Entity::Update()
{

	if (m_pCurrentAnimation != nullptr)
	{
		if (m_pCurrentAnimation->Update(&m_currentFrameIndex, &m_currentFrameTime, m_pSprite) == false)
			StopAnimation();
	}
	OnUpdate();
}

void Entity::FixedUpdate()
{
	m_velocity += m_acceleration;
	m_acceleration = sf::Vector2f(0.f, 0.f);
	sf::Vector2f translation = m_velocity * FIXED_DT;
	m_pos += translation;

	/*if (m_target.isSet)
	{
		m_target.distance -= distance;

		if (m_target.distance <= 0.f)
		{
			SetPosition(m_target.position.x, m_target.position.y);
			m_direction = sf::Vector2f(0.f, 0.f);
			m_target.isSet = false;
		}
	}*/

	OnFixedUpdate();
}


bool Entity::PlayAnimation(const char* animationName)
{
	Animation* pAnim = AnimationManager::Get()->GetAnimation(animationName);
	if (pAnim != nullptr)
	{
		m_pSprite = pAnim->GetSprite();
		m_pCurrentAnimation = pAnim;
		m_currentFrameIndex = 0;
		m_currentFrameTime = 0.f;
		m_pCurrentAnimation->PlayAnimation(m_pSprite);
		return true;
	}
	return false;
}

void Entity::StopAnimation()
{
	m_pCurrentAnimation = nullptr;
}

void Entity::DisplayEntity()
{
	m_isDrawable = true;
}

void Entity::HideEntity()
{
	m_isDrawable = false;
}
