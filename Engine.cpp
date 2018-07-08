/*
 * Engine.cpp
 *
 *  Created on: 28 juin 2018
 *	  Author: Crabman
 */

#include "Engine.hpp"

enum callBackType { NONE, QUIT, GAME1, GAME2, GAME3, GAME4, GAME5, GAME6 };


bool Engine::init()
{
	std::string gameName = "Princess Peace";
	m_windowSize.width = 1080;
	m_windowSize.height = 720;
	
	//simple game facile
	level level1
	{
		350,
		4,
		30,
		false
	};
	m_levels.push_back(level1);
	
	//simple game normal
	level level2
	{
		200,
		6,
		40,
		false
	};
	m_levels.push_back(level2);
	
	//simple game difficile
	level level3
	{
		100,
		8,
		50,
		false
	};
	m_levels.push_back(level3);
	
	//time attack game facile
	level level4
	{
		350,
		4,
		25,
		true
	};
	m_levels.push_back(level4);
	
	//time attack game normal
	level level5
	{
		200,
		6,
		35,
		true
	};
	m_levels.push_back(level5);
	
	//time attack game difficile
	level level6
	{
		100,
		8,
		40,
		true
	};
	m_levels.push_back(level6);
	
	if(!m_backgroundMenuTexture.loadFromFile("textures/background_menu.png"))
	{
		std::cerr << "Error during import textures/background_menu.png" << std::endl;
		return (false);
	}
	
	if(!m_backgroundGameTexture.loadFromFile("textures/background_game.png"))
	{
		std::cerr << "Error during import textures/background_game.png" << std::endl;
		return (false);
	}

	//Button
	if(!m_buttonsTexture.loadFromFile("textures/buttons.png"))
	{
		std::cerr << "Error during import textures/buttons.png" << std::endl;
		return (false);
	}

	//Player
	if(!m_playerTexture.loadFromFile("textures/player.png"))
	{
		std::cerr << "Error during import textures/player.png" << std::endl;
		return (false);
	}
	//pnj
	if(!m_pnjTexture.loadFromFile("textures/pnj.png"))
	{
		std::cerr << "Error during import textures/pnj.png" << std::endl;
		return (false);
	}	
	
	//heart
	if(!m_heartTexture.loadFromFile("textures/heart.png"))
	{
		std::cerr << "Error during import textures/heart.png" << std::endl;
		return (false);
	}
	//emote
	if(!m_emotesTexture.loadFromFile("textures/emotes.png"))
	{
		std::cerr << "Error during import textures/emotes.png" << std::endl;
		return (false);
	}
	
	if(!m_lifesTexture.loadFromFile("textures/lifeshud.png"))
	{
		std::cerr << "Error during import textures/lifeshud.png" << std::endl;
		return (false);
	}
	
	// font
	if (!m_font.loadFromFile("font/default.ttf"))
	{
		std::cerr << "Error during import font/default.ttf" << std::endl;
		return (false);
	}

	//text win
	m_winText.setFont(m_font);
	m_winText.setCharacterSize(80);
	m_winText.setString("Youpi");
	m_winText.setOrigin(sf::Vector2f(m_winText.getLocalBounds().width/2, m_winText.getLocalBounds().height/2));
	m_winText.setPosition( sf::Vector2f(static_cast<float>(m_windowSize.width/2), static_cast<float>(m_windowSize.height/2)) );
	
	//text lost
	m_lostText.setFont(m_font);
	m_lostText.setCharacterSize(80);
	m_lostText.setString("Perdu");
	m_lostText.setOrigin(sf::Vector2f(m_lostText.getLocalBounds().width/2, m_lostText.getLocalBounds().height/2));
	m_lostText.setPosition( sf::Vector2f(static_cast<float>(m_windowSize.width/2), static_cast<float>(m_windowSize.height/2)) );
	

	// menu selected
	m_menuSelected.setTexture(m_buttonsTexture);
	m_menuSelected.setTextureRect(sf::IntRect(0, 210, 210, 35));
	m_menuSelected.setOrigin(sf::Vector2f(105, 17));
	
	//pause
	m_pauseText.setFont(m_font);
	m_pauseText.setCharacterSize(80);
	m_pauseText.setString("PAUSE");
	m_pauseText.setOrigin(sf::Vector2f(m_pauseText.getLocalBounds().width/2, m_pauseText.getLocalBounds().height/2));
	m_pauseText.setPosition( sf::Vector2f( static_cast<float>(m_windowSize.width/2), static_cast<float>(m_windowSize.height/2)) );
	
	// sound pause
	if (!m_pauseBuffer.loadFromFile("sounds/pause.ogg"))
	{
		std::cerr << "Error during import sounds/pause.ogg" << std::endl;
		return (false);
	}
	m_pauseSound.setBuffer(m_pauseBuffer);
	
	// sound win
	if (!m_playerWinBuffer.loadFromFile("sounds/player_win.ogg"))
	{
		std::cerr << "Error during import sounds/player_win.ogg" << std::endl;
		return (false);
	}
	m_playerWinSound.setBuffer(m_playerWinBuffer);	
	
	//sound player
	if (!m_playerHeartBuffer.loadFromFile("sounds/player_heart.ogg"))
	{
		std::cerr << "Error during import sounds/player_heart.ogg" << std::endl;
		return (false);
	}
	m_playerHeartSound.setBuffer(m_playerHeartBuffer);
	
	//sound player lost life
	if (!m_playerLostLifeBuffer.loadFromFile("sounds/player_lost_life.ogg"))
	{
		std::cerr << "Error during import sounds/player_lost_life.ogg" << std::endl;
		return (false);
	}
	m_playerLostLifeSound.setBuffer(m_playerLostLifeBuffer);	
	
	//sound heart
	if (!m_heartTouchBuffer.loadFromFile("sounds/heart_touch.ogg"))
	{
		std::cerr << "Error during import sounds/heart_touch.ogg" << std::endl;
		return (false);
	}
	m_heartTouchSound.setBuffer(m_heartTouchBuffer);
	
	//sound pnjHappy
	if (!m_pnjHappyBuffer.loadFromFile("sounds/pnj_happy.ogg"))
	{
		std::cerr << "Error during import sounds/pnj_happy.ogg" << std::endl;
		return (false);
	}
	m_pnjHappySound.setBuffer(m_pnjHappyBuffer);	
	
	sf::Listener::setPosition(static_cast<float>(m_windowSize.width/2), 0.f, 0.f);
	sf::Listener::setDirection(0.f, 0.f, 1.f);
	sf::Listener::setGlobalVolume(100.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);

	//bestScore
	//m_bestScore = 0;
	m_hud = new Hud(m_font, m_lifesTexture);
	m_hud->load();
	
	m_window.create(sf::VideoMode(static_cast<unsigned int>(m_windowSize.width), static_cast<unsigned int>(m_windowSize.height)), gameName);
	m_window.setFramerateLimit(60);
	//m_window.setVerticalSyncEnabled(true);

	srand(static_cast<unsigned int>(time(NULL)));

	m_render.create(static_cast<unsigned int>(m_windowSize.width), static_cast<unsigned int>(m_windowSize.height) );
	m_view.setCenter(sf::Vector2f(static_cast<float>(m_windowSize.width/2), static_cast<float>(m_windowSize.height/2) ));
	m_view.setSize(sf::Vector2f(static_cast<float>(m_windowSize.width), static_cast<float>(m_windowSize.height) ));
	m_window.setView(m_view);
	
	m_haveFocus = true;
	m_running = true;
	
	return (true);
}

