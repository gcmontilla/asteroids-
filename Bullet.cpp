//
// Created by Gregory Montilla on 12/10/17.
//

#include "Bullet.h"

using namespace std;
Bullet::Bullet(Texture &t) {
    s.setTexture(t);
    s.setOrigin(t.getSize().x/2, t.getSize().y/2);
}

void Bullet::draw(RenderWindow &window) {
    window.draw(s);
}

void Bullet::setDirection(Vector2f &direction) {
    _direction = direction;
}

void Bullet::setPosition(float x, float y) {
    s.setPosition(x,y);
}

void Bullet::setRotation(float angle) {
    s.setRotation(angle);
}

void Bullet::fire() {
    float rads = (3.1415926536f/180)*s.getRotation();
    // cout << s.getRotation() << endl;
    //cout << "rad " << rads << endl;
    Vector2f direction (MAX_SPEED*sinf(rads), -MAX_SPEED*cosf(rads));
    s.move(direction);
}

Vector2f Bullet::getPosition() {
    return s.getPosition();
}

FloatRect Bullet::getBounds() {
    return s.getGlobalBounds();
}