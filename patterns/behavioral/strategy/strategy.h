#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include <iostream>
#include <memory>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Strategy */
namespace Strategy {

class Context;

/* Strategy Interface */
class IStrategy {
 public:
  virtual ~IStrategy() {}
  virtual void Cook() const = 0;
};

/* Context */
class Context {
 public:
  explicit Context(std::unique_ptr<IStrategy> strategy) {
    SetStrategy(std::move(strategy));
  }

  /* update the strategy */
  void SetStrategy(std::unique_ptr<IStrategy> strategy) {
    PrintNewStrategy(*strategy);
    m_strategy = std::move(strategy);
  }

  /* do something useful */
  void MakeOrder() { m_strategy->Cook(); }

 private:
  void PrintNewStrategy(const IStrategy& strategy) const {
    std::cout << PrinterState::Quote
              << "The new context's strategy: " << typeid(strategy).name()
              << ".\n";
  }

  std::unique_ptr<IStrategy> m_strategy;
};

/* Strategy 1: Ramen */
class StrategyRamen : public IStrategy {
 public:
  void Cook() const override {
    std::cout << PrinterState::PlainText << "Cooking ramen\n";
  }
};

/* Strategy 2: Gyoza */
class StrategyGyoza : public IStrategy {
 public:
  void Cook() const override {
    std::cout << PrinterState::PlainText << "Cooking gyoza\n";
  }
};

/* Strategy Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Strategy") {}

 private:
  void BusinessLogic() final {
    std::cout << PrinterState::Quote
              << "Each dish has a different cooking strategy. "
              << "But there is only one way to order a dish.\n\n";

    /* create the context, the default state is Ramen */
    std::unique_ptr<Context> restaurant =
        std::make_unique<Context>(std::make_unique<StrategyRamen>());

    restaurant->MakeOrder();
    restaurant->SetStrategy(std::make_unique<StrategyGyoza>());
    restaurant->MakeOrder();
  }
};

}  // namespace Strategy

#endif /* __STRATEGY_H__ */
