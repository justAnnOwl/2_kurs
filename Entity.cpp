#include "Entity.h"
#include "Map.h"

Sprite Entity::GetSprite() {
	return sprite;
}
FloatRect Entity::getEntityRect() {//�-��� ��������� ��������������. ��� �����,������� (���,�����).
	return FloatRect(x, y, w, h);//��� �-��� ����� ��� �������� ������������ 
}
void Hero::KeyCheck()
{// �������� ��������� �����������
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
			//����������� �� �����
			//isOnGround=true;
		}
		//else if (Keyboard::isKeyPressed(Keyboard::Escape))////////////////////////////////////////�������� ����������!!!!!!!!!!!
		
		else {
			state = stay;
			speed = 0;
		}
	}
}
void Hero:: CheckCollisionWithMap(float Dx, float Dy, string* TileMap ) {
	//Level lvl(levelNum);
	for (int i = y / 32; i < (y + h) / 32; i++) { // ������ �� ��������� �����
		for (int j = x / 32; j < (x + w) / 32; j++) {
			if (TileMap[i][j] == '0') {
				if (Dy > 0) {//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
					y = i * 32 - h;
					dy = 0;
					isOnGround = true;
				}
				if (Dy < 0) {//������������ � �������� ������ �����
					y = i * 32+32;
					dy = 0;
				}
				if (Dx > 0) {//� ������ ����� �����
					x = j * 32 - w;
				}
				if (Dx < 0) {// � ����� ����� �����
					x = j * 32+32 ;
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

//bool IsSolid() {
//	return TileMap solid or no  � ������� � � ��� �������� �����
//}
void Hero::Update(float time, string* TileMap) {
	dx = 0;
	KeyCheck();
	switch (state) {// �������� JUMP � ��
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
	CheckCollisionWithMap(dx, 0, TileMap);// ��������� ������������ �� �
	y += dy * time;
	CheckCollisionWithMap(0, dy, TileMap);// ��������� ������������ �� Y
	sprite.setPosition(x, y);
	if (health < 1) {
		isAlive = false;
		//����� �� ������
	}
	if (!isMove) speed = 0;
	//setPlayerCoordinateForView(x, y); //�������� VIEW!!!
	if (isAlive) {
		//setPlayerCoordinateForView(x, y);
	}
	dy += 0.0015 * time;
}
//void Enemy:: Update(float time) {
//	if (name == "Enemy") {
//		//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }
//		//������ ����������� �������� ������ 3 ���
//		CheckCollisionWithMap(dx, 0);
//		x += dx * time;
//		sprite.setPosition(x + w / 2, y + h / 2);
//		//if (health <= 0) { life = false; }
//	}
//}