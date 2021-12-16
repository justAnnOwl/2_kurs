
#include "Textbox.h"
bool isMouseOver(sf::RenderWindow& window, int btnPosX, int btnPosY, int btnW, int btnH) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;


	int btnxPosWidth = btnPosX + btnW;
	int btnyPosHeight = btnPosY + btnH;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}
void textRender(Text& text, string& str, int size, int X, int Y) {
	text.setString(str);
	text.setCharacterSize(size);
	text.setPosition(X, Y);
}