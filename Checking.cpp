#include "checking.h"

using namespace std;
double checkNumber()
{
	double number;
	while (true)
	{
		cin >> number;
		if (cin.get() != '\n')
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "������������ ��������\n ��������� ����\n";
		}
		else break;
	}

	return number;
}
double checkDiapason(int a, int b) {//��������� ������������ ������������� ���������
	double number;
	while (true) {
		number = checkNumber();
		if (number == 0) return number;
		if (number< a || number>b || number / (int)number != 1) cout << "������������ ��������\n ��������� ����\n";
		else return number;
	}
}
double checkNumberPositive() {
	double number;
	while (true) {
		number = checkNumber();
		if (number < 0 || number / (int)number != 1) cout << "������������ ��������\n ��������� ����\n";
		else return number;
	}
}
bool checkStr() {
	string str;
	getline(cin, str);
	double length = str.length();
	for (int i = 0; i < length - 1; i++)
	{
		if (str[i] != '+' && str[i] != '-' &&
			str[i] != '*' && str[i] != '/' &&
			str[i] != '(' && str[i] != ')' &&
			((str[i] < 'a') || (str[i] > 'z')) &&
			((str[i] < 'A') || (str[i] > 'Z')))
		{
			cout << "������������ ���������\n";
			return false;
		}
		if (str[i] == ' ') {
			for (int k = i; k < length - 1; k++)
			{
				str[k] = str[k + 1];
				i--;
			}
			cout << "\n���� ������ ���� ��� �������, ���� ���!\n";
		}
	}
	return true;
}