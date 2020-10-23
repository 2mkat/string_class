#include "l_string.h"
#include <vector>

using namespace std;

int String::Len(const char* str_) {
    int length = 0;
    for (int i = 0; str_[i] != '\0'; ++i) {
        length++;
    }
    len = length;
    return len;
}

//конструктор создание пустой строки с длинной len_
String::String(int len_){
    len = len_;
    str = new char[len + 1];
    str[len] = '\0';
}

//конструктор с параметрами, при создании объекта класса необходимо передать строку которую он будет хранить
String::String(const char* str_) {
    int len = Len(str_);

    this->str = new char[len + 1];   //+1 символ так как нужно место в массиве под терминирующий 0
    for (int i = 0; i < len; ++i) {   //копируем символы строки в массив нашего класса
        this->str[i] = str_[i];
    }
    this->str[len + 1] = '\0';
}

//конструктор копирования, необходим для создании точной копи объекта класса но в другой области памяти
String::String(const String &c1) {
    int length = Len(c1.str);
    this->str = new char[length + 1];

    for (int i = 0; i < length; i++){
        this->str[i] = c1.str[i];
    }

    this->str[length] = '\0';
}

// деструктор, отвечает за освобождение ресурвов занятых объектом, вызывается при уничтожении объекта класса
String:: ~String() {
    delete[] this->str;
}

char& String::operator[] (int index){
    return str[index];
}

String& String::operator= (const String& c1) {
    if(this->str != nullptr) {
        delete[] str;
    }

    int length = Len(c1.str);
    this->str = new char[length + 1];
    for (int i = 0; i < length; ++i) {
        this->str[i] = c1.str[i];
    }
    this->str[len + 1] = '\0';

    return *this;
}

bool String::operator== (const String& c1) const{
    int res = strcmp(c1.str, this->str);
    return (res == 0) ? true : false;
}

bool String::operator!= (const String& c1) const{
    return !operator==(c1);
}

String& String::operator+= (String& c1) {
    int length = c1.len + len;
    char* res = new char[length + 1];

    for (int i = 0; i < len; ++i) {
        res[i] = str[i];
    }
    for (int j = 0; j < c1.len; ++j) {
        res[len + j] = c1.str[j];
    }

    res[length] = '\0';

    if(this->str != nullptr) {
        delete[] str;
    }

    str = res;

    return *this;
}

String String::operator+ (const String& c1){

    String res;

    res.len = this->len + c1.len;
    res.str = new char[res.len + 1];

    for (int i = 0; i < this->len; ++i) {
        res.str[i] = str[i];
    }
    for (int j = 0; j < c1.len; ++j) {
        res.str[this->len + j] = c1.str[j];
    }

    res.str[res.len] = '\0';

    return res;
}

//выделяет подстроку из исходной строки с i-ого по j-ый символ
String String::operator() (int pointer1, int pointer2){
    String res;
    res.len = pointer2 - pointer1;
    res.str = new char[res.len + 1];

    for(int i = pointer1, j = 0; i <= pointer2; ++i, ++j){
        res[j] = str[i];
    }
    res.str[res.len] = '\0';

    return res;
}

//БМ-поиск
int String::bin_search(String &c1){
    vector<int> table;

    //инициализируем все элементы таблицы длинной образца
    for (int i = 0; i < 256; i++){
        table.push_back(c1.len);
    }

    //заполнение таблицы
    int i = 0;
    while (i < c1.len-1){
        table[c1.str[i]] = c1.len - 1 - i;
        i++;
    }

    int j = c1.len - 1;
    i = c1.len - 1;

    //алгоритм БМ-поиска
    while (i<len && j >= 0){
        int k = i;
        j = c1.len - 1;

        while (j>=0){
            if (str[k]==c1.str[j]){
                j--; k--;
            }
            //если символы не равны то делаем сдвиг согласно таблице
            else{
                i = i + table[str[i]];
                j = c1.len - 1;
                break;
            }
        }
    }
    //возврат позиции
    //если не найдено	-1
    //если найдено		i + 1 - original.len

    return (j >= 0) ? -1 : i + 1 - c1.len;
}

int String::kmp_search(String& c1){
    int* newj = new int[c1.len];
    int k = -1,
        j = 0;

    newj[0] = -1;

    //заполнение массива NewJ для образца
    while (j < c1.len - 1){
        if (k >= 0 && c1.str[j] != c1.str[k]){
            k = newj[k];
        }
        else{
            k++; j++;

            if (c1.str[j] == c1.str[k]){
                newj[j] = newj[k];
            }
            else{
                newj[j] = k;
            }
        }
    }

    for(int p = 0; p < c1.len; ++p){
        cout << newj[p];
    }
    cout << endl;

    int i = 0; j = 0;
    //алгоритм КМП-поиск
    while (j < c1.len){
        //проверка выхода за границы
        if (!(i < len)){
            delete[] newj;
            newj = nullptr;
            return -1;
        }

        while (true){
            if (!(j >= 0)){
                i++; j++;
                break;
            }

            if (!(str[i] != c1.str[j])){
                i++; j++;
                break;
            }

            j = newj[j];
        }
    }

    delete[] newj;
    newj = nullptr;

    return i - c1.len;
}

std::ostream& operator<< (ostream& out, String& c1){
    for (int i = 0; i < c1.len; i++){
        out << c1.str[i];
    }
    return out;
}
