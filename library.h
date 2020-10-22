#ifndef STRING_PROJECT_LIBRARY_H
#define STRING_PROJECT_LIBRARY_H

#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class String{
    char* str = nullptr;
    int len;

public:
    int Len(const char* str_);

    //конструктор создание пустой строки с длинной len_
    explicit String(int len_ = 0);

    //конструктор с параметрами, при создании объекта класса необходимо передать строку которую он будет хранить
    explicit String(const char* str_);

    //конструктор копирования, необходим для создании точной копи объекта класса но в другой области памяти
    String(const String &c1);

    // деструктор, отвечает за освобождение ресурвов занятых объектом, вызывается при уничтожении объекта класса
    ~String();

    char &operator[] (int index);

    String& operator= (const String& c1);

    bool operator== (const String& c1) const;

    bool operator!= (const String& c1) const;

    String& operator+= (String& c1);

    String operator+ (const String& c1);

    String operator() (int i, int j);

    friend ostream& operator<< (ostream& out, String& c1);

    int  bin_search(String& c1);

    int kmp_search(String&);
};

#endif //STRING_PROJECT_LIBRARY_H
