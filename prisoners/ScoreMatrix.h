//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_SCOREMATRIX_H
#define PRISONERS_SCOREMATRIX_H

#include <vector>
#include "Strategy.h"

class ScoreMatrix
{
public:
    ScoreMatrix();
    std::tuple<int, int, int> getScores(Decision d1, Decision d2, Decision d3) const;
    void loadFromFile(const std::string & filename);

private:
    std::vector<int> defectsScores;
    std::vector<int> cooperatesScores;
};


#endif //PRISONERS_SCOREMATRIX_H
