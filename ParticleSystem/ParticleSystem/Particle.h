#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
using namespace std;

class Particle :public sf::Drawable, sf::Transformable {

private:
	float lifeTime;
	float lifeLeft;
	int scaleFactor = 20;
	int easingType;
	sf::Vector2f vel;
	sf::Vector2f particleSize;
	sf::RectangleShape rect;
	sf::Texture tex;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f quadEasing(float dt);
	sf::Vector2f sinEasing(float dt);
	sf::Vector2f expoEasing(float dt);

public:
	Particle(sf::Vector2f pos, sf::Texture& tex, int easingType);
	~Particle();

	void update(float dt);
	void setVel(sf::Vector2f vel) { this->vel = vel; }
	void setLifeTime(float lifeTime) { this->lifeTime = lifeTime; this->lifeLeft = lifeTime; }
	float getLifeLeft() { return this->lifeLeft; }
	void resetParticle(float lifeTime, sf::Vector2f vel, sf::Vector2f pos);
};