Engine::~Engine()
{
	
}

bool Engine::running()
{
	return (m_running && m_window.isOpen());
}

void Engine::stop()
{
	m_running = false;
	m_window.close();
}


void Engine::resize(unsigned int width, unsigned int height)
{
	float nW = static_cast<float>(width) / static_cast<float>(m_windowSize.width);
	float nH = static_cast<float>(height) / static_cast<float>(m_windowSize.height);
	float scale = (nW < nH) ? nW : nH;
	m_view.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	m_view.zoom(1.f/scale);
	m_window.setView(m_view);
}

void Engine::launch(int callBack)
{
	switch (callBack)
	{
		case QUIT:
		{
			stop();
			break;
		}		
		case GAME1:
		{
			game(0);
			break;
		}
		case GAME2:
		{
			game(1);
			break;
		}
		case GAME3:
		{
			game(2);
			break;
		}		
		case GAME4:
		{
			game(3);
			break;
		}	
		case GAME5:
		{
			game(4);
			break;
		}	
		case GAME6:
		{
			game(5);
			break;
		}
		default:
			break;
	}
}

bool Engine::isPaused()
{
	return (m_pause);
}

void Engine::setPause(const bool isWin, const bool isLost)
{
	if ((!isWin && !isLost) || m_pause)
	{
		m_pause = !m_pause;
		m_pauseSound.play();
	}
}

