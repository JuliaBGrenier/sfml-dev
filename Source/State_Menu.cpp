#include "../Include/State_Menu.h"


const sf::Time State_Menu::TimePerFrame = sf::seconds(1.f/60.f);


State_Menu::State_Menu(State_Game &s1)
: s1(s1)
, mPlaying(false)
, mFont()
, mtextColor(143,16,208,255)
, mReverseColor(false)
, mTxt_title()
, mTxt_resetScore()
, mTxt_score()
, mTxt_continue()
{
	mFont.loadFromFile("Media/dogica.ttf");

    mTxt_title.setFont(mFont);
    mTxt_resetScore.setFont(mFont);
    mTxt_score.setFont(mFont);
    mTxt_continue.setFont(mFont);

    mTxt_title.setString("Tic Tac Toe");
    mTxt_resetScore.setString("Press 'r' to reset the score");
    mTxt_score.setString(std::string("X won " + std::to_string(s1.getScoreX()) + " games and O won " + std::to_string(s1.getScoreO()) + " games"));
    mTxt_continue.setString("Click on the screen to continue");

    mTxt_title.setFillColor(mtextColor);
    mTxt_title.setCharacterSize(50);
    mTxt_title.setPosition(24, 50);
    mTxt_title.setLineSpacing(2.f);

    mTxt_resetScore.setFillColor(mtextColor);
    mTxt_resetScore.setCharacterSize(18);
    mTxt_resetScore.setPosition(50, 250);
    mTxt_resetScore.setLineSpacing(2.f);

    mTxt_score.setFillColor(mtextColor);
    mTxt_score.setCharacterSize(30);
    mTxt_score.setPosition(100, 300);
    mTxt_score.setLineSpacing(2.f);

    mTxt_continue.setFillColor(mtextColor);
    mTxt_continue.setCharacterSize(18);
    mTxt_continue.setPosition(20, 500);

}


void State_Menu::handlePlayerInput(int x, int y)
{
    mPlaying = true;
    //std::cout << "sup cutie Cam Cam d'amour" << std::endl;
}


int State_Menu::processEvents(sf::RenderWindow &Window)
{
    sf::Event event;
    while (Window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::MouseButtonPressed:
                handlePlayerInput(event.mouseButton.x, event.mouseButton.y);
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::R)
                    s1.resetScore();
                break;
            case sf::Event::Closed:
                return (-1);
                break;
        }
    }
    return 1;
}

void State_Menu::update(sf::Time deltaTime)
{

    mTxt_score.setString(std::string("X won " + std::to_string(s1.getScoreX()) + " games" + "\n\t and\n" + "O won " + std::to_string(s1.getScoreO()) + " games"));

    // Text color animation

    if (mReverseColor == false)
    {
        mtextColor.r+=4;
    }
    if (mReverseColor == true)
    {
        mtextColor.r-=4;
    }

    if (mtextColor.r <= 5 || mtextColor.r >= 250)
    {
        mReverseColor = !mReverseColor;
    }

    mTxt_continue.setFillColor(mtextColor);
}

void State_Menu::render(sf::RenderWindow &Window)
{
    Window.clear(sf::Color(8, 0, 60, 255));
    Window.draw(mTxt_title);
    Window.draw(mTxt_resetScore);
    Window.draw(mTxt_score);
    Window.draw(mTxt_continue);
    Window.display();
}

int State_Menu::run(sf::RenderWindow &Window)
{

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (Window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            if (mPlaying == true) {
                mPlaying = false;
                return 0;
            }

            update(TimePerFrame);

            return (processEvents(Window));
        }
        render(Window);
    }

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}
