#pragma once

class Scene;
class Sprite;
class Color;
class Animation;
class UIEntity;

#include <list>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <optional>

class Entity
{
public:

    enum Collider : int {
        AABB,
        Circle
    };
    struct Target
    {
        sf::Vector2i position;
        float distance;
        bool isSet;
    };

protected:

   

    sf::Sprite* m_pSprite = nullptr;

    sf::Vector2f m_pos = sf::Vector2f(0.0f, 0.0f);

    sf::Vector2f m_velocity = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f m_acceleration = sf::Vector2f(0.0f, 0.0f);
    Target m_target = {};
    float m_speed = 0.0f;

    float m_width = 0.0f;
    float m_height = 0.0f;
    int m_tag = 0;
    std::list<int> m_tagWithoutCollision = {};
    
    const char* m_name = "Entity";

    int m_layer = 0;
    Animation* m_pCurrentAnimation = nullptr;
    int m_currentFrameIndex = 0; 
    float m_currentFrameTime = 0.0f;

    bool m_toDestroy = false;
    
    bool m_isActive = true;

    bool m_hasCollision = false;

    bool m_isDrawable = false;

    bool m_isUI = false;
    bool m_isText = false;

    Scene* m_pScene = nullptr;

    bool m_hasTickEvent = false;

    std::list<Entity*>::iterator* m_pDrawIterator = nullptr;
    std::list<Entity*>::iterator* m_pColliderIterator = nullptr;

    Entity::Collider m_collider = Entity::Collider::AABB;

public:
    
    

    // Position
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;

    // Movement
    bool GoToDirection(int x, int y, float speed = -1.f);
    
    void SetVelocity(float x, float y);
    void SetVelocity(sf::Vector2f velocity);
    void SetAcceleration(float x, float y);
    void AddAcceleration(float x, float y);
    void AddAcceleration(sf::Vector2f acceleration);

    sf::Vector2f GetVelocity() const { return m_velocity; }
    sf::Vector2f GetAcceleration() const { return m_acceleration; }
    
    bool AttractToPosition(int x, int y, float speed = -1.f);
    bool ReppelFromPosition(int x, int y, float speed = -1.f);

    void SetSpeed(float speed);

    // Collisions
    
    void SetTag(int tag);
    int GetTag();

    Entity::Collider GetCollider();

    bool IsColliding(Entity* other) const;
    bool isAABBColliding(float x1,float y1,float w1,float h1, float x2, float y2, float w2, float h2) const;
    bool isCircleColliding(float x1, float y1, float r1, float x2, float y2, float r2) const;
    bool isAABBCircleColliding(float x1, float y1, float w1, float h1, float x2, float y2, float r2) const;
    bool IsInside(float x, float y) const;

    bool AllowedCollision(Entity* pEntity);
    void AddTagWithoutCollision(int tag) { m_tagWithoutCollision.push_back(tag); }

    // Values
    void SetName(const char* name) { m_name = name; }
    const char* GetName();

    void SetScale(float scaleX, float scaleY);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);
    float GetWidth() const;
    float GetHeight() const;

    virtual void SetLayer(int layer);
    virtual int GetLayer() { return m_layer; }

    void SetSpriteTexture(const char* texturePath);
    void SetSpriteTexture(sf::Texture* texture);
    void ChangeSprite(sf::Sprite* pSprite);
    sf::Sprite* GetSprite();


	bool IsTag(int tag) const { return m_tag == tag; }

	void Destroy() { m_toDestroy = true; }
	bool ToDestroy() const { return m_toDestroy; }

	template<typename T>
	T* GetScene() const;
    Scene* GetScene() const;

	float GetDeltaTime() const;
	
    bool PlayAnimation(const char* animationName);
    void StopAnimation();

    template<typename T>
    T* CreateEntity();

    void DisplayEntity();
    void HideEntity();

protected:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnFixedUpdate() {};
    virtual void OnInitialize() {};
    virtual void OnCollision(Entity* collidedWith) {};
    virtual void OnTick() {};

private:
    void Update();
    void FixedUpdate();

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"