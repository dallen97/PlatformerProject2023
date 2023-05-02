#include <SFML/Graphics.hpp>
#include "Gamefuncs.hpp"

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();

	states.texture = &Texture;

	target.draw(Vertices, states);
};

void Entity::Set_Texture(const char* Tex) {
	Texture.loadFromFile(Tex);
}

Player::Player(float X,float Y,float W,float H) {
	Speed = 100.f;

	Vertices.setPrimitiveType(sf::Quads);
	Vertices.resize(4);

	Vertices[0].position = sf::Vector2f(0, 0);
	Vertices[1].position = sf::Vector2f(W, 0);
	Vertices[2].position = sf::Vector2f(W, H);
	Vertices[3].position = sf::Vector2f(0, H);

	Vertices[0].texCoords = sf::Vector2f(0, 0);
	Vertices[1].texCoords = sf::Vector2f(W, 0);
	Vertices[2].texCoords = sf::Vector2f(W, H);
	Vertices[3].texCoords = sf::Vector2f(0, H);

};

void Player::Update(bool &D, bool &A, bool &W, bool &S, float &Time) {
	

	if (W) {
		Velocity.y = -1.f;
	}
	if (A) {
		Velocity.x = -1.f;
	}
	if (S) {
		Velocity.y = 1.f;
	}
	if (D) {
		Velocity.y = 1.f;
	}
	if (!(W || S)) {
		Velocity.y = 0;
	}
	if (!(A || D)) {
		Velocity.x = 0;
	}
	
	X += Velocity.x * Speed * Time;
	Y += Velocity.y * Speed * Time;

	setPosition(X, Y);
}

void Platform::Initialize(float X, float Y, float W, float H) {
	Vertices.setPrimitiveType(sf::Quads);
	Vertices.resize(4);

	Vertices[0].position = sf::Vector2f(0, 0);
	Vertices[1].position = sf::Vector2f(W, 0);
	Vertices[2].position = sf::Vector2f(W, H);
	Vertices[3].position = sf::Vector2f(0, H);

	Vertices[0].texCoords = sf::Vector2f(0, 0);
	Vertices[1].texCoords = sf::Vector2f(W, 0);
	Vertices[2].texCoords = sf::Vector2f(W, H);
	Vertices[3].texCoords = sf::Vector2f(0, H);

	setPosition(X, Y);
};