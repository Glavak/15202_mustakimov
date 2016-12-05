//
// Created by glavak on 24.11.16.
//

#include "Sgs.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Sgs();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("sgs", create);
}

Sgs::~Sgs()
{

}

Decision Sgs::Decide()
{
    if (move_number < 10)
    {
        lastChoice = pattern[move_number++];
    }
    else if (master == -1)
    {
        if (matchedPattern1 || matchedPattern2)
        {
            lastChoice = rand() % 2 ? Defect : Cooperate;
        }
        else
        {
            lastChoice = Defect;
        }
    }
    else if (master == 0)
    {
        lastChoice = Defect;
    }
    else
    {
        lastChoice = Cooperate;
    }

    return lastChoice;
}

void Sgs::AddEnemyDecision(Decision d1, Decision d2)
{
    if (move_number - 1 < 9)
    {
        if (matchedPattern1 && d1 != pattern[move_number - 1])
        {
            matchedPattern1 = false;
        }
        if (matchedPattern2 && d2 != pattern[move_number - 1])
        {
            matchedPattern2 = false;
        }
    }
    else if (master == -1 &&
             matchedPattern1 &&
             d1 == Defect &&
             lastChoice == Cooperate)
    {
        master = 1;
    }
    else if (master == -1 &&
             matchedPattern1 &&
             d2 == Defect &&
             lastChoice == Cooperate)
    {
        master = 2;
    }
    else if (master == -1 &&
             matchedPattern2 &&
             d2 == Cooperate &&
             lastChoice == Defect)
    {
        master = 0;
    }
    else if (master == -1 &&
             matchedPattern1 &&
             d1 == Cooperate &&
             lastChoice == Defect)
    {
        master = 0;
    }
}

void Sgs::PrintData(std::ostream & stream) const
{
    stream << "Southampton Group Strategy" << matchedPattern1 << matchedPattern2 << " m:" << master;
}
