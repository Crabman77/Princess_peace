/*
 * Hud.hpp
 *
 *  Created on: 30 juin 2018
 *      Author: Crabman
 */

#ifndef HUD_HPP_
#define HUD_HPP_

#include <SFML/Graphics.hpp>
#include <sstream> 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


struct score
{
	int highScore;
	int highTime;
};

class Hud
{
public:
	Hud(sf::Font& font, sf::Texture& lifesTexture);
	~Hud();
	void reset();
	int getLifes();
	void setLifes(int lifes);
	bool decreaseLife();
	void update();
	void draw(sf::RenderTexture& render);
	int getScore();
	void increaseScore(int score);
	void decreaseScore(int score);
	void updatetime(float elapsedTime);
	void resetScore();
	void resettime();
	float getTime();
	void setHighScore(long unsigned int levelNb);
	void updateHighScore(long unsigned int levelNb, bool isGametimeAtttack);
	void load();
	void save();
	
private:
	const sf::Texture* m_lifesTexture;
	std::vector<sf::IntRect> m_anim;
	sf::Vector2i m_size;
	
	sf::Sprite m_lifesSprite;
	sf::Text m_scoreText;
	sf::Text m_timeText;
	sf::Text m_highScoreText;
	sf::Text m_highTimeText;
	
	int m_lifes;
	int m_score;
	float m_time;
	float m_lifesLostTimeout;
	float m_lifesTime;
	int m_highScore;
	int m_highTime;
	
	std::string m_fileName;
	std::vector<struct score> m_highScores;
};

#endif /* HUD_HPP_ */
