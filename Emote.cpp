/*
 * Emote.cpp
 *
 *  Created on: 29 juin 2018
 *      Author: gui
 */

#include "Emote.hpp"

Emote::Emote(const sf::Texture& texture)
{
    m_frame = 4;
    m_size = sf::Vector2f(32, 32);
    m_texture = &texture;
    m_sprite.setTexture(*m_texture);
    for( int i = 0; i < m_frame; i++ )
    {
        m_anim.push_back(sf::IntRect(static_cast<int>(i*m_size.x), 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y) ));
    }
    
    m_sprite.setTextureRect(m_anim[0]);
    //m_sprite.setPosition(newPos);
    m_sprite.setScale(0.6f,0.6f);
    m_sprite.setOrigin(sf::Vector2f(m_size.x/2.f, m_size.y));
}

Emote::~Emote()
{
	
}

void Emote::setPos(sf::Vector2f pos)
{
	pos.y-=35;
	m_sprite.setPosition(pos);
}

sf::Sprite Emote::getSprite(const int num)
{
	m_sprite.setTextureRect(m_anim[static_cast<long unsigned int>(num)]);
	return (m_sprite);
}
