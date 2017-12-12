//
// Created by Gregory Montilla on 12/11/17.
//

#include "Game.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Spaceship.cpp"
#include "Bullet.cpp"
#include "Asteroid.cpp"

void Game::Run() {
    Clock clock;
    float spawnTimer = 0;
    float bulletTimer = 0;
    srand(time(NULL));
    RenderWindow game(VideoMode(W, H), "ASTEROIDS!");
    game.setFramerateLimit(60);
    int score = 0;
    bool play = true;

    Font font;
    font.loadFromFile("OpenSans-Regular.ttf");

    Text scoreText(to_string(score), font, 65);
    Text asteroidsText("ASTEROIDS", font, 65);
    asteroidsText.setFillColor(Color::White);
    asteroidsText.setPosition(25,20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition((asteroidsText.getPosition().x+asteroidsText.getGlobalBounds().width)+25,20);

    Texture background, ship, bullet, asteroid;
    background.loadFromFile("background.png");
    ship.loadFromFile("ship.png");
    bullet.loadFromFile("bullet.png");
    asteroid.loadFromFile("asteroid.png");

    background.setSmooth(true);
    ship.setSmooth(true);
    bullet.setSmooth(true);
    asteroid.setSmooth(true);

    Sprite bg(background);
    Sprite test(asteroid);
    Spaceship ss(ship);

    vector<Bullet> bullets;
    vector<Asteroid> asteroids;
    vector<Vector2f> points;
    int i = 0;
    while (game.isOpen()) {
        game.clear();
        Event e;
        if (play) {
            scoreText.setString(to_string(score));
            spawnTimer += clock.getElapsedTime().asSeconds() / 100;
            bulletTimer += clock.getElapsedTime().asSeconds() / 100;

            while (game.pollEvent(e)) {
                switch (e.type) {
                    case Event::Closed:
                        game.close();
                        break;
                    case Event::MouseButtonReleased:
                        cout << e.mouseButton.x << endl;
                        cout << e.mouseButton.y << endl;

                    default:
                        break;
                }
            }

            while (asteroids.size() < 50 && spawnTimer > 3) {
                Asteroid a(asteroid);
                asteroids.push_back(a);
                points.push_back(ss.getPosition());
                spawnTimer = 0;
            }

            if (Keyboard::isKeyPressed(Keyboard::A)) {
                ss.turnLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                ss.turnRight();
            }
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                ss.thrust();
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                if (bulletTimer > 2) {
                    Bullet nb(bullet);
                    nb.setRotation(ss.getRotation());
                    nb.setPosition(ss.getX(), ss.getY());
                    bullets.push_back(nb);
                    bulletTimer = 0;
                }
            }

            game.clear();
            game.draw(bg);

            for (int i = 0; i < bullets.size(); i++) {
                bullets[i].draw(game);
                bullets[i].fire();
            }

            for (int i = 0; i < asteroids.size(); i++) {
                asteroids[i].draw(game);
                asteroids[i].straight(points[i].x, points[i].y);
            }

            for (int i = 0; i < bullets.size(); i++) {
                if (bullets[i].getPosition().x < -20 || bullets[i].getPosition().x > W + 20 ||
                    bullets[i].getPosition().y < -20 || bullets[i].getPosition().y > H + 20) {
                    bullets.erase(bullets.begin() + i);
                } else {
                    for (int j = 0; j < asteroids.size(); j++) {
                        if (asteroids[j].getPosition().x < -20 || asteroids[j].getPosition().x > W + 20 ||
                            asteroids[j].getPosition().y < -20 || asteroids[j].getPosition().y > H + 20) {
                            asteroids.erase(asteroids.begin() + j);
                        } else if (asteroids[j].getBounds().intersects(bullets[i].getBounds())) {
                            asteroids.erase(asteroids.begin() + j);
                            bullets.erase(bullets.begin() + i);
                            score ++;
                            break;
                        }
                    }
                }
            }

            for (int i = 0; i < asteroids.size(); i++) {
                if (asteroids[i].getBounds().intersects(ss.getBounds())) {
                    play = false;
                }
            }

            ss.draw(game);
            game.draw(scoreText);
            game.draw(asteroidsText);
            game.display();
        } else {
            Event e;
            Text lose("YOU LOST!", font, 250);
            lose.setFillColor(Color::Red);
            lose.setOrigin(lose.getGlobalBounds().width/2, lose.getGlobalBounds().height/2);
            lose.setPosition(W/2,H/2-200);
            Text restart("PLAY AGAIN?", font, 200);
            restart.setOrigin(restart.getGlobalBounds().width/2, restart.getGlobalBounds().height/2);
            restart.setPosition(W/2, H/2+ 200);
            restart.setFillColor(Color::Red);


            while (game.pollEvent(e)) {
                switch (e.type) {
                    case Event::Closed:
                        game.close();
                        break;
                    case Event::MouseButtonReleased:
                        int x = e.mouseButton.x;
                        int y = e.mouseButton.y;
                        if (restart.getGlobalBounds().contains(x,y)) {
                            asteroids.clear();
                            points.clear();
                            bullets.clear();
                            score = 0;
                            clock.restart();
                            spawnTimer = 0;
                            bulletTimer = 0;
                            play = true;
                            break;
                        }
                }
            }
            game.draw(bg);
            game.draw(asteroidsText);
            game.draw(restart);
            game.draw(lose);
            game.draw(scoreText);
            game.display();
        }
    }
}