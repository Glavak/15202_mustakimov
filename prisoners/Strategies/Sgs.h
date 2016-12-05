//
// Created by glavak on 24.11.16.
//

#ifndef PRISONERS_SGS_H
#define PRISONERS_SGS_H


#include <vector>
#include "../Strategy.h"

class Sgs : public Strategy
{
public:
    virtual ~Sgs() override;

    virtual Decision Decide() override;
    virtual void AddEnemyDecision(Decision d1, Decision d2) override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    int move_number = 0;

    Decision lastChoice;

    std::vector<Decision> choices1;
    std::vector<Decision> choices2;

    bool matchedPattern1 = true;
    bool matchedPattern2 = true;

    int master = -1; // -1 - Unknown, 0 - me, 1,2 - someone else

    Decision pattern[10] = {
            Defect,
            Defect,
            Cooperate,
            Cooperate,
            Defect,
            Cooperate,
            Defect,
            Cooperate,
            Defect,
            Defect
    };
};


#endif //PRISONERS_SGS_H
