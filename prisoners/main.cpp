#include <iostream>
#include <vector>
#include <string>
#include "Controller.h"

enum Modes
{
    Unset,
    Detailed,
    Fast,
    Tournament
};

struct Arguments
{
    std::vector<std::string> names;
    int steps = 1;
    Modes mode = Modes::Unset;
    std::string configDirectory = ".";
    std::string matrixFile = "";
};

int main(int argc, char * argv[])
{
    Arguments arguments;

    std::string modePrefix("--mode=");
    std::string stepsPrefix("--steps=");
    std::string configsPrefix("--configs=");
    std::string matrixPrefix("--matrix=");

    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);

        if (arg.compare(0, modePrefix.size(), modePrefix) == 0)
        {
            arg = arg.substr(modePrefix.size());
            if(arg.compare("detailed") == 0)
            {
                arguments.mode = Modes ::Detailed;
            }
            else if(arg.compare("fast") == 0)
            {
                arguments.mode = Modes ::Fast;
            }
            else if(arg.compare("tournament") == 0)
            {
                arguments.mode = Modes ::Tournament;
            }
        }
        else if (arg.compare(0, stepsPrefix.size(), stepsPrefix) == 0)
        {
            arg = arg.substr(stepsPrefix.size());
            arguments.steps = atoi(arg.c_str());
        }
        else if (arg.compare(0, matrixPrefix.size(), matrixPrefix) == 0)
        {
            arg = arg.substr(matrixPrefix.size());
            arguments.matrixFile = arg.c_str();
        }
        else
        {
            arguments.names.push_back(arg);
        }
    }

    if (arguments.mode == Modes::Unset)
    {
        if (arguments.names.size() == 3)
        {
            arguments.mode = Modes::Detailed;
        }
        else
        {
            arguments.mode = Modes::Tournament;
        }
    }

    ScoreMatrix matrix;
    if(arguments.matrixFile.compare("") != 0)
    {
        matrix.loadFromFile(arguments.matrixFile);
    }
    Controller controller(matrix, arguments.names);

    if(arguments.mode == Modes::Detailed)
    {
        std::string command;
        std::getline(std::cin, command);
        while (command.compare("quit") != 0)
        {
            if(command.compare("tick") == 0)
            {
                controller.tick(1);
                controller.printState();
            }
            else if(command.compare(0, 5, "tick ") == 0)
            {
                command = command.substr(5);
                controller.tick(atoi(command.c_str()));
                controller.printState();
            }
            std::getline(std::cin, command);
        }
    }
    else if(arguments.mode == Modes::Fast)
    {
        std::cout << "Last turn:" << std::endl;
        controller.tick(arguments.steps);
        controller.printState();
    }
    std::cout << std::endl;
    controller.printWinner();

    return 0;
}