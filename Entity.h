#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <vector>
#include <list>


using namespace sf;
using namespace std;
class Entity {
protected:
	String name;
	Texture texture;
	Sprite sprite;


	double dx,
		dy,
		x,
		y,
		speed,
		moveTimer;

	int w,
		h,
		health,
		dir;



public:
	bool isAlive,
		isMove,
		isOnGround;
	Entity(Image& image, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H;
		name = Name;
		moveTimer = 0;
		speed = 0; 
		dir = 0; dx = 0; dy = 0;
		isAlive = true;
		isOnGround = false;
		isMove = false;
		texture.loadFromImage(image); // Загрузка текстуры из картинки
		sprite.setTexture(texture); // Установка текстуры спрайту
		 // Установка первоначального положения объекта 
		///////////!!!!!!!!!!!!!! не по центру. а где-то в начале нужно посчитать по карте
	}
	double GetX() {
		return x;
	}
	double GetY() {
		return y;
	}
	int GetHealth() {
		return health;
	}
	FloatRect getEntityRect();
	Sprite GetSprite();
	virtual void Update(float, string*) {};
	virtual void CheckCollisionWithMap(float, float, string*) {};
	//friend bool isGame();
};

class Hero : public Entity {
	int coin;
public:

	enum { left, right, up, down, jump, climb, stay } state;
	
	Hero(Image& image, String Name, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H) {
		if (name == "Hero") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w/2, h/2);
			coin = 0;
			health = 3;
		}
	}
	void KeyCheck();
	void CheckCollisionWithMap(float Dx, float Dy, string* TileMap);
	void Update(float time, string*	 TileMap);
	int GetCoin() {
		return coin;
	}
	void SetHealthMinus() {
		health--;
	}
};
class Enemy : public Entity {
public:
	Enemy(Image& image, string Name, float X, float Y, int W, int H) :Entity(image, Name ,X, Y, W, H) {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w , h);
			dx = 0.05;
	}
	void CheckCollisionWithMap(float Dx, float Dy, string* TileMap);
	void Update(float time, string* TileMap);
};

