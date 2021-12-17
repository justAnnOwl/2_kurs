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
		sprite.setOrigin(w /54, h /54); // Установка первоначального положения объекта 
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
	//map<string, bool> key; // Информация о нажатиях клавиш хранится в массиве 
	Hero(Image& image, String Name, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H) {
		//obj = level.GetObjectsByName("solid"); // Получаем объекты, нужные для взаимодействия врага с картой
		if (name == "Hero") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			coin = 0;
			health = 3;
			////////ВОПРОС ПО КООРДИНАТАМ ВНОВЬ!!!!!!!
			//state = stay;
			/// ВОЗМОЖНО, НУЖНА ДРУГАЯ СКОРОСТЬ!
		}
	}
	void KeyCheck();
	void CheckCollisionWithMap(float Dx, float Dy, string* TileMap);
	void Update(float time, string*	 TileMap);
	int GetCoin() {
		return coin;
	}
};
class Enemy : public Entity {
public:
	Enemy(Image& image, String Name, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		//		obj = level.GetObjectsByName("solid");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
		if (name == "Enemy") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
	}
	//void CheckCollisionWithMap(float Dx, float Dy) {
	//	//нужно прописать .rect
	//	for (int i = 0; i < obj.size(); i++) {
	//		if (getRect().intersects(obj.at(i).rect)) {
	//			if (obj.at(i).name == "solid") {
	//				if (Dy > 0) {
	//					y = obj.at(i).rect.top - h;
	//					dy = 0;
	//					isOnGround = true;
	//				}
	//				if (Dy < 0) {
	//					y = obj.at(i).rect.top + obj.at(i).rect.height;
	//					dy = 0;
	//				}
	//				if (Dx > 0) {
	//					x = obj.at(i).rect.left - w;
	//					dx = -0.1;
	//					sprite.scale(-1, 1); // Установка масштаба -1 отразить
	//				}
	//				if (Dx < 0) {
	//					x = obj.at(i).rect.left + obj.at(i).rect.width;
	//					dx = 0.1;
	//					sprite.scale(-1, 1);
	//				}
	//			}
	//		}
	//	}
	//}
	//void Update(float time) {
	//	if (name == "Enemy") {
	//		CheckCollisionWithMap(dx, 0);
	//		x += dx * time;
	//		sprite.setPosition(x + w / 2, y + h / 2);
	//	if (health <= 0) { life = false; }
	//	}
	//}

};

