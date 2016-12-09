//
// Created by glavak on 16.10.16.
//

#include <fstream>
#include <tuple>
#include "ScoreMatrix.h"

ScoreMatrix::ScoreMatrix()
{
    defectsScores.push_back(-1); // Doesn't matter
    defectsScores.push_back(0);
    defectsScores.push_back(2);
    defectsScores.push_back(4);

    cooperatesScores.push_back(1);
    cooperatesScores.push_back(3);
    cooperatesScores.push_back(5);
    cooperatesScores.push_back(-1); // Doesn't matter
}

std::tuple<int, int, int> ScoreMatrix::getScores(Decision d1, Decision d2, Decision d3) const
{
    int cooperateCount = 0;

    if (d1 == Decision::Cooperate) cooperateCount++;
    if (d2 == Decision::Cooperate) cooperateCount++;
    if (d3 == Decision::Cooperate) cooperateCount++;

    int scores[3];

    if (d1 == Decision::Cooperate)
    {
        scores[0] = defectsScores[cooperateCount];
    }
    else
    {
        scores[0] = cooperatesScores[cooperateCount];
    }

    if (d2 == Decision::Cooperate)
    {
        scores[1] = defectsScores[cooperateCount];
    }
    else
    {
        scores[1] = cooperatesScores[cooperateCount];
    }

    if (d3 == Decision::Cooperate)
    {
        scores[2] = defectsScores[cooperateCount];
    }
    else
    {
        scores[2] = cooperatesScores[cooperateCount];
    }

    return std::make_tuple(scores[0], scores[1], scores[2]);
}

void ScoreMatrix::loadFromFile(const std::string & filename)
{
    std::ifstream file;
    file.open(filename);
    std::string ignore;

    file >> ignore;
    file >> defectsScores[1];
    file >> defectsScores[2];
    file >> defectsScores[3];

    file >> cooperatesScores[0];
    file >> cooperatesScores[1];
    file >> cooperatesScores[2];
    file >> ignore;
}
