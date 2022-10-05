#include "../Include/State_Game.h"


const sf::Time State_Game::TimePerFrame = sf::seconds(1.f/30.f);


State_Game::State_Game()
: mBackground()
, mTextures()
, mTextureX()
, mTextureO()
, mTicTacToe {{'n','n','n'},{'n','n','n'},{'n','n','n'}} // n : nothing
, mPlayerTurn('x')
, mScoreX(0)
, mScoreO(0)
, mCurrentState(0)
{
    mTextures.loadFromFile("Media/output.png");
    mTextureX.loadFromFile("Media/x_animated2.png");
    mTextureO.loadFromFile("Media/o_animated.png");

    mBackground.setTexture(mTextures);
    mBackground.setTextureRect(sf::IntRect(0, 0, 32, 32));
    mBackground.setScale(600/mBackground.getLocalBounds().width,600/mBackground.getLocalBounds().height);
    mBackground.setPosition(0.f, 0.f);

    /*.
        00 01 02
        10 11 12
        20 21 22
    */

    int margin = 20;

    mBoardGame[0][0].setPosition(margin,margin);
    mBoardGame[0][1].setPosition(180+2*margin,margin);
    mBoardGame[0][2].setPosition(380+2*margin,margin);
    mBoardGame[1][0].setPosition(margin,180+2*margin);
    mBoardGame[1][1].setPosition(180+2*margin,180+2*margin);
    mBoardGame[1][2].setPosition(380+2*margin,180+2*margin);
    mBoardGame[2][0].setPosition(margin,380+2*margin);
    mBoardGame[2][1].setPosition(180+2*margin,380+2*margin);
    mBoardGame[2][2].setPosition(380+2*margin,380+2*margin);

}


int State_Game::run(sf::RenderWindow &Window)
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (Window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            if (mCurrentState == 1) {
                mCurrentState = 0;
                return 1;
            }
            update(TimePerFrame);

            return (processEvents(Window));
        }
        render(Window);
    }

    return (-1);
}


int State_Game::getScoreX()
{
    return mScoreX;
}

int State_Game::getScoreO()
{
    return mScoreO;
}

void State_Game::resetScore()
{
    mScoreX = 0;
    mScoreO = 0;
}


int State_Game::processEvents(sf::RenderWindow &Window)
{
    sf::Event event;
    while (Window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::MouseButtonPressed:
                handlePlayerInput(event.mouseButton.x, event.mouseButton.y);
                break;
            case sf::Event::Closed:
                return (-1);
                break;
        }
    }
    return 0;
}

void State_Game::switchTurn()
{
    if (mPlayerTurn == 'x')
        mPlayerTurn = 'o';
    else
        mPlayerTurn = 'x';
}

