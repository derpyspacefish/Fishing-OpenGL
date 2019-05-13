#pragma once
class SpecialKeyInput
{
public:
	enum SPECIALKEY {SHIFT, CTRL};
	bool isKeyDown(SPECIALKEY key);
	void setKeyDown(SPECIALKEY key);
	void setKeyUp(SPECIALKEY key);
private:
	bool keys[2];
};

