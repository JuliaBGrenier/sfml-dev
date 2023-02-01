#include "../Include/Application.h"

Application::Application()
{

}

void Application::run()
{
    //Applications variables
    std::vector<cState*> States;
    int currentState = 1;

	//Window creation
	sf::RenderWindow Window(sf::VideoMode(600, 600), "SFML Application", sf::Style::Titlebar | sf::Style::Close);

	//Screens preparations
	State_Game s0_game;
	States.push_back(&s0_game); // ATTENTION CREATE A COPY
	State_Menu s1_menu(s0_game); // ToDo => optimize
	States.push_back(&s1_menu); // BUT using vector of pointers => debugging

	//Main loop
	while (currentState >= 0)
	{
		currentState = States[currentState]->run(Window);
	}
}
