#ifndef __STATE_H__
#define __STATE_H__

#include <iostream>
#include <string>
#include <memory>

#include "../../iPattern.h"

/* GoF design pattern: State */
namespace State {

class Context;

/* State Interface */
class IState {
public:
    virtual ~IState() {}
    virtual void Cook(Context& context) = 0;
};

/* Context */
class Context {
public:
    explicit Context(std::unique_ptr<IState> state) {
        SetState(std::move(state));
    }

    /* Update the state */
    void SetState(std::unique_ptr<IState> state) {
        PrintNewState(*state);
        m_state = std::move(state);
    }

    /* Do something useful */
    void MakeOrder() {
        m_state->Cook(*this);
    }

private:
    void PrintNewState(const IState& state) const {
        std::cout <<
            PrinterState::Quote <<
            "New context state: " << typeid(state).name() << ".\n";
    }

    std::unique_ptr<IState> m_state;
};

/* State 1: Ramen */
class StateRamen : public IState {
public:
    void Cook(Context& context) override;

    static int GetBonusGyozaThreshold() {
        /* free gyoza after each every ramen 3 orders */
        return 3;
    }

private:
    static int m_ramenCounter;
};

int StateRamen::m_ramenCounter = 0;

/* State 2: Bonus Gyoza */
class StateBonusGyoza : public IState {
public:
    void Cook(Context& context) override;
};

void StateBonusGyoza::Cook(Context& context) {
    /* cook */
    std::cout << PrinterState::PlainText << "Gyoza: Cooking bonus gyoza\n";

    /* and then restore the previous state */
    std::cout << PrinterState::PlainText << "Gyoza: restore the previous state\n";
    context.SetState(std::make_unique<StateRamen>());
}

void StateRamen::Cook(Context& context) {
    std::cout << PrinterState::PlainText << "Ramen: Cooking ramen\n";

    /* cook free gyoza after every X orders */
    if (0 == (++m_ramenCounter) % GetBonusGyozaThreshold()) {
        context.SetState(std::make_unique<StateBonusGyoza>());
        context.MakeOrder();
    }
}

/* State */
class Pattern : public IPattern {
public:
    Pattern() : IPattern("State") {}

private:
    void BusinessLogic() final {
        std::cout <<
            PrinterState::Quote <<
            "There is a promo in our restaurant. " <<
            "We give you free gyoza after every " <<
            StateRamen::GetBonusGyozaThreshold() <<
            " ramen orders\n";

        /* create the context, the default state is Ramen */
        std::unique_ptr<Context> restaurant =
            std::make_unique<Context>(std::make_unique<StateRamen>());

        for (int i = 1; i <= StateRamen::GetBonusGyozaThreshold() + 1; ++i) {
            std::cout << PrinterState::PlainText << "order " << i << ": ";
            restaurant->MakeOrder();
        }
    }
};

} /* namespace */

#endif /* __STATE_H__*/
