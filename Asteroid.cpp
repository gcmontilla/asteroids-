//
// Created by Gregory Montilla on 12/10/17.
//

//#include "Spaceship.cpp"
#include "Asteroid.h"
#include <cmath>

using namespace std;

Asteroid::Asteroid(Texture &t) {
    s.setTexture(t);
    s.setOrigin(t.getSize().x/2, t.getSize().y/2);
    s.setScale(generateOutside(1,2), generateOutside(1,2));
    spawn();
    speed = generateOutside(10,20);
}

void Asteroid::chase(Vector2f direction) {
    s.move(direction*speed);
}

void Asteroid::draw(RenderWindow &window) {
    window.draw(s);
}

Vector2f Asteroid::aim(Spaceship spaceship) {
    Vector2f ss = spaceship.getPosition();
    Vector2f a = s.getPosition();
    Vector2f aim = ss-a;
    Vector2f aimNorm = aim / sqrtf(powf(aim.x, 2.f) + powf(aim.y, 2.f));
    return aimNorm;
}

void Asteroid::spawn() {
    int random = rand() % 4;
    float x, y;
    switch (random) {
        case 0:
            x = generateOutside(-X, 0);
            y = generateOutside(0, Y);
            break;
        case 1:
            x = generateOutside(10+X, X);
            y = generateOutside(0, Y);
            break;
        case 2:
            x = generateOutside(0, X);
            y = generateOutside(-Y, 0);
            break;
        case 3:
            x = generateOutside(0, X);
            y = generateOutside(10+Y, Y);
            break;
    }
    s.setPosition(x,y);
}

float Asteroid::generateOutside(int low, int hi) {
    float x = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(hi-low)))+low;
    return x;
}

void Asteroid::straight(float x, float y) {
    float dx = (x-s.getPosition().x)*speed;
    float dy = (y-s.getPosition().y)*speed;
    float angle = atan(dy/dx);
    Vector2f direction (-speed*cosf(angle), -speed*sinf(angle));
    s.move(direction);
}

Vector2f Asteroid::getPosition() {
    return s.getPosition();
}

FloatRect Asteroid::getBounds() {
    return s.getGlobalBounds();
}