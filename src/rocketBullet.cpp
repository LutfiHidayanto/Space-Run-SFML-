#include "rocketBullet.hpp"

RocketBullet::RocketBullet(sf::Texture *texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	BulletShape.setTexture(*texture);
	BulletShape.setPosition(pos_x, pos_y);
	direction.x = dir_x;
	direction.y = dir_y;
	movementSpeed = movement_speed;
}

RocketBullet::~RocketBullet()
{

}

const sf::FloatRect RocketBullet::getBounds() const
{
	return BulletShape.getGlobalBounds();
}

void RocketBullet::update()
{
	//Movement
	BulletShape.move(movementSpeed * direction);
}

void RocketBullet::render(sf::RenderWindow  &window)
{
	window.draw(BulletShape);
}