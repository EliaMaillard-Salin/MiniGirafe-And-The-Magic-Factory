#include "pch.h"
#include "Prop.h"

void RessourcesProp::Init(RESSOURCES_PROPS propID, PROP_STATE propState )
{
    std::string textureName = "PropTexture_";
    textureName += (int)propID;
    m_ressourceID = propID;
    m_state = propState;
    m_ID = propID + propState;
    SetSpriteTexture("PropTexture");
    // TOCHANGE
}


void Potion::Init(POTION_TYPES type)
{
    m_ID = type;
    m_type = type;
    SetSpriteTexture("PropTexture"); // TOCHANGE AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAALED
}

int Prop::GetID()
{
    return m_ID;
}
