#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
//#include "cStats.h"

class cLander
{
private:
	/// Wa¿ne
	//cStats staty;
	/// Obiekt. Zbiór prymitywów
	sf::RectangleShape lander;
	sf::ConvexShape thrust;

	sf::ConvexShape rcsL;
	sf::ConvexShape rcsR;
	/// Pozycja
	sf::Vector2f coord;
	sf::Vector2f vel;
	float rotV;
	float rot;

	/// W³aœciwoœci fizyczne
	float mass;// masa pojazdu w kg, bez paliwa!
	float fuelLIQ;// w kg
	float fuelRCS;// w kg

	int vector;
	float vectorP;
	/// W³aœciwoœci pojazdu
	float acc;
	float maxPower;

	/// Statystyki

	long double info;
	sf::Font font;

	sf::Text txtVelY;
	std::string strVelY;

	sf::Text txtVelX;
	std::string strVelX;

	sf::Text txtRot;
	std::string strRot;

	sf::Text txtThr;
	std::string strThr;

	sf::Text txtFuel;
	std::string strFuel;

	sf::Text txtRCS;
	std::string strRCS;

public:

	cLander(void)
	{
		/// Tworzenie obiektu (l¹downika)
		lander.setFillColor(sf::Color(255,255,255));
		lander.setSize(sf::Vector2f(20, 20));
		lander.setOrigin(10,10);

		thrust.setFillColor(sf::Color(0,0,0,0));
		thrust.setOutlineColor( sf::Color(150,150,255));
		thrust.setOutlineThickness(1);
		thrust.setOrigin(10, -15);
		thrust.setPointCount(3);
		thrust.setPoint(0,sf::Vector2f(5,0));
		thrust.setPoint(1,sf::Vector2f(15,0));
		thrust.setPoint(2,sf::Vector2f(10,10));

		rcsL.setOrigin(-12,0);
		rcsL.setFillColor(sf::Color(0,0,0,0));
		rcsL.setOutlineColor(sf::Color(255,255,150));
		rcsL.setOutlineThickness(1);
		rcsL.setPointCount(3);
		rcsL.setPoint(0,sf::Vector2f(0,0));
		rcsL.setPoint(1,sf::Vector2f(0,0));
		rcsL.setPoint(2,sf::Vector2f(0,0));

		rcsR.setOrigin(12,0);
		rcsR.setFillColor(sf::Color(0,0,0,0));
		rcsR.setOutlineColor(sf::Color(255,255,150));
		rcsR.setOutlineThickness(1);
		rcsR.setPointCount(3);
		rcsR.setPoint(0,sf::Vector2f(0,0));
		rcsR.setPoint(1,sf::Vector2f(0,0));
		rcsR.setPoint(2,sf::Vector2f(0,0));
		/// Ustawianie parametrów obiektu (l¹downika)
		maxPower=5;
		coord.x = 400;
		coord.y = 200;
		rotV = 0;
		rot=0;
		acc=5;

		lander.setPosition( coord );

		/// Ustawienie prametrów statystyk obiektu
		font.loadFromFile("Volter.ttf");

		strVelY = "Loading Data";
		txtVelY.setFont( font );
		txtVelY.setCharacterSize(13);
		txtVelY.setOrigin(120,50);
		txtVelY.setString(strVelY);
		txtVelY.setColor(sf::Color().White);

		txtVelX = txtVelY;
		txtVelX.setString(strVelX);
		txtVelX.setOrigin(txtVelY.getOrigin().x,txtVelY.getOrigin().y-15);

		txtRot = txtVelY;
		txtRot.setString(strRot);
		txtRot.setOrigin(txtVelX.getOrigin().x,txtVelX.getOrigin().y-15);

		txtThr = txtVelY;
		txtThr.setString(strThr);
		txtThr.setOrigin(-30,txtVelY.getOrigin().y);

		txtFuel = txtThr;
		txtFuel.setString(strFuel);
		txtFuel.setOrigin(txtThr.getOrigin().x,txtThr.getOrigin().y-15);

		txtRCS = txtThr;
		txtRCS.setString(strRCS);
		txtRCS.setOrigin(txtFuel.getOrigin().x,txtFuel.getOrigin().y-15);


	}

	virtual ~cLander(void)
	{
	}

