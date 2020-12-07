#include <vector>
#include <iostream>

class Depositor //Observer abstract class, 예금자 추상 클래스
{
public:
    virtual void update(int money) = 0;
};

class Bank //Subject
{
    int interest;
    std::vector<Depositor*> depositors;
public:
    void attach(Depositor* dps) {
        depositors.push_back(dps);
    }
    void addInterest(int interest) //이자 발생
    {
        this->interest = interest;
        notify();
    }
    void notify() // 이자 발생을 각 예금자에게 알림
    {
        for (int i = 0; i < depositors.size(); ++i)
            depositors[i]->update(interest);
    }
};

class DepositorA : public Depositor //예금자 A
{
    int deposit;
public:
    DepositorA(Bank* bank, int money)
    {
        bank->attach(this); //예금자 A를 은행에 등록
        deposit = money;
    }
    void update(int money)
    {
        deposit += money;
        std::cout << " Depositor_A's balance is "
            << deposit << '\n';
    }
};
class DepositorB :public Depositor  //예금자 B
{
    int deposit;
public:
    DepositorB(Bank* bank, int money)
    {
        bank->attach(this); //예금자 B를 은행에 등록
        deposit = money;
    }
    void update(int money)
    {
        deposit += money;
        std::cout << " Depositor_B's balance is "
            << deposit << '\n';
    }
};

int main()
{
    Bank subj;
    DepositorA depA(&subj, 3000);
    DepositorB depB(&subj, 4000);
    subj.addInterest(10); //이자 10이 발생 --> 각 예금자는 자동 통보 받는다.
}