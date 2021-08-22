#ifndef __MEMENTO_H__
#define __MEMENTO_H__

#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <chrono>
#include <vector>
#include <thread>

#include "../../iPattern.h"

/* GoF design pattern: Memento */
namespace Memento {

/* Memento Interface */
class IMemento {
public:
    virtual ~IMemento() {}
    virtual std::string GetMeta() const = 0;
    virtual std::string GetDate() const = 0;
    virtual std::string GetState() const = 0;
};

/* Concrete memento: implements concrete data for its Originator
 * The constructor must be the only way to change the internal state
 */
class ConcreteMemento : public IMemento {
public:
    explicit ConcreteMemento(std::string state)
    : m_state(std::move(state))
    , m_date([] {
            /* get date / time */
            std::time_t now = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            std::string tmp(32, '\0');
            std::strftime(&tmp[0], tmp.size(), "%Y-%m-%d %H:%M:%S",
                          std::localtime(&now));
            return tmp;
    }())
    {}

    /* Originator uses this method to restore its state */
    std::string GetState() const override {
        return m_state;
    }

    /* Originator use these methods to display metadata */
    std::string GetMeta() const override {
        return m_date + " / " + m_state;
    }

    std::string GetDate() const override {
        return m_date;
    }

private:
    std::string m_state;
    std::string m_date;
};

/* Originator */
class Originator {
public:
    explicit Originator(std::string state) : m_state(std::move(state)) {
        std::cout <<
            PrinterState::PlainText <<
            "Originator's initial state = " << m_state << '\n';
    }

    /* Changes the current state */
    void AddIngridient(const std::string& ingredient) {
        m_state += ", " + ingredient;
        std::cout <<
            PrinterState::PlainText <<
            "Originator's new state: " << m_state << '\n';
    }

    /* Save the current state */
    std::unique_ptr<IMemento> Save() {
        return std::make_unique<ConcreteMemento>(m_state);
    }

    /* Restore the previous state */
    void Restore(std::unique_ptr<IMemento> memento) {
        m_state = memento->GetState();
        std::cout <<
            PrinterState::PlainText <<
            "Originator' state restored: " << m_state << '\n';
    }

    const std::string& GetState() const {
        return m_state;
    }

private:
    std::string m_state;
};


/* Caretaker */
class Caretaker {
public:
    explicit Caretaker(std::shared_ptr<Originator> originator)
    : m_originator(std::move(originator))
    {}

    void Backup() {
        std::cout <<
            PrinterState::PlainText <<
            "Caretaker: Saving Originator's state.\n";
        m_history.push_back(m_originator->Save());
    }

    void Undo() {
        if (m_history.empty()) {
            return;
        }

        std::unique_ptr<IMemento> memento = std::move(m_history.back());
        m_history.pop_back();
        std::cout <<
            PrinterState::PlainText <<
            "Caretaker is restoring the state from '" <<
            m_originator->GetState() <<
            "' to '" <<
            memento->GetState() << "'\n";

        m_originator->Restore(std::move(memento));
    }

    void PrintHistory() const {
        std::cout << PrinterState::PlainText << "Caretaker: List of snapshots\n";

        for (const auto& memento : m_history) {
            std::cout << PrinterState::PlainText << memento->GetMeta() << '\n';
        }
    }

private:
    std::vector<std::unique_ptr<IMemento>> m_history;
    std::shared_ptr<Originator> m_originator;
};

/* Memento */
class Pattern : public IPattern {
public:
    Pattern() : IPattern("Memento") {}

private:
    void BusinessLogic() final {
        std::cout <<
            PrinterState::Quote <<
            "I'm a chef in a ramen restaurant. I want to make " <<
            "the best ramen. I will change the recipe and receive feedback " <<
            "from customers. If the customers are unhappy, we should be " <<
            "able to roll back the recipe to the last successful state.\n";

        /* ramen recipe. initial state is: soup, noodles */
        std::shared_ptr<Originator> ramenRecipe =
            std::make_shared<Originator>("soup, noodles");
        /* chef */
        std::unique_ptr<Caretaker> chef =
            std::make_unique<Caretaker>(ramenRecipe);

        /* wait for feeback */
        WaitForFeedback();
        /* our customers are happy, backup the initial recipe */
        chef->Backup();

        /* add an egg */
        AddNewIngredient(*ramenRecipe, "egg");
        /* our customers are happy, backup the recipe */
        std::cout <<
            PrinterState::Quote <<
            "I've added an egg to the recipe and sales went up\n";
        chef->Backup();

        /* add nori */
        AddNewIngredient(*ramenRecipe, "nori");
        /* our customers are happy, backup the recipe */
        std::cout <<
            PrinterState::Quote <<
            "I've added nori to the recipe and sales went up\n";
        chef->Backup();

        /* add bacon */
        AddNewIngredient(*ramenRecipe, "bacon");
        /* our customers don't like bacon, restore the last state */
        std::cout <<
            PrinterState::Quote <<
            "I've added bacon to the recipe and sales dropped. " <<
            "Let's restore the previous state.\n";

        chef->PrintHistory();
        chef->Undo();
    }

    static void AddNewIngredient(Originator& recipe,
                                 std::string item) {
        std::cout <<
            PrinterState::Quote << "Let's add " << item << "\n";
        recipe.AddIngridient(std::move(item));
        WaitForFeedback();
    }

    static void WaitForFeedback() {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1000ms);
    }
};

} /* namespace */

#endif /* __MEMENTO_H__*/
