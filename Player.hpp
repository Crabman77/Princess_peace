/*
 * Player.hpp
 *
 *  Created on: 28 juin 2018
 *	  Author: Crabman
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(const sf::Texture& texture, const sf::IntRect windowSize);
	~Player();
	void reset();
	void updateHeartCooldown(float elapsedTime);
	bool canHaveHeart() const;
	void setAttachHeart();
	void setDettachHeart();
	bool haveHeart() const;
	sf::Sprite getSprite() const;
	void setPos(sf::Vector2f pos);
	void setPosX(float pos);
	void setPosY(float pos);
	sf::Vector2f getPos() const;
	void setLifes(int lifes);
	void move(float elapsedTime);
private:
	sf::IntRect m_windowSize;
	
	//texture|animation
	const sf::Texture* m_texture;
	sf::Sprite m_sprite;
	std::vector<sf::IntRect> m_anim;
	long unsigned int m_frame;
	sf::Vector2f m_size;
	float m_duration;
	bool isAnimated;
	long unsigned int m_activeFrame;
	float m_time;
	float m_speed;
	bool m_haveHeart;
	float m_heartCooldown;
	
};

#endif /* PLAYER_HPP_ */
