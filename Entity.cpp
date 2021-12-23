#include "Entity.h"
#include "Map.h"

Sprite Entity::GetSprite() {
	return sprite;
}
FloatRect Entity::getEntityRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
}
void Hero::KeyCheck()
{// ДОПИСАТЬ ОСТАЛЬНЫЕ НАПРАВЛЕНИЯ
	if (Keyboard::isKeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
			sprite.setScale(1, 1);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
			sprite.setScale(-1, 1);//////&&&&
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && (isOnGround)) {
			if (state != climb) {
				isOnGround = false;
				state = jump;
				dy = -0.6;
			}
			else {
				dy = -0.05;
			}

		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			dy = 0.1;
			//переместить на землю
			//isOnGround=true;
		}
		//else if (Keyboard::isKeyPressed(Keyboard::Escape))////////////////////////////////////////ВЫЗЫВАЕТ ИСКЛЮЧЕНИЯ!!!!!!!!!!!

		else {
			state = stay;
			speed = 0;
		}
	}
}
void Hero::CheckCollisionWithMap(float Dx, float Dy, string* TileMap) {
	//Level lvl(levelNum);
	for (int i = y / 32; i < (y + h) / 32; i++) { // Проход по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++) {
			if (TileMap[i][j] == '0') {
				if (Dy > 0) {//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
					y = i * 32 - h;
					dy = 0;
					isOnGround = true;
				}
				if (Dy < 0) {//столкновение с верхними краями карты
					y = i * 32 + 32;
					dy = 0;
				}
				if (Dx > 0) {//с правым краем карты
					x = j * 32 - w;
				}
				if (Dx < 0) {// с левым краем карты
					x = j * 32 + 32;
					dx = 0;
				}
			}
			if (TileMap[i][j] == 'c') {
				coin++;
				TileMap[i][j] = ' ';
			}
		}
	}
}


void Hero::Update(float time, string* TileMap) {
	dx = 0;
	KeyCheck();
	switch (state) {// ДОПИСАТЬ JUMP И ДР
	case right: dx = speed;
		break;
	case left: dx = -speed;
		break;
	case up: dx = 0;
		break;
	case down: dx = 0;
		break;
	case stay:
		break;
	}
	x += dx * time;
	CheckCollisionWithMap(dx, 0, TileMap);// Обработка столкновений по Х
	y += dy * time;
	CheckCollisionWithMap(0, dy, TileMap);// Обработка столкновений по Y
	sprite.setPosition(x, y);
	if (health < 1) {
		isAlive = false;
		//ВЫХОД ИЗ УРОВНЯ
	}
	if (!isMove) speed = 0;
	dy += 0.0015 * time;
}

void Enemy::CheckCollisionWithMap(float Dx, float Dy, string* TileMap) {
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
			{
				if (Dy > 0) { y = i * 32. - h; }// По Y вниз
				if (Dy < 0) { y = i * 32. + 32.; }// Столкновение с верхними краями карты					
				if (Dx > 0) {
					x = j * 32. - w;
					dx = -0.1;
					sprite.scale(-1, 1);
				}//с правым краем карты
				if (Dx < 0) {  // С левым краем
					x = j * 32. + 32;
					dx = 0.1;
					sprite.scale(-1, 1);
				}

			}
		}
}
void Enemy::Update(float time, string* TileMap) {
	CheckCollisionWithMap(dx, 0, TileMap);
	x += dx * time / 1.1;
	sprite.setPosition(x + w / 2., y + h / 2.);
	if (health <= 0) {
		isAlive = false;
	}
}