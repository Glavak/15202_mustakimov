#include <iostream>
#include <vector>
#include <string>
#include "Controller.h"
#include "Arguments.h"


int main(int argc, char * argv[])
{
    Arguments arguments(argc, argv);
    srand((unsigned int) time(nullptr));

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
    if (arguments.matrixFile.compare("") != 0)
    {
        matrix.loadFromFile(arguments.matrixFile);
    }
    Controller controller(matrix, arguments.configDirectory, arguments.names);

    if (arguments.mode == Modes::Detailed)
    {
        std::string command;
        std::getline(std::cin, command);
        while (command.compare("quit") != 0)
        {
            if (command.compare("tick") == 0)
            {
                controller.tick(1);
                controller.printState();
            }
            else if (command.compare(0, 5, "tick ") == 0)
            {
                command = command.substr(5);
                controller.tick(atoi(command.c_str()));
                controller.printState();
            }
            std::getline(std::cin, command);
        }
    }
    else if (arguments.mode == Modes::Fast)
    {
        std::cout << "Last turn:" << std::endl;
        controller.tick(arguments.steps);
        controller.printState();
    }
    else if (arguments.mode == Modes::Tournament)
    {
        controller.tick(arguments.steps);
    }
    std::cout << std::endl;
    controller.printWinner();

    return 0;
}