#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <iomanip>
#include <cstdint>
#include <sstream>

#include "../../iPattern.h"

/* GoF design pattern: Prorotype */

namespace Prototype {

/* Helper */
enum class Person {
    Me,
    Friend,
    Waiter
};

/* Helper */
std::ostream& operator << (std::ostream& os, Person type) {
    if (type == Person::Me) {
        os << "[Me]";
    } else if (type == Person::Waiter) {
        os << "[Waiter]";
    } else if (type == Person::Friend) {
        os << "[FoM]";
    } else {
        throw std::runtime_error("");
    }

    return os;
}

/* Helper */
class Print {
public:
    static void Say(Person person, const std::string& text) {
        std::cout << person << " " << text << std::endl;
    }

    static void Say(const std::string& text) {
        std::cout << text << std::endl;
    }

    static void NewLine() {
        std::cout << std::endl;
    }
};


/* Food Interface */
class IFood {
public:
    IFood(std::string name)
    : m_name(move(name)) 
    {}

    virtual ~IFood() {}

    virtual std::unique_ptr<IFood> Clone() const = 0;

    virtual void Eat() = 0;

    const std::string& GetName() const {
        return m_name;
    }

protected:
    const std::string m_name;
};

/* Ramen */
class Ramen : public IFood {
public:
    Ramen(std::string name, std::uint16_t weight = 500, bool fork = false)
    : IFood(move(name))
    , m_weight(weight)
    , m_fork(fork) {
        std::cout << GetName() << " created." << GetInfo() << std::endl;
    }

    ~Ramen() {
        std::cout << GetName() << " destroyed." << GetInfo() << std::endl;
    }

    Ramen& AddFork(bool fork) {
        m_fork = fork;
        std::cout << GetName() <<
                     ": set fork = " << std::boolalpha << m_fork << std::endl;
        return *this;
    }

    void Eat() override {
        const std::uint16_t eatStep = 100;

        m_weight = m_weight > eatStep ? m_weight - eatStep : 0;
        std::cout << "Eating " << GetName() << ": " << GetInfo() << std::endl;
    }

    std::unique_ptr<IFood> Clone() const override {
        return std::make_unique<Ramen>(m_name, m_weight, m_fork);
    }

private:
    std::string GetInfo() {
        std::stringstream ss;

        ss << "Weight = " << m_weight << ", Fork = " << std::boolalpha << m_fork;
        return ss.str();
    }

private:
    std::uint16_t m_weight;
    bool m_fork;
};

/* Prototype Pattern */
class Pattern : public IPattern {
public:
    Pattern()
    : IPattern("Prototype")
    {}

private:
    void BusinessLogic() final {
        const std::string ramenName = "Miso Ramen";

        /* create */
        Print::Say(Person::Me, "Hi. I will have a Ramen.");
        Print::Say(Person::Waiter, "Sure. This is the best ramen in our city.");
        Ramen myRamen(ramenName);
        Print::NewLine();

        /* update */
        Print::Say(Person::Me, "I cannot use chopsticks. May I have a fork?");
        myRamen.AddFork(true);
        myRamen.Eat();
        Print::NewLine();

        /* clone */
        Print::Say("A friend of mine went to the restaurant...");
        Print::Say(Person::Friend, "Hi. What are you eating?");
        Print::Say(Person::Me, ramenName);
        Print::Say(Person::Friend, "Waiter, I'd like to have the same ramen.");

        auto friendsRamen = myRamen.Clone();
        Print::NewLine();

        Print::Say(Person::Friend, "Waiter, my bowl is not full.");
        Print::Say(Person::Waiter, "Yes. You asked for the same. This is the same.");
        Print::Say(Person::Friend, "o_O");
        Print::Say(Person::Me, "o_O");
    }
};

} /* namespace */
