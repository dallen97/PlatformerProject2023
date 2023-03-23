//Creator: Dustin Allen
//COP 3003: Programming 2
//Summary: This program is meant to be a single level platformer game, to include a few obstacles and end with a message
//		   congratulating the player for completion of the level.

#include <SFML/Graphics.hpp>
#include <iostream>

int Window_Width = 1260;	//initiating the window size (temporary as unsure of size wanted later on)
int Window_Height = 720;
int Half_Height = Window_Height / 2;
int Half_Width = Window_Width / 2;

using std::cout;
using std::endl;
using namespace sf; //used to not have to type sf:: in front of multiple lines

// following class/functions will be moved to a header file later on, currently here for ease of access.

class Platform_Class{
public:
	float X_Position;
	float Y_Position;
	float X_Speed;
	float Y_Speed;
	Sprite Plat_Image;
	int Scale;
	float Top_Side;
	float Left_Side;
	float Right_Side;
	float Bottom_Side;
	Platform_Class(float X_Pos, float Y_Pos,Sprite Floor_Sprite) {
		Scale= 7;
		Plat_Image = Floor_Sprite; // sets the image used for the platforms to the sprite from the setter
		Plat_Image.setPosition(X_Pos,Y_Pos); // sets position
		Plat_Image.setScale(Scale, Scale); //scaler
		Left_Side = Plat_Image.getPosition().x;
		Right_Side = Plat_Image.getPosition().x + (Plat_Image.getLocalBounds().width * Scale);
		Top_Side = Plat_Image.getPosition().y;
		Bottom_Side = Plat_Image.getPosition().y + (Plat_Image.getLocalBounds().height * Scale);

	}
};

class Player_Class {	//Class creation for Player
	public:	
		//making public so player has access to values when playing
		bool Face_Right;
		bool Player_Grounded;
		bool Is_Collision;
		float X_Position;
		float Y_Position;
		float X_Speed;
		float Y_Speed;
		float Top_Side;
		float Left_Side;
		float Right_Side;
		float Bottom_Side;
		int Scale;

		Sprite Player_Sprite;

		Player_Class(Sprite Sprite) {	// function to contain the x and y position/speed
			Player_Sprite = Sprite;
			Face_Right = true;	//determines if player is facing right (later use)
			X_Position = 0;
			Y_Position = 0;
			X_Speed = 0;
			Y_Speed = 0;
			Player_Grounded = false; //checks if the player is touching the ground
			Scale = 2;
			Player_Sprite.setScale(Scale, Scale);
			Is_Collision = false; // checks if the player has collided with anything

			cout << "stuff" << endl;
			
		}
		void Player_Update(bool Player_Up,bool Player_Down,bool Player_Left,bool Player_Right, Platform_Class Level[5])
			{	// void function to refelct player movement inputs. called later in function
			//speeds are assigned based on the bool values passed on, platform array Level is now pased to this for collision purposes
			if (Player_Right)
			{
				Face_Right = true;
				X_Speed = 5;
			}
			if (Player_Left)
			{
				Face_Right = false;
				X_Speed = -5;
			}
			if (Player_Up)
			{
				Y_Speed = -5;
			}
			if (Player_Down)
			{
				Y_Speed = 5;
			}
			else if (!Player_Right && !Player_Left && !Player_Up && !Player_Down) //if the player is not inputing any 
				//direction, then the player is standing still
			{
				X_Speed = 0;
				Y_Speed = 0;
			}


			if (Player_Grounded == true) { // if player is touching ground then the verticle speed is set to 0
				Y_Speed = 0;
			}

			Player_Sprite.move(Vector2f(X_Speed, 0)); //allows the sprite to move around on the screen
			Collision(X_Speed,0,Level); //calls the collision function
			Player_Sprite.move(Vector2f(0, Y_Speed));
			Collision(0, Y_Speed, Level);
						
		}

