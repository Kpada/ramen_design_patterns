#ifndef __SINGLETON_H__
#define __SINGLETON_H__

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
    explicit Food(std::string name) : m_name(move(name)) {
        std::cout << PrinterState::PlainText << m_name << " created\n";
    }

    void Eat() {
        std::cout <<
            PrinterState::PlainText << "Someone is eating " << m_name << '\n';
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
        std::cout << PrinterState::Quote << "Singleton Chef created!\n";
    }

    ~Chef() {
        std::cout << PrinterState::Quote << "Singleton Chef destroyed!\n";
    }

    /* delete copy / move */
    Chef(const Chef&) = delete;
    Chef& operator = (const Chef&) = delete;
    Chef(Chef&&) = delete;
    Chef& operator = (Chef&&) = delete;
};

/* Singleton Pattern */
class Pattern : public IPattern {
public:
    Pattern() : IPattern("Singleton") {}

private:
    void BusinessLogic() final {
        std::cout <<
            PrinterState::PlainText <<
            "I'm visiting a ramen restaurant. There is only one chef is " <<
            "working here. Regardless of the number of visitors, only this " <<
            "chef can prepare the order.\n" <<
            "He is a singleton.\n";

        Chef& chef1 = Chef::GetInstance();
        {
            std::cout << PrinterState::Quote << "Visitor2 is ordering ramen.\n";
            Chef& chef2 = Chef::GetInstance();
            chef2.CookRamen().Eat();
        }

        std::cout << PrinterState::Quote << "Visitor1 is ordering gyoza.\n";
        chef1.CookGyoza().Eat();

        std::cout << PrinterState::Quote << "Visitor3 is ordering udon.\n";
        Chef::GetInstance().CookUdon().Eat();
    }
};

} /* namespace */

#endif /* __SINGLETON_H__ */
