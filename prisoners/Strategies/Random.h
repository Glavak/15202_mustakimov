//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_RANDOM_H
#define PRISONERS_RANDOM_H


#include "../Strategy.h"

class Random : public Strategy
{
public:
    virtual ~Random() override;

    virtual Decision Decide() override;

    virtual void AddEnemyDecision(Decision d1, Decision d2) override;

    virtual void printData(std::ostream & stream) const override;
};


#endif //PRISONERS_RANDOM_H
