#include <vector>
#include <iostream>

class Car{
public:
    virtual void echoName() = 0;
};

class Sonata : public Car{
public:
    void echoName(){
        std::cout << "I'm Sonata!" << std::endl;
    }
};
class Malibu : public Car{
public:
    void echoName(){
        std::cout << "I'm Malibu!" << std::endl;
    }
};
class Spark : public Car{
public:
    void echoName(){
        std::cout << "I'm Spark!" << std::endl;
    }
};

int main(){  //클라이언트 프로그램
    std::vector<Car*> carCollection;
    int choice;

    while (true){
        std::cout << "Choice: (Sonata:1, Malibu:2, Sparck:3, Done:0): ";
        std::cin >> choice;
        if (choice == 0)
            break;
        else if (choice == 1)
            carCollection.push_back(new Sonata);
        else if (choice == 2)
            carCollection.push_back(new Malibu);
        else
            carCollection.push_back(new Spark);
    }
    for (int i = 0; i < carCollection.size(); i++)
        carCollection[i]->echoName();
    for (int i = 0; i < carCollection.size(); i++)
        delete carCollection[i];
    while (1);
}