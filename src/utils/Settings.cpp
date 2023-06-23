#include "Settings.h"

float Settings::scale;
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
