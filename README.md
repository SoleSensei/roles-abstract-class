# abstract fight class

## There are three characters now:

  1) Warrior - just attacks
  
  2) Berserk - could attack and has a rage mode
  
  3) Mage - could attack and heal 

In 'Class' class we have pure virtual function - strength(), which returns sum of all pers stats.

Every fight is rand(); You could change SLEEP_TIME at define, to change fight speed.

## Avaliable functions:
 
    Warrior.attack(Class& other) //everybody
    
    Berserk.rage_attack(Class& other) //Berserk increase his damage and attacks
    
    Mage.heal (Class& other) //Mage healing smb  
    
    Mage.regen() //Mage increase his health
    
## Roles hierarchy

    Role -> DamageDealer -> Warrior -> Berserk
    
         -> Support      -> Mage
