#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class RocketBullet
{
private:
	sf::Sprite BulletShape;
	sf::Vector2f direction;
	float movementSpeed;
public:
	RocketBullet(sf::Texture *texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~RocketBullet();

	//Accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderWindow  &window);
};
