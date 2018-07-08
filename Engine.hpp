/*
 * Engine.hpp
 *
 *  Created on: 28 juin 2018
 *	  Author: crabman
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "Heart.hpp"
#include "Pnj.hpp"
#include "Emote.hpp"
#include "Hud.hpp"
#include "Button.hpp"


struct level
{
	float playerPosY;
	int pnjsNb;
	float pnjsHumorTimeout;
	bool isGametimeAtttack;
};


class Engine
{
public:
	
	~Engine();
	void cleanup()
	{
		delete m_hud;
	};
	
	bool init();
	bool running();
	void stop();
	void resize(unsigned int width, unsigned int height);
	void launch(int callBack);
	bool isPaused();
	void setPause(const bool isWin, const bool isLost);
	void display();
	void menu();
	void game(long unsigned int levelNb);
	
private:
	sf::IntRect m_windowSize;
	bool m_running;
	bool m_pause;
	bool m_haveFocus;

	sf::Font m_font;
	sf::RenderWindow m_window;
	sf::RenderTexture m_render;
	sf::View m_view;
	std::vector<struct level>  m_levels;
	Hud* m_hud;
	//button
	sf::Texture m_buttonsTexture;
	sf::Sprite m_menuSelected;
	unsigned int m_menuButtonSelected1;
	unsigned int m_menuButtonSelected2;
	
	//text
	sf::Text m_winText;
	sf::Text m_lostText;
	sf::Text m_pauseText;

	// sound
	sf::SoundBuffer m_playerWinBuffer;
	sf::Sound m_playerWinSound;   
	
	sf::SoundBuffer m_pauseBuffer;
	sf::Sound m_pauseSound;
	
	sf::SoundBuffer m_playerHeartBuffer;
	sf::Sound m_playerHeartSound;
	
	sf::SoundBuffer m_playerLostLifeBuffer;
	sf::Sound m_playerLostLifeSound;
	
	sf::SoundBuffer m_heartTouchBuffer;
	sf::Sound m_heartTouchSound;
	
	sf::SoundBuffer m_pnjHappyBuffer;
	sf::Sound m_pnjHappySound;
	
	
	//textures
	sf::Texture m_backgroundMenuTexture;
	sf::Texture m_backgroundGameTexture; 
	sf::Texture m_playerTexture;
	sf::Texture m_pnjTexture;
	sf::Texture m_heartTexture;
	sf::Texture m_emotesTexture;
	sf::Texture m_lifesTexture;
};

#endif /* ENGINE_HPP_ */
