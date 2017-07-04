#include "StudentWorld.h"
#include <string>
//#include "actor.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <stack>

//#include "GameController.h"
static const double PI = 4 * atan(1.0);
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    
  
    Compiler *compilerForEntrant0, *compilerForEntrant1,*compilerForEntrant2, *compilerForEntrant3;
    Anthill *ah0 = nullptr, *ah1 = nullptr, *ah2 = nullptr, *ah3 = nullptr;

    std::vector<std::string> fileNames = getFilenamesOfAntPrograms();
    compilerForEntrant0 = new Compiler;
    compilerForEntrant1 = new Compiler;
    compilerForEntrant2 = new Compiler;
    compilerForEntrant3 = new Compiler;
    
    std::string error;

         if ( ! compilerForEntrant0->compile(fileNames[0], error))
        {

        setError(fileNames[0] + " " + error);
       
        return GWSTATUS_LEVEL_ERROR;
        }
         else if ( ! compilerForEntrant1->compile(fileNames[1], error))
         {
             
             setError(fileNames[1] + " " + error);
             
             return GWSTATUS_LEVEL_ERROR;
         }
         else if ( ! compilerForEntrant2->compile(fileNames[2], error))
         {
             
             setError(fileNames[2] + " " + error);
             
             return GWSTATUS_LEVEL_ERROR;
         }
         else if ( ! compilerForEntrant3->compile(fileNames[3], error))
         {
             
             setError(fileNames[3] + " " + error);
             
             return GWSTATUS_LEVEL_ERROR;
         }


    
    LoadFieldandMatch(m_actors,compilerForEntrant0,compilerForEntrant1,compilerForEntrant2,compilerForEntrant3,ah0,ah1,ah2,ah3);
    
  
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //srand(time(NULL));
    updateTickCount();
    for(int y = 0; y < 64; y++)
    {
        for(int x = 0; x < 64; x++)
        {
         if(m_actors[x][y].size() != 0)
         {
             for(list<Actor*>:: iterator p = m_actors[x][y].begin(); p != m_actors[x][y].end();p++ )
             {
                 if(!(*p)->isdead())
                     (*p)->doSomething();
                 
             }
                 
                }
        }
    }
    relocate();
    removeDeadGameObjects();
                

    int antsAnt0, antsAnt1, antsAnt2, antsAnt3; //int winningAntNumber;
    antsAnt0 = getNumberOfAntsForAnt(0);
    antsAnt1 = getNumberOfAntsForAnt(1);
    antsAnt2 = getNumberOfAntsForAnt(2);
    antsAnt3 = getNumberOfAntsForAnt(3);
    setDisplayText(antsAnt0, antsAnt1, antsAnt2, antsAnt3);
    if (m_tick == 2000)
    {
        if(antsAnt0 < 6 && antsAnt1 < 6 && antsAnt2 < 6 && antsAnt3 < 6)
            return GWSTATUS_NO_WINNER;
        else
        {
            int array[4] = {antsAnt0, antsAnt1, antsAnt2, antsAnt3};
            int max = 0; stack<int> k;
            
            for(int i=0;i<4;i++)
            {
                if(array[i]>max)
                    max = array[i];
              
            }
            for(int i=0;i<4;i++)
            {
                if(array[i] == max)
                    k.push(i);
            }
            if(k.size() == 1)
            {
                if(antsAnt0 == max)
                    setWinner("Jim");
                if(antsAnt1 == max)
                    setWinner("Natalie");
                if(antsAnt2 == max)
                    setWinner("Ann");
                if(antsAnt3 == max)
                    setWinner("Billy");
                
            }
            else{
                int size = k.size();
                int min_tick = 0; int n = -1; int m = 0;
                for(int i = 0; i < size; i++)
                {
                    int x = k.top();
                    k.pop();
                    if(x == 0)
                        m = last_tick0;
                    else if(x == 1)
                        m = last_tick1;
                    else if(x == 2)
                        m = last_tick2;
                    else if(x == 3)
                        m = last_tick3;
                    if(min_tick > m)
                    {
                        min_tick = m;
                        n = x;
                    }
                }
                if(n == 0)
                    setWinner("Jim");
                else if(n == 1)
                    setWinner("Natalie");
                else if(n == 2)
                    setWinner("Ann");
                else if(n == 3)
                    setWinner("Billy");



                
            }
            
        }
        return  GWSTATUS_PLAYER_WON;
    }

    return GWSTATUS_CONTINUE_GAME;
    
}
void StudentWorld::cleanUp()
{
    for(int y = 0; y < 64; y++)
    {
        for(int x = 0; x < 64; x++)
        {
            while(m_actors[x][y].size() != 0)
            {
                m_actors[x][y].pop_back();
                
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StudentWorld::setDisplayText(int a, int b, int c, int d)

{

    string s = formateString(m_tick, a, b, c, d);
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}
string StudentWorld::formateString(int a, int b, int c, int d, int e)
{
    string A = to_string(a);
    string B = to_string(b);
    string C = to_string(c);
    string D = to_string(d);
    string E = to_string(e);
    string s = "Ticks: " + A + " -Jim: " + B + " ants " + " Natalie " + C + " ants " + " Ann " + D + " ants " + " Billy " + E +" ants ";
    return s;
}
int StudentWorld::getNumberOfAntsForAnt(int n)
{
    if(n == 0)
        return antnumber0;
    else if (n == 1)
        return antnumber1;
    else if (n == 2)
        return antnumber2;
    else if (n == 3)
        return antnumber3;
    else
        return 0;
    
}
void StudentWorld::setNumberOfAntsForAnt(int n, int p)
{
    if(n == 0)
         antnumber0 = p;
    else if (n == 1)
         antnumber1 = p;
    else if (n == 2)
        antnumber2 = p;
    else if (n == 3)
        antnumber3 = p;
   
}
bool StudentWorld::LoadFieldandMatch(list<Actor*> ac[64][64],Compiler* c0,Compiler* c1,Compiler* c2,Compiler* c3,Anthill* a1, Anthill* a2, Anthill* a3,Anthill* a0)
{

    Field f;
    string fieldfile = getFieldFilename();
    
    if(f.loadField(fieldfile) != Field::LoadResult::load_success)
        return false;

    
        for(int y = 0; y < 64; y++)
    {
        for(int x = 0; x < 64; x++)
        {
            Field::FieldItem item = f.getContentsOf(x, y);
            if(item == Field::FieldItem::rock)
                ac[x][y].push_back(new Pebble(this, x, y));
            else if(item == Field::FieldItem::grasshopper)
                ac[x][y].push_back(new BabyGrasshopper(this, x, y));
            else if(item == Field::FieldItem::food)
                ac[x][y].push_back(new Food(this, x, y,6000));
            else if(item == Field::FieldItem::poison)
                ac[x][y].push_back(new Poison(this, x, y));
            else if(item == Field::FieldItem::water)
                ac[x][y].push_back(new PoolofWater(this, x, y));
            else if(item == Field::FieldItem::anthill0)
            {
                a0 = new Anthill(this, x, y,c0,0);
                ac[x][y].push_back(a0);
            }
            else if(item == Field::FieldItem::anthill1)
            {
                a1 = new Anthill(this, x, y,c1,1);
                ac[x][y].push_back(a1);
            }
            else if(item == Field::FieldItem::anthill2)
            {
                a2 = new Anthill(this, x, y,c2,2);
                ac[x][y].push_back(a2);
            }
            else if(item == Field::FieldItem::anthill3)
            {
                a3 = new Anthill(this, x, y,c3,3);
                ac[x][y].push_back(a3);
            }



            }
    }
    return true;
}


void StudentWorld::updateTickCount()
{
    m_tick++;
}
int StudentWorld::gettick()
{
    return m_tick;
}
void StudentWorld::setlasttick0(int t)
{
    last_tick0 = t;
}
void StudentWorld::setlasttick1(int t)
{
    last_tick1 = t;
}
void StudentWorld::setlasttick2(int t)
{
    last_tick2 = t;
}
void StudentWorld::setlasttick3(int t)
{
    last_tick3 = t;
}
void StudentWorld::removeDeadGameObjects()
{
    for(int y = 0; y < 64; y++)
    {
        for(int x = 0; x < 64; x++)
        {
            for(list<Actor*>:: iterator p = m_actors[x][y].begin(); p != m_actors[x][y].end();)
            {
                if((*p)->isdead() == true)
                {
                    (*p) -> ~Actor();
                    p = m_actors[x][y].erase(p);
                }
                else
                    p++;
            }
            
        }
    }

}
void StudentWorld::relocate()
{
    for(int y = 0; y < 64; y++)
    {
        for(int x = 0; x < 64; x++)
        {
            if(m_actors[x][y].size() != 0)
            {

                for(list<Actor*>:: iterator p = m_actors[x][y].begin(); p != m_actors[x][y].end();)
                {
                    int nowX = (*p) -> getX(), nowY = (*p) -> getY();
                    if( x != nowX || y != nowY)
                    {
                        m_actors[nowX][nowY].push_back(*p);
                        p = m_actors[x][y].erase(p);
                    }
                    else
                        p++;

      }
            }
        }
    }

}





bool StudentWorld::moveOneStep(Actor* ap)
{
    
    if(ap ->getDirection()== GraphObject::Direction::down)
    {

        if(m_actors[ap->getX()][ap->getY()-1].size() == 0)
        {
            ap->moveTo(ap->getX(), ap->getY()-1);
            ap->decreasedistance();

            return false;
        }
        else
        {
            
            if(m_actors[ap->getX()][ap->getY()-1].front() -> getID() != PEBBLE_ID)
            {
                ap->moveTo(ap->getX(), ap->getY()-1);
                ap->decreasedistance();

                return false;
            }
            else
            {ap->setdistance(0);
                return true;
            }
            
        }
    }
    else if(ap ->getDirection() == GraphObject::Direction::right)
    {

        if(m_actors[ap->getX()+1][ap->getY()].size() == 0)
        {
            ap->moveTo(ap->getX()+1, ap->getY());
            ap->decreasedistance();

            return false;
        }
        else
        {
            
            if(m_actors[ap->getX() + 1][ap->getY()].front() -> getID() != PEBBLE_ID)
            {
                ap->moveTo(ap->getX()+1, ap->getY());
                ap->decreasedistance();

                return false;
            }

            else
            {ap->setdistance(0);
                return true;
            }
            
        }
    }
    else if(ap ->getDirection() == GraphObject::Direction::up)
    {

        if(m_actors[ap->getX()][ap->getY()+1].size() == 0)
        {
           ap->moveTo(ap->getX(), ap->getY()+1);
            ap->decreasedistance();

            return false;
        }
        else
        {
            
            if(m_actors[ap->getX()][ap->getY()+1].front() -> getID() != PEBBLE_ID)
            {
                ap->moveTo(ap->getX(), ap->getY()+1);
                ap->decreasedistance();

                return false;
            }
            else
            {ap->setdistance(0);
                return true;
            }
            
        }
    }
    else
    {

        if(m_actors[ap->getX()-1][ap->getY()].size() == 0)
        {
           ap->moveTo(ap->getX()-1, ap->getY());
            ap->decreasedistance();

            return false;
        }
        else
        {
            
            if(m_actors[ap->getX()-1][ap->getY()].front() -> getID() != PEBBLE_ID)
            {
                ap->moveTo(ap->getX()-1, ap->getY());
                ap->decreasedistance();

                return false;
            }
            else
            {ap->setdistance(0);
                return true;
            }
            
        }
        
        
    }
    }

void StudentWorld::addNewFood(int x, int y,int unit)
{
    m_actors[x][y].push_back(new Food(this,x,y,unit));
}
bool StudentWorld::eat(Actor* ap)
{
    //list<Actor*> temp = m_actors[ap->getX()][ap->getY()];
        if(m_actors[ap->getX()][ap->getY()].size() == 0)
            return false;
        else
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
               if((*p) -> getID() == FOOD_ID)
                {
                    if((*p)->gethitpoint() > 200)
                    {
                        (*p) -> sethitpoint((*p)->gethitpoint() - 200);
                        ap -> sethitpoint(ap -> gethitpoint() + 200);
                       
                    }
                    else
                    {
                        ap -> sethitpoint(ap -> gethitpoint() + (*p) -> gethitpoint());
                        (*p)->sethitpoint(0);
                    }
                    return true;
                }
            }
            return false;
        }
}
bool StudentWorld::absorb(Anthill* ap) 
{
    if(m_actors[ap->getX()][ap->getY()].size() == 0)
        return false;
    else
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == FOOD_ID)
            {
                if((*p)->gethitpoint() > 10000)
                {
                    (*p) -> sethitpoint((*p)->gethitpoint() - 10000);
                    ap -> sethitpoint(ap -> gethitpoint() + 10000);
                    
                }
                else
                {
                    ap -> sethitpoint(ap -> gethitpoint() + (*p) -> gethitpoint());
                    (*p)->sethitpoint(0);
                }
                return true;
            }
        }
        return false;
    }

    
}
void StudentWorld::turn(Actor* ap)
{
    ap -> setdead();
    m_actors[ap->getX()][ap->getY()].push_back(new AdultGrasshopper(this,ap -> getX(),ap -> getY()));
}
void StudentWorld::jump(Actor* ap)
{
    double randAngle = 0; int randX = 0, randY = 0;
    int nowX,nowY;
    do
    {
        randAngle = ((double)rand() / (double)RAND_MAX) * PI*2;
        randX = cos(randAngle) * 10;
        randY = sin(randAngle) * 10;
        nowX = (ap) -> getX() + randX;
        nowY = (ap) -> getY() + randY;
        if((ap) -> getX() + randX >= 63)
            nowX = 62;
        else if((ap) -> getX() + randX <= 0)
            nowX = 1;
        if((ap) -> getY() + randY >= 63)
            nowY = 62;
        else if((ap) -> getY() + randY <= 0)
            nowY= 1;
           

    }while(m_actors[nowX][nowY].size() != 0 && m_actors[nowX][nowY].back() -> getID() == PEBBLE_ID);
    

    ap ->moveTo(nowX, nowY);
    ap -> setdistance(0);
    }
