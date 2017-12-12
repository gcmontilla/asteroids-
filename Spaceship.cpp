//
// Created by Gregory Montilla on 12/10/17.
//

#include "Spaceship.h"
#include <cmath>

Spaceship::Spaceship(Texture &t) {
    s.setTexture(t);
    s.setOrigin(t.getSize().x/2, t.getSize().y/2);
    s.setScale(.3f, .3f);
    s.setPosition(W/2, H/2);
}

void Spaceship::draw(RenderWindow &window) {
    window.draw(s);
}

void Spaceship::turnLeft() {
    s.rotate(-10.f);
}

void Spaceship::turnRight() {
    s.rotate(10.f);
}

void Spaceship::thrust() {
    Vector2f direction = getDirection();
    s.move(direction);
}

float Spaceship::getX() {
    return s.getPosition().x;
}

float Spaceship::getY() {
    return s.getPosition().y;
}

Vector2f Spaceship::getDirection() {
    float rads = (3.1415926536f/180)*s.getRotation();
    Vector2f direction (10*sinf(rads), -10*cosf(rads));
    return direction;
}

float Spaceship::getRotation() {
    return s.getRotation();
}

Vector2f Spaceship::getPosition() {
    return s.getPosition();
}

FloatRect Spaceship::getBounds() {
    return s.getGlobalBounds();
}