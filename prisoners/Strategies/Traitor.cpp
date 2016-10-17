//
// Created by glavak on 16.10.16.
//

#include "Traitor.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Traitor();
    }

    bool registered = Factory::getInstance()->reg("traitor", create);
}

Traitor::~Traitor()
{

}

Decision Traitor::Decide()
{
    return Decision::Defect;
}

void Traitor::AddEnemyDecision(Decision d1, Decision d2)
{

}

void Traitor::printData(std::ostream & stream) const
{
    stream << "Traitor";
}
