#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>

class String {
private:
    char* str;
    int length;

    int static mystrlen(const char* temp) {
        int i = 0;
        while (temp[i] != '\0')
            i++;
        return i;
    }

public:
    String() {
        str = nullptr;
        length = 0;
    }

    //конструктор создания
    explicit String(const char* str)
    {
        length = mystrlen(str);
        this->str = new char[length + 1];
        strcpy(this->str, str);
    }
    //конструктор копирования
    String(const String& other)
    {
        this->length = other.length;
        this->str = new char[length + 1];
        strcpy(this->str, other.str);
    }
    ~String() {
        delete[] this->str;
    }

    String& operator=(const String& other);
    String& operator=(const char* new_str);
    String operator+(const String& other);
    String operator+(const char*);
    friend String operator+(const char* new_str, const String& object);
    void operator+=(const char* new_str);
    void operator+=(const String& other);
    char operator[](int i);
    String operator*(int i);
    friend String operator*(int i, const String& object);
    bool operator==(const String& other);
    bool operator!=(const String& other);

    int lengthStr() const;
    String reverse();
    String UP();
    String DOWN();
    bool in(const char* new_str);
    bool in(const String& other);
    void Print();

};
