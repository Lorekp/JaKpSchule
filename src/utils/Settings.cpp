#include "Settings.h"

float Settings::scale;
float Settings::fontSize;
Settings* Settings::sInstance = nullptr;

Settings::Settings()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

void Settings::setScale(float& newScale)
{
	sInstance->scale = newScale;
}

float& Settings::getScale()
{
	return sInstance->scale;
}

void Settings::setFontSize(float& newFontSize)
{
	sInstance->fontSize = newFontSize;
}

float& Settings::getFontSize()
{
	return sInstance->fontSize;
}
