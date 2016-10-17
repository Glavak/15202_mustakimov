//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_GOOD_H
#define PRISONERS_GOOD_H


#include "../Strategy.h"
#include <iostream>

class Traitor : public Strategy
{
public:
    virtual ~Traitor() override;

    virtual Decision Decide() override;

    virtual void AddEnemyDecision(Decision d1, Decision d2) override;

    virtual void printData(std::ostream & stream) const override;
};


#endif //PRISONERS_GOOD_H
