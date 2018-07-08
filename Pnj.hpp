/*
 * Pnj.hpp
 *
 *  Created on: 28 juin 2018
 *      Author: Crabman
 */

#ifndef PNJ_HPP_
#define PNJ_HPP_

#include <SFML/Graphics.hpp>

class Pnj
{
public:
	Pnj(const sf::Texture& texture, const sf::Vector2f pos, const bool isGametimeAtttack, const int humor, float humorTimeout, const sf::IntRect windowSize);
	~Pnj();
	
	void reset();
	sf::FloatRect getBound() const;
	sf::Sprite getSprite();
	void setPosX(int pos);
	sf::Vector2f getPos();
	void setHumor(int humor);
	int getHumor() const;
	int getHumorMax() const;
	bool canIncreaseHumor() const;
	bool canDecreaseHumor() const;
	void increaseHumor();
	void decreaseHumor();
	bool updateHumor(const float elapsedTime);
	void setTexture();
	bool getLook()const;
	void setLook(const bool look);
	float getWaitTime() const;
	void updateWaitTime(const float elapsedTime);
	void moveTo(const sf::Vector2f pos);
	void move(float elapsedTime);
	void update(const float elapsedTime);
	
	
private:
	sf::IntRect m_windowSize;
	
	//texture|animation
	const sf::Texture* m_texture;
	sf::Sprite m_sprite;
	std::vector<sf::IntRect> m_anim0;
	std::vector<sf::IntRect> m_anim1;
	long unsigned int m_frame;
	sf::Vector2f m_size;
	float m_duration;
	bool isWalk;
	long unsigned int m_activeFrame;
	float m_time;
	float m_speed;
	bool m_lookAtRight;
	float m_waitTime;
	int m_humor;
	int m_humorMax;
	float m_humorTimeout;
	float m_humorTime;
	bool m_isGametimeAtttack;
	
};

#endif /* PNJ_HPP_ */
