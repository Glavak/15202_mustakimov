//
// Created by glavak on 14.10.16.
//

#ifndef STARCRAFT_FACTORY_H
#define STARCRAFT_FACTORY_H

#include <string>
#include <unordered_map>
#include "Strategy.h"

template <class T>
class DefaultErrorPolicy
{
public:
    static T* HandleError()
    {

    }
};

template <class Tproduct, class Tid>
class Factory
{
public:
    typedef Tproduct * (* creator_t)();

    static Factory * getInstance()
    {
        static Factory<Tproduct, Tid> f;
        return &f;
    }

    Tproduct * create(const Tid & id)
    {
        auto iter= creators.find(id);
        if(creators.end() == iter)
        {
            throw "No such id";
            //return ErrorPolicy::HandleError();
        }
        return (*iter).second();
    }

    bool reg(const Tid & id, const creator_t & creator)
    {
        creators[id] = creator;
        return true;
    }

    Factory(const Factory &) = delete;

    Factory & operator=(const Factory &) = delete;

private:
    Factory()
    {}

    std::unordered_map<Tid, creator_t> creators;
};

#endif //STARCRAFT_FACTORY_H
