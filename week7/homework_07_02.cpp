#include <iostream>

bool funcA() {
    int c;
    std::cin >> c;
    if (c < 10) //Let's assume this is exception
        return false;
    return true;
}
int main() {
    try{
        if (funcA()) {

        }
        else {
            throw "Exception : Invalid Input!!";
        }
    }catch(const char* s){
        std::cout << s << std::endl;
    }
    return 0;
}
