//
// Created by glavak on 23.11.16.
//

#include "Fortress4.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Fortress4();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("fortress4", create);
}

Fortress4::~Fortress4()
{

}

Decision Fortress4::Decide()
{
    if (move_number < 3)
    {
        move_number++;
        return Defect;
    }
    else if (move_number == 3)
    {
        move_number++;
        return Cooperate;
    }
    else
    {
        if (isOpponent1RecognizedEnemy && isOpponent2RecognizedEnemy)
        {
            return Defect;
        }
        else
        {
            return Cooperate;
        }
    }
}

void Fortress4::AddEnemyDecision(Decision d1, Decision d2)
{
    if (move_number < 4)
    {
        if (d1 == Decision::Cooperate) isOpponent1RecognizedEnemy = true;
        if (d2 == Decision::Cooperate) isOpponent2RecognizedEnemy = true;
    }
    else if (move_number == 4)
    {
        if (d1 == Decision::Defect) isOpponent1RecognizedEnemy = true;
        if (d2 == Decision::Defect) isOpponent2RecognizedEnemy = true;
    }
    else
    {
        if (d1 == Decision::Defect) isOpponent1RecognizedEnemy = true;
        if (d2 == Decision::Defect) isOpponent2RecognizedEnemy = true;
    }
}

void Fortress4::PrintData(std::ostream & stream) const
{
    stream << "Fortress4" << isOpponent1RecognizedEnemy << isOpponent2RecognizedEnemy;
}
