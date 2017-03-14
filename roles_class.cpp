#include <iostream>
#include <cstdlib>

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
    DamageDealer(): health_(30), attack_power_(10)
    {
        health_ = 30;
        attack_power_ = 10;

    }
    
    virtual void receive_damage(int dmg)
    {
        if(dmg >= health_)
        {
            health_ = 0;
            cout << " is dead" << endl;
        }
        else health_ -= dmg;
    }
    
    virtual int health() const { return health_; }      
};

class Warrior: public DamageDealer
{
protected:
    int sub_class_flg_; //if attacker warrior flg == 1 else 0
public:
    Warrior(): sub_class_flg_(1) {}
    virtual int strength () const
    {
        return health_ + attack_power_;
    }

    virtual void attack (Warrior& other)
    {
        const int dmg = rand() % attack_power_;
        if (sub_class_flg_) cout << "Warrior";
        cout << " deals damage: " << dmg << endl;
        other.receive_damage(dmg);
    }
    int health() const { return health_; }      
};

class Berserk: public Warrior
{
public:
    Berserk()
    {
        health_ = 40;
        attack_power_ = 15;
        rage_ = 5;
    }

    int strength () const
    {
        return health_ + attack_power_ + rage_;
    }

    void rage_attack(Warrior& w)
    {
        const int dmg = attack_power_ * (1 + rage_/100.);
        rage_ = 0;
        w.receive_damage(dmg);
    }
    void attack(Warrior& other)
    {
        rage_ += 5;
        cout << "Berserk";
        sub_class_flg_ = 0;
        Warrior::attack(other);
    }

protected:
    int rage_;
};


int main ()
{
     Class * w = new Warrior;
     Class * b = new Berserk;
     Warrior w1;
     Berserk b1;
         
        w1.attack(b1);
        b1.attack(w1);
        b1.attack(w1);
        w1.attack(b1);

    cout << w -> strength() << endl;
    cout << b -> strength() << endl;


    return 0;
}



