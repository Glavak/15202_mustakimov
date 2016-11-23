//
// Created by glavak on 23.11.16.
//

#ifndef PRISONERS_FORTREES4_H
#define PRISONERS_FORTREES4_H


#include <vector>
#include "../Strategy.h"

class Fortress4 : public Strategy
{
public:
    virtual ~Fortress4() override;

    virtual Decision Decide() override;
    virtual void AddEnemyDecision(Decision d1, Decision d2) override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    int move_number = 0;
    bool isOpponent1RecognizedEnemy = false;
    bool isOpponent2RecognizedEnemy = false;

    std::vector<Decision> choices;
};

#endif //PRISONERS_FORTREES4_H
