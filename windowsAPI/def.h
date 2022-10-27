#pragma once

#define SINGLE(type)						\
public:										\
	static type* GetInstance()				\
	{										\
		static type* mInstance;				\
		if (mInstance == nullptr)			\
		{									\
			mInstance = new type();			\
			return mInstance;				\
		}									\
		return mInstance;					\
	}										\
											\
	static void DistroyInstance()			\
	{										\
	if (GetInstance())						\
		delete GetInstance();				\
	}										\
											\
private:									\
	type();									\
	~type();								\

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

enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};

enum class eBrushColor
{
	Transparent, // ≈ı∏Ì
	Black,
	Gray, // 71, 71, 71
	White,
	End,
};

enum class eComponentType
{
	Animator,
	Collider,
	Sound,
	End
};