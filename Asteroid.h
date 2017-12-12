//
// Created by Gregory Montilla on 12/10/17.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include <SFML/Graphics.hpp>

using namespace sf;
int MAX = 25;
int X = 2048;
int Y = 1536;

class Asteroid {
public:
    Asteroid(Texture &t);
    void spawn();
    void chase(Vector2f direction);
    void draw(RenderWindow &window);
    Vector2f aim(Spaceship spaceship);
    void straight(float x, float y);
    float generateOutside(int low, int hi);
    void changeSpeed();
    Vector2f getPosition();
    FloatRect getBounds();
    bool life=true;
private:
    Sprite s;
    float speed;
};
#endif //ASTEROIDS_ASTEROID_H
