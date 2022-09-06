
#ifndef RECT
#define RECT true
#include "Point.h"

struct Rect{
    float x;
    float y;
    float w;
    float h;

    Rect() : Rect(0, 0, 0, 0){}
    Rect(float x, float y) : Rect(x, y, 0, 0){}

    Rect(float x, float y, float w, float h)
    {
        if(w < 0){
            x += w;
            w *= -1;
        }
        if(h < 0){
            y += h;
            h *= -1;
        }
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    void include(Point p){
      if(p.x < this->x){
        this->w += this->x - p.x;
        this->x = p.x;
      }
      if(p.y < this->y){
        this->w += this->y - p.y;
        this->y = p.y;
      }
      if(p.x > this->x + this->w){
        this->w += p.x - (this->x + this->w);
      }
      if(p.y > this->y + this->h){
        this->h += p.y - (this->y + this->h);
      }
    }

    bool contains(Point a){
        if(this->x > a.x)
            return false;
        if(this->y > a.y)
            return false;
        if(this->x + this->w < a.x)
            return false;
        if(this->y + this->h < a.y)
            return false;
        return true;
    }

    bool overlaps(Rect a){
        if(this->x > a.x + a.w)
            return false;
        if(this->y > a.y + a.h)
            return false;
        if(this->x + this->w < a.x)
            return false;
        if(this->y + this->h < a.y)
            return false;
        return true;
    }

    std::string encode()
    {
    char *data = new char[4 * sizeof(float)];
    int size = 0;

    // X
    memcpy(data + size, &(this->x), sizeof(this->x));
    size += sizeof(this->x);
    // Y
    memcpy(data + size, &(this->y), sizeof(this->y));
    size += sizeof(this->y);
    // W
    memcpy(data + size, &(this->w), sizeof(this->w));
    size += sizeof(this->w);
    // H
    memcpy(data + size, &(this->h), sizeof(this->h));
    size += sizeof(this->h);

    return std::string(data, size);
    }

};

#endif
