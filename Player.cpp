/*
 * Player.cpp
 *
 *  Created on: 28 juin 2018
 *	  Author: Crabman
 */

#include "Player.hpp"

Player::Player(const sf::Texture& texture,const sf::IntRect windowSize)
{
	m_windowSize = windowSize;
	m_texture = &texture;
	m_frame = 1;
	m_size = sf::Vector2f(128.f, 128.f);
	m_duration = 2.f;
	isAnimated = false;
	m_activeFrame = 0;
	m_time = 0.f;
	m_speed = 240.f;
	m_haveHeart = false;
	m_heartCooldown = 0.2f;
	m_sprite.setTexture(*m_texture);
	
	for( long unsigned int i = 0; i < m_frame; i++ )
	{
		m_anim.push_back( sf::IntRect(static_cast<int>(m_size.x*i), 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y)) );
	}
	
	m_sprite.setTextureRect(m_anim[m_activeFrame]);
	m_sprite.setOrigin( sf::Vector2f(static_cast<float>(m_size.x/2), static_cast<float>(m_size.y/2)) );
	m_sprite.setRotation(0);
	m_sprite.scale(0.5,0.5);
	m_sprite.setPosition(sf::Vector2f(static_cast<float>(m_windowSize.width/2), 100.f));
}

Player::~Player()
{
	
}

void Player::reset()
{
	m_heartCooldown = 0.2f;
	m_haveHeart = false;
	m_time = 0.f;
	m_sprite.setPosition(sf::Vector2f(static_cast<float>(m_windowSize.width/2), m_sprite.getPosition().y));
}

void Player::updateHeartCooldown(float elapsedTime)
{
	m_heartCooldown -= elapsedTime;
}

bool Player::canHaveHeart() const
{
	return (m_heartCooldown <= 0.f);
}

void Player::setAttachHeart()
{
	m_haveHeart = true;
}

void Player::setDettachHeart()
{
	m_heartCooldown = 1.6f;
	m_haveHeart = false;
}

bool Player::haveHeart() const
{
	return (m_haveHeart);
}

sf::Sprite Player::getSprite() const
{
	return (m_sprite);
}

void Player::setPos(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void Player::setPosX(float pos)
{
	m_sprite.setPosition(sf::Vector2f(pos, m_sprite.getPosition().y));
}

void Player::setPosY(float pos)
{
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, pos));
}

sf::Vector2f Player::getPos() const
{
	return (m_sprite.getPosition());
}

void Player::move(float elapsedTime)
{
	sf::Vector2f pos = m_sprite.getPosition();
	float size = m_sprite.getTextureRect().width*m_sprite.getScale().x;
	float speed = m_speed * elapsedTime;
	float movement;
	// LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (pos.x-(size/2)  > 0)
		{
			movement = pos.x-(size/2) - speed;
			if(movement < 0)
				speed += movement;
			m_sprite.move(-speed, 0.0);
		}
	// RIGHT
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (pos.x+(size/2) < m_windowSize.width)
		{
			movement = pos.x + (size/2) + speed - m_windowSize.width;
			if (movement >= 0)
				speed -= movement;
			m_sprite.move(speed, 0.0);
		}
	}
}
