/*
 * Heart.hpp
 *
 *  Created on: 28 juin 2018
 *      Author: gui
 */

#ifndef HEART_HPP_
#define HEART_HPP_

#include <SFML/Graphics.hpp>

class Heart
{
public:
	Heart(const sf::Texture& texture);
	~Heart();
	sf::FloatRect getBound() const;
	sf::Sprite getSprite() const;
	void setPos(sf::Vector2f pos);
	bool isAttached() const;
	void setAttached(bool stat);
	bool canRemove() const;
	void setRemovable();
	void move(float elapsedTime);
	
private:
	long unsigned int m_frame;
    sf::Vector2f m_size;
    //float m_duration;
    const sf::Texture* m_texture;
    bool m_attached;
    std::vector<sf::IntRect> m_anim;
    sf::Sprite m_sprite;
    long unsigned int m_activeFrame;
    float m_speed;
    float m_time;
    bool m_canRemove;
};

#endif /* HEART_HPP_ */
