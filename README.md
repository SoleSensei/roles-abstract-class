# abstract fight class

## There are three characters now:

  1) Warrior - just attacks
  
  2) Berserk - could attack and has a rage mode
  
  3) Mage - could attack and heal 

In 'Class' class we have pure virtual function - strength(), which returns sum of all pers stats.

Every fight is rand(); You could change SLEEP_TIME at define, to change fight speed.

## Avaliable functions:
 
    Smb.attack(Class& other) //everybody
    
    Berserk.rage_attack(Class& other) //Berserk increases his damage and attacks
    
    Mage.heal (Class& other) //Mage heals smb  
    
    Mage.regen() //Mage increases his mana
    
    Mage.ressurect(Class& other) //ressurect smb, if he has enough mana
    
    Smb.gethealth() //get current health
   
    
## examples:

    Warrior w;
    Berserk b;
    Mage m;
    w.attack(b);
    if (b.gethealth() > 0)
        b.rage_attack(m);
    m.regen();
    m.heal(m);
    
    
## Roles hierarchy

    Role -> DamageDealer -> Warrior -> Berserk
    
         -> Support      -> Mage
