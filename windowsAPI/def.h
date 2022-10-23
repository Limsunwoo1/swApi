#pragma once

#define KEY_PRESSE(KEY) sw::Input::GetkeyState(KEY) == sw::eKeyState::PRESSED
#define KEY_DOWN(KEY) sw::Input::GetkeyState(KEY) == sw::eKeyState::DOWN
#define KEY_UP(KEY) sw::Input::GetkeyState(KEY) == sw:: eKeyState::UP

enum class eSceneType
{
	Logo,
	Title,
	Play,
	End,
	Max,
};