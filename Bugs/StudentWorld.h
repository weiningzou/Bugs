#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>
#include "Field.h"
#include "Compiler.h"
//class Actor;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
        m_tick = 0;
	}
    ~StudentWorld();
    virtual int init();
    virtual int move();
     virtual void cleanUp();
    void setlasttick1(int t);
    void setlasttick2(int t);
    void setlasttick3(int t);
    void setlasttick0(int t);
    int gettick();
    bool moveOneStep(Actor* ap);
    void addNewFood(int x, int y, int unit);
    bool eat(Actor* ap);
    void turn(Actor* ap);
    void jump(Actor* ap);
    void toxic(Actor* ap);
    void stun(Actor* ap);
    void addObjectToSimulation(Actor* ap);
    void bite(Actor* ap);
    void pickupfood(Ant* ap);
    void dropfood(Ant* ap);
    bool athill(Ant* ap);
    bool havefood(Actor* ap);
    int getNumberOfAntsForAnt(int n);
    void setNumberOfAntsForAnt(int n, int p);
    bool haveenemy(Ant* ap);
    void antBite(Ant* ap);
    void creatpheromne(Ant* ap);
    bool smellpheromne(Ant* ap);
    bool smelldanger(Ant* ap);
    void turnclockwise(Ant* ap) const;
    bool havepebble(Ant* ap) const;
    void turncounterclockwise(Ant* ap) const;
    bool absorb(Anthill* ap);
private:
    bool LoadFieldandMatch(std::list<Actor*> ac[64][64],Compiler* c1,Compiler* c2,Compiler* c3,Compiler* c4,Anthill* a1, Anthill* a2, Anthill* a3,Anthill* a4);
    void updateTickCount();
    void removeDeadGameObjects();
    void relocate();
    std::string formateString(int a, int b, int c, int d, int e);
    void setDisplayText(int a, int b, int c, int d);
    std::list<Actor*> m_actors[64][64];
    int m_tick;
    int antnumber1;
    int antnumber2;
    int antnumber3;
    int antnumber0;
    int last_tick0;
    int last_tick1;
    int last_tick2;
    int last_tick3;
    };

#endif // STUDENTWORLD_H_
