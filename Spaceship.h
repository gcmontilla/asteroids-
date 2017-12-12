//
// Created by Gregory Montilla on 12/10/17.
//

#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H
#include <SFML/Graphics.hpp>

using namespace sf;
const int W = 2048;
const int H = 1536;

class Spaceship {
public:
    Spaceship(Texture &t);
    void draw(RenderWindow & window);
    void turnLeft();
    void turnRight();
    void thrust();
    float getX();
    float getY();
    Vector2f getDirection();
    Vector2f getPosition();
    float getRotation();
    FloatRect getBounds();
private:
    Sprite s;
};

#endif //ASTEROIDS_SPACESHIP_H
