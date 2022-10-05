#ifndef STATE_MENU_H
#define STATE_MENU_H


#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Include/cState.h"
#include "../Include/State_Game.h"

class State_Menu : public cState
{
	public:	State_Menu(State_Game &s1);
		virtual int run(sf::RenderWindow &Window);


	private:

        void    handlePlayerInput(int x, int y);

        int		processEvents(sf::RenderWindow &Window);
        void    update(sf::Time deltaTime);
        void    render(sf::RenderWindow &Window);

	private:
		static const sf::Time	TimePerFrame;

		State_Game	&s1;

		bool		mPlaying;
		sf::Font 	mFont;
		sf::Color	mtextColor;
		bool		mReverseColor;
		sf::Text	mTxt_title;
		sf::Text	mTxt_resetScore;
		sf::Text	mTxt_score;
		sf::Text	mTxt_continue;


};


#endif // STATE_MENU_H
