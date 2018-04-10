#include "ParticleSystem.h"
#include "Particle.h"
#include <ostream>

ParticleSystem::ParticleSystem(int numberOfParticles, sf::Vector2f pos) {
	this->angleRange = 45;
	this->totalParticles = numberOfParticles;
	this->emissionLocation = pos;

	particles.resize(numberOfParticles);
	for (int i = 0; i < numberOfParticles; i++)
		particles[i] = new Particle(emissionLocation, particleTex, easingType);
}

ParticleSystem::ParticleSystem(int numberOfParticles, int angleRange, sf::Vector2f emissionLocation, sf::Texture& tex, int easingType) {
	this->angleRange = angleRange;
	this->totalParticles = numberOfParticles;
	this->emissionLocation = emissionLocation;
	this->particleTex = tex;
	this->easingType = easingType;

	particles.resize(numberOfParticles);

	for (int i = 0; i < numberOfParticles; i++)
		particles[i] = new Particle(emissionLocation, tex, easingType);
}

ParticleSystem::~ParticleSystem() {
	for (int i = 0; i < particles.size(); i++)
		delete particles[i];
	
	particles.clear();
}

void ParticleSystem::update(float dt) {
	for (int i = 0; i < totalParticles; i++) {
		if (particles[i] != NULL) {
			particles[i]->update(dt);

			if (particles[i]->getLifeLeft() <= 0) {
				float angle = (std::rand() % angleRange) * 3.14f / 180.f + (90.f - (float)angleRange/2.f) * 3.14f / 180.f;
				float speed = (std::rand() % 50) + 50.f;
				float lifeTime = (float)(std::rand() % 2000) / 1000.f + 1.f;
				particles[i]->resetParticle(lifeTime, sf::Vector2f(-std::cos(angle)*speed, -std::sin(angle) * speed), emissionLocation);
			}
		}

	}
	
}

void ParticleSystem::increaseParticleCount(int numNewParticles) {
	int oldSize = particles.size();
	if (numNewParticles < 0) {
		for (int i = oldSize - 1; i > oldSize + numNewParticles - 1; i--) {
			delete particles[i];
			particles[i] = NULL;
		}
	}
	else{
		particles.resize(oldSize + numNewParticles);

		for (int i = oldSize - 1; i < particles.size(); i++)
			particles[i] = new Particle(emissionLocation, particleTex, easingType);
	}

	totalParticles = totalParticles + numNewParticles;
	cout << totalParticles << endl;
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;

	for(int i = 0; i < totalParticles; i++)
		if(particles[i] != NULL)
			target.draw(*particles[i], states);
}

