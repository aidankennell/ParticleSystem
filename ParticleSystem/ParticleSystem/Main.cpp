#include "ParticleSystem.h"

int main()
{
	bool addReleased = true, subtractReleased = true;
	int additive = 20;

	sf::Texture tex1;
	tex1.loadFromFile("Assets/star.png");

	sf::Texture tex2;
	tex2.loadFromFile("Assets/fire.png");

	sf::Texture tex3;
	tex3.loadFromFile("Assets/dog.png");

	sf::RenderWindow window(sf::VideoMode(800, 600), "Particles");

	ParticleSystem particleSystem1(20 ,45, sf::Vector2f(600, 580), tex1, 1);
	ParticleSystem particleSystem2(20, 90, sf::Vector2f(400, 580), tex2, 2);
	ParticleSystem particleSystem3(20, 15, sf::Vector2f(200, 580), tex3, 3);
	//ParticleSystem particleSystem1(100, sf::Vector2f(600, 580));
	//ParticleSystem particleSystem2(100, sf::Vector2f(400, 580));
	//ParticleSystem particleSystem3(100, sf::Vector2f(200, 580));
	sf::Clock clock;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && subtractReleased) {
			particleSystem1.increaseParticleCount(-additive);
			particleSystem2.increaseParticleCount(-additive);
			particleSystem3.increaseParticleCount(-additive);
			subtractReleased = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && addReleased) {
			particleSystem1.increaseParticleCount(additive);
			particleSystem2.increaseParticleCount(additive);
			particleSystem3.increaseParticleCount(additive);
			addReleased = false;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
			addReleased = true;
			subtractReleased = true;
		}

		float dt = clock.restart().asSeconds();
		particleSystem1.update(dt);
		particleSystem2.update(dt);
		particleSystem3.update(dt);

		window.clear();
		window.draw(particleSystem1);
		window.draw(particleSystem2);
		window.draw(particleSystem3);
		window.display();
	}

	return 0;
}
