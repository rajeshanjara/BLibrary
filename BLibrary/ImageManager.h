#pragma once
#include "openjpeg-2.1\openjpeg.h"

typedef enum
{
    PNG, JPG
}IMAGE_e;

class image
{
public:
    virtual SIZE getDimension() = 0;
};

class icon : public image
{};

class thumbnail : public image
{};

class normal : public image
{};

class imageutil
{
    bool compress(SIZE) {}
};


class ImageManager
{
public:
    ImageManager();
    ~ImageManager();
    bool loadImage(LPCSTR lpcszFilename);
};