void Engine::display()
{
	m_render.display();
	sf::Sprite renderSprite(m_render.getTexture());
	m_window.clear(sf::Color::Black);
	m_window.draw(renderSprite);
	m_window.display();
}

void Engine::menu()
{
	sf::Sprite backgroundMenuSprite(m_backgroundMenuTexture);
	backgroundMenuSprite.setPosition(sf::Vector2f(0, 0));
	sf::Text versionText;
	versionText.setFont(m_font);
	versionText.setCharacterSize(15);
	versionText.setString("Crabman 2018  V 1.0");
	versionText.setPosition(sf::Vector2f(870, 695));
	
	// menu
	m_menuButtonSelected1 = 0;
	std::vector<Button*> buttons;
	//game 1
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 0), GAME1, sf::Vector2f(540, 260)));
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 35), GAME2, sf::Vector2f(540, 305)));
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 70), GAME3, sf::Vector2f(540, 350)));
	//timeattack
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 0), GAME4, sf::Vector2f(540, 490)));
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 35), GAME5, sf::Vector2f(540, 535)));
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 70), GAME6, sf::Vector2f(540, 580)));
	//exit
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 105), QUIT, sf::Vector2f(540, 660)));
	bool mouseReleased = false;
	sf::Event event;
	while (running())
	{
		mouseReleased = false;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					stop();
					break;
				}
				case sf::Event::Resized:
				{
					resize(event.size.width, event.size.height);
					break;
				}
				case sf::Event::LostFocus:
				{
					m_haveFocus = false;
					break;
				}
				case sf::Event::GainedFocus:
				{
					m_haveFocus = true;
					break;
				}
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape: //escape
						{
							stop();
							break;
						}
						case sf::Keyboard::Return: //enter
						{
							launch(buttons[m_menuButtonSelected1]->getCallBack());
							break;
						}
						case sf::Keyboard::Up:
						{
							if (m_haveFocus && m_menuButtonSelected1 > 0)
							{
								m_menuButtonSelected1--;
							}
							break;
						}
						case sf::Keyboard::Down:
						{
							if (m_haveFocus && m_menuButtonSelected1 < buttons.size()-1)
							{
								m_menuButtonSelected1++;
							}
							break;
						}
						default: break;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							mouseReleased = true;
							break;
						default: break;
					}
					break;
				}
				default: break;
			}
		}
		
		m_render.clear(sf::Color::Black);
		m_render.draw(backgroundMenuSprite);
		sf::Vector2i mPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f worldPos = m_window.mapPixelToCoords(mPos);
		for (unsigned int i=0;i<buttons.size();i++)
		{
			if (buttons[i]->isPressed() && mouseReleased)
			{
				mouseReleased = false;
				launch(buttons[i]->getCallBack());
			}
			buttons[i]->update(worldPos);
			m_render.draw(buttons[i]->getSprite());
		}
		sf::Vector2f pos = buttons[m_menuButtonSelected1]->getPosition();
		m_menuSelected.setPosition(pos.x, pos.y);
		m_render.draw(m_menuSelected);
		m_render.draw(versionText);
		display();
	}
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete(buttons[i]);
	}
}

