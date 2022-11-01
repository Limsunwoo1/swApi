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


#define KEY_PRESSE(KEY) sw::Input::GetInstance()->GetkeyState(KEY) == sw::eKeyState::PRESSED
#define KEY_DOWN(KEY) sw::Input::GetInstance()->GetkeyState(KEY) == sw::eKeyState::DOWN
#define KEY_UP(KEY) sw::Input::GetInstance()->GetkeyState(KEY) == sw:: eKeyState::UP

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

#define COLLIDER_LAYER 16

enum class eColliderLayer : short
{
	Default,
	BackGround,
	Tile,
	Player,
	Player_ProjectTile,
	Monster,
	Monster_ProjectTile,


	UI = COLLIDER_LAYER - 1,
	END = COLLIDER_LAYER,
};

union ColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};

	UINT64 ID;
};

enum class EventType
{
	NONE,
	AddObejct,
	DeleteObject,
	End,
};

struct EventInfo
{
	EventType Type;
	void* Parameter1;
	void* Parameter2;
	void* Parameter3;


	EventInfo() : Type(EventType::NONE), Parameter1(nullptr), Parameter2(nullptr), Parameter3(nullptr) {};
	EventInfo(EventType InType) : Type(InType), Parameter1(nullptr), Parameter2(nullptr), Parameter3(nullptr) {};
	EventInfo(EventType InType, void* InParameter1) : Type(InType), Parameter1(InParameter1), Parameter2(nullptr), Parameter3(nullptr) {};
	EventInfo(EventType InType, void* InParameter1, void* InParameter2) : Type(InType), Parameter1(InParameter1), Parameter2(InParameter2), Parameter3(nullptr) {};
	EventInfo(EventType InType, void* InParameter1, void* InParameter2, void* InParameter3) : Type(InType), Parameter1(InParameter1), Parameter2(InParameter2), Parameter3(InParameter3) {};

	~EventInfo() = default;
};