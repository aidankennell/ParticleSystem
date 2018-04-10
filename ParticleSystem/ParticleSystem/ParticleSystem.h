#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ParticleSystem.h"
#include "Particle.h"

#include<iostream>
using namespace std;

class ParticleSystem : public sf::Drawable, public sf::Transformable{
private:
	int angleRange;
	int easingType;
	int totalParticles;
	sf::Vector2f emissionLocation;
	std::vector<Particle*> particles;
	sf::Texture particleTex;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	ParticleSystem(int numberOfParticles, sf::Vector2f pos);
	ParticleSystem(int numberOfParticles, int angleRange, sf::Vector2f emissionLocation, sf::Texture& tex, int easingType);
	~ParticleSystem();
	void update(float dt);
	void increaseParticleCount(int numNewParticles);
};

