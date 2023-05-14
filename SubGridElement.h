#pragma once
class SubGridElement
{
public:
	int getRotation();
	int getType();
	int getSide();
	void setSide(int newSide);
	void setRotation(int newRotation);
	SubGridElement();
protected:
	int rotation;
	int type;
	int side;
};

