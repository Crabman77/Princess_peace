/*
 * Hud.cpp
 *
 *  Created on: 30 juin 2018
 *      Author: Crabman
 */

#include "Hud.hpp"

Hud::Hud(sf::Font& font, sf::Texture& lifesTexture)
{
	m_fileName = "score.txt";
	
	for( int i = 0; i < 6; i++ )
	{
		score s
		{
			0,
			0,
		};
		m_highScores.push_back(s);
	}
	
	//lifes
	m_lifesLostTimeout = 10;
	m_lifesTime = 0;
	m_lifes = 3;
	m_lifesTexture = &lifesTexture;
	m_size = sf::Vector2i(96, 32);
	m_anim.push_back( sf::IntRect(0, 0, m_size.x, m_size.y) );
	m_anim.push_back( sf::IntRect(0, 32, m_size.x, m_size.y) );
	m_anim.push_back( sf::IntRect(0, 64, m_size.x, m_size.y) );
	m_anim.push_back( sf::IntRect(0, 96, m_size.x, m_size.y) );
	
	m_lifesSprite.setTexture(*m_lifesTexture);
	m_lifesSprite.setTextureRect(m_anim[3]);
	m_lifesSprite.setOrigin(sf::Vector2f(0.f, 0.f));
	m_lifesSprite.setPosition(sf::Vector2f(10.f, 5.f));
	
	//score
	m_score = 0;
	m_scoreText.setFont(font);
	m_scoreText.setCharacterSize(20);
	//m_scoreText.setString("Score:0");
	//m_scoreText.setPosition(sf::Vector2f(540, 5));
	
	//time
	m_time = 0;
	m_timeText.setFont(font);
	m_timeText.setCharacterSize(20);
	m_timeText.setString("Time:0");
	//m_timeText.setPosition(sf::Vector2f(920, 20));
	
	//highScore
	m_highScore = 0;
	m_highScoreText.setFont(font);
	m_highScoreText.setCharacterSize(20);	
	
	//highTime
	m_highTime = 0;
	m_highTimeText.setFont(font);
	m_highTimeText.setCharacterSize(20);
}

Hud::~Hud()
{

}

void Hud::reset()
{
	m_lifes = 3;	
	m_score = 0;
	m_time = 0;
}

int Hud::getLifes()
{
	return (m_lifes);
}

void Hud::setLifes(int lifes)
{
	m_lifes = lifes;
}

bool Hud::decreaseLife()
{
	if (m_lifesTime < m_lifesLostTimeout)
	{
		return (false);
	}
	m_lifes -= 1;
	m_lifesTime = 0;	
	return (true);
}

void Hud::update()
{
	int lifes = m_lifes;
	if (lifes < 0)
		lifes = 0;
	if (lifes > 3)
		lifes = 3;
	m_lifesSprite.setTextureRect(m_anim[static_cast<long unsigned int>(lifes)]);
	
	//score
	m_scoreText.setString(std::to_string(m_score));
	//sf::FloatRect bound = m_scoreText.getLocalBounds();
	//m_scoreText.setOrigin(sf::Vector2f(bound.width/2 , 0));
	m_scoreText.setPosition(sf::Vector2f(300, 26));
	
	//time
	m_timeText.setString(std::to_string(int(m_time)));
	//bound = m_timeText.getLocalBounds();
	//m_timeText.setOrigin(sf::Vector2f(bound.width/2 , 0));	
	m_timeText.setPosition(sf::Vector2f(300, 45));
	
	
	//highScore
	m_highScoreText.setString(std::to_string(m_highScore));
	//bound = m_highScoreText.getLocalBounds();
	//m_highScoreText.setOrigin(sf::Vector2f(bound.width/2 , 0));
	m_highScoreText.setPosition(sf::Vector2f(881, 25));	
	
	
	//highTime
	m_highTimeText.setString(std::to_string(int(m_highTime)));
	//bound = m_highTimeText.getLocalBounds();
	//m_highTimeText.setOrigin(sf::Vector2f(bound.width/2 , 0));	
	m_highTimeText.setPosition(sf::Vector2f(881, 45));
}

void Hud::draw(sf::RenderTexture& render)
{
	render.draw(m_lifesSprite);
	render.draw(m_scoreText);
	render.draw(m_timeText);
	render.draw(m_highScoreText);
	render.draw(m_highTimeText);
}

int Hud::getScore()
{
	return(m_score);
}

void Hud::increaseScore(int score)
{
	m_score += score;
}

void Hud::decreaseScore(int score)
{
	m_score -= score;
	if (m_score < 0)
		m_score = 0;
}

void Hud::updatetime(float elapsedTime)
{
	m_time += elapsedTime;
	m_lifesTime += elapsedTime;
}

void Hud::resetScore()
{
	m_score = 0;
}

void Hud::resettime()
{
	m_time = 0;
}

float Hud::getTime()
{
	return (m_time);
}


void Hud::setHighScore(long unsigned int levelNb)
{
	m_highScore = m_highScores[levelNb].highScore;
	m_highTime = m_highScores[levelNb].highTime;
}


void Hud::updateHighScore(long unsigned int levelNb, bool isGametimeAtttack)
{
	if (isGametimeAtttack)
	{
		if (m_highTime == 0 || static_cast<int>(m_time) < m_highTime)
		{
			m_highScore = m_score;
			m_highTime = static_cast<int>(m_time);
			m_highScores[levelNb].highScore = m_highScore;
			m_highScores[levelNb].highTime = m_highTime;
			save();
		}
	}
	else
	{
		if (m_score > m_highScore)
		{
			m_highScore = m_score;
			m_highTime = static_cast<int>(m_time);
			m_highScores[levelNb].highScore = m_highScore;
			m_highScores[levelNb].highTime = m_highTime;
			save();
		}
	}
}

void Hud::load()
{
	std::ifstream file(m_fileName.c_str(), std::ios::in);
	if(!file)
	{
		std::cerr << "Erreur, impossible d'ouvrir " << m_fileName << " !" << std::endl;
		return;
	}
	std::string line;
	while (getline(file, line))
	{
		std::istringstream iss( line );
		long unsigned int n = 0;
		long unsigned int s = 0;
		long unsigned int t = 0;
		iss >> n;
		iss >> s;
		iss >> t;
		if (n < 6)
		{
			m_highScores[n].highScore = s;
			m_highScores[n].highTime = t;
		}
	}
	file.close();
}

void Hud::save()
{
	std::ofstream file(m_fileName.c_str(), std::ios::out | std::ios::trunc);
	if(!file)
	{
		std::cerr << "Erreur, impossible d'ouvrir le fichier" << m_fileName << "!" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < m_highScores.size(); i++){ 
		score s = m_highScores[i];
		file << std::to_string(i) << " " << std::to_string(int(s.highScore)) << " " << std::to_string(int(s.highTime)) << std::endl;
	}
	file.close();
}
