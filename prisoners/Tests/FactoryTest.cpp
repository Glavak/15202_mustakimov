//
// Created by glavak on 21.10.16.
//

#include <gtest/gtest.h>
#include "../Factory.h"
#include "../Strategies/Traitor.h"

Traitor * expected = new Traitor();

Strategy * testCreator()
{
    return expected;
}

TEST(FactoryTests, Test)
{
    Factory::getInstance()->reg("test", testCreator);

    auto actual = Factory::getInstance()->create("test");

    ASSERT_EQ(expected, actual);
}

