#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Compiler.h"
class StudentWorld;

const int PEBBLE_ID = 0;	// up to four different competitor colonies
const int BABYGRASSHOPPER_ID = 1;
const int FOOD_ID = 2;
const int ADULTGRASSHOPPER_ID = 3;
const int POISON_ID = 4;
const int POOLOFWATER_ID = 5;
const int ANTHILL0_ID = 6;
const int ANTHILL1_ID = 7;
const int ANTHILL2_ID = 8;
const int ANTHILL3_ID = 9;
const int ANT_ID0 = 10;
const int ANT_ID1 = 11;
const int ANT_ID2 = 12;
const int ANT_ID3 = 13;
const int PHEROMONE_ID0 = 14;
const int PHEROMONE_ID1 = 15;
const int PHEROMONE_ID2 = 16;
const int PHEROMONE_ID3 = 17;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(StudentWorld* ap, int imageID, int startX, int startY, Direction dir, int depth, double size);
    ~Actor();
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    bool isdead() const;
    void setdead();
    int gethitpoint() const;
    void decreasehitpoint();
    void sethitpoint(int p);
    bool getstun() const;
    void changestun();
    void changesleep();
    int getsleep();
    void setsleep(int sp);
    virtual int getID() const = 0;
    virtual void setdistance(int d){};
    virtual void decreasedistance(){};
    void changebitten();
    bool getbitten();
private:
    StudentWorld* m_world;
    bool m_dead;
    int m_hitpoint;
    bool m_stun;
    int sleep = 0;
    bool m_bitten;
    //int role;
};




// ant class
class Ant: public Actor
{
public:
    Ant(StudentWorld* ap, int startX, int startY, Compiler* c,int imageID);
    ~Ant(){};
    
    virtual int getID() const;
    int gethold() const;
    void sethold(int c);
    int getcolony() const;
      virtual void doSomething();
private:
    Compiler* m_complier;
    int m_colony;
    int m_carry;
    int m_counter = 0;
    void runCommand(const Compiler::Command& c);
    void eatfood();
    bool ishungury() const;

};





//grasshopper class
class GrassHopper: public Actor
{
public:
    GrassHopper(StudentWorld* ap,int imageID, int startX, int startY, Direction dir, int depth,double size);
    ~GrassHopper();
    void  move();
    virtual void doSomething() = 0;
    virtual void decreasedistance();
    virtual void setdistance(int d);
    int getdistance() const;

    virtual int getID() const= 0;
private:
    
    int distance = 0;

    
};




//babygrasshopper class
class BabyGrasshopper: public GrassHopper
{
public:
    BabyGrasshopper(StudentWorld* ap, int startX, int startY);
    ~BabyGrasshopper();
     virtual int getID() const;
    virtual void doSomething();
private:
};



//adultgrasshopper class
class AdultGrasshopper : public GrassHopper
{
public:
    AdultGrasshopper(StudentWorld* ap, int startX, int startY);
    ~AdultGrasshopper();
    virtual int getID() const;
     virtual void doSomething();
private:
   
    
};



//pebble class
class Pebble: public Actor
{
public:
    Pebble(StudentWorld* ap, int startX, int startY);
    
    ~Pebble();
    virtual int getID() const;
    virtual void doSomething(){};
private:
    
    
};

//food class
class Food : public Actor
{
public:
    Food(StudentWorld* ap, int startX, int startY, int unit);
     virtual void doSomething();
    virtual int getID() const;
private:
   
};


//phromone class
class Phromone : public Actor
{
public:
    Phromone(StudentWorld* ap, int startX, int startY,  int imageID);
     virtual void doSomething();
    ~Phromone(){};
    int getID() const;
private:
    int m_group;
   
};


//anthill class
class Anthill : public Actor
{
public:
    Anthill(StudentWorld* ap, int startX, int startY, Compiler* c, int colony);
    virtual int getID() const;
    virtual void doSomething();
private:
    Compiler* m_complier;
    int  m_colony;
    void giveBirth();
};



//pool of water class
class PoolofWater : public Actor
{
public:
    PoolofWater(StudentWorld* ap, int startX, int startY);
    virtual void doSomething();
    ~PoolofWater();
    virtual int getID() const;
private:
    
};





// poison class
class Poison : public Actor
{
public:
    Poison(StudentWorld* ap, int startX, int startY);
    ~Poison();
    virtual int getID() const;
   virtual void doSomething();
private:
    
};





#endif // ACTOR_H_


