#include "Player.h"
#include "Button.h"
#include "Textbox.h"
#include "Entity.h"
#include "HashAndSalt.h"
#include "Checking.h"
#include "Map.h"
#include "View.h"
#include <iomanip>
#include <iostream>
using namespace std;
///////////////////////СДЕЛАТЬ ЗАКРЫТИЕ УРОВНЯ И ЗАПИСЬ ИГРОКА В ВЕКТОР, РАЗОБРАТЬСЯ С ЕСК, КООРДИНАТЫ /54
bool Player::NewGame(vector<Player>& vec_of_players, Player& player) {

	RenderWindow windowNick(VideoMode(800, 300), "NICK INPUT");// но размер 96
	Texture bgTexture;
	bgTexture.loadFromFile("images/BirdsAndMountains.png");

	Sprite background(bgTexture);
	background.setPosition(0, 0);
	windowNick.setKeyRepeatEnabled(true);
	Font font;
	if (!font.loadFromFile("Jokerman.ttf")) {
		cout << "Font error!";
	}
	//Textbox upLineText(30, Color::Red, false);
	Text upLineText; //Надпись сверху
	string upStr = "Your new nickname: ";
	textRender(upLineText, upStr, 50, 150, 10);

	upLineText.setFont(font);
	//upLineText.setFillColor(Color::White);
	upLineText.setOutlineThickness(3);
	upLineText.setOutlineColor(Color::Cyan);
	upLineText.setStyle(Text::Bold | Text::Underlined);


	//Button okButton("OK", { 50, 100 }, 40, Color::White, Color::Cyan);
	//okButton.setFont(font);
	//okButton.setPosition(100, 340);
	Texture textureButtonOK;
	textureButtonOK.loadFromFile("images/Buttons/OK.png");
	Sprite spriteOkButton(textureButtonOK);
	spriteOkButton.setPosition(100, 220);

	Texture textureButtonCANCEL;
	textureButtonCANCEL.loadFromFile("images/Buttons/CANCEL.png");
	Sprite spriteCANCELButton(textureButtonCANCEL);
	spriteCANCELButton.setPosition(500, 220);

	Textbox nickText(80, Color::Cyan, true);
	nickText.setFont(font);
	nickText.setPosition(20, 80);
	nickText.setFont(font);
	bool flag = true;
	while (flag)
	{

		Event Event;

		if (Keyboard::isKeyPressed(sf::Keyboard::Return)) { // Правый enter
			nickText.setSelected(true);
		}
		else if (Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			nickText.setSelected(false);
		}

		//Event Loop:
		while (windowNick.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				windowNick.close();
			case sf::Event::TextEntered:
				nickText.typedOn(Event);
			case sf::Event::MouseMoved:
				if (isMouseOver(windowNick, 100, 220, 200, 48)) {
					spriteOkButton.setColor(sf::Color::Green);
				}
				else if (isMouseOver(windowNick, 500, 220, 200, 48)) {
					spriteCANCELButton.setColor(sf::Color::Green);
				}
				else {
					spriteOkButton.setColor(sf::Color::White);
					spriteCANCELButton.setColor(sf::Color::White);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (isMouseOver(windowNick, 500, 220, 200, 48)) {
					return false;
				}
				if (isMouseOver(windowNick, 100, 220, 200, 48)) {
					/*if (isNickDuplicate(vec_of_players, nickText.getText())) {*/

					Texture takenNickT;
					takenNickT.loadFromFile("images/takenNickname.jpg");
					Sprite takenNickS(takenNickT);
					takenNickS.setPosition(100, 100);
					windowNick.draw(takenNickS);
					windowNick.display();


					player.SetNick(nickText.getText());// ///////////ПРОВЕРКА!!!!!!!!!!!!!!!!!!!!!!!!!11
					player.SetLevel(1);
					vec_of_players.push_back(player);
					windowNick.close();
					flag = false;
					return true;
				}
			}
		}

		windowNick.clear();
		windowNick.draw(background);
		nickText.drawTo(windowNick);
		windowNick.draw(spriteOkButton);
		windowNick.draw(spriteCANCELButton);
		windowNick.draw(upLineText);
		windowNick.display();

	}


}
void Player::ChoosePlayer(vector<Player>& vec_of_players, Player& player)

