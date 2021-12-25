
#include <iostream>
#include <sstream>
//#include <_vector>
#include <iomanip>
#include <list>
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Checking.h"
#include <windows.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;



void  Menu(string& file,RenderWindow& window, _vector<Player>& vec_of_players);




int main() {
	//HWND hWnd = GetConsoleWindow();//Получиление дескриптора(что-то вроде указателя на окно)
	//MoveWindow(hWnd, 490, 150, 420, 450, TRUE);

	setlocale(LC_ALL, "Rus");
	Player player;
	_vector<Player> vec_of_players;
	 string file = "File_of_players.txt";
	RenderWindow window(VideoMode(1700, 900), "THE Adventures");
	player.readFilePlayers(file, vec_of_players, window);	
    Menu(file, window, vec_of_players);//вызов меню
	 // () - прямоугольник, определяющий 
	// установка по заданному пр-ку                            отображаемую зону
	//Player player;
	
	
}






void Menu(string& file, RenderWindow& window, _vector<Player>& vec_of_players) {
	//string file = "File_of_players";
	Texture menuTextureNG, menuTextureC, menuTextureS, menuTextureE, menuBackground;
	menuTextureNG.loadFromFile("images/Buttons/NEWGAME.png");
	menuTextureC.loadFromFile("images/Buttons/CONTINUE.png");
	menuTextureS.loadFromFile("images/Buttons/SCORE.png");
	menuTextureE.loadFromFile("images/Buttons/EXIT.png");
	menuBackground.loadFromFile("images/Mountains.png");
	Sprite
		menuContinue(menuTextureC),
		menuNewGame(menuTextureNG),
		menuScore(menuTextureS),
		menuExit(menuTextureE),
		menuBg(menuBackground);

	bool isMenu = 1;
	int menuNum = 0;
	menuBg.setPosition(0, 0);
	menuContinue.setPosition(570, 200);
	menuNewGame.setPosition(570, 340);
	menuScore.setPosition(570, 480);
	menuExit.setPosition(570, 620);




	//////////////////////////////МЕНЮ///////////////////
	bool flag = true;
	while (flag) {
		Player player;
		menuNewGame.setColor(Color::White);
		menuContinue.setColor(Color::White);
		menuScore.setColor(Color::White);
		menuExit.setColor(Color::White);

		menuNum = 0;
		window.clear(Color(129, 181, 221));

			if (vec_of_players.size() != 0) {
			if (IntRect(570, 200, 300, 50).contains(Mouse::getPosition(window))) {
				menuContinue.setColor(Color::Green);
				menuNum = 1;
			}
		}
		if (IntRect(570, 340, 300, 50).contains(Mouse::getPosition(window))) {
			menuNewGame.setColor(Color::Green);
			menuNum = 2;
		}
		if (IntRect(570, 480, 300, 50).contains(Mouse::getPosition(window))) {
			menuScore.setColor(Color::Green);
			menuNum = 3;
		}
		if (IntRect(570, 620, 300, 50).contains(Mouse::getPosition(window))) {
			menuExit.setColor(Color::Green);
			menuNum = 4;
		}



		window.draw(menuBg);
		if (vec_of_players.size() != 0) {
			window.draw(menuContinue);
		}
		window.draw(menuNewGame);
		window.draw(menuScore);
		window.draw(menuExit);
		window.display();
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menuNum) {
			case 1: //window.close();
				//player.ChoosePlayer(vec_of_players, player)
				window.setVisible(false);
				if (player.LogIn(file, vec_of_players)) {
					if (player.GetRole() == "user")
						UserMenu(file, vec_of_players, player);

					else if (player.GetRole() == "admin")
						adminMenu(file, vec_of_players, player);

					ChangeVector(vec_of_players, player);
				}
			//	player.writeFilePlayers(file, vec_of_players);
				break;
			case 2: //window.close();
				//if (player.NewGame(vec_of_players, player)) {
				window.setVisible(false);
				player.SignUp(file, vec_of_players);
				if (player.GetRole() == "user")
					Game( player);
				else if (player.GetRole() == "admin")
					adminMenu(file, vec_of_players, player);
				ChangeVector(vec_of_players, player);
				player.writeEndFilePlayers(file,player);
				//player.writeFilePlayers(file, vec_of_players);
				break;
			case 3:window.setVisible(false);
				MenuShowScore(vec_of_players);
				break;
			case 4:player.writeFilePlayers(file, vec_of_players);
				flag = false;
				window.close();
			}
			window.setVisible(true);
			//switch (menuNum) {
			//case 1: isMenu = false;
			//	// СОЗДАНИЕ ОКНА ВЫБОРА ИГРОКА
			//	break;
			//case 2: isMenu = false;
			//	// ОКНО РЕГИСТРАЦИИ
			//	// Выходим из меню
			//	break;
			//case 3: break;
			//case 4:
			//	// ЗАПИСЬ В ФАЙЛ
			//	window.close();
			//	isMenu = false;
			//	break;
			//}
			//	if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			//	if (menuNum == 2) {
			//		/*window.draw(about); */window.display(); 
			//	while (!Keyboard::isKeyPressed(Keyboard::Escape));
			//	}
			//	if (menuNum == 3) {
			//		window.close(); isMenu = false; 
			//	}

		}

	}
	
}
