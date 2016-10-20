//
// Created by glavak on 16.10.16.
//

#include <fstream>
#include "ScoreMatrix.h"

ScoreMatrix::ScoreMatrix()
{
    defectsScores = new int[4]{-1/*doesn't matter*/, 0, 2, 4};
    cooperatesScores = new int[4]{1, 3, 5, -1/*doesn't matter*/};
}

int * ScoreMatrix::getScores(Decision d1, Decision d2, Decision d3)
{
    int defectsCount = 0;

    if (d1 == Decision::Defect) defectsCount++;
    if (d2 == Decision::Defect) defectsCount++;
    if (d3 == Decision::Defect) defectsCount++;

    int * scores = new int[3];

    if (d1 == Decision::Defect)
    {
        scores[0] = defectsScores[defectsCount];
    }
    else
    {
        scores[0] = cooperatesScores[defectsCount];
    }

    if (d2 == Decision::Defect)
    {
        scores[1] = defectsScores[defectsCount];
    }
    else
    {
        scores[1] = cooperatesScores[defectsCount];
    }

    if (d3 == Decision::Defect)
    {
        scores[2] = defectsScores[defectsCount];
    }
    else
    {
        scores[2] = cooperatesScores[defectsCount];
    }

    return scores;
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
