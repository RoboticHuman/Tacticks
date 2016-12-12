#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include <utility>

#pragma once

///
/// @defgroup navlib Navigation Libraries
/// @brief Libraries that extract meaningful data from raw meshes or other navigation libraries
///

/**
 * @brief      A container that manages all instances of a particular Navigation Library type
 */
template <typename NavLibType>
class NavLibContainer{
    /**
     * @brief      A container that manages all instances of a particular Navigation Library type
     */
    static std::vector< std::weak_ptr<NavLibType> > navLibCache;
public:
    /**
     * @brief      Gets a Navigation Library created with the passed parameters
     * @details    Returns a smart pointer to a newly created Navigation Library or to an existing one if a Navigation Library with similar specifications already exists
     */
    template <typename ...argTypes>
    static std::shared_ptr<NavLibType> getNavigationLibrary (argTypes... args);
};


template <typename NavLibType>
std::vector< std::weak_ptr<NavLibType> > NavLibContainer<NavLibType>::navLibCache;

template <typename NavLibType>
template <typename ...argTypes>
std::shared_ptr<NavLibType> NavLibContainer<NavLibType>::getNavigationLibrary (argTypes... args)
{
    // Check if there exists a previously constructed Navigation Library similar to the one the user wants to create
    for (int i=0; i<navLibCache.size();){
        
        if (!navLibCache[i].expired()) {
            if (navLibCache[i].lock()->constructedWithSameParams(args...))
                return navLibCache[i].lock();
            i++;
        }
        else {
            std::iter_swap(navLibCache.begin()+i, navLibCache.end() - 1);
            navLibCache.pop_back();
        }
    }
    
    std::shared_ptr<NavLibType> temp = std::make_shared<NavLibType>(args...);
    
    // Create a new Navigtion Library and store it otherwise
    navLibCache.push_back(temp);
    
    return temp;
    
}