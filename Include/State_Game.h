#ifndef STATE_GAME_H
#define STATE_GAME_H


#include <iostream>

#include <SFML/Graphics.hpp>

#include "../Include/cState.h"
#include "../Include/animation.h"

class State_Game : public cState
{
    public: State_Game();
    virtual int run(sf::RenderWindow &Window);
        int     getScoreX();
        int     getScoreO();
        void    resetScore();

    private:
        int     processEvents(sf::RenderWindow &Window);

        void    switchTurn();
        void    manageBoard(int x, int y);
        void    handlePlayerInput(int x, int y);
        void    makeAMove(int box);
        void    checkWinner();
        void    gameEnd();
        void    drawBoard(sf::RenderWindow &Window);


        void    update(sf::Time deltaTime);
        void    render(sf::RenderWindow &Window);



    private:
		static const sf::Time	TimePerFrame;

        sf::Sprite          mBoardGame[3][3]; // Contains the sprite of the board
        sf::Sprite          mBackground;
        sf::Texture         mTextures;
        sf::Texture         mTextureX;
        sf::Texture         mTextureO;
        char                mTicTacToe[3][3];   // Array of char that reflects the board
        char                mPlayerTurn;
        int                 mScoreX;
        int                 mScoreO;
        int                 mCurrentState;

};

#endif // STATE_GAME_H
