/*
 * Heart.cpp
 *
 *  Created on: 28 juin 2018
 *	  Author: Crabman
 */

#include "Heart.hpp"

Heart::Heart(const sf::Texture& texture)
{
	m_frame = 1;
	m_size = sf::Vector2f(32, 32);
	m_texture = &texture;
	m_sprite.setTexture(*m_texture);
	for (long unsigned int i = 0; i < m_frame; i++ )
	{
		m_anim.push_back(sf::IntRect(i*m_size.x, 0, m_size.x, m_size.y));
	}

	m_activeFrame = 0;
	m_sprite.setTextureRect(m_anim[m_activeFrame]);
	//m_sprite.setPosition(newPos);
	m_sprite.setOrigin(sf::Vector2f(m_size.x/2, 0));
	m_sprite.setScale(0.7, 0.7);
	m_speed = 180;
	m_time = 0;
	m_attached = true;
	m_canRemove = false;

}

Heart::~Heart()
{
	// TODO Auto-generated destructor stub
}

sf::FloatRect Heart::getBound() const
{
	sf::FloatRect rect = m_sprite.getGlobalBounds();
	return (rect);
}

sf::Sprite Heart::getSprite() const
{
	return (m_sprite);
}


void Heart::setPos(sf::Vector2f pos)
{	
	m_sprite.setPosition(pos);
}

bool Heart::isAttached() const
{
	return(m_attached);
}

void Heart::setAttached(bool stat)
{
	m_attached = stat;
}

bool Heart::canRemove() const
{
	return(m_canRemove);
}

void Heart::setRemovable()
{
	m_canRemove = true;
}

void Heart::move(float elapsedTime)
{
	if (!m_attached)
	{
		float speed = m_speed * elapsedTime;
		m_sprite.move(0.0, speed);
	
		if (m_sprite.getPosition().y > 780)
		{
			m_canRemove = true;
		}
	}
}