void State_Game::manageBoard(int x, int y)
{

    if (mPlayerTurn == 'x')
    {
        mBoardGame[x][y].setTexture(mTextureX);
        mBoardGame[x][y].setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
    else
    {
        mBoardGame[x][y].setTexture(mTextureO);
        mBoardGame[x][y].setTextureRect(sf::IntRect(0, 0, 16, 16));
    }

    // mBoardGame[x][y].setScale(5.9,5.9);

    mBoardGame[x][y].setScale(10,10);

    mTicTacToe[x][y] = mPlayerTurn;
    checkWinner();

    switchTurn();
}


/*
    1 2 3
    4 5 6
    7 8 9
*/

void State_Game::handlePlayerInput(int x, int y)
{
    int windowSize(600);

    if (y < windowSize/3)
    {
        if (x < windowSize/3)
            makeAMove(1);
        else if (x > windowSize/3 && x < 2*windowSize/3)
            makeAMove(2);
        else if (x > 2*windowSize/3)
            makeAMove(3);
    }
    else if (y > windowSize/3 && y < 2*windowSize/3)
    {
        if (x < windowSize/3)
            makeAMove(4);
        else if (windowSize/3 < x && x < 2*windowSize/3)
            makeAMove(5);
        else if (2*windowSize/3 < x)
            makeAMove(6);
    }
    else if (y > 2*windowSize/3)
    {
        if (x < windowSize/3)
            makeAMove(7);
        else if (windowSize/3 < x && x < 2*windowSize/3)
            makeAMove(8);
        else if (2*windowSize/3 < x)
            makeAMove(9);
    }
}

void State_Game::makeAMove(int box)
{
    switch (box)
    {
        case 1:
            if (mTicTacToe[0][0] == 'n')
            {
                manageBoard(0,0);
            }
            break;
        case 2:
            if (mTicTacToe[0][1] == 'n')
            {
                manageBoard(0,1);
            }
            break;
        case 3:
            if (mTicTacToe[0][2] == 'n')
            {
                manageBoard(0,2);
            }
            break;
        case 4:
            if (mTicTacToe[1][0] == 'n')
            {
                manageBoard(1,0);
            }
            break;
        case 5:
            if (mTicTacToe[1][1] == 'n')
            {
                manageBoard(1,1);
            }
            break;
        case 6:
            if (mTicTacToe[1][2] == 'n')
            {
                manageBoard(1,2);
            }
            break;
        case 7:
            if (mTicTacToe[2][0] == 'n')
            {
                manageBoard(2,0);
            }
            break;
        case 8:
            if (mTicTacToe[2][1] == 'n')
            {
                manageBoard(2,1);
            }
            break;
        case 9:
            if (mTicTacToe[2][2] == 'n')
            {
                manageBoard(2,2);
            }
            break;
    }
}

void State_Game::checkWinner()
{

    // Verify if line  xxx or ooo
    for (int l=0; l<=2; l+=1) {

        if (mTicTacToe[l][0] == 'x' && mTicTacToe[l][1] == 'x' && mTicTacToe[l][2] == 'x') {
                mScoreX++;
                gameEnd();
        }
        else if (mTicTacToe[l][0] == 'o' && mTicTacToe[l][1] == 'o' && mTicTacToe[l][2] == 'o') {
                mScoreO++;
                gameEnd();
        }
    }

    // Verify if column
    for (int c=0; c<=2; c+=1) {
        if (mTicTacToe[0][c] == 'x' && mTicTacToe[1][c] == 'x' && mTicTacToe[2][c] == 'x') {
                mScoreX++;
                gameEnd();
        }
        else if (mTicTacToe[0][c] == 'o' && mTicTacToe[1][c] == 'o' && mTicTacToe[2][c] == 'o') {
                mScoreO++;
                gameEnd();
        }
    }

    // Verify if diagonal
    if (mTicTacToe[0][0] == 'x' && mTicTacToe[1][1] == 'x' && mTicTacToe[2][2] == 'x') {
        mScoreX++;
        gameEnd();
    }
    else if (mTicTacToe[0][0] == 'o' && mTicTacToe[1][1] == 'o' && mTicTacToe[2][2] == 'o') {
        mScoreO++;
        gameEnd();
    }
    if (mTicTacToe[0][2] == 'x' && mTicTacToe[1][1] == 'x' && mTicTacToe[2][0] == 'x') {
        mScoreX++;
        gameEnd();
    }
    else if (mTicTacToe[0][2] == 'o' && mTicTacToe[1][1] == 'o' && mTicTacToe[2][0] == 'o') {
        mScoreO++;
        gameEnd();
    }

    // Verify if tie
    if (mTicTacToe[0][0] != 'n' && mTicTacToe[0][1] != 'n' && mTicTacToe[0][2] != 'n' &&
        mTicTacToe[1][0] != 'n' && mTicTacToe[1][1] != 'n' && mTicTacToe[1][2] != 'n' &&
        mTicTacToe[2][0] != 'n' && mTicTacToe[2][1] != 'n' && mTicTacToe[2][2] != 'n') {

        std::cout << "tie" << std::endl;
        gameEnd();

    }


}

void State_Game::gameEnd()
{
    // Empty the board
    for (int l=0; l<=2; l+=1) {
        mTicTacToe[l][0] = 'n';
        mTicTacToe[l][1] = 'n';
        mTicTacToe[l][2] = 'n';
    }

    mCurrentState = 1;

}

void State_Game::drawBoard(sf::RenderWindow &Window)
{
    // Only draw sprite from array that has something in it
    for (int l=0; l<=2; l+=1)
    {
        if (mTicTacToe[l][0] != 'n')
            Window.draw(mBoardGame[l][0]);
        if (mTicTacToe[l][1] != 'n')
            Window.draw(mBoardGame[l][1]);
        if (mTicTacToe[l][2] != 'n')
            Window.draw(mBoardGame[l][2]);
    }
}

void State_Game::update(sf::Time deltaTime)
{
    for (int l=0; l<=2; l+=1)
    {
            //std::cout << "update cupcake" << std::endl;
        if (mTicTacToe[l][0] != 'n')
            animation(mBoardGame[l][0], deltaTime);
        if (mTicTacToe[l][1] != 'n')
            animation(mBoardGame[l][1], deltaTime);
        if (mTicTacToe[l][2] != 'n')
            animation(mBoardGame[l][2], deltaTime);
    }
}

void State_Game::render(sf::RenderWindow &Window)
{
    Window.clear();
    Window.draw(mBackground);
    drawBoard(Window);
    Window.display();
}
