#include "UiBase.h"

namespace sw
{
	UiBase::UiBase(eUIType type)
		: mType(type)
		, mbFullScreen(false)
		, mbEnable(false)
	{
		
	}

	UiBase::~UiBase()
	{

	}

	void UiBase::Initialize()
	{
	}

	void UiBase::Active()
	{
	}

	void UiBase::InActive()
	{
	}

	void UiBase::Tick()
	{
	}

	void UiBase::Render(HDC hdc)
	{
	}

	void UiBase::UIClear()
	{
	}
}