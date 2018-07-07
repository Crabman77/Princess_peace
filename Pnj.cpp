/*
 * Pnj.cpp
 *
 *  Created on: 28 juin 2018
 *	  Author: Crabman
 */

#include "Pnj.hpp"


Pnj::Pnj(const sf::Texture& texture,const sf::Vector2f pos, const bool isGametimeAtttack,const int humor,const float humorTimeout, const sf::IntRect windowSize)
{
	m_windowSize = windowSize;
	m_texture = &texture;
	m_frame = 9;
	m_size = sf::Vector2f(35, 64);
	m_duration = 0.6;
	isWalk = false;
	m_activeFrame = 0;
	m_time = 0;
	m_speed = 100;
	m_humor = humor;
	m_humorMax = 3;
	m_humorTimeout = humorTimeout;
	m_humorTime = m_humorTimeout;
	m_isGametimeAtttack = isGametimeAtttack;
	m_sprite.setTexture(*m_texture);
	
	for( long unsigned int i = 0; i < m_frame; i++ )
	{
		m_anim0.push_back(sf::IntRect(m_size.x*i, 0, m_size.x, m_size.y));
	}
	for( long unsigned int i = 0; i < m_frame; i++ )
	{
		m_anim1.push_back(sf::IntRect(m_size.x*i, 64, m_size.x, m_size.y));
	}
	
	m_sprite.setTextureRect(m_anim0[m_activeFrame]);
	m_sprite.setOrigin(sf::Vector2f(m_size.x/2, m_size.y/2));
	m_sprite.setRotation(0);
	m_lookAtRight = true;
	m_waitTime = 2;
	m_sprite.setPosition(pos);
}

Pnj::~Pnj()
{
	
}

void Pnj::reset()
{
	m_humorTime = m_humorTimeout;
	m_humor = 0;
}

sf::FloatRect Pnj::getBound() const
{
	sf::FloatRect rect = m_sprite.getGlobalBounds();
	return (rect);
}

sf::Sprite Pnj::getSprite()
{
	return (m_sprite);
}

void Pnj::setPosX(int pos)
{
	m_sprite.setPosition(sf::Vector2f(pos, 668));
}

sf::Vector2f Pnj::getPos()
{
	return (m_sprite.getPosition());
}

void Pnj::setHumor(int humor)
{
	m_humorTime = m_humorTimeout;
	m_humor = humor;
}

int Pnj::getHumor() const
{
	return (m_humor);
}

int Pnj::getHumorMax() const
{
	return (m_humorMax);
}

bool Pnj::canIncreaseHumor() const
{
	return (m_humor < m_humorMax);
}

bool Pnj::canDecreaseHumor() const
{
	return (m_humor > 0);
}

void Pnj::increaseHumor()
{
	m_humorTime = m_humorTimeout;
	if (m_humor < m_humorMax)
		m_humor++;
}

void Pnj::decreaseHumor()
{
	m_humorTime = m_humorTimeout;
	if (m_humor > 0)
		m_humor--;
}


bool Pnj::updateHumor(const float elapsedTime)
{
	if (m_humor < m_humorMax || !m_isGametimeAtttack) //time attack mode not decrese if humor is max
		m_humorTime -= elapsedTime;
	if (m_humorTime <= 0 )
	{
		m_humorTime = m_humorTimeout;
		if (m_humor > 0)
			m_humor--;
		else
			return (false);
	}
	return (true);
}

void Pnj::setTexture()
{
	if (m_lookAtRight)
	{
		m_sprite.setTextureRect(m_anim0[m_activeFrame]);
	}else
	{
		m_sprite.setTextureRect(m_anim1[m_activeFrame]);
	}
}

bool Pnj::getLook() const
{
	return (m_lookAtRight);
}

void Pnj::setLook(const bool look)
{
	m_lookAtRight = look;
}

float Pnj::getWaitTime() const
{
	return (m_waitTime);
}

void Pnj::updateWaitTime(const float elapsedTime)
{
	m_waitTime -= elapsedTime;
}

void Pnj::moveTo(const sf::Vector2f pos)
{
	m_sprite.move(pos);
}

void Pnj::move(float elapsedTime)
{
	m_waitTime -= elapsedTime;
	if (m_waitTime <= 0)
	{
		int go = rand()%(5);
		m_lookAtRight = (rand()%(2) >= 1);
		if (go < 2)
		{
			isWalk = false;
			m_waitTime = 2.0;
			m_activeFrame = 0;
		}else
		{
			isWalk = true;
			m_waitTime = rand()%(3)+1* m_duration;
			m_activeFrame = 1;
		}
	}
	
	if (isWalk)
	{
		float speed = m_speed * elapsedTime;
		if (m_lookAtRight)
		{
			m_sprite.move(speed, 0.0);
			if (m_sprite.getPosition().x > m_windowSize.width-15)
			{
				m_lookAtRight = false;
			}			
		}else
		{
			m_sprite.move(-speed, 0.0);
			if (m_sprite.getPosition().x < 15)
			{
				m_lookAtRight = true;
			}
		}
	}
}

void Pnj::update(const float elapsedTime)
{
	m_time += elapsedTime;
	if (m_time > m_duration || (!isWalk  && m_activeFrame != 0))
	{
		m_time = 0;
		m_activeFrame = 0;
		setTexture();
	}else if (isWalk)
	{
		if (m_time > (m_duration/m_frame)*m_activeFrame)
		{
			m_activeFrame++;
			if (m_activeFrame >= m_frame)
			{
				m_activeFrame = 0;
				m_time = 0;
			}
			setTexture();
		}
	}
}
