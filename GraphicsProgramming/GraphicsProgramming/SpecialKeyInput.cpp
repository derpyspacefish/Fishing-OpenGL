#include "SpecialKeyInput.h"

bool SpecialKeyInput::isKeyDown(SPECIALKEY key)
{
	if (keys[key] == true)
	{
		return true;
	}
	return false;
}

void SpecialKeyInput::setKeyDown(SPECIALKEY key)
{
	keys[key] = true;
}

void SpecialKeyInput::setKeyUp(SPECIALKEY key)
{
	keys[key] = false;
}
