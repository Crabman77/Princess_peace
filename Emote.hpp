/*
 * Emote.hpp
 *
 *  Created on: 29 juin 2018
 *      Author: gui
 */

#ifndef EMOTE_HPP_
#define EMOTE_HPP_

#include <SFML/Graphics.hpp>


class Emote
{
public:
	Emote(const sf::Texture& texture);
	~Emote();
	void setPos(sf::Vector2f pos);
	sf::Sprite getSprite(const int num);
	
private:
    int m_frame;
    sf::Vector2f m_size;
    const sf::Texture* m_texture;
    std::vector<sf::IntRect> m_anim;
    sf::Sprite m_sprite;
};

#endif /* EMOTE_HPP_ */
