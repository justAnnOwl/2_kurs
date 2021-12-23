#pragma once
#include <iostream>
#include <fstream>
#include <vector> 
#include <iterator>
#include <algorithm>
#include <conio.h>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Player {
	string nick;
	double timeHighScore;
	int level;
	int highScore;
	string hash;
	string salt;
	string role;//main_admin, admin, user
	int access;//1, 0 

public:
	Player(string nick) {
		this->nick = nick;
		timeHighScore = -1;
		highScore = 0;
		level = 0;
	};
	Player() {
		this->nick = nick;
		timeHighScore = -1;
		highScore = 0;
		level = 0;
	};

	void SetNick(string temp) {
		nick = temp;
	}
	void SetTimeHighScore(double temp) {
		timeHighScore = temp;
	}
	void SetLevel(int temp) {
		level = temp;
	}
	void SetHighScore(int temp) {
		highScore = temp;
	}
	void SetAccess(int access) {
		this->access = access;
	}
	int GetLevel() {
		return level;
	}
	string GetNick() {
		return nick;
	}
	string GetRole() {
		return role;
	}
	double GetTimeHighScore() {
		return timeHighScore;
	}
	int GetHighScore() {
		return highScore;
	}
	int GetAccess() {
		return access;
	}
	
	  void writeFilePlayers(string&, vector<Player>);
	  void writeEndFilePlayers(string&, Player);
	  void readFilePlayers(string&, vector<Player>&, RenderWindow& window);
	  void ChoosePlayer(vector<Player>& vec_of_players, Player& player);
	  bool NewGame(vector<Player>& vec_of_players, Player& player);
	  bool LogIn(string& file, vector <Player>& vec_of_players);
	  void SignUp(string& file, vector <Player>& vec_of_players);
	 
	  friend void ShowPlayersForAdmin(vector<Player>& vec_of_players);
	  friend void ShowScore(vector<Player>& vec_of_players);
	  friend void changePassword(string& file, vector <Player>& vec_of_players, int i);
	  friend  void changePassword(string& file, vector <Player>& vec_of_players, int i);
	
};

//------------------����------------------------
void Game( Player& player);
void SetHeroCoordinateForView(float x, float y);

string* ChangeLevelBecauseOfEnd(string* TileMap, int hight, int width);
void ChangeVector(vector<Player>& vec_of_players, Player& player);
string createNewPassword();
string enterPassword();
string createNewLogin(vector <Player> vec_of_players);
void UserMenu(string& file, vector<Player>& vec_of_players, Player& player);
int PauseKeyCheck(RenderWindow& window);
int GameOverKeyCheck(RenderWindow& window);
void SetNullPlayer(Player& player);
//----------------------�����-----------------------------
void CurrentStatus(Text& text, int health, int gameTime, int coin);
void LevelEnd(Text& text, int levelNum, int gameTime, int coin);
void MenuShowScore(vector<Player>& vec_of_players);
void ShowPlayersForAdmin(vector<Player>& vec_of_players);
void ShowScore(vector<Player>& vec_of_players);
void AdminTableHead();
void  ScoreTableHead();
int SwitchEsc();
int SwitchGameOver();
//--------------------����������---------------------
void SortPlayers(vector <Player> vec_of_players);
bool UpSortByNick(Player a, Player b);
bool DownSortByNick(Player a, Player b);
bool UpSortByLevel(Player a, Player b);
bool DownSortByLevel(Player a, Player b);
bool UpSortByScore(Player a, Player b);
bool DownSortByScore(Player a, Player b);
//--------------------�����---------------------
void SearchPlayer(vector<Player> vec_of_players);
void SearchByLevel(vector<Player> vec_of_players);
void SearchByNick(vector<Player> vec_of_players);
void SearchByScore(vector<Player> vec_of_players);
int FindPlayerIndex(vector<Player> vec_of_players, string nick);
//---------------------�����---------------------
void adminMenu(string& file, vector<Player>& vec_of_players, Player& player);
void adminSystemWorkMenu(string& file, vector <Player>& vec_of_players);
void ChangeAccess(string& file, vector <Player>& vec_of_players);
int changeOpposite(int num);
void DeletePlayer(vector <Player>& vec_of_players);
bool isTrue();
bool  isNickDuplicate(vector<Player>& vec_of_players, string nick);
bool findDuplicate(string first_item, string second_item);