	void loopObject( sf::RenderWindow & window, sf::Time & czasFiz, float gravA )
	{
		vel.y += (gravA * czasFiz.asSeconds() ) ;
		rot +=rotV * czasFiz.asSeconds();

		coord.x += vel.x * czasFiz.asSeconds();
		coord.y += vel.y * czasFiz.asSeconds();
		lander.setRotation(rot);;
		lander.setPosition(coord);

		thrust.setPosition(coord);
		thrust.setRotation(rot);

		rcsL.setPosition(coord);
		rcsL.setRotation(rot);

		rcsR.setPosition(coord);
		rcsR.setRotation(rot);

		///Statystyki
		txtVelY.setPosition(coord);
		txtVelX.setPosition(coord);
		txtRot.setPosition(coord);
		txtThr.setPosition(coord);
		txtFuel.setPosition(coord);
		txtRCS.setPosition(coord);
		
		
		/// Wektorowanie
		vector = rot/90;
		
		vectorP= rot/90-vector;
		std::cout << "\rRot:" << rot << "\tVelY:" << vel.y <<" m/s" << "\tVelX:" << vel.x <<" m/s\t";

		/// Wektorowanie ci¹gu
		if( vector==0 )
		{
			vel.x += (acc* czasFiz.asSeconds()) * vectorP;
			vel.y -= (acc* czasFiz.asSeconds()) * (1-vectorP);
		}
		
		if( vector==1 )
		{
			vel.y += (acc* czasFiz.asSeconds()) * vectorP;
			vel.x += (acc* czasFiz.asSeconds()) * (1-vectorP);
		}
		
		if( vector==2 )
		{
			vel.x -= (acc* czasFiz.asSeconds()) * vectorP;
			vel.y += (acc* czasFiz.asSeconds()) * (1-vectorP);
		}
				
		if( vector==3 )
		{
			vel.y -= (acc* czasFiz.asSeconds()) * vectorP;
			vel.x -= (acc* czasFiz.asSeconds()) * (1-vectorP);
		}
	
		
		
		/// Utrzymywanie poprawnoœci dzia³ania
		if( rot >=360.0f  )
		{
			rot = 0;
		}

		if( rot < 0 )
		{
			rot = 359.9f;
		}

		if( coord.y >= 600.0f )
		{
			coord.y = 1;
		}
		if( coord.y < 0 )
		{
			coord.y = 599;
		}
		if( coord.x >= 800.0f )
		{
			coord.x = 1;
		}
		if( coord.x < 0.0f )
		{
			coord.x = 799;
		}
		
		/// Koniec
	}


	void drawObject ( sf::RenderWindow & window )
	{
		/// Rysowanie poszczególnych czêœci

		window.draw(lander);

		// Plomienie!
		thrust.setPoint(2,sf::Vector2f( randomize(9.5f,2) ,randomize(acc*3,5)));
		thrust.setPoint(0,sf::Vector2f(5+(maxPower-acc),0));
		thrust.setPoint(1,sf::Vector2f(15-(maxPower-acc),0));
		if( acc >0)
		{
			window.draw(thrust);
		}
		///RCS!

		window.draw(rcsL);
		window.draw(rcsR);
		rcsL.setPoint(1,sf::Vector2f(0,(rcsL.getPoint(1).y/1.05)));
		rcsL.setPoint(2,sf::Vector2f(0,(rcsL.getPoint(2).y/1.05)));
		rcsR.setPoint(1,sf::Vector2f(0,(rcsR.getPoint(1).y/1.05)));
		rcsR.setPoint(2,sf::Vector2f(0,(rcsR.getPoint(2).y/1.05)));
		
		///Statystyki!

		info = acc/maxPower*100;
		strThr = "Throtle: " + std::to_string( info ) + "%";
		txtThr.setString( strThr );
		window.draw( txtThr );

		info = NULL;
		strFuel = "Liquid Fuel: NaN";
		txtFuel.setString( strFuel );
		window.draw( txtFuel );

		info = NULL;
		strRCS = "RCS Fuel: NaN";
		txtRCS.setString( strRCS );
		window.draw( txtRCS );

		info = ceil(vel.y);
		strVelY = "V Y: "+std::to_string( info )+" m/s";
		txtVelY.setString( sf::String( strVelY ) );
		window.draw(txtVelY);


		info = ceil(vel.x);
		strVelX = "V X: "+std::to_string( info )+" m/s";
		txtVelX.setString( sf::String( strVelX ) );
		window.draw(txtVelX);

		info = ceil(rot);
		strRot = "Rot: "+std::to_string( info )+"'";
		txtRot.setString( sf::String( strRot) );
		if(info >90 && info < 270)
		{
			txtRot.setColor(sf::Color().Red);
		}
		else
		{
			txtRot.setColor(sf::Color().White);
		}
		window.draw(txtRot);
		

	}

	void rotateObject (float newRotV)
	{
		rotV += newRotV;

		rcsL.setPoint(1,sf::Vector2f( 0, -(newRotV*3) ) );
		rcsL.setPoint(2,sf::Vector2f( 2,  -(newRotV*3)) );
		rcsR.setPoint(1,sf::Vector2f( -2, (newRotV*3) ) );
		rcsR.setPoint(2,sf::Vector2f( 0, (newRotV*3) ) );
	}

	void accelerateObject (float newAcc )
	{
		acc += newAcc;
		if (acc > maxPower)
		{
			acc = maxPower;
		}
		if (acc < 0)
		{
			acc = 0;
		}
	}

	float randomize( float min, int ile )
	{
		return rand()%ile + min;
	}
};

