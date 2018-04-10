#include "Particle.h"


Particle::Particle(sf::Vector2f pos, sf::Texture& tex, int easingType) {
	lifeTime = 0.f;
	lifeLeft = 0.f;
	particleSize = sf::Vector2f(12, 12);
	rect.setSize(particleSize);
	rect.setOrigin(particleSize.x / 2, particleSize.y / 2);
	rect.setPosition(pos);
	this->tex = tex;
	this->easingType = easingType;
	rect.setTexture(&this->tex);
}

Particle::~Particle() {
	
}

void Particle::update(float dt) {
	sf::Vector2f oldSize = rect.getSize();
	lifeLeft -= dt;

	switch (easingType){
	case 1:
		rect.setPosition(quadEasing(dt));
		break;
	case 2:
		rect.setPosition(sinEasing(dt));
		break;
	case 3:
		rect.setPosition(expoEasing(dt));
		break;
	default:
		rect.setPosition(rect.getPosition() + vel * dt);
		break;
	}
	rect.setSize(sf::Vector2f(oldSize.x + scaleFactor*dt, oldSize.y + scaleFactor*dt));
}

void Particle::resetParticle(float lifeTime, sf::Vector2f vel, sf::Vector2f pos) {
	this->lifeTime = lifeTime;
	this->lifeLeft = lifeTime;
	this->vel = vel;
	rect.setPosition(pos);
	rect.setSize(particleSize);
}


void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(rect, states);
}

sf::Vector2f Particle::quadEasing(float dt) {
	float t = lifeTime / lifeLeft;
	
	return vel*t*t*dt + rect.getPosition();
}

sf::Vector2f Particle::sinEasing(float dt) {
	return vel * std::sin(lifeTime / lifeLeft * (3.14f / 2.f)) * dt + rect.getPosition();
}

sf::Vector2f Particle::expoEasing(float dt) {
	float pow = std::pow(2, 10.f * (lifeTime / lifeLeft - 1));
	return rect.getPosition() + vel * dt  * pow;
}

