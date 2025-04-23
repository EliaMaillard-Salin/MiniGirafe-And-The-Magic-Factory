#include "pch.h"
#include "main.h"
#include "GameManager.h"
#include "SceneTest.h"
#include "SceneMenu.h"

int main()
{
	GameManager* pInstance = GameManager::Get();
	
	pInstance->CreateNewWindow(1920, 1080, "Test",5000);

	pInstance->LaunchScene<SceneTest>();

	return 0;
}