{
	int vecSize = vec_of_players.size();
	Player temp;
	//ВЫЗОВ ОКНА
	//ВЫВОД СПИСКА

	RenderWindow windowChoice(VideoMode(300, 900), "Choose a player");// но размер 48
	string nickList;
	//	for (int i = 0; i < vecSize; i++) {
	//		nickList +=to_string(i+1)+ vec_of_players.at(i).GetNick()+'\n';
	//}
	Font font;
	if (!font.loadFromFile("Jokerman.ttf")) {
		cout << "Font error!";
	}
	Text upLineText;
	string str = "CHOOSE";
	textRender(upLineText, str, 30, 40, 0);
	upLineText.setFont(font);
	upLineText.setFillColor(Color::Red);
	upLineText.setStyle(Text::Bold | Text::Underlined);
	//upLineText.setCharacterSize(30); // Pixel размер
	//upLineText.setString("CHOOSE: ");
	//upLineText.setPosition(40, 0);//задаем позицию текста, отступая от центра камеры


	vector<Text> text_vec;
	Texture textureButton;
	textureButton.loadFromFile("images/Buttons/NICK.png");
	vector<Sprite> spriteButton;
	windowChoice.draw(upLineText);
	for (int i = 0; i < vecSize; i++) {
		spriteButton[i].setPosition(20, i * 48 + 48);
		str = vec_of_players[i].GetNick();
		textRender(text_vec[i], str, 20, 50, i * 48 + 48);
		text_vec[i].setStyle(Text::Bold);
		text_vec[i].setFont(font);
		text_vec[i].setFillColor(Color::Cyan);
		//text_vec[i].setString(vec_of_players[i].GetNick());
//text_vec[i].setPosition(30, i * 20 + 20);//задаем позицию текста
//text_vec[i].setCharacterSize(10); // Pixel размер
		windowChoice.draw(text_vec[i]);
	}

	int counter = 0;
	while (!Keyboard::isKeyPressed(Keyboard::Enter)) {
		for (int i = 0; i < vecSize; i++) {
			spriteButton[i].setColor(Color::White);
		}


		windowChoice.clear(Color(129, 181, 221));
		for (int i = 0; i < vecSize; i++) {
			if (Keyboard::isKeyPressed(Keyboard::Down) && counter < vecSize - 1) {
				spriteButton[counter].setColor(Color::Blue);
				counter++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up) && counter > 1) {
				spriteButton[counter].setColor(Color::Blue);
				counter--;
			}
		}
		windowChoice.display();
	}
	//ВЫ ДЕЙСТВИТЕЛЬНО ХОТИТЕ ВЫБРАТЬ 	



	player.nick = vec_of_players[counter].nick;
	player.role = vec_of_players[counter].role;
	player.access = vec_of_players[counter].access;
	player.hash = vec_of_players[counter].hash;
	player.salt = vec_of_players[counter].salt;
	player.level = vec_of_players[counter].level;
	player.highScore = vec_of_players[counter].highScore;

	windowChoice.close();
	///
}
bool Game(RenderWindow& w, Player& player) {
	RenderWindow window(VideoMode(1700, 900), "THE Adventures");
	view.reset(FloatRect(0, 0, 1700, 800));
	Font font;
	font.loadFromFile("Jokerman.ttf");

	bool flagLevel = true;
	while (flagLevel) {

		Level lvl(player.GetLevel());
		string* TileMap = lvl.levelMap;
		//bool game = isGame(window);
		Image mapImage;
		mapImage.loadFromFile("1tiles.png");
		Texture mapTexture;
		mapTexture.loadFromImage(mapImage);
		Sprite mapSprite;
		mapSprite.setTexture(mapTexture);

		Image heroImage;
		heroImage.loadFromFile("Queen.png");


		Hero hero(heroImage, "Hero", 50, 50, 54, 54);

		Clock clock;
		Clock gameClock;
		int gameTime = 0;
		while (window.isOpen()) {
			float time = clock.getElapsedTime().asMicroseconds();
			//clock_t start = clock();

			if (hero.GetCoin() < lvl.GetCoin()) { // Если собраны не все монетки уровня,
				gameTime = gameClock.getElapsedTime().asSeconds();// то игровое время идёт вперед
			}
			else { 
				view.move(0.8, 0); // Карта движется вправо
			}
			clock.restart();
			time = time / 200;

			Event event;
			while (window.pollEvent(event))// Пока есть системное событие, обрабатываем его
			{
				if (event.type == Event::Closed)
					window.close();
			}
			hero.Update(time, TileMap);
			viewmap(time);/// ПЕРЕДАТЬ КАСАНИЕ 0 ЧТОБЫ НЕ ДВИГАЛАСЬ------------------------------------------------------------------------------------------------
			changeview();
			window.setView(view); // Контроль, какая часть видна
			window.clear(Color(255, 255, 255));//77 83 1404

			for (int i = 0; i < lvl.GetHight(); i++)
				for (int j = 0; j < lvl.GetWidth(); j++)
				{
					if (TileMap[i][j] == ' ')  mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
					if (TileMap[i][j] == '0')  mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
					if ((TileMap[i][j] == 'c')) mapSprite.setTextureRect(IntRect(32, 0, 32, 32));

					mapSprite.setPosition(j * 32, i * 32); //раскидывает квадратики, превращая в карту.
					//то есть задает каждому из них позицию.если убрать, 
						//то вся карта нарисуется в одном квадрате 32 * 32 и мы увидим один квадрат

					window.draw(mapSprite);
				}

			Text currentStatus("", font, 40);
			CurrentStatus(currentStatus, hero.GetHealth(), gameTime, hero.GetCoin());
			if (hero.GetCoin() < lvl.GetCoin())window.draw(currentStatus);//рисую этот текст
			else {
				TileMap = ChangeLevelBecauseOfEnd(TileMap, lvl.GetHight(), lvl.GetWidth());
				Text levelEndText("", font, 60);
				LevelEnd(levelEndText, player.GetLevel(), gameTime, hero.GetCoin());
				window.draw(levelEndText);
			}

			window.draw(hero.GetSprite());
			window.display();




		}
		////////////// ПРОДОЛЖИТЬ ИЛИ НЕТ
		if (hero.isAlive) {
			player.SetLevel(player.GetLevel() + 1);
			if (hero.GetCoin() > player.GetHighScore()) {
				player.SetTimeHighScore(hero.GetCoin());
			}
		}
	}
	return true;//////////////////////////////////////////////nononoon
}
void CurrentStatus(Text& text, int health, int gameTime, int coin) {


	text.setFillColor(Color::Magenta);
	text.setStyle(Text::Bold);
	std::ostringstream heroHealthString, gameTimeString, heroCoinString;    // объявили переменную здоровья и времени
	heroHealthString << health;
	gameTimeString << gameTime;		//формируем строку
	heroCoinString << coin;
	text.setString("HEALTH  " + heroHealthString.str() +
		"\nTIME: " + gameTimeString.str() +
		"\nCOIN " + heroCoinString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()

	text.setPosition(view.getCenter().x + 570, view.getCenter().y - 350);//задаем позицию текста, отступая от центра камеры
}
void LevelEnd(Text& text, int levelNum, int gameTime, int coin) {
	text.setCharacterSize(60);
	text.setFillColor(Color::Green);
	text.setStyle(Text::Bold);

	int minuteTime = gameTime / 60;
	int secondTime = gameTime % 60;

	ostringstream level_str, min_str, sec_str, coin_str;
	level_str << levelNum;
	min_str << minuteTime;
	sec_str << secondTime;
	coin_str << coin;
	text.setString("LEVEL  " + level_str.str() + "  COMPLETED!!!" +
		"\n GAME TIME " + min_str.str() + ':' + sec_str.str() +
		"\n COINS " + coin_str.str());

	text.setPosition(view.getCenter().x-300, view.getCenter().y-100);
}
void SetHeroCoordinateForView(float x, float y) {

	float tempX = x;
	float tempY = y;
	//if (x < 320) tempX = 320;
		//if (y < 240) tempY = 240;//верхнюю сторону
	if (y > 624) tempY = 624;// Нижнюю сторону для новой карты
	view.setCenter(tempX, tempY);
}
string* ChangeLevelBecauseOfEnd(string* TileMap, int hight, int width) {// ФУНКЦИЯ ОБНУЛЕНИЯ МОНЕТОК ПО ВСЕМУ УРОВНЮ
	for (int i = 0; i < hight; i++)
		for (int j = 0; j < width; j++)
		{
			if ((TileMap[i][j] == 'c' || TileMap[i][j] == 'h'))
				TileMap[i][j] = ' ';
		}
	return TileMap;
}
//-----------------------ФАЙЛЫ-----------------------
void Player::writeFilePlayers(string& file, vector <Player> vec_of_players)// Создание файла Players
{
	ofstream fout(file, ios::out);
	for (int i = 0; i < vec_of_players.size(); i++)
	{
		fout << vec_of_players[i].nick << " "
			<< vec_of_players[i].role << " "
			<< vec_of_players[i].access << " "
			<< vec_of_players[i].hash << " "
			<< vec_of_players[i].salt << " "
			<< vec_of_players[i].level << " "
			<< vec_of_players[i].highScore;

		if (i < vec_of_players.size() - 1)
			fout << endl;
	}
	fout.close();
}
void Player::writeEndFilePlayers(string& file, Player new_player)
{
	ofstream fadd(file, ios::app); // Открыли файл для дозаписи
	fadd << endl;
	fadd << new_player.nick << " "
		<< new_player.role << " "
		<< new_player.access << " "
		<< new_player.hash << " "
		<< new_player.salt << " "
		<< new_player.level << " "
		<< new_player.highScore;

	fadd.close();
	return;
}
void Player::readFilePlayers(string& file, vector <Player>& vec_of_players, RenderWindow& window)
{/////////////////////НЕ ПОДСВЕЧИАТЬ ПРОДОЛЖИТЬ ИГРУ
	ifstream fin(file, ios::in);
	///////////////////НУЖЕН ЛИ ПАРОЛЬ
	Player temp;
	string   nick, salt, password;
	if (!fin.is_open()) { // ADD NEW PLAYER
		cout << "ФАЙЛ ПУСТ!!!";
		cout << "\nРегистрация главного администратора:\n Введите логин:  ";
		getline(cin, nick);
		temp.nick = nick;
		salt = generateSalt(SALT_SIZE);
		temp.salt = salt;
		password = createNewPassword();
		temp.hash = sha256(sha256(password + salt) + sha256(password));
		temp.role = "admin";
		temp.access = 1;
		temp.highScore = 0;
		temp.level = 1;
		vec_of_players.push_back(temp);
		cout << "\nРегистрация прошла \x1b[32mуспешно\x1b[35m ";
		writeFilePlayers(file, vec_of_players);
		adminMenu(file, vec_of_players, window);
		fin.close();
	}
	else
	{
		Player player_temp;
		while (!fin.eof())// ЗАВИСАЕТ !!!
		{
			fin >> player_temp.nick
				>> player_temp.role
				>> player_temp.access
				>> player_temp.hash
				>> player_temp.salt
				>> player_temp.level
				>> player_temp.highScore;

			vec_of_players.push_back(player_temp);
		}
		fin.close();
		//	mainMenu(vec_of_accounts, vec_of_students);
	}

}

//---------------------АККАУНТЫ-----------------------
void Player::SignUp(string& file, vector <Player>& vec_of_players) {
	string  nick, password, salt, hash_pass_with_salt;
	Player temp;

	temp.nick = this->nick = createNewLogin(vec_of_players);
	temp.access = this->access = 1;
	temp.role = this->role = "user";
	temp.level = this->level = 1;
	salt = generateSalt(SALT_SIZE);
	temp.salt = this->salt = salt;
	password = createNewPassword();
	temp.hash = this->hash = sha256(sha256(password + salt) + sha256(password));

	vec_of_players.push_back(temp);
	cout << "\nРегистрация прошла \x1b[32mуспешно\x1b[35m ";
	system("pause>null");
	writeEndFilePlayers(file, temp);
}
void Player::LogIn(string& file, vector <Player>& vec_of_players) {
	string nick, password, salt, hash;
	for (int attempt = 2; attempt > -1; attempt--) {
		system("cls");
		cout << "~~~~~~~~~~~~~~~~~~ АВТОРИЗАЦИЯ ~~~~~~~~~~~~~~~~~~~~\n" <<
			"Введите логин: ";
		while (true) {
			getline(cin, nick);
			if (nick != "\n") break;
		}
		bool find_pass = false, find_log = false;
		int i = 0;
		while (find_log == false && i < vec_of_players.size()) {
			find_log = findDuplicate(nick, vec_of_players[i].nick);// Если найдено совпадение, то find=true
			i++;
		}
		i--;
		cout << "\nВведите пароль:";
		cin.clear();
		password = enterPassword();

		if (find_log == true) {// Если нашли такой логин///________
			salt = vec_of_players[i].salt;// То извлекаем соль
			hash = sha256(sha256(password + salt) + sha256(password));

			if (hash == vec_of_players[i].hash) {// Если пароль введён верно
				this->nick = vec_of_players[i].nick;
				this->level = vec_of_players[i].level;
				this->access = vec_of_players[i].access;
				this->role = vec_of_players[i].role;
				this->hash = vec_of_players[i].hash;
				this->highScore = vec_of_players[i].highScore;
				this->salt = vec_of_players[i].salt;
				if (vec_of_players[i].access != 1) {// Если есть доступ
					cout << "\nВаш аккаунт \x1b[31mнедоступен\x1b[35m :(\n";
					system("pause>null");
				}
				return;
			}
			//ВЫЗОВ ИНТЕРФЕЙСА______________________________________ 
		}
		cout << "\n\tНеверное имя пользователя или пароль\n" <<
			"\n\tКоличество оставшихся попыток: " << attempt << endl;
		system("pause>null");
	}
	cout << "Попробуйте позже!\n";

}
void changePassword(string& file, vector <Player>& vec_of_players, int i) {
	system("cls");
	cout << "-------------Изменение пароля---------------";
	for (int attempt = 3; attempt > 0; attempt--) {

		cout << "\nВведите старый пароль: ";
		string old_password = enterPassword();
		string salt = vec_of_players[i].salt;
		string hash = sha256(sha256(old_password + salt) + sha256(old_password));

		if (hash == vec_of_players[i].hash) {//если пароль введён верно
			string new_password = createNewPassword();//вводим новый пароль
			salt = generateSalt(SALT_SIZE);
			string hash_pass_with_salt = sha256(sha256(new_password + salt) + sha256(new_password));
			vec_of_players[i].hash = hash_pass_with_salt;
			vec_of_players[i].salt = salt;
			cout << "Пароль \x1b[31mуспешно\x1b[35m изменён";
		}
		else cout << "Пароль введён \x1b[31mневерно\x1b[35m\n" <<
			"Количество оставшихся попыток: " << attempt << endl;
	}
	cout << "Попробуйте позже!\n";

}
string createNewPassword() {//не менее 4 символов
	string password, repeat_password;
	bool   flag = true;
	while (flag == true) {
		while (true) {
			cout << "\nВведите пароль: ";
			password = enterPassword();
			if (password.length() < 4) {
				cout << "\n \x1b[31mПароль должен содержать не менее 4-х символов!\x1b[35m\n";
				password.clear();
			}
			else break;
		}

		cout << "\nПовторите пароль: ";
		repeat_password = enterPassword();

		if (password == repeat_password)flag = false;
		else {
			cout << "\n\x1b[31mПароли не совпадают\x1b[35m"; //cout << "\x1b[31mHello\x1b[0m" << endl;
			//cout << "\e[1;1H\e[2J"<< "\e[1;1H\e[2J";//очищаем две строчки консоли
		}
	}
	return password;
}
string createNewLogin(vector <Player> vec_of_players) {
	string nick;
	bool   flag = true, repeat = false;
	int    i = 0;

	while (flag == true) {
		system("cls");
		cout << "Введите никнейм: ";
		cin.clear();
		getline(cin, nick);
		while (i < vec_of_players.size() && repeat == false) {

			repeat = findDuplicate(vec_of_players[i].GetNick(), nick);
			if (repeat == true) {
				cout << "Данный никнейм\x1b[31m уже используется\x1b[35m :(\n";
				system("pause>null");
				break;
			}
			i++;
		}
		if (repeat == false) flag = false;// Если повторений нет,то выходим из цикла
	}
	return nick;
}
string enterPassword() {
	vector <char> password;
	string str;
	char   symbol;
	bool flag = true;
	int  length = 0;

	do//если enter, то ввод пароля окончен
	{
		symbol = _getch();


		if (symbol == '\b') {//если нажали backspace
			if (password.size() != 0)//иначе стирать нечего
			{
				cout << '\b' << ' ' << '\b';	/////////////_______________________ВОПРОС ПО ПОВОДУ ДВАЖДЫ ИЛИ ОДИН
				password.pop_back();
			}
			else continue;
		}
		else if (symbol == '\r') flag = false;
		else {//если любой другой символ, то помещаем его в строку пароля
			length++;
			password.push_back(symbol);
			//system("cls");//очищаем консоль
		//	for (int i = 0; i < password.size(); i++)
			cout << '*';//выводим *, соответствующие длине введённого пароля
		}
	} while (flag == true);



	password.push_back('\0');
	//for (int i = 0; i < password.size(); i++) {
	//	str += password.at(i);//помещаем из вектора в строку
	//}/////////////___________________НУЖНО ЛИ ДОБАВИТЬ \0_???????????????
	str = (char*)&password[0];
	return str;
}
//void deletePlayer(vector <Player>& vec_of_accounts) {
//	while (true) {
//		system("cls");
//		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ УДАЛЕНИЕ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
//		//showAccounts(vec_of_accounts);
//		cout << "\nВведите № удаляемого аккаунта: ";
//		int number = checkDiapason(1, vec_of_accounts.size());
//		number--;
//		if (number == 0) cout << "\n\t\n\x1b[31mНельзя удалить главного администратора из системы!\x1b[35m\n";
//		else {
//			vector <Account> temp = vec_of_accounts;
//			temp.erase(temp.begin() + number);
//			system("cls");
//			showAccounts(temp);
//			cout << "\n\n\tСохранить изменения?\n\t 1 - да\n\t 0 - нет\n\t ->";
//			bool yesOrNo = isTrue();
//			if (yesOrNo) vec_of_accounts.erase(vec_of_accounts.begin() + number);
//			cout << "\n\n\tПродолжить?\n\t 1 - да\n\t 2 - вернуться в меню\n\t ->";
//			yesOrNo = isTrue();
//			if (yesOrNo == 0) return;
//		}
//	}
//}

//----------------------ВЫВОД-----------------------------
void MenuShowScore(vector<Player>& vec_of_players) {
	while (true) {
		cout << "\n\t CHOOSE: \n\t\t1 -  SORT\n\t\t2 - SEARCH\n\t\t" <<
			"\n\t\t0 - cancel\n\n\t->:";
		int choice = checkDiapason(0, 3);
		if (choice == 0) return;
		switch (choice) {
		case 1: SortPlayers(vec_of_players);
			break;
		case 2: SearchPlayer(vec_of_players);
			break;
		}
	}
}
void ShowPlayersForAdmin(vector<Player>& vec_of_players) {
	//nick
	AdminTableHead();
	for (int i = 0; i < vec_of_players.size(); i++) {
		int id = i + 1;
		cout << '|' << setw(3) << id << setw(2) << ' |' << vec_of_players[i].nick <<
			setw(21 - vec_of_players[i].nick.length()) << '|' <<
			vec_of_players[i].role << setw(4) << '|' << setw(13 - vec_of_players[i].role.length()) <<
			vec_of_players[i].access << '| ' << setw(4) <<
			vec_of_players[i].level << setw(4) << '|' << setw(4) <<
			vec_of_players[i].highScore << setw(4) << '|';
		if (i != vec_of_players.size() - 1)
			cout << "\n|----|----------------------+------------+----------+---------+--------------|\n";
		else
			cout << "\n==============================================================================";
	}

}
void ShowScore(vector<Player>& vec_of_players) {
	if (vec_of_players.size() < 1) {
		cout << "\n\tNO PLAYERS";
	}
	else {
		for (int i = 0; i < vec_of_players.size(); i++) {
			cout << "| " << setw(3) << i + 1 << setw(2) <<
				" |" << vec_of_players[i].GetNick() << setw(23 - vec_of_players[i].GetNick().length()) <<
				'|' << setw(7) << vec_of_players[i].GetLevel() << setw(7) << '|' << setw(10) <<
				vec_of_players[i].GetHighScore() << setw(8) << '|';
			if (i != vec_of_players.size() - 1)
				cout << "\n|----|----------------------|--------------|---------------------|\n";
			else
				cout << "\n=================================================================";

		}
	}
}
void AdminTableHead() {
	cout << "==============================================================================" <<
		"\n| ID |         NICK         |    ROLE    |  ACCESS  |  LEVEL  |    SCORE     |\n" <<
		"|====|======================+============+==========+=========+==============|\n";
}
void  ScoreTableHead() {
	cout << "=================================================================" <<
		"\n| ID |         NICK         |    LEVEL     |    HIGH SCORE      |\n" <<
		"|====|======================+==============+====================|\n";
}

//--------------------СОРТИРОВКА---------------------
void SortPlayers(vector <Player>& vec_of_players) {
	vector <Player> copy_vec;
	while (true) {
		system("cls");
		ScoreTableHead();
		ShowScore(vec_of_players);
		cout << "\n\t Sort by: \n\t\t1 -  NICK\n\t\t2 - LEVEL\n\t\t" <<
			"3 - HIGH SCORE\n\t\t0 - cancel\n\n\t->:";
		int choice = checkDiapason(0, 3);
		if (choice == 0) return;
		cout << " \n 1 - Up\n 2 - Down\n\n\t->: ";
		int way = checkDiapason(1, 2);
		switch (choice) {
		case 1:
			if (way == 1) sort(copy_vec.begin(), copy_vec.end(), UpSortByNick);
			else sort(copy_vec.begin(), copy_vec.end(), DownSortByNick);
			break;
		case 2: if (way == 1) sort(copy_vec.begin(), copy_vec.end(), UpSortByLevel);
			  else sort(copy_vec.begin(), copy_vec.end(), DownSortByLevel);
			break;
		case 3:if (way == 1) sort(copy_vec.begin(), copy_vec.end(), UpSortByScore);
			  else sort(copy_vec.begin(), copy_vec.end(), DownSortByScore);
			break;
		}
		ScoreTableHead();
		ShowScore(vec_of_players);

	}
}
bool UpSortByNick(Player a, Player b) {
	return a.GetNick() < b.GetNick();
}
bool DownSortByNick(Player a, Player b) {
	return a.GetNick() > b.GetNick();
}
bool UpSortByLevel(Player a, Player b) {
	return a.GetLevel() < b.GetLevel();
}
bool DownSortByLevel(Player a, Player b) {
	return a.GetLevel() > b.GetLevel();
}
bool UpSortByScore(Player a, Player b) {
	return a.GetHighScore() < b.GetHighScore();
}
bool DownSortByScore(Player a, Player b) {
	return a.GetHighScore() > b.GetHighScore();
}
//--------------------ПОИСК---------------------
void SearchPlayer(vector <Player>& vec_of_players) {
	while (true) {
		system("cls");
		/*userTableHead();
		showSystemTable(vec_of_students);*/
		cout << "\n\t Search by: \n\t\t1 -  NICK\n\t\t2 - LEVEL\n\t\t" <<
			"3 - HIGH SCORE\n\t\t0 - cancel\n\n\t->";
		int choice = checkDiapason(0, 3);
		if (choice == 0) return;
		switch (choice)
		{
		case 1: SearchByNick(vec_of_players);
			break;
		case 2: SearchByLevel(vec_of_players);
			break;
		case 3: SearchByScore(vec_of_players); break;
		}
	}
}
void SearchByLevel(vector<Player>& vec_of_players) {
	cout << "\n Enter level: ";
	int level = checkNumberPositive();
	vector <Player> search_vec;
	int counter = 0;
	for (int i = 0; i < vec_of_players.size(); i++) {
		if (vec_of_players[i].GetLevel() == level) {
			search_vec.push_back(vec_of_players[i]);
			counter++;
		}
	}
	if (counter != 0) {
		ScoreTableHead();
		ShowScore(search_vec);
		cout << counter << "\n players at all ";
	}
	else cout << "\nNo one player is found";
	system("pause>null");
	return;

}
void SearchByNick(vector <Player>& vec_of_players) {
	system("cls");
	cout << "\n\t Enter nick : ";
	vector <Player> search_vec;
	int		strLength = 0;
	string str;
	char   symbol;
	bool second_flag = true;
	while (second_flag) {
		bool flag = true;
		do
		{
			symbol = _getch();


			if (symbol == '\b') {//если нажали backspace
				if (str.size() != 0)//иначе стирать нечего
				{
					cout << '\b' << ' ' << '\b';
					str.erase(str.size() - 1);

				}
				else continue;
			}
			else if (symbol == '\r') {
				if (strLength < 1)
					cout << " \n Empty input!\n Try again: ";
				else {
					flag = false;
					second_flag = false;
				}
			}

			else {//если любой другой символ, то помещаем его в строку 
				if ((symbol > 64 && symbol < 91) || (symbol > 96 && symbol < 123) || symbol == '_' || symbol == '-' || symbol == ' ') {// ASCII '0'= 48, '9'=57
					cout << symbol;
					str.push_back(symbol);
					//strLength++;
					flag = false;
				}
				//else NOTHING
			}
		} while (flag == true);

		str.push_back('\0');
		// (char*)&str[0];
		for (int i = 0; i < vec_of_players.size(); i++) {
			if (vec_of_players[i].GetNick().substr(0, str.size()) == str)
				search_vec.push_back(vec_of_players.at(i));
		}
		ScoreTableHead();
		ShowScore(search_vec);
	}

}
void SearchByScore(vector <Player> vec_of_players) {
	cout << "\n Enter search diapason: \n\tFrom : ";
	double begin = checkDiapason(0, 10);
	cout << "\n\tTo : ";
	double end = checkDiapason(0, 10);
	vector <Player> search_vec;
	int counter = 0;
	for (int i = 0; i < vec_of_players.size(); i++) {
		if (vec_of_players[i].GetHighScore() >= begin &&
			vec_of_players[i].GetHighScore() <= end) {
			search_vec.push_back(vec_of_players[i]);
			counter++;
		}
	}
	if (counter != 0) {
		ScoreTableHead();
		ShowScore(search_vec);
		cout << counter << "\n players at all ";
	}
	else cout << "\nNo one player is found!";
	system("pause>null");
	return;
}
//---------------------АДМИН---------------------
void adminMenu(string& file, vector<Player>& vec_of_players, RenderWindow& window) {// Передаем сам вектор и номер аккаунта
	while (true) {
		system("pause>null");
		system("cls");
		//cin.clear();
		cout << "~~~~~~~~~~~~~~~~~\n" <<
			" | 1 | Работа с игроками\n" <<
			" | 2 | Сменить пароль\n" <<
			" | 3 | ИГРА\n" <<
			" | 0 | Назад\n" <<
			"~~~~~~~~~~~~~~~~~\n\n  -> ";
		int   choice = checkDiapason(0, 3);
		switch (choice) {
		case 1: adminSystemWorkMenu(file, vec_of_players);
			break;
		case 2: changePassword(file, vec_of_players, 0);
			break;
		case 3: Game(window, vec_of_players[0]);
			break;
		case 0:// ВЫХОД В ГЛАВНОЕ ОКОННОЕ МЕНЮ
			return;
		}
	}
}
void adminSystemWorkMenu(string& file, vector <Player>& vec_of_players) {
	while (true) {
		system("pause>nul");
		system("cls");
		cin.clear();

		cout << "~~~~~~~~~~~~~~~~~\n" <<
			" | 1 | Просмотр\n" <<
			" | 2 | Изменить доступ\n | 3 | Удалить\n" <<
			"\n | 0 | Назад\n" <<
			" ~~~~~~~~~~~~~~~~~\n\n  -> ";
		int choice = checkDiapason(0, 3);
		switch (choice) {
		case 1: ShowPlayersForAdmin(vec_of_players);
			break;
		case 2: ChangeAccess(file, vec_of_players);
			break;
		case 3: DeletePlayer(vec_of_players);
			break;
		case 0:return;
		}

	}
}
void ChangeAccess(string& file, vector <Player>& vec_of_players) {
	while (true) {
		ShowPlayersForAdmin(vec_of_players);
		cout << "\n\n\tВведите номер игрока, доступ которому нужно изменить: ";
		int num = checkDiapason(1, vec_of_players.size());
		num--;
		if (num == 0) cout << "Настройка доступа администратора невозможна!\n";
		else {
			cout << "Вы действительно хотите изменить доступ игроку " << vec_of_players[num].GetNick() << " ?\n" <<
				"\n\t 1 - да\n\t 0 - нет. Я так шучу.\n\t->";
			bool choice = isTrue();
			if (choice == true)
				vec_of_players[num].SetAccess(changeOpposite(vec_of_players[num].GetAccess()));

		}
		Player p;
		cout << "\n\n\t 1 - Продолжить\n\t 0 - назад\n\t\t -> ";
		int choice = checkDiapason(0, 1);
		if (choice == 0) {
			p.writeFilePlayers(file, vec_of_players);
			return;
		}
	}
}
int changeOpposite(int num) {// Если передаваемое значение = 0, то меняет на 1 и наоборот
	return (num == 0) ? 1 : 0;
}
void DeletePlayer(vector <Player>& vec_of_players) {
	//showAccounts(vec_of_accounts);
	while (true) {
		system("cls");
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ УДАЛЕНИЕ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		//adminAccountTableHead();
		ShowPlayersForAdmin(vec_of_players);
		cout << "\nВведите № удаляемого аккаунта: ";
		int number = checkDiapason(1, vec_of_players.size());
		number--;
		if (number == 0) cout << "\n\t\n\x1b[31mНельзя удалить главного администратора из системы!\x1b[35m\n";
		else {
			vector <Player> temp = vec_of_players;
			temp.erase(temp.begin() + number);//////////////////////  А ТОЧНО ЛИ НУЖНОЕ УДАЛЯЕТ??????????????????
			system("cls");
			ShowPlayersForAdmin(temp);
			cout << "\n\n\tСохранить изменения?\n\t 1 - да\n\t 0 - нет\n\t ->";
			bool yesOrNo = isTrue();
			if (yesOrNo) vec_of_players.erase(vec_of_players.begin() + number);
			cout << "\n\n\tПродолжить?\n\t 1 - да\n\t 2 - вернуться в меню\n\t ->";
			yesOrNo = isTrue();
			if (yesOrNo == 0) return;
		}
	}
}

bool isTrue() {
	//cout << "\n\t 1 - Продолжить\n\t 0 - назад";
	int choice = checkDiapason(0, 1);
	if (choice == 1) return true;
	else return false;
}
bool  isNickDuplicate(vector<Player>& vec_of_players, string nick) {
	for (int i = 0; i < vec_of_players.size(); i++) {
		if (findDuplicate(vec_of_players[i].GetNick(), nick))
			return true;
	}
	return false;
}
bool findDuplicate(string first_item, string second_item) {// Возвращает true, если совпали значения
	return first_item == second_item;
}