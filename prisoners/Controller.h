//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_CONTROLLER_H
#define PRISONERS_CONTROLLER_H


#include <unordered_map>
#include <vector>
#include "Strategy.h"
#include "ScoreMatrix.h"

struct StrategyInfo
{
    StrategyInfo(Strategy * strategy)
    {
        this->strategy = strategy;
    }

    Strategy * strategy;
    int currentScore = 0;
    int lastScore = 0;
    Decision lastDecision;
};

class Controller
{
public:
    Controller(ScoreMatrix matrix, const std::string & strategiesConfigPath, std::vector<std::string> names);
    void tick(int count);

    void printState() const;
    void printWinner() const;

private:
    std::vector<StrategyInfo> strategies;
    ScoreMatrix scoreMatrix;
    std::string strategiesConfigPath;

    void addStrategy(const std::string & name);
    void fight(size_t num1, size_t num2, size_t num3);
    void tournamentTick();

};


#endif //PRISONERS_CONTROLLER_H
