//
// Created by glavak on 16.10.16.
//

#include <iostream>
#include "Controller.h"
#include "Factory.h"

std::ostream & operator<<(std::ostream & stream, const StrategyInfo & info)
{
    stream << *info.strategy << " "
           << (info.lastDecision == Decision::Defect ? "defects" : "cooperates")
           << " and gains " << info.lastScore << " points"
           << " with total of " << info.currentScore << " points";
    return stream;
}

Controller::Controller(
        const ScoreMatrix & matrix,
        const std::string & strategiesConfigPath,
        const std::vector<std::string> & names,
        int steps) : scoreMatrix(matrix)
{
    this->strategiesConfigPath = strategiesConfigPath;
    this->steps = steps;

    for (std::string name : names)
    {
        addStrategy(name);
    }
}

void Controller::printState() const
{
    int index = 0;
    for (StrategyInfo info : strategies)
    {
        std::cout << " #" << index++ << " " << info << std::endl;
    }
}

void Controller::printWinner() const
{
    const StrategyInfo * maxStrategy = nullptr;
    const StrategyInfo * minStrategy = nullptr;
    for (size_t i = 0; i < strategies.size(); i++)
    {
        if (maxStrategy == nullptr ||
            strategies.at(i).currentScore > maxStrategy->currentScore)
        {
            maxStrategy = &strategies.at(i);
        }
        if (minStrategy == nullptr ||
            strategies.at(i).currentScore < minStrategy->currentScore)
        {
            minStrategy = &strategies.at(i);
        }
    }
    std::cout << "The winner is "
              << *maxStrategy->strategy
              << " with "
              << maxStrategy->currentScore
              << " points"
              << std::endl;
    std::cout << "And "
              << *minStrategy->strategy
              << " gonna rot in prison with "
              << minStrategy->currentScore
              << " points"
              << std::endl;
}

void Controller::addStrategy(const std::string & name)
{
    std::shared_ptr<Strategy> strategy(Factory<Strategy, std::string>::getInstance()->create(name));
    StrategyInfo strategyInfo(strategy);
    strategies.push_back(strategyInfo);
    strategyInfo.strategy->LoadConfig(this->strategiesConfigPath);
}

void Controller::fight(size_t num1, size_t num2, size_t num3)
{
    std::shared_ptr<Strategy> s1 = strategies.at(num1).strategy;
    std::shared_ptr<Strategy> s2 = strategies.at(num2).strategy;
    std::shared_ptr<Strategy> s3 = strategies.at(num3).strategy;

    Decision d1 = s1->Decide();
    Decision d2 = s2->Decide();
    Decision d3 = s3->Decide();

    s1->AddEnemyDecision(d2, d3);
    s2->AddEnemyDecision(d1, d3);
    s3->AddEnemyDecision(d1, d2);

    auto scores = scoreMatrix.getScores(d1, d2, d3);

    strategies.at(num1).currentScore += std::get<0>(scores);
    strategies.at(num2).currentScore += std::get<1>(scores);
    strategies.at(num3).currentScore += std::get<2>(scores);

    strategies.at(num1).lastScore = std::get<0>(scores);
    strategies.at(num2).lastScore = std::get<1>(scores);
    strategies.at(num3).lastScore = std::get<2>(scores);

    strategies.at(num1).lastDecision = d1;
    strategies.at(num2).lastDecision = d2;
    strategies.at(num3).lastDecision = d3;
}

const std::vector<StrategyInfo> & Controller::getStrategies() const
{
    return strategies;
}
