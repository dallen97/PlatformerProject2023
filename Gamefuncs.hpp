#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Entity : public sf::Drawable, public sf::Transformable {
private:
	
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray Vertices;
	sf::Texture Texture;
	sf::Vector2f Velocity;
	float X, Y, W, H;
	void Set_Texture(const char* Tex);
};

class Player : public Entity {
private:
	float Speed;
public:
	Player(float X,float Y,float W,float D);
	void Update(bool &Player_Left, bool &Player_Right, bool &Player_Up, bool &Player_Down, float &Time);
};

class Platform : public Entity {
private:
	
public:
	void Initialize(float X, float Y, float W, float H);
};
