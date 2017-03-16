#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

using namespace std;


class Class //base abstract class 
{   
public:
    virtual int strength () const = 0; 
    virtual ~Class() {}
};

class DamageDealer: public Class
{
protected: //open access to inheritor
    int health_;
    int attack_power_;
public:
    char cl_name[10];

    DamageDealer(): health_(30), attack_power_(10)
    {
        health_ = 30;
        attack_power_ = 10;
        strcpy(cl_name,"default");
    }
    void receive_damage(int dmg)
    {
        if (dmg == 0) cout << "missed!" << endl;
        if(dmg >= health_)
        {
            health_ = 0;
            cout << cl_name << " is dead" << endl;
        }
        else health_ -= dmg;
    }
    int health() const { return health_; }      
};

class Warrior: public DamageDealer
{
public:
    Warrior()
    {
        //standart health and power
        strcpy(cl_name,"Warrior");
    }

    
    int strength () const
    {
        return health_ + attack_power_;
    }

    virtual void attack (Warrior& other)
    {
        if (health_ == 0)
        {
            cout << cl_name << " was dead" << endl;
            return;
        }
        if (other.health_ == 0)
        {
            cout << other.cl_name << " was dead" << endl;
            return;
        }
        srand(time(0));
        const int dmg = rand() % attack_power_;
        cout << cl_name << " deals " << dmg << " damage " << other.cl_name << endl;
        other.receive_damage(dmg);
    }
};

class Berserk: public Warrior
{
protected:
    int rage_;
public:
    Berserk()
    {
        health_ = 40;
        attack_power_ = 15;
        rage_ = 5;
        strcpy(cl_name,"Berserk");
    }

    int strength () const
    {
        return health_ + attack_power_ + rage_;
    }

    void rage_attack(Warrior& w)
    {
        const double ratio = rage_/100. + 1;
        const int dmg = attack_power_ * ratio;
        cout << "~Berserk in rage~ x" << ratio << endl;
        rage_ = 0;
        cout << cl_name << " deals " << dmg << " damage " << w.cl_name << endl;
        w.receive_damage(dmg);
    }
    void attack(Warrior& other)
    {
        Warrior::attack(other);
        rage_ += 5;
    }

};


int main ()
{
     //Class * w = new Warrior;
     Warrior w1;
     Berserk b1;
     Class * w = &w1;
     Class * b = &b1;
         
    cout << "Warrior strength: "<< w -> strength() << endl;
    cout << "Berserk strength: "<< b -> strength() << endl;
        b1.rage_attack(w1);
        w1.attack(b1);
        w1.attack(b1);
        w1.attack(b1);
    cout << "Warrior health: "<< w1.health() << endl;

    cout << "Berserk health: "<< b1.health() << endl;
        w1.attack(b1);
        w1.attack(b1);
        w1.attack(b1);
        w1.attack(b1);
        w1.attack(b1);
        w1.attack(b1);
        b1.rage_attack(w1);
        b1.attack(w1);
        w1.attack(b1);

    cout << "Warrior strength: "<< w -> strength() << endl;
    cout << "Berserk strength: "<< b -> strength() << endl;


    return 0;
}



