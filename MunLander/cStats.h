#pragma once
#include <SFML/Graphics.hpp>
class cStats
{
private:
	sf::Font font;
	sf::Text velX;
	sf::Text velY;
	sf::Text acc;
public:

	cStats(void)
	{
		velX.setOrigin(20,15);
		velY.setOrigin(20,25);
		acc.setOrigin(20,35);

		velX.setString( sf::String( "velX" ) );
		velY.setString( sf::String( "velY" ) );
		acc.setString( sf::String( "acc" ) );
	}

	virtual ~cStats(void)
	{
		
	}


	void drawStats ( sf::RenderWindow & window, sf::Vector2f const coord )
	{
		velX.setPosition(coord);
		velY.setPosition(coord);
		acc.setPosition(coord);

		window.draw(velX);
		window.draw(velY);
		window.draw(acc);

	}
};

