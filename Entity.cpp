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
		else if (Keyboard::isKeyPressed(Keyboard::Escape))////////////////////////////////////////ВЫЗЫВАЕТ ИСКЛЮЧЕНИЯ!!!!!!!!!!!
		{
			bool flag = true;
			RenderWindow pauseWindow(VideoMode(500, 300), "PAUSE");
			Texture bgT;
			bgT.loadFromFile("images/BirdsAndMountains.png");
			Sprite bgS(bgT);
			bgS.setPosition(0, 0);// 

			Texture levelContinueT;
			levelContinueT.loadFromFile("images/Buttons/LevelContinue.png");
			Sprite levelContinueS(levelContinueT);
			levelContinueS.setPosition(50, 50);///////////////////////////////////////////////////////////////////////////////=================================================================================

			Texture levelCancelT;
			levelCancelT.loadFromFile("images/Buttons/ExitToMenu.png");
			Sprite levelCancelS(levelCancelT);
			levelCancelS.setPosition(50, 175);
			int menuNum;
			while (flag) {
				levelContinueS.setColor(Color::White);
				levelCancelS.setColor(Color::White);
				menuNum = PauseKeyCheck(pauseWindow);
				switch (menuNum) {
				case 1:
					levelContinueS.setColor(Color::Green);
					if (Mouse::isButtonPressed(Mouse::Left)) {
						state = stay;
						speed = 0;
						return;
					}
					break;
				case 2: levelCancelS.setColor(Color::Green);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						break;
					}

				}
					pauseWindow.clear();
					pauseWindow.draw(bgS);
					pauseWindow.draw(levelContinueS);
					pauseWindow.draw(levelCancelS);
					pauseWindow.display();
					//system("pause");								   //m_render->window().close();
						//else if (Keyboard::isKeyPressed(Keyboard::Down))&& на лестнице {
						/*	state = down;
						}*/
						//else if( ESC )ОТКРЫТЬ МЕНЮ 
						//if (!isKeyP)
					//system("pause");
				
			}

		}
		else {
			state = stay;
			speed = 0;
		}
	}
}
void Hero:: CheckCollisionWithMap(float Dx, float Dy, string* TileMap ) {
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
				}
			}
			 if (TileMap[i][j] == 'c') {
				coin++;
				TileMap[i][j] = ' ';
			 }
		}
	}
}
int PauseKeyCheck(RenderWindow&window) {

	

		int menuNum=0 ;
		if (IntRect(50, 50, 400, 80).contains(Mouse::getPosition(window))) {
			menuNum = 1;
		}
		if (IntRect(50, 175, 400, 80).contains(Mouse::getPosition(window))) {
			menuNum = 2;
		}
		return menuNum;
	
}
//bool IsSolid() {
//	return TileMap solid or no  И ПРЕДАТЬ В О ВЬЮ ДВИЖЕНИЯ КАРТЫ
//}
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
	case stay: break;
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
	//setPlayerCoordinateForView(x, y); //НАПИСАТЬ VIEW!!!
	if (isAlive) {
		//setPlayerCoordinateForView(x, y);
	}
	dy += 0.0015 * time;// ПОЧЕМУ ИМЕННО ЭТО ЧИСЛО???
}
//void Enemy:: Update(float time) {
//	if (name == "Enemy") {
//		//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }
//		//меняет направление примерно каждые 3 сек
//		CheckCollisionWithMap(dx, 0);
//		x += dx * time;
//		sprite.setPosition(x + w / 2, y + h / 2);
//		//if (health <= 0) { life = false; }
//	}
//}