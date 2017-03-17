#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

#define SLEEP_TIME 100000

using namespace std;


class Class //base abstract class 
{
protected: //open access to inheritor
    int health_;
    int attack_power_;
    char cl_name[10];
public:
    virtual int strength () const = 0; 
    virtual ~Class() {}
    
    void receive_damage(int dmg)
    {
        if (dmg == 0) cout << "~ missed! ~" << endl;
        if(dmg >= health_)
        {
            health_ = 0;
            cout << "~ " << cl_name << " is dead ~" << endl;
        }
        else health_ -= dmg;
    }

    virtual int gethealth () const { return health_; };
    virtual void addhealth (const int v)  { health_ += v; };
    virtual const char* get_name () const = 0;


};

class Role: public Class
{
public:
    Role() //default parametres
    {
        attack_power_ = health_ = 0;
        strcpy(cl_name,"default");
    }
    void DamageDealer(const char* name)
    {
        health_ = 30;
        attack_power_ = 10;
        strcpy( cl_name , name );
    }
    void Support(const char* name)
    {
        health_ = 20;
        attack_power_ = 4;
        strcpy( cl_name , name );
    }
    int gethealth () const { return health_; };
    void addhealth (const int v)  { health_ += v; };
    const char* get_name () const { return cl_name; };
};  

class Mage: public Role
{
protected:
    int mana_;
public:
    Mage() //standart health and power
    {
        Role::Support("Mage");      
        mana_ = 10;
    }
    int strength() const
    {
        if (health_ == 0) return 0;
        return mana_ + health_ + attack_power_;
    }
    void attack (Class& other)
    {
        if (health_ == 0)
        {
            cout << cl_name << " was dead" << endl;
            return;
        }
        if (other.gethealth() == 0)
        {
            cout << other.get_name() << " was dead" << endl;
            return;
        }
        srand( time(0) );
        const int dmg = rand() % attack_power_;
        cout << cl_name << " deals " << dmg << " damage to " << other.get_name() << endl;
        other.receive_damage(dmg);
    }
    void heal (Class& other)
    {
        if (other.gethealth() == 0)
        {
            cout << other.get_name() << " was dead" << endl;
            return;
        }
        srand( time(0) );
        const int hp = rand() % mana_;
        if (!hp) cout << "~ " << cl_name << " forgot the spell ~" << endl;
        mana_ -= hp;
        cout << cl_name << " heals " << other.get_name() << " with " << hp << " hp" << endl;
        other.addhealth(hp);
    }
    void regen ()
    {
        const int reg = rand() % 6;
        if (!reg) cout << "~ " << cl_name << " forgot the spell ~" << endl;
        mana_ += reg;
        cout << cl_name << " regen " << reg << " mana" << endl;
    }
};


class Warrior: public Role
{
public:
    Warrior() //standart health and power
    {
        Role::DamageDealer("Warrior");
    }

    
    int strength () const
    {
        if (health_ == 0) return 0;
        return health_ + attack_power_;
    }

    virtual void attack (Class& other)
    {
        if (health_ == 0)
        {
            cout << cl_name << " was dead" << endl;
            return;
        }
        if (other.gethealth() == 0)
        {
            cout << other.get_name() << " was dead" << endl;
            return;
        }
        srand( time(0) );
        const int dmg = rand() % attack_power_;
        cout << cl_name << " deals " << dmg << " damage to " << other.get_name() << endl;
        other.receive_damage(dmg);
    }
};

class Berserk: public Warrior
{
private:
    int rage_;
public:
    Berserk()
    {
        Role::DamageDealer("Berserk");
        health_ = 40;
        attack_power_ = 15;
        rage_ = 5;
    }

    int strength () const
    {
        if (health_ == 0) return 0;
        return health_ + attack_power_ + rage_;
    }

    void rage_attack(Class& w)
    {
        if (health_ == 0)
        {
            cout << cl_name << " was dead" << endl;
            return;
        }
        if (w.gethealth() == 0)
        {
            cout << w.get_name() << " was dead" << endl;
            return;
        }
        srand(time(0));
        const double ratio = rage_/100. + 1;
        const int dmg = rand() % (int)( attack_power_ * ratio );
        cout << "~ Berserk in rage ~  x" << ratio << endl;
        rage_ = 0;
        cout << cl_name << " deals " << dmg << " damage to " << w.get_name() << endl;
        w.receive_damage(dmg);
    }
    void attack(Class& other)
    {
        Warrior::attack(other);
        rage_ += 5;
    }

};

void fight(Warrior& w, Berserk& b, Mage& m)
{
    for (int i = 1; i<100; ++i)
    {
        if (b.gethealth() > 0 )
        {
            if ( (i%15 == 0) && w.gethealth())
                b.rage_attack(w);
            else
            if ( (i%4 == 0) && w.gethealth())
                b.attack(w);
            if ( (i%7 == 0) && m.gethealth()) b.attack(m);
        }
        else return;
        usleep(SLEEP_TIME);
        if (w.gethealth() > 0)
        {
            if( (i%3 == 0) && b.gethealth() )
                w.attack(b);
        }
        usleep(SLEEP_TIME);
        if (m.gethealth() > 0)
        {
            if ( (i%3 == 0) && w.gethealth() && w.gethealth() <= 30)
                m.heal(w);
            else if (i%4 == 0) m.regen();
            if ( (i%10 == 0) && b.gethealth())
                m.attack(b);
        }
        else return;
        usleep(SLEEP_TIME);
    }
}

int main ()
{
    Warrior w1;
    Berserk b1;
    Mage m1;
    Class * m = &m1;
    Class * w = &w1;
    Class * b = &b1;
         
    cout << "Warrior strength: "<< w -> strength() << endl;
    cout << "Berserk strength: "<< b -> strength() << endl;
    cout << "Mage strength: "<< m -> strength() << endl;

    cout << "\nThe Battle bigins!\n" << endl;
    
    
    fight(w1,b1,m1);
    
    
    cout << "\nThe Battle finished!\n" << endl;
    if (w->gethealth()) cout << "Warriors won!" << endl;
    else cout << "Berserk won!" << endl;
    
    cout << "\nWarrior health: "<< w -> gethealth() << endl;
    cout << "Berserk health: "<< b -> gethealth() << endl;
    cout << "Mage health: "<< m -> gethealth() << endl;

    cout << "\nWarrior strength: "<< w -> strength() << endl;
    cout << "Berserk strength: "<< b -> strength() << endl;
    cout << "Mage strength: "<< m -> strength() << endl;


    return 0;
}



