#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
using namespace std;

#ifndef NavLibContainer_h
#define NavLibContainer_h


/**
 * @brief      A container that manages all instances of a particular Navigation Library type
 */
template <typename NavLibType>
class NavLibContainer{
    /**
     * @brief      A container that manages all instances of a particular Navigation Library type
     */
    static vector< shared_ptr<NavLibType> > navLibCache;
public:
    /**
     * @brief      Gets a Navigation Library created with the passed parameters
     * @details    Returns a smart pointer to a newly created Navigation Library or to an existing one if a Navigation Library with similar specifications already exists
     */
    template <typename ...argTypes>
    static shared_ptr<NavLibType> getNavigationLibrary (argTypes... args);
};


template <typename NavLibType>
vector< shared_ptr<NavLibType> > NavLibContainer<NavLibType>::navLibCache;

template <typename NavLibType>
template <typename ...argTypes>
shared_ptr<NavLibType> NavLibContainer<NavLibType>::getNavigationLibrary (argTypes... args)
{
    // Check if there exists a previously constructed Navigation Library similar to the one the user wants to create
    for (shared_ptr<NavLibType>& temp : navLibCache){
        if (temp->constructedWithSameParams(args...))
            return temp;
    }
    
    // Create a new Navigtion Library and store it otherwise
    navLibCache.push_back(make_shared<NavLibType>(args...));
    
    return navLibCache.back();
    
}

#endif