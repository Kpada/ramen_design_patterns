#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include <iostream>
#include <string>
#include <memory>

#include "../../iPattern.h"


/* GoF design pattern: Adapter */
namespace Adapter {

/* Interface */
class IMealChopsticks {
public:
    virtual ~IMealChopsticks() {}
    virtual void Eat() const = 0;
    virtual void TakeChopsticks() = 0;

protected:
    bool m_gotUtensils = false;
};

/* Interface */
class IMealFork {
public:
    virtual ~IMealFork() {}
    virtual void Eat() const = 0;
    virtual void TakeFork() = 0;

protected:
    bool m_gotUtensils = false;
};

/* Ramen */
class Ramen : public IMealChopsticks {
public:
    void TakeChopsticks() override {
        m_gotUtensils = true;
        std::cout << PrinterState::PlainText << "Got utensils (chopsticks)\n";
    }

    void Eat() const override {
        if (m_gotUtensils) {
            std::cout << PrinterState::PlainText << "The ramen has been eaten\n";
        }
    }
};

/* Sausage */
class Sausage : public IMealFork {
public:
    void TakeFork() override {
        m_gotUtensils = true;
        std::cout << PrinterState::PlainText << "Got utensils (fork)\n";
    }

    void Eat() const override {
        if (m_gotUtensils) {
            std::cout << PrinterState::PlainText << "The sausage has been eaten\n";
        }
    }
};

/* Adapter */
class ForkToChopsticksAdapter : public IMealFork {
public:
    explicit ForkToChopsticksAdapter(std::shared_ptr<IMealChopsticks> meal)
    : m_chopsticksMeal(std::move(meal))
    {}

    void TakeFork() override {
        std::cout <<
            PrinterState::PlainText <<
            "Fork to Chopshicks adapter. Calling 'TakeChopsticks'.\n";

        m_chopsticksMeal->TakeChopsticks();
    }

    void Eat() const override {
        m_chopsticksMeal->Eat();
    }

private:
    std::shared_ptr<IMealChopsticks> m_chopsticksMeal;
};

/* Adapter Pattern */
class Pattern : public IPattern {
public:
    Pattern() : IPattern("Adapter") {}

private:
    void BusinessLogic() final {
        std::cout << PrinterState::Quote << "I'm going to eat a sausage using a fork\n";
        std::shared_ptr<IMealFork> sausage = std::make_shared<Sausage>();
        EatWithFork(sausage);

        std::cout << PrinterState::Quote << "I'm going to eat ramen using chopsticks\n";
        std::shared_ptr<IMealChopsticks> ramen = std::make_shared<Ramen>();
        EatWithChopsticks(ramen);

        std::cout << PrinterState::Quote << "I'm going to eat ramen using a fork\n";
        std::shared_ptr<IMealFork> adapter =
            std::make_shared<ForkToChopsticksAdapter>(ramen);
        EatWithFork(adapter);
    }

    static void EatWithFork(std::shared_ptr<IMealFork> mealFork) {
        mealFork->TakeFork();
        mealFork->Eat();
    }

    static void EatWithChopsticks(std::shared_ptr<IMealChopsticks> mealChopsticks) {
        mealChopsticks->TakeChopsticks();
        mealChopsticks->Eat();
    }
};

} /* namespace */

#endif /* __ADAPTER_H__ */