void StudentWorld::toxic(Actor* ap)
{
    for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
    {
        if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
        {
            if((*p) -> gethitpoint() <= 150)
            {
                (*p) -> sethitpoint(1);
                //cout<<"dead by poison"<<endl;
            }
            else if((*p) -> gethitpoint() > 150)
                (*p) -> sethitpoint((*p)->gethitpoint() - 150);
            //cout<<"get hit"<<endl;
        }
        
    }
    
}
void StudentWorld::stun(Actor* ap)
{
    for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
    {
       if((*p) -> getID() == BABYGRASSHOPPER_ID )
        {
            if((*p) -> getsleep() == 2)
            {
                if((*p) -> getstun() == false)
                {
                    (*p) -> setsleep(0);
                    (*p) -> changestun();
                    //cout<<"stun"<<endl;
                }
                else
                {(*p) -> changestun();
                //cout<<"aweak"<<endl;
                }
                
            }
        }
        else if((*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
        {
            if((*p) -> getsleep() == 0)
                (*p) -> changesleep();
            else if((*p) -> getsleep() == 1)
                (*p) -> changesleep();
            else if((*p) -> getsleep() == 2)
                (*p) -> changesleep();
        }
    }
}
void StudentWorld::addObjectToSimulation(Actor* ap)
{
    m_actors[ap->getX()][ap->getY()].push_back(ap);
}

void StudentWorld::bite(Actor* ap)
{

    if(m_actors[ap->getX()][ap->getY()].size() == 0)
        return;
    else
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
            {
                if((*p)->gethitpoint() > 50)
                {
                    (*p) -> sethitpoint((*p)->gethitpoint() - 50);
                   
                }
                else
                {
                    (*p)->sethitpoint(1);
                    
                }
                (*p)-> changebitten();
               break;
            }
        }
   
    }

}
void StudentWorld::pickupfood(Ant* ap)
{
    if(m_actors[ap->getX()][ap->getY()].size() == 0)
        return;
    else
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == FOOD_ID)
            {
               if(ap -> gethold() + (*p) -> gethitpoint() < 1800)
               {
                   if((*p) -> gethitpoint() > 400)
                   {
                       ap -> sethold(ap -> gethold() + 400);
                       (*p) -> sethitpoint((*p) -> gethitpoint() -400);
                   }
                   else
                   {
                       ap -> sethold(ap -> gethold() + (*p) -> gethitpoint());
                       (*p) -> sethitpoint(0);
                   }
               }
                else
                {
                    (*p) -> sethitpoint((*p) -> gethitpoint() - 1800 + ap -> gethold());
                    ap -> sethold(1800);
                    
                }
            }
        }
    }

}
void StudentWorld::dropfood(Ant* ap)
{
    if(ap -> gethold() > 0)
    {

    if(m_actors[ap->getX()][ap->getY()].size() == 0)
    {
            addNewFood(ap->getX(), ap->getY(), ap->gethold());
            ap->sethold(0);
        
    }
    else
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == FOOD_ID)
            {
                (*p) -> sethitpoint((*p) -> gethitpoint() + ap -> gethold());
                 ap->sethold(0);
                return;
            }
            
        }
        addNewFood(ap->getX(), ap->getY(), ap->gethold());
        ap->sethold(0);
        
    }
        
    }
}
bool StudentWorld::athill(Ant* ap)
{
   
    if(m_actors[ap->getX()][ap->getY()].size() == 0)
        return false;
    else
    {
        if(ap -> getID() == ANT_ID0)
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == ANTHILL0_ID)
              return true;
        }
        else if(ap -> getID() == ANT_ID1)
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == ANTHILL1_ID)
                    return true;
            }
        else if(ap -> getID() == ANT_ID2)
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == ANTHILL2_ID)
                    return true;
            }
        else if(ap -> getID() == ANT_ID3)
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == ANTHILL3_ID)
                    return true;
            }
        return false;
    }
}
bool StudentWorld::havefood(Actor* ap)
{
    if(m_actors[ap->getX()][ap->getY()].size() == 0)
        return false;
    else
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == FOOD_ID)
                return true;
        }
    }
    return false;
}
bool StudentWorld::haveenemy(Ant* ap)
{
    if(m_actors[ap->getX()][ap->getY()].size() == 0)
        return false;
    else
    {
        if(ap -> getID() == ANT_ID0)
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                {
                    
                    return true;
                }
            }
        else if(ap -> getID() == ANT_ID1)
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ADULTGRASSHOPPER_ID ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
        else if(ap -> getID() == ANT_ID2)
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
               if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID3)
                    return true;
            }
        else if(ap -> getID() == ANT_ID3)
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ADULTGRASSHOPPER_ID)
                    return true;
            }
        return false;
    }
}
void StudentWorld::antBite(Ant* ap)
{
    if(m_actors[ap->getX()][ap->getY()].size() == 0)
        return;
    else
    {if(ap -> getID() == ANT_ID0)
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
            {
                if((*p)->gethitpoint() > 15)
                {
                    (*p) -> sethitpoint((*p)->gethitpoint() - 15);
                    //cout<<"hit"<<endl;
                }
                else
                {
                    (*p)->sethitpoint(1);
                    //cout<<"dead by bite"<<endl;
                }
                (*p) -> changebitten();
                break;
                }

        }
    else if(ap -> getID() == ANT_ID1)
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ADULTGRASSHOPPER_ID ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
            {
                if((*p)->gethitpoint() > 15)
                {
                    (*p) -> sethitpoint((*p)->gethitpoint() - 15);
                    //cout<<"hit"<<endl;
                }
                else
                {
                    (*p)->sethitpoint(1);
                    //cout<<"dead by bite"<<endl;
                }
                (*p)-> changebitten();
                break;
            }

            
        }
    else if(ap -> getID() == ANT_ID2)
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID3)
            {
                if((*p)->gethitpoint() > 15)
                {
                    (*p) -> sethitpoint((*p)->gethitpoint() - 15);
                    //cout<<"hit"<<endl;
                }
                else
                {
                    (*p)->sethitpoint(1);
                    //cout<<"dead by bite"<<endl;
                }
                (*p) -> changebitten();
                break;
            }

            
        }
    else if(ap -> getID() == ANT_ID3)
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 ||(*p) -> getID() == ANT_ID2 || (*p) -> getID() == ADULTGRASSHOPPER_ID)
            {
                if((*p)->gethitpoint() > 15)
                {
                    (*p) -> sethitpoint((*p)->gethitpoint() - 15);
                    //cout<<"hit"<<endl;
                }
                else
                {
                    (*p)->sethitpoint(1);
                    //cout<<"dead by bite"<<endl;
                }
                (*p) -> changebitten();
                break;
            }

            
        }
        
    }

}
void StudentWorld::creatpheromne(Ant* ap)
{
    if(ap -> getID() == ANT_ID0)
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == PHEROMONE_ID0)
            {
                (*p) -> sethitpoint((*p) -> gethitpoint() + 256);
                if((*p) -> gethitpoint() > 768)
                    (*p) -> sethitpoint(768);
                return;
            }
                
        }
        m_actors[ap->getX()][ap->getY()].push_back(new Phromone(this, ap->getX(), ap->getY(),IID_PHEROMONE_TYPE0));
    }
    else if(ap -> getID() == ANT_ID1)
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == PHEROMONE_ID1)
            {
                (*p) -> sethitpoint((*p) -> gethitpoint() + 256);
                if((*p) -> gethitpoint() > 768)
                    (*p) -> sethitpoint(768);
                return;
            }
            
        }

        m_actors[ap->getX()][ap->getY()].push_back(new Phromone(this, ap->getX(), ap->getY(),IID_PHEROMONE_TYPE1));
    }
    else if(ap -> getID() == ANT_ID2)
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == PHEROMONE_ID2)
            {
                (*p) -> sethitpoint((*p) -> gethitpoint() + 256);
                if((*p) -> gethitpoint() > 768)
                    (*p) -> sethitpoint(768);
                return;
            }
            
        }

        m_actors[ap->getX()][ap->getY()].push_back(new Phromone(this, ap->getX(), ap->getY(),IID_PHEROMONE_TYPE2));
    }
    else if(ap -> getID() == ANT_ID3)
    {
        for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()].begin(); p != m_actors[ap->getX()][ap->getY()].end(); p++)
        {
            if((*p) -> getID() == PHEROMONE_ID3)
            {
                (*p) -> sethitpoint((*p) -> gethitpoint() + 256);
                if((*p) -> gethitpoint() > 768)
                    (*p) -> sethitpoint(768);
                return;
            }
            
        }

        m_actors[ap->getX()][ap->getY()].push_back(new Phromone(this, ap->getX(), ap->getY(),IID_PHEROMONE_TYPE3));
    }
}
bool StudentWorld::smellpheromne(Ant* ap)
{
    if(ap -> getID() == ANT_ID0)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            
            if(m_actors[ap->getX()][ap->getY()-1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID0)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::right)
        {
            
            if(m_actors[ap->getX()+1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID0)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::up)
        {
            
            if(m_actors[ap->getX()][ap->getY()+1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID0)
                        return true;
                }
                return false;
            }
        }
        else
        {
            
            if(m_actors[ap->getX()-1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID0)
                        return true;
                }
                return false;
            }
        }
  
    }
    else if(ap -> getID() == ANT_ID1)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            
            if(m_actors[ap->getX()][ap->getY()-1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID1)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::right)
        {
            
            if(m_actors[ap->getX()+1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID1)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::up)
        {
            
            if(m_actors[ap->getX()][ap->getY()+1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID1)
                        return true;
                }
                return false;
            }
        }
        else
        {
            
            if(m_actors[ap->getX()-1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID1)
                        return true;
                }
                return false;
            }
        }
        
    }
    else if(ap -> getID() == ANT_ID2)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            
            if(m_actors[ap->getX()][ap->getY()-1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID2)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::right)
        {
            
            if(m_actors[ap->getX()+1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID2)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::up)
        {
            
            if(m_actors[ap->getX()][ap->getY()+1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID2)
                        return true;
                }
                return false;
            }
        }
        else
        {
            
            if(m_actors[ap->getX()-1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID2)
                        return true;
                }
                return false;
            }
        }
        
    }
    else if(ap -> getID() == ANT_ID3)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            
            if(m_actors[ap->getX()][ap->getY()-1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID3)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::right)
        {
            
            if(m_actors[ap->getX()+1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID3)
                        return true;
                }
                return false;
            }
        }
        else if(ap ->getDirection()== GraphObject::Direction::up)
        {
            
            if(m_actors[ap->getX()][ap->getY()+1].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID3)
                        return true;
                }
                return false;
            }
        }
        else
        {
            
            if(m_actors[ap->getX()-1][ap->getY()].size() == 0)
                return false;
            else
            {
                for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
                {
                    if((*p) -> getID() == PHEROMONE_ID3)
                        return true;
                }
                return false;
            }
        }
        
    }

    return false;

}
bool StudentWorld::smelldanger(Ant* ap)
{
    if(ap -> getID() == ANT_ID0)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
        }
        else if(ap ->getDirection() == GraphObject::Direction::right)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        else if(ap ->getDirection() == GraphObject::Direction::up)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        else
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }

    }
    
    else if(ap -> getID() == ANT_ID1)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
        }
        else if(ap ->getDirection() == GraphObject::Direction::right)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        else if(ap ->getDirection() == GraphObject::Direction::up)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        else
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        
    }
    else if(ap -> getID() == ANT_ID2)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
        }
        else if(ap ->getDirection() == GraphObject::Direction::right)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        else if(ap ->getDirection() == GraphObject::Direction::up)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        else
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID1 || (*p) -> getID() == ANT_ID3)
                    return true;
            }
            return false;
            
        }
        
    }
    else if(ap -> getID() == ANT_ID3)
    {
        if(ap ->getDirection()== GraphObject::Direction::down)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()-1].begin(); p != m_actors[ap->getX()][ap->getY()-1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID1)
                    return true;
            }
            return false;
        }
        else if(ap ->getDirection() == GraphObject::Direction::right)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()+1][ap->getY()].begin(); p != m_actors[ap->getX()+1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID1)
                    return true;
            }
            return false;
            
        }
        else if(ap ->getDirection() == GraphObject::Direction::up)
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()][ap->getY()+1].begin(); p != m_actors[ap->getX()][ap->getY()+1].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID1)
                    return true;
            }
            return false;
            
        }
        else
        {
            for(list<Actor*>:: iterator p = m_actors[ap->getX()-1][ap->getY()].begin(); p != m_actors[ap->getX()-1][ap->getY()].end(); p++)
            {
                if((*p) -> getID() == POOLOFWATER_ID || (*p) -> getID() == POISON_ID || (*p) -> getID() == BABYGRASSHOPPER_ID || (*p) -> getID() == ADULTGRASSHOPPER_ID || (*p) -> getID() == ANT_ID0 || (*p) -> getID() == ANT_ID2 || (*p) -> getID() == ANT_ID1)
                    return true;
            }
            return false;
            
        }
        
    }
    return false;
    
}
void StudentWorld::turnclockwise(Ant* ap) const
{
    if(ap ->getDirection()== GraphObject::Direction::up)
    {
        ap -> setDirection(GraphObject::Direction::right);
            }
    else if(ap ->getDirection() == GraphObject::Direction::right)
    {
        ap -> setDirection(GraphObject::Direction::down);
            }
    else if(ap ->getDirection() == GraphObject::Direction::down)
    {
        ap -> setDirection(GraphObject::Direction::left);
            }
    else
    {
        ap -> setDirection(GraphObject::Direction::up);
    }

}
bool StudentWorld::havepebble(Ant* ap) const
{
    if(ap ->getDirection()== GraphObject::Direction::down)
    {
        if(m_actors[ap->getX()][ap->getY()-1].size() == 0)
            return false;
        
        else
        {
            
            if(m_actors[ap->getX()][ap->getY()-1].front() -> getID() != PEBBLE_ID)
                return false;
            else
                return true;
            
            
        }
    }
    else if(ap ->getDirection() == GraphObject::Direction::right)
    {
        if(m_actors[ap->getX()+1][ap->getY()].size() == 0)
            return false;
        
        else
        {
            
            if(m_actors[ap->getX()+1][ap->getY()].front() -> getID() != PEBBLE_ID)
                return false;
            else
                return true;
            
            
        }
    }
    else if(ap ->getDirection() == GraphObject::Direction::up)
    {
        if(m_actors[ap->getX()][ap->getY()+1].size() == 0)
            return false;
        
        else
        {
            
            if(m_actors[ap->getX()][ap->getY()+1].front() -> getID() != PEBBLE_ID)
                return false;
            else
                return true;
            
            
        }
    }
    else
    {
        if(m_actors[ap->getX()-1][ap->getY()].size() == 0)
            return false;
        
        else
        {
            
            if(m_actors[ap->getX()-1][ap->getY()].front() -> getID() != PEBBLE_ID)
                return false;
            else
                return true;
            
            
        }
        
    }
}
void StudentWorld::turncounterclockwise(Ant* ap) const
{
    if(ap ->getDirection()== GraphObject::Direction::up)
    {
        ap -> setDirection(GraphObject::Direction::left);
    }
    else if(ap ->getDirection() == GraphObject::Direction::right)
    {
        ap -> setDirection(GraphObject::Direction::up);
    }
    else if(ap ->getDirection() == GraphObject::Direction::down)
    {
        ap -> setDirection(GraphObject::Direction::right);
    }
    else
    {
        ap -> setDirection(GraphObject::Direction::down);
    }
    
}