void Engine::game(long unsigned int levelNb)
{
	if (levelNb >= (m_levels.size()))
	{
		levelNb = 0;
	}
	m_hud->reset();
	m_hud->setHighScore(levelNb);
	
	float playerPosY = m_levels[levelNb].playerPosY;
	int pnjsNb = m_levels[levelNb].pnjsNb;
	float pnjsHumorTimeout = m_levels[levelNb].pnjsHumorTimeout;
	bool isGametimeAtttack = m_levels[levelNb].isGametimeAtttack;
	
	// menu
	std::vector<Button*> buttons;
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 140), 1, sf::Vector2f(540, 490)));
	buttons.push_back(new Button(m_buttonsTexture, sf::Vector2f(140, 35), sf::Vector2f(0, 175), 0, sf::Vector2f(540, 535)));
	m_menuButtonSelected2 = 0;
	
	sf::Sprite backgroundSprite(m_backgroundGameTexture);

	Player* player = new Player(m_playerTexture, m_windowSize);
	player->setPosY(playerPosY);
	
	Emote* emote = new Emote(m_emotesTexture);
	
	std::vector<Pnj*> pnjs;
	std::vector<Heart*> hearts;
	
	m_pause = false;
	bool ingame = true;
	bool mouseReleased = false;
	sf::Event event;
	sf::Clock time;	
	
	bool isWin = false;
	bool isLost = false;

	for (int i = 0; i < pnjsNb; i++)
	{
		float x = static_cast<float>(rand()%((m_windowSize.width-100)+50));
		float y = 668.0f;
		pnjs.push_back(new Pnj(m_pnjTexture, sf::Vector2f(x, y), isGametimeAtttack, 0, pnjsHumorTimeout, m_windowSize));
	}

	while (ingame && m_window.isOpen())	
	{
		mouseReleased = false;
		float elapsedTime = time.restart().asSeconds();
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					ingame = false;
					break;
				}
				case sf::Event::Resized:
				{
					resize(event.size.width, event.size.height);
					break;
				}
				case sf::Event::LostFocus:
				{
					m_haveFocus = false;
					break;
				}
				case sf::Event::GainedFocus:
				{
					m_haveFocus = true;
					break;
				}
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{
						case sf::Keyboard::Escape: //return
						{
							ingame = false;
							break;
						}
						case sf::Keyboard::P: //pause
						{
							setPause(isWin, isLost);
							break;
						}					case sf::Keyboard::Up:
						{
							if (m_haveFocus && (isWin || isLost) && m_menuButtonSelected2 > 0)
							{
								m_menuButtonSelected2--;
							}
							break;
						}
						case sf::Keyboard::Down:
						{
							if (m_haveFocus && (isWin || isLost) && m_menuButtonSelected2 < buttons.size()-1)
							{
								m_menuButtonSelected2++;
							}
							break;
						}
						case sf::Keyboard::Return: //enter
						{
							if (isWin || isLost)
							{
								int callback = buttons[m_menuButtonSelected2]->getCallBack();
								if (callback == 0)
								{
									ingame = false;
								}else if (callback == 1)
								{
									isWin = false;
									isLost = false;
									m_hud->reset();
									player->reset();
									for (size_t i = 0; i < pnjs.size(); i++)
									{
										int x = rand()%((m_windowSize.width-100)+50);
										pnjs[i]->setPosX(x);
										pnjs[i]->reset();
									}
									for(size_t i = 0; i < hearts.size(); i++)
										delete(hearts[i]);
									hearts.clear();
								}
							}
							break;				
						}
						default: break;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
						{
							mouseReleased = true;
							break;
						}
						default: break;
					}
					break;
				}
				default: break;
			}
		}
		
		if (!isWin && !isLost && !isPaused())
		{
			m_hud->updatetime(elapsedTime);
			if (!player->haveHeart())
			{
				player->updateHeartCooldown(elapsedTime);
				if (player->canHaveHeart())
				{	
					hearts.push_back(new Heart(m_heartTexture));
					player->setAttachHeart();
				}
			}
			if (m_haveFocus)
				player->move(elapsedTime);
			
			for(size_t i = 0; i < hearts.size(); i++)
			{
				if (hearts[i]->isAttached())
				{
					hearts[i]->setPos(player->getPos());
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_haveFocus){
						hearts[i]->setAttached(false);
						player->setDettachHeart();
						m_playerHeartSound.play();
					}
				}else
				{
					hearts[i]->move(elapsedTime);
				}
			}
			
			//pnjs move
			for(size_t i = 0; i < pnjs.size(); i++)
			{
				pnjs[i]->move(elapsedTime);
				pnjs[i]->update(elapsedTime);
				
				for(size_t j = 0; j < hearts.size(); j++)
				{
					if (!hearts[j]->canRemove() && hearts[j]->getBound().intersects(pnjs[i]->getBound()))
					{
						if (pnjs[i]->canIncreaseHumor())
						{
							pnjs[i]->increaseHumor();
							if (pnjs[i]->getHumor() == pnjs[i]->getHumorMax())
							{
								m_pnjHappySound.play();
							}
							m_hud->increaseScore(10);
						}else {
							pnjs[i]->increaseHumor();
							m_hud->increaseScore(20);
						}
						
						hearts[j]->setRemovable();
						m_heartTouchSound.play();
					}
				}
				//update humor and take 1 life
				if (!pnjs[i]->updateHumor(elapsedTime))
				{
					if (m_hud->decreaseLife())
					{
						m_playerLostLifeSound.play();
						if (m_hud->getLifes() < 0)
						{
							isLost = true;
							break;
						}
					}
				}
			}
			
			bool pnjsHappy = true;
			for (size_t i = 0; i < pnjs.size(); i++)
			{
				if (pnjs[i]->getHumor() < pnjs[i]->getHumorMax())
				{
					pnjsHappy = false;
					break;
				}
			}
			if (pnjsHappy)
			{
				isWin = true;
				m_playerWinSound.play();
				m_hud->updateHighScore(levelNb, isGametimeAtttack);
			}
		}
		
		//drawing
		m_render.clear(sf::Color::Black);
		m_render.draw(backgroundSprite);
		m_render.draw(player->getSprite());
		
		//pnjs emotes draw
		for(size_t i = 0; i < pnjs.size(); i++)
		{
			m_render.draw(pnjs[i]->getSprite());
			emote->setPos(pnjs[i]->getPos());
			m_render.draw(emote->getSprite(pnjs[i]->getHumor()));
		}
		
		//hearts drawing
		for(size_t i = 0; i < hearts.size(); i++)
		{
			m_render.draw(hearts[i]->getSprite());
		}
		
		//hud drawing
		m_hud->update();
		m_hud->draw(m_render);
		
		if (isWin)
		{
			m_render.draw(m_winText);
		} else if (isPaused())
		{
			m_render.draw(m_pauseText);
		}else if (isLost)
		{
			m_render.draw(m_lostText);
		}
		
		//buttons
		if (isWin || isLost)
		{
			sf::Vector2i mPos = sf::Mouse::getPosition(m_window);
			sf::Vector2f worldPos = m_window.mapPixelToCoords(mPos);
			for (unsigned int i=0;i<buttons.size();i++)
			{
				if (buttons[i]->isPressed() && mouseReleased)
				{
					mouseReleased = false;
					int callback = buttons[i]->getCallBack();
					if (callback == 0)
					{
						ingame = false;
					}else if (callback == 1)
					{
						isWin = false;
						isLost = false;
						m_hud->reset();
						player->reset();
						for (size_t k = 0; k < pnjs.size(); k++)
						{
							int x = rand()%((m_windowSize.width-100)+50);
							pnjs[k]->setPosX(x);
							pnjs[k]->reset();
						}
						for(size_t j = 0; j < hearts.size(); j++)
						{
							delete(hearts[j]);
						}
						hearts.clear();
					}
					break;
				}
				buttons[i]->update(worldPos);
				m_render.draw(buttons[i]->getSprite());
			}
			sf::Vector2f pos = buttons[m_menuButtonSelected2]->getPosition();
			m_menuSelected.setPosition(pos.x, pos.y);
			m_render.draw(m_menuSelected);
		}
		display();
		for (auto itr = hearts.begin(); itr != hearts.end();)
		{
			if ((*itr)->canRemove())
			{
				itr = hearts.erase(itr);
			} else
			{
				++itr;
			}
		}
	}
	
	//clear before quit
	delete player;
	delete emote;
	for(size_t i = 0; i < hearts.size(); i++)
	{
		delete(hearts[i]);
	}
	hearts.clear();
	
	//pnjs
	for(size_t i = 0; i < pnjs.size(); i++)
		delete(pnjs[i]);
	pnjs.clear();
	
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete(buttons[i]);
	}
	buttons.clear();
}
