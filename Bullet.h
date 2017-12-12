//
// Created by Gregory Montilla on 12/10/17.
//

#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H


class Bullet {
public:
    Bullet(Texture &t);
    Vector2f _direction;
    void draw(RenderWindow &window);
    void setDirection(Vector2f &direction);
    void setPosition(float x, float y);
    void fire();
    void setRotation(float angle);
    Vector2f getPosition();
    FloatRect getBounds();
    bool life = true;
private:
    Sprite s;
    float MAX_SPEED = 25;
};


#endif //ASTEROIDS_BULLET_H
