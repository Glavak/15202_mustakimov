//
// Created by glavak on 21.10.16.
//

#include <gtest/gtest.h>
#include "../Arguments.h"
#include "../ControllerFast.h"
#include "../ControllerDetailed.h"

TEST(GameTests, ArgumentsTest)
{
    char * a[6] = {(char *) "",
                   (char *) "--mode=fast",
                   (char *) "--steps=5",
                   (char *) "asd",
                   (char *) "asd",
                   (char *) "asd"};
    Arguments args(6, a);

    EXPECT_EQ(Modes::Fast, args.mode);
    EXPECT_EQ(5, args.steps);

    EXPECT_EQ(3, args.names.size());
    EXPECT_EQ("asd", args.names[0]);
}

TEST(GameTests, ControllerFast)
{
    ScoreMatrix m;
    std::vector<std::string> names;
    names.push_back("loyal");
    names.push_back("loyal");
    names.push_back("traitor");
    ControllerFast controllerFast(m, "", names, 2);

    controllerFast.doJob();

    auto infos = controllerFast.getStrategies();
    auto scores = m.getScores(Cooperate, Cooperate, Defect);

    EXPECT_EQ(3, infos.size());
    EXPECT_EQ(std::get<0>(scores) * 2, infos[0].currentScore);
    EXPECT_EQ(std::get<1>(scores) * 2, infos[1].currentScore);
    EXPECT_EQ(std::get<2>(scores) * 2, infos[2].currentScore);
}

TEST(GameTests, ControllerTournament)
{
    ScoreMatrix m;
    std::vector<std::string> names;
    names.push_back("loyal");
    names.push_back("loyal");
    names.push_back("traitor");
    names.push_back("traitor");
    ControllerFast controllerTournament(m, "", names, 1);

    controllerTournament.doJob();

    auto infos = controllerTournament.getStrategies();

    EXPECT_EQ(4, infos.size());
    EXPECT_EQ(2, infos[0].currentScore);
    EXPECT_EQ(2, infos[1].currentScore);
    EXPECT_EQ(5, infos[2].currentScore);
    EXPECT_EQ(0, infos[3].currentScore);
}

TEST(GameTests, ControllerDetailed)
{
    ScoreMatrix m;
    std::vector<std::string> names;
    names.push_back("loyal");
    names.push_back("loyal");
    names.push_back("traitor");
    ControllerDetailed controllerDetailed(m, "", names, 2);

    controllerDetailed.doJob();

    auto infos = controllerDetailed.getStrategies();
    auto scores = m.getScores(Cooperate, Cooperate, Defect);

    EXPECT_EQ(3, infos.size());
    EXPECT_EQ(std::get<0>(scores), infos[0].currentScore);
    EXPECT_EQ(std::get<1>(scores), infos[1].currentScore);
    EXPECT_EQ(std::get<2>(scores), infos[2].currentScore);
}