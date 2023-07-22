#ifndef __PROXY_H__
#define __PROXY_H__

#include <iostream>
#include <memory>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Proxy */
namespace Proxy {

using Age = unsigned;

class CountyLaws {
 public:
  static constexpr Age GetMinAllowedAgeToDrinkAlcohol() { return 20; }
};

/* Interface */
class IDinner {
 public:
  virtual ~IDinner() noexcept = default;
  virtual void DrinkBeer() const = 0;
  virtual void EatRamen() const = 0;
};

/* Service */
class Dinner : public IDinner {
 public:
  void DrinkBeer() const override {
    std::cout << PrinterState::PlainText << "Someone's drinking beer\n";
  }

  void EatRamen() const override {
    std::cout << PrinterState::PlainText << "Someone's eating ramen\n";
  }
};

/* Proxy. It checks the visitor's age to make sure he is allowed to drink beer
 */
class ProxyDinner : public IDinner {
 public:
  explicit ProxyDinner(Age visitorAge) : m_age(visitorAge) {}

  void DrinkBeer() const override {
    if (isAllowedToDrinkAlcohol()) {
      m_beer->DrinkBeer();
    } else {
      std::cout << PrinterState::PlainText
                << "Drink beer failed: Sorry, you're too young\n";
    }
  }

  void EatRamen() const override { m_beer->EatRamen(); }

 private:
  bool isAllowedToDrinkAlcohol() const {
    return m_age >= m_minAgeToDrinkAlcohol;
  }

 private:
  const Age m_age;
  const Age m_minAgeToDrinkAlcohol =
      CountyLaws::GetMinAllowedAgeToDrinkAlcohol();
  std::unique_ptr<IDinner> m_beer = std::make_unique<Dinner>();
};

/* Proxy Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Proxy") {}

 private:
  void BusinessLogic() const final {
    const Age myAge = 29;
    const Age schoolboyAge = CountyLaws::GetMinAllowedAgeToDrinkAlcohol() - 3;

    std::cout << PrinterState::Quote
              << "I'm going to have dinner: ramen and beer. "
              << "In this country you can drink alcohol from the age of "
              << CountyLaws::GetMinAllowedAgeToDrinkAlcohol() << ". I'm "
              << myAge << ".\n";

    std::unique_ptr<IDinner> dinner = std::make_unique<ProxyDinner>(myAge);
    dinner->DrinkBeer();
    dinner->EatRamen();

    std::cout << PrinterState::Quote
              << "A schoolboy entered the restaurant. He's " << schoolboyAge
              << ". "
              << "He is not allowed to drink beer.\n";

    dinner = std::make_unique<ProxyDinner>(schoolboyAge);
    dinner->DrinkBeer();
    dinner->EatRamen();
  }
};

}  // namespace Proxy

#endif /* __PROXY_H__ */
