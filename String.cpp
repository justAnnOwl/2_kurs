#include "String.h"


String& String::operator=(const String& other) {
    if (this->str != nullptr)
        delete[] this->str;

    this->length = other.length;
    this->str = new char[length + 1];
    strcpy(this->str, other.str);
    return *this;
}

String& String::operator=(const char* new_str) {
    if (this->str != nullptr)
        delete[] this->str;

    this->length = mystrlen(new_str);
    this->str = new char[length + 1];
    strcpy(this->str, new_str);
    return *this;
}

String String::operator+(const String& other) {
    String temp;
    int first = this->length;
    int second = other.length;
    int sum = first + second;
    temp.str = new char[sum + 1];
    temp.length = sum;
    for (int i = 0; i < sum; i++) {
        if (i < first)
            temp.str[i] = this->str[i];
        else
            temp.str[i] = other.str[i - first];
    }
    temp.str[sum] = '\0';
    return temp;
}

String String::operator+(const char* new_str) {

    String temp;
    int first = this->length;
    int second = mystrlen(new_str);
    int sum = first + second;
    temp.str = new char[sum + 1];
    temp.length = sum;
    for (int i = 0; i < sum; i++) {
        if (i < first)
            temp.str[i] = this->str[i];
        else
            temp.str[i] = new_str[i - first];
    }
    temp.str[sum] = '\0';
    return temp;

}

String operator+(const char* new_str, const String& object) {
    String temp;
    int size_str = strlen(new_str);
    temp.length = object.length + size_str;
    temp.str = new char[temp.length + 1];
    for (int i = 0; i < temp.length; i++) {
        if (i < size_str)
            temp.str[i] = new_str[i];
        else
            temp.str[i] = object.str[i - size_str];
    }
    temp.str[temp.length] = '\0';
    return temp;
}

bool String::operator==(const String& other) {
    if (this->length != other.length)
        return false;
    for (int i = 0; i < length; i++)
        if (this->str[i] != other.str[i])
            return false;
    return true;
}

bool String::operator!=(const String& other) {
    return !(*this == other);
}

void String::operator+=(const char* new_str) {
    *this = *this + new_str;
}

void String::operator+=(const String& other) {
    *this = *this + other;
}

char String::operator[](int i) {
    if (i < length && i >= 0)
        return this->str[i];
    else if (i >= -length && i < 0)
        return this->str[length + i];
    else
        return '#';
}

String String::operator*(int i) {
    String temp;
    temp.length = this->length * i;
    temp.str = new char[temp.length + 1];
    for (int j = 0; j < i; j++)
        for (int k = 0; k < this->length; k++)
            temp.str[k + j * this->length] = this->str[k];
    return temp;
}

String operator*(int i, const String& object) {
    String temp;
    temp.length = object.length * i;
    temp.str = new char[temp.length + 1];
    for (int j = 0; j < i; j++)
        for (int k = 0; k < object.length; k++)
            temp.str[k + j * object.length] = object.str[k];
    return temp;
}


int String::lengthStr() const {
    return length;
}

String String::reverse() {
    String temp;
    temp.length = length;
    temp.str = new char[length + 1];
    for (int i = 0; i < length; i++) {
        temp.str[i] = str[length - i - 1];
    }
    temp.str[length] = '\0';
    return temp;
}

String String::UP()
{
    String temp = *this;
    for (int i = 0; i < length; i++)
        if (temp.str[i] >= 'a' && temp.str[i] <= 'z')
            temp.str[i] -= 32;
    return temp;
}

String String::DOWN()
{
    String temp = *this;
    for (int i = 0; i < length; i++)
        if (temp.str[i] >= 'A' && temp.str[i] <= 'Z')
            temp.str[i] += 32;
    return temp;
}

bool String::in(const char* new_str)
{
    int new_len = mystrlen(new_str);
    for (int i = 0; i < length - new_len + 1; i++)
    {
        if (str[i] == new_str[0])
        {
            bool flag = true;
            for (int j = 1; j < new_len; j++)
                if (str[i + j] != new_str[j])
                    flag = false;

            if (flag)
                return true;
        }
    }
    return false;
}

bool String::in(const String& other)
{
    int new_len = other.length;
    for (int i = 0; i < length - new_len + 1; i++)
    {
        if (str[i] == other.str[0])
        {
            bool flag = true;
            for (int j = 1; j < new_len; j++)
                if (str[i + j] != other.str[j])
                    flag = false;

            if (flag)
                return true;
        }
    }
    return false;
}

void String::Print() {
    std::cout << str << std::endl;
}