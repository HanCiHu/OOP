#include <vector>
#include <iostream>

class Car{
public:
    static Car* produceCar(int choice);
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
Car* Car::produceCar(int choice) {
    if (choice == 1)
        return new Sonata;
    else if (choice == 2)
        return new Malibu;
    else
        return new Spark;
}
int main(){
    std::vector<Car*> carCollection;
    int choice;

    while (true){
        std::cout << "Choice: (Sonata:1, Malibu:2, Sparck:3, Done:0): ";
        std::cin >> choice;
        if (choice == 0)
            break;
        carCollection.push_back(Car::produceCar(choice));
    }
    for (int i = 0; i < carCollection.size(); i++)
        carCollection[i]->echoName();
    for (int i = 0; i < carCollection.size(); i++)
        delete carCollection[i];
    while (1);
}