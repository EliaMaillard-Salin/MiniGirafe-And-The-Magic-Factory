#pragma once
#include "Button.h"

class PlayButton : public Button
{
	UIText* m_pTitle = nullptr;

public:
	PlayButton() = default;
	~PlayButton();

	void Init(std::string text);

	void OnClick() override;
};

class QuitButton : public Button
{
	UIText* m_pTitle = nullptr;

public:
	QuitButton() = default;
	~QuitButton();

	void Init(std::string text);

	void OnClick() override {};
};

class SettingsButton : public Button
{
	UIText* m_pTitle = nullptr;

public:
	SettingsButton() = default;
	~SettingsButton();

	void Init(std::string text);

	void OnClick() override {};
};

