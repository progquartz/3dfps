#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <math.h>

using namespace sf;
using namespace std;

class Bullet {
public:
	CircleShape shape;
	Vector2f currvelocity;
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currvelocity(0, 0), maxSpeed(15)
	{
		this->shape.setFillColor(Color::Red);
		this->shape.setRadius(radius);
	}

	

};
int main()
{
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(800, 600), "cat dodge");
	// 1 frame = 0.016s
	window.setFramerateLimit(60);

	// player
	CircleShape player(25.f);
	player.setFillColor(Color::Black);

	// vector
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDIrNormalize;

	// bullet
	Bullet b1;
	vector<Bullet> Bullets;
	int bulletcount = 0;

	Bullets.push_back(Bullet(b1));

	// enemy

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
			}
		}
		
		// update
		// 벡터의 길이 = |v| = sqrt(v.x^2 + v.y^2)
		// 벡터의 일반화 = u = v / |v|

		// vector
		playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDIrNormalize = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		cout << aimDIrNormalize.x << " " << aimDIrNormalize.y << "\n";

		// player
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.move(-8.f, 0);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.move(8.f, 0);
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.move(0, -8.f);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.move(0, 8.f);
		
		// shooting
		if (bulletcount < 4) {
			bulletcount++;
		}
		if (Mouse::isButtonPressed(Mouse::Left) &&bulletcount >= 4) {
			b1.shape.setPosition(playerCenter);
			b1.currvelocity = aimDIrNormalize * b1.maxSpeed;

			Bullets.push_back(Bullet(b1));
			bulletcount = 0;
		}

		for (size_t i = 0; i < Bullets.size(); i++) {
			Bullets[i].shape.move(Bullets[i].currvelocity);
			if (Bullets[i].shape.getPosition().x > window.getSize().x || Bullets[i].shape.getPosition().x + Bullets[i].shape.getRadius() * 2 < 0 || Bullets[i].shape.getPosition().y > window.getSize().y || Bullets[i].shape.getPosition().y + Bullets[i].shape.getRadius() * 2 < 0)
				Bullets.erase(Bullets.begin() + i);
		}
		
		// draw
		window.clear(Color::White);

		window.draw(player);
		for (size_t i = 0; i < Bullets.size(); i++) {
			window.draw(Bullets[i].shape);
		}
		window.display();
	}

	return 0;
}