		void Collision(float X_Speed, float Y_Speed ,Platform_Class Level[5]) {
			for (int y = 0; y < 5; y++) {

				if (Player_Sprite.getPosition().x + Player_Sprite.getLocalBounds().width * Scale >
					Level[y].Left_Side && Player_Sprite.getPosition().x < Level[y].Right_Side &&
					Player_Sprite.getPosition().y + Player_Sprite.getLocalBounds().height * Scale >
					Level[y].Top_Side && Player_Sprite.getPosition().y < Level[y].Bottom_Side) {
					Is_Collision = true; // sets is_collision to true if the player is touching the bounds of the the current platform held in the Level array
					//scale is taken into account for this with the Scale variable
				}
				else {
					Is_Collision = false; // if the player isnt touching then collision is false
				}
				if (Is_Collision) { //if is_collision is true then this helps create the collision
					if (X_Speed > 0) {
						Player_Sprite.setPosition(Vector2f(Level[y].Left_Side - Player_Sprite.getLocalBounds().width * Scale, Player_Sprite.getPosition().y));
					}
					if (X_Speed < 0) {
						Player_Sprite.setPosition(Vector2f(Level[y].Right_Side, Player_Sprite.getPosition().y));
					}
					if (Y_Speed > 0) {
						Player_Sprite.setPosition(Vector2f(Player_Sprite.getPosition().x, Level[y].Top_Side - Player_Sprite.getLocalBounds().height * Scale));
					}
					if (Y_Speed < 0) {
						Player_Sprite.setPosition(Vector2f(Player_Sprite.getPosition().x, Level[y].Bottom_Side));
					}
				}
			}
		}

};



int main()
{
	RenderWindow app(VideoMode(Window_Width, Window_Height), "Platforming Game");//rendering the window and giving the window the title "platforming game"
	Event e;

	bool Player_Up, Player_Down, Player_Left, Player_Right = false; // setting these values as false so the player is still when not moving

	Font Game_Font;	//sets a font variable
	Game_Font.loadFromFile("C:/Windows/Fonts/arial.ttf"); //loads a font from the c drive


	Texture Char_Sprite;	//loading up a texture and pulling the texture from a file located in the x64
	Char_Sprite.loadFromFile("data/images/slime.png");	
	Sprite Slime_Sprite(Char_Sprite);

	Texture Platform_Sprites;
	Platform_Sprites.loadFromFile("assets/floors.png"); //loads up textrure from the file located in the assets folder
	//load from file not working for some reason, still troubleshooting this.
	Sprite Floor_Sprite1(Platform_Sprites);
	Floor_Sprite1.setTextureRect(IntRect(0,0,16,16)); //choosing parts of the texture png to display. will have accurate values once
	// the load from file portion is working properly
	
	Player_Class Player_Object(Slime_Sprite); //calling the Player_Class and creating an object
;

	Platform_Class Level_One[5]={Platform_Class(100,200,Floor_Sprite1),Platform_Class(205,200,Floor_Sprite1),
								 Platform_Class(310,200,Floor_Sprite1) ,Platform_Class(415,200,Floor_Sprite1),
								 Platform_Class(520,200,Floor_Sprite1)};

	View view(Vector2f(0.0f, 0.0f), Vector2f(Window_Width,Window_Height));

	while (app.isOpen())
	{
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}
		
		//the following is assigning the following four variables the bool value true or false based on the players keyboard inputs.
	
		Player_Right = Keyboard::isKeyPressed(Keyboard::Right);
		Player_Left = Keyboard::isKeyPressed(Keyboard::Left);
		Player_Up = Keyboard::isKeyPressed(Keyboard::Up);
		Player_Down = Keyboard::isKeyPressed(Keyboard::Down);
		Player_Object.Player_Update(Player_Up, Player_Down, Player_Left, Player_Right, Level_One); // the four variables are then passed to the function Player_Update in the player_object object

		view.setCenter(Vector2f(Player_Object.Player_Sprite.getPosition().x +
								Player_Object.Player_Sprite.getLocalBounds().width * Player_Object.Scale / 2.0f,
								Player_Object.Player_Sprite.getPosition().y + Player_Object.Player_Sprite.getLocalBounds().height *
								Player_Object.Scale)); // sets the center of the screen on the player's character

		app.setView(view);// sets the view 
		app.clear(Color(13,176,185));
		app.setFramerateLimit(60); // sets framerate to prevent discrepencies in player movement speed due to
		// varying processing speeds of computers
		app.draw(Player_Object.Player_Sprite); //draws the sprite added

		for (int i = 0; i < 5; i++) {
			app.draw(Level_One[i].Plat_Image); // draws the platforms that have collision working
		}
		
		app.display();
	}
	return 0;
}
