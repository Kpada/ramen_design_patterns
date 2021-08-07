#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <thread>

#include "../../iPattern.h"


/* GoF design pattern: Singleton */

namespace Singleton {

/* Food */
class Food {
public:
    explicit Food(std::string name)
    : m_name(move(name)) {
        std::cout << " " << m_name << " created." << std::endl;
    }

    void Eat() {
        std::cout << "Someone is eating " << m_name << std::endl;
    }

private:
    const std::string m_name;
};

/* Singleton - a chef at a restaurant */
class Chef {
public:
    /* creates and returns the singleton */
    static Chef& GetInstance() {
        static Chef instance;
        return instance;
    }

    Food CookRamen() {
        return Food("ramen");
    }

    Food CookGyoza() {
        return Food("gyoza");
    }

    Food CookUdon() {
        return Food("udon");
    }

private:
    /* hide the constructor */
    Chef() {
        std::cout << " Chef created" << std::endl;
    }

    /* delete copy/move */
    Chef(const Chef&) = delete;
    Chef& operator=(const Chef&) = delete;
    Chef(Chef&&) = delete;
    Chef& operator=(Chef&&) = delete;
};

/* Singleton Pattern */
class Pattern : public IPattern {
public:
    Pattern()
    : IPattern("Singleton")
    {}

private:
    void BusinessLogic() final {
        std::cout <<
            "I'm visiting a ramen restaurant. " <<
            "There is only one chef working here." << std::endl <<
            "Regardless of the number of visitors, " <<
            "only this chef can prepare the order. He is a singleton." <<
            std::endl << std::endl;

        Chef& chef = Chef::GetInstance();

        {
            std::cout << "Visitor2 ordered ramen." << std::endl;
            Chef& chef2 = Chef::GetInstance();
            chef2.CookRamen().Eat();
        }

        std::cout << "Visitor1 ordered gyoza." << std::endl;
        chef.CookGyoza().Eat();

        std::cout << "Visitor3 ordered udon." << std::endl;
        Chef::GetInstance().CookUdon().Eat();

        std::cout << "I'm leaving the restaurant." << std::endl;
    }
};

} /* namespace */
