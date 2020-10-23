#include <iostream>
#include "l_string.h"
#include "l_string.cpp"

int main(){

    String str("FGYTFGYHFFGGTT");
    String str2("FGYTFGYHFFGGTT");

    cout << str.kmp_search(str2);


    return 0;
}
