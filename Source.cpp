//Creator: Dustin Allen
//COP 3003: Programming 2
//Summary: This program is meant to be a single level platformer game, to include a few obstacles and end with a message
//		   congratulating the player for completion of the level.

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gamefuncs.hpp"

int Window_Width = 1260;	//initiating the window size (temporary as unsure of size wanted later on)
int Window_Height = 720;
using std::cout;
using std::endl;
using namespace sf; //used to not have to type sf:: in front of multiple lines


int main()
{
	RenderWindow app(VideoMode(Window_Width, Window_Height), "Platforming Game");//rendering the window and giving the window the title "platforming game"
	Event e;

	bool Player_Up, Player_Down, Player_Left, Player_Right = false; // setting these values as false so the player is still when not moving


	int Level_Array[10][10] = { {0,0,0,0,0,0,0,0,0,0},
							  {0,0,0,0,0,0,1,1,0,0},
							  {0,0,0,0,0,0,0,0,0,0},
							  {0,0,0,0,0,0,0,0,0,0},
							  {0,0,0,0,0,0,0,0,0,0},
							  {0,0,0,0,0,0,0,0,0,0},
							  {0,0,0,0,0,0,0,0,0,0},
							  {1,0,0,0,0,0,0,0,0,0},
							  {0,1,0,0,0,0,0,0,0,0},
							  {0,0,1,1,1,1,1,0,0,0},
	};

	Platform level[100];

	int Level_Size = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Level_Array[i][j] == 1) {
				level[Level_Size].Initialize(j*45, i*45,15,15);
				level[Level_Size].Set_Texture("data/images/floor.png");
				Level_Size++;
			}
		}
	}

	Player player(-200, 100 ,50, 50);
	player.Set_Texture("data/images/slime.png");
	View view(Vector2f(0.0f, 0.0f), Vector2f(Window_Width,Window_Height));
	view.zoom(10);
	Clock gameClock;

	while (app.isOpen())
	{
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}
		
		//the following is assigning the following four variables the bool value true or false based on the players keyboard inputs.
	
		Player_Right = Keyboard::isKeyPressed(Keyboard::D);
		Player_Left = Keyboard::isKeyPressed(Keyboard::A);
		Player_Up = Keyboard::isKeyPressed(Keyboard::W);
		Player_Down = Keyboard::isKeyPressed(Keyboard::S);


		float Game_Time = gameClock.getElapsedTime().asSeconds();


		player.Update(Player_Left, Player_Right, Player_Up, Player_Down, Game_Time);
		view.setCenter(player.X + player.W/2.f, player.Y + player.H/2.f); // sets the center of the screen on the player's character
		gameClock.restart().asSeconds();

		app.setView(view);// sets the view 
		app.clear(Color(13,176,185));
		app.setFramerateLimit(60); // sets framerate to prevent discrepencies in player movement speed due to
		// varying processing speeds of computers
		app.draw(player);

		for (int i = 0; i < Level_Size; i++) {
			app.draw(level[i]); // draws the platforms that have collision working
		}
		
		app.display();
	}
	return 0;
}