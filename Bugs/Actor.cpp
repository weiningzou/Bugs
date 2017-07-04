#include "Actor.h"
#include "StudentWorld.h"
#include <stdlib.h>
#include <ctime>
#include <string>
using namespace std;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
//Actor


Actor::Actor(StudentWorld* ap, int imageID, int startX, int startY, Direction dir, int depth,double size):GraphObject(imageID, startX, startY, dir, depth, size)
{
    m_world = ap;
    m_dead = false;
    //m_stun = false;
    m_bitten = false;
}
Actor::~Actor(){}
StudentWorld* Actor::getWorld()
{
    return m_world;
}
bool Actor::isdead() const
{
    return m_dead;
}
void Actor::setdead()
{
    m_dead = true;
}
int Actor::gethitpoint() const
{
    return m_hitpoint;
}
void Actor::decreasehitpoint()
{
    m_hitpoint--;
}
void Actor::sethitpoint(int p)
{
    m_hitpoint = p;
}
bool Actor::getstun() const
{
    return m_stun;
}
void Actor::changestun()
{
    if (m_stun == true)
        m_stun = false;
    else
        m_stun = true;
}
void Actor::changesleep()
{
    if(sleep == 2)
        sleep =0;
    else
        sleep++;
   
}
int Actor::getsleep()
{
    return sleep;
}
void Actor::setsleep(int sp)
{
    sleep = sp;
}
void Actor::changebitten()
{
    if(m_bitten == true)
        m_bitten = false;
    else
        m_bitten = true;
}
bool Actor::getbitten()
{
    return m_bitten;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









//GrassHopper
//constructor
GrassHopper::GrassHopper(StudentWorld* ap,int imageID, int startX, int startY, Direction dir, int depth,double size):Actor(ap,imageID, startX, startY, dir, depth, size)
{
    
    
}
GrassHopper::~GrassHopper(){}
int GrassHopper::getdistance() const
{
    return distance;
}
void GrassHopper::decreasedistance()
{
    distance--;
    
}
void GrassHopper::setdistance(int d)
{
    distance = d;
}

void GrassHopper::move()
{
    if(getdistance() == 0)
    {
        
        setdistance(rand() % 9 + 2);
        int ran1 = rand() % 4;
        
        switch (ran1) {
                
            case 0:
                setDirection(up);
                break;
            case 1:
                setDirection(right);
                break;
            case 2:
                setDirection(down);
                break;
            case 3:
                setDirection(left);
                break;
        }
    }
    getWorld()-> moveOneStep(this);
    
    
}

//check if the grasshopper is dead
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//BabyGrasshopper
BabyGrasshopper::BabyGrasshopper(StudentWorld* ap,int startX, int startY):GrassHopper(ap,IID_BABY_GRASSHOPPER, startX, startY, none, 1, 0.25)
{
    sethitpoint(500);
    //srand(time(NULL));
    int ran = rand() % 4;
    switch (ran + 1) {
        //case 0:
          //  setDirection(none);
           // break;
        case 1:
            setDirection(up);
            break;
        case 2:
            setDirection(right);
            break;
        case 3:
            setDirection(down);
            break;
        case 4:
            setDirection(left);
            break;
        default:
            setDirection(none);break;
    }
}
BabyGrasshopper::~BabyGrasshopper(){}
void BabyGrasshopper::doSomething()
{
    decreasehitpoint();
    if(gethitpoint() == 0)
        setdead();
        
    if(isdead())
    {
        getWorld() -> addNewFood(getX(), getY(),100);
        return;}
    if(getsleep() == 0)
    {
        bool eat; int ran = rand() % 2;
        
    
        
        if(gethitpoint() > 1600)
        {
            getWorld() -> turn(this);
        }
    
    
        eat = getWorld() -> eat(this);
        if(eat == true)
        {
            if(ran == 0)
                move();
        }
        else
            move();
    }
    changesleep();
}


int BabyGrasshopper::getID() const
{
    return BABYGRASSHOPPER_ID;
}









////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Pebble
Pebble::Pebble(StudentWorld* ap, int startX, int startY):Actor(ap,IID_ROCK, startX, startY, right, 1, 0.25)
{}
Pebble::~Pebble(){}
int Pebble::getID() const
{
    return PEBBLE_ID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//food
Food::Food(StudentWorld* ap, int startX, int startY,int unit ) : Actor(ap, IID_FOOD, startX, startY, right, 2, 0.25)
{
    sethitpoint(unit);
    
}
int Food::getID() const
{
    return FOOD_ID;
}

void Food::doSomething()
{
    if(gethitpoint() == 0)
    {
        setdead();
    }
    if(isdead())
        return;
    
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Poison
Poison::Poison(StudentWorld* ap, int startX, int startY) : Actor(ap, IID_POISON, startX, startY, right, 2, 0.25)
{}
int Poison::getID() const
{
    return POISON_ID;
}
Poison::~Poison(){};
void Poison::doSomething()
{
    getWorld() -> toxic(this);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PoolofWater
PoolofWater::PoolofWater(StudentWorld* ap, int startX, int startY): Actor(ap, IID_WATER_POOL, startX, startY, right, 2, 0.2)
{}
int PoolofWater::getID() const
{
    return POOLOFWATER_ID;
}
PoolofWater::~PoolofWater(){};
void PoolofWater::doSomething()
{
    getWorld() -> stun(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//AdultGrassHopper
AdultGrasshopper::AdultGrasshopper(StudentWorld* ap, int startX, int startY):GrassHopper(ap,IID_ADULT_GRASSHOPPER, startX, startY, none, 1, 0.25)
{
    sethitpoint(1600);
    int ran = rand() % 5;
    switch (ran) {
        case 0:
            setDirection(none);
            break;
        case 1:
            setDirection(up);
            break;
        case 2:
            setDirection(right);
            break;
        case 3:
            setDirection(down);
            break;
        case 4:
            setDirection(left);
            break;
}
}
AdultGrasshopper::~AdultGrasshopper(){};
void AdultGrasshopper::doSomething()
{
    decreasehitpoint();
    if(gethitpoint() == 0)
    {
        setdead();
        getWorld() -> addNewFood(getX(), getY(),100);
    }
    if(isdead())
        return;
    if(getsleep() == 0)
    {
        
        bool eat; int ran1 = rand() % 2, ran2 = rand() % 10, ran3 = rand() % 3;
        if(ran3 == 0)
            getWorld() -> bite(this);
        
        if(ran2 == 5)
        {
            getWorld() -> jump(this);
            changesleep();
            return;
        }
  
        eat = getWorld() -> eat(this);
        if(eat == true)
        {
            if(ran1 == 0)
                move();
        }
        else
            move();
    }
     changesleep();
}


int AdultGrasshopper::getID() const
{
    return ADULTGRASSHOPPER_ID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class anthill
Anthill::Anthill(StudentWorld* ap, int startX, int startY, Compiler* c, int colony): Actor(ap, IID_ANT_HILL, startX, startY, right, 2, 0.2)
{
    sethitpoint(8999);
    m_complier = c;
    m_colony = colony;
}
void Anthill::doSomething()
{
    decreasehitpoint();
    //cout<<"point"<<gethitpoint()<<endl;
    if(gethitpoint() == 0)
        setdead();
    if(isdead())
        return;
    if(getWorld() -> havefood(this))
    {getWorld() -> absorb(this);
        cout<<"absorb"<<endl;
        return;}
    if(gethitpoint() > 2000)
    {
        giveBirth();
        sethitpoint(gethitpoint() - 1500);
    }
    
}
int Anthill::getID() const
{
    switch(m_colony) {
        case 0:
            return ANTHILL0_ID;
            break;
        case 1:
            return ANTHILL1_ID;
            break;
        case 2:
            return ANTHILL2_ID;
            break;
        case 3:
            return ANTHILL3_ID;
            break;
        default:
            break;
    }
 return 0;
}
void Anthill::giveBirth()
{
    cout<<"givebirth"<<endl;
    if(m_colony == 0)
    {
        Ant* newAnt = new Ant(getWorld(),getX(),getY(),m_complier,IID_ANT_TYPE0);
        getWorld() -> addObjectToSimulation(newAnt);
        getWorld() -> setNumberOfAntsForAnt(0,getWorld() -> getNumberOfAntsForAnt(0)+1);
        getWorld() -> setlasttick0(getWorld() -> gettick());
        
    }
    else if(m_colony == 1)
    {
        Ant* newAnt = new Ant(getWorld(),getX(),getY(),m_complier,IID_ANT_TYPE1);
        getWorld() -> addObjectToSimulation(newAnt);
         getWorld() -> setNumberOfAntsForAnt(1,getWorld() -> getNumberOfAntsForAnt(1)+1);
        getWorld() -> setlasttick1(getWorld() -> gettick());
    }
    else if(m_colony == 2)
    {
        Ant* newAnt = new Ant(getWorld(),getX(),getY(),m_complier,IID_ANT_TYPE2);
        getWorld() -> addObjectToSimulation(newAnt);
         getWorld() -> setNumberOfAntsForAnt(2,getWorld() -> getNumberOfAntsForAnt(2)+1);
        getWorld() -> setlasttick2(getWorld() -> gettick());
    }
    else if(m_colony == 3)
    {
        Ant* newAnt = new Ant(getWorld(),getX(),getY(),m_complier,IID_ANT_TYPE3);
        getWorld() -> addObjectToSimulation(newAnt);
         getWorld() -> setNumberOfAntsForAnt(3,getWorld() -> getNumberOfAntsForAnt(3)+1);
        getWorld() -> setlasttick3(getWorld() -> gettick());
    }
    
                                                     
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Pheromone
Phromone::Phromone(StudentWorld* ap, int startX, int startY, int imageID):Actor(ap, imageID, startX, startY, right, 2, 0.2)
{
    sethitpoint(256);
    if(imageID == IID_PHEROMONE_TYPE0)
        m_group = 0;
    else if (imageID == IID_PHEROMONE_TYPE1)
        m_group = 1;
    else if (imageID == IID_PHEROMONE_TYPE2)
        m_group = 2;
    else if (imageID == IID_PHEROMONE_TYPE3)
        m_group = 3;
}
void Phromone::doSomething()
{
    decreasehitpoint();
    if(gethitpoint() == 0)
        setdead();
}
int Phromone::getID() const
{
    switch(m_group) {
        case 0:
            return PHEROMONE_ID0;
            break;
        case 1:
            return PHEROMONE_ID1;
            break;
        case 2:
            return PHEROMONE_ID2;
            break;
        case 3:
            return PHEROMONE_ID3;
            break;
            
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class Ant
Ant::Ant(StudentWorld* ap, int startX, int startY, Compiler* c,int imageID): Actor(ap, imageID, startX, startY, right, 1, 0.2)
{
    sethitpoint(1500);
    m_complier = c;
    m_carry = 0;
   
    if(imageID == IID_ANT_TYPE0)
        m_colony = 0;
    else if (imageID == IID_ANT_TYPE1)
        m_colony = 1;
    else if (imageID == IID_ANT_TYPE2)
        m_colony = 2;
    else if (imageID == IID_ANT_TYPE3)
        m_colony = 3;
    int ran = rand() % 5;
    switch (ran) {
        case 0:
            setDirection(none);
            break;
        case 1:
            setDirection(up);
            break;
        case 2:
            setDirection(right);
            break;
        case 3:
            setDirection(down);
            break;
        case 4:
            setDirection(left);
            break;
    }

    
}
void Ant::doSomething()
{

    Compiler::Command cmd;
    
    decreasehitpoint();
    //cout<<gethitpoint()<<endl;
    if(gethitpoint() == 0)
    {setdead();
        //cout<<"dead";
    }
    //cout<<"point"<<gethitpoint()<<endl;
    if(isdead())
    {
        getWorld() -> addNewFood(getX(), getY(),100);
        if(m_colony == 0)
             getWorld() -> setNumberOfAntsForAnt(0,getWorld() -> getNumberOfAntsForAnt(0)-1);
        else if(m_colony == 1)
             getWorld() -> setNumberOfAntsForAnt(1,getWorld() -> getNumberOfAntsForAnt(1)-1);
        else if(m_colony == 2)
             getWorld() -> setNumberOfAntsForAnt(2,getWorld() -> getNumberOfAntsForAnt(2)-1);
        else if(m_colony == 3)
             getWorld() -> setNumberOfAntsForAnt(3,getWorld() -> getNumberOfAntsForAnt(3)-1);
        return;
    }
    
    if(getsleep() == 0)
    {
        m_complier->getCommand(m_counter, cmd);
        runCommand(cmd);
        
        
    }
    if(getbitten() == true)
        changebitten();
    
}
int Ant::getID() const
{
    switch(m_colony) {
        case 0:
            return ANT_ID0;
            break;
        case 1:
            return ANT_ID1;
            break;
        case 2:
            return ANT_ID2;
            break;
        case 3:
            return ANT_ID3;
            break;
        
    }
    return 0;
}



int Ant::gethold() const
{
    return m_carry;
}
void Ant:: sethold(int c)
{
    m_carry = c;
}
void Ant::runCommand(const Compiler::Command& c)
{
    int time = 0;
   if(time < 10)
   {
    int m_lastRandomNumberGenerated = -1;
    if(c.opcode == Compiler::moveForward)
    {
       getWorld() -> moveOneStep(this);
            m_counter++;
        time++;
    }
    else if(c.opcode == Compiler::emitPheromone)
        
    {
        getWorld() -> creatpheromne(this);
        m_counter++;
        time++;
    }
    
    else if(c.opcode == Compiler::faceRandomDirection)
        {
        int ran = rand() % 4;
        switch (ran) {
            case 0:
                setDirection(up);
                break;
            case 1:
                setDirection(right);
                break;
            case 2:
                setDirection(down);
                break;
            case 3:
                setDirection(left);
            break;}
        m_counter++;
            time++;

    }
    else if(c.opcode == Compiler::rotateClockwise)
    {getWorld() -> turnclockwise(this);
        //cout<<"rotate"<<endl;
        m_counter++;
        time++;
    }
    else if(c.opcode == Compiler::rotateCounterClockwise)
    {getWorld() -> turncounterclockwise(this);
        //cout<<"rotate2"<<endl;
        m_counter++;
        time++;
    }
    else if(c.opcode == Compiler::bite)
    {
        getWorld() -> antBite(this);
        //cout<<"get"<<endl;
        m_counter++;
        time++;
        cout<<"bite"<<endl;
    }

    else if (c.opcode == Compiler::pickupFood)
    {
        getWorld() -> pickupfood(this);
        //cout<<"getfood"<<endl;
        m_counter++;
        time++;
    }
    else if (c.opcode == Compiler::dropFood)
    {
        getWorld() -> dropfood(this);
        //cout<<"drop"<<endl;
        m_counter++;
        time++;
    }
    else if (c.opcode == Compiler::eatFood)
    {
        eatfood();
        //cout<<"eatfood"<<endl;
        m_counter++;
        time++;
    }
    else if (c.opcode == Compiler::goto_command)
        m_counter = stoi(c.operand1);
        
    else if (c.opcode == Compiler::generateRandomNumber)
    {
        m_lastRandomNumberGenerated = randInt(0, stoi(c.operand1));
        m_counter++;
        time++;
    }

    else if (c.opcode == Compiler::if_command)
    {
        if(stoi(c.operand1) == 0)
        {
            if(getWorld() -> smelldanger(this))
            {   m_counter = stoi(c.operand2);
                //cout<<"danger"<<endl;
               
            }
            else
             m_counter++;
                time++;
            
        }
        else if (stoi(c.operand1) == 1)
        {
            if(getWorld() -> smellpheromne(this))
            {   m_counter = stoi(c.operand2);
                //cout<<"smell"<<endl;
                
            }
            else
                m_counter++;
            time++;
        }
        else if (stoi(c.operand1) == 2)
        {
            if(getbitten() == true)
            {
                m_counter = stoi(c.operand2);
                cout<<"bitten"<<endl;
               
            }
            else
                m_counter++;
            time++;
        }
        else if (stoi(c.operand1) == 3)
        {
            if(m_carry != 0)
            {
                m_counter = stoi(c.operand2);
                //cout<<"carryfood"<<endl;
            }
            else
                m_counter++;
            time++;
        }

        else if (stoi(c.operand1) == 4)
        {
            if(ishungury())
                m_counter = stoi(c.operand2);
            else
                m_counter++;
            time++;
        }
        else if(stoi(c.operand1) == 5)
        {
           if(getWorld() -> athill(this))
           {   m_counter = stoi(c.operand2);
              // cout<<"at hill"<<endl;
           }
            else
                m_counter++;
            time++;
         }
        else if(stoi(c.operand1) == 6)
        {
            if(getWorld() -> havefood(this))
            {
                m_counter = stoi(c.operand2);
                //cout<<"havefood"<<endl;
            }
            else
                m_counter++;
            time++;
            
        }
        
        else if(stoi(c.operand1) == 7)
        {
            if(getWorld() -> haveenemy(this))
            {
                m_counter = stoi(c.operand2);
                //cout<<"run"<<endl;
            }
            else
                m_counter++;
            time++;
            
        }

        else if(stoi(c.operand1) == 8)
        {
            if(getWorld() -> havepebble(this))
                m_counter = stoi(c.operand2);
            else
                m_counter++;
            time++;
        }
        else if(stoi(c.operand1) == 9)
        {
            if(m_lastRandomNumberGenerated == 0)
                m_counter = stoi(c.operand2);
            else
                m_counter++;
            time++;
        }
    }
   }
}
bool Ant::ishungury() const
{
    if(gethitpoint() < 25)
        return true;
    return false;
}
void Ant::eatfood()
{
    m_carry = m_carry - 100;
    sethitpoint(gethitpoint() + 100);
}
int Ant::getcolony() const
{
    return m_colony;
}
