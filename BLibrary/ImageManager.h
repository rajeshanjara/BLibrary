#pragma once

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
};

