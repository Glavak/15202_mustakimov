//
// Created by glavak on 16.10.16.
//

#include "Random.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Random();
    }

    bool registered = Factory::getInstance()->reg("random", create);
}

Random::~Random()
{

}

Decision Random::Decide()
{
    if (rand() % 2)
    {
        return Defect;
    }
    else
    {
        return Cooperate;
    }
}

void Random::AddEnemyDecision(Decision d1, Decision d2)
{

}

void Random::printData(std::ostream & stream) const
{
    stream << "Random";
}