#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../../iPattern.h"

/* GoF design pattern: Bridge */

/*
 *         A
 *      /     \                    A         N
 *     Aa      Ab       ===>    /     \     / \
 *    / \     /  \            Aa(N) Ab(N)  1   2
 *  Aa1 Aa2  Ab1 Ab2
 */

namespace Bridge {

/* Implementation */
class INoodles {
 public:
  virtual ~INoodles() {}
  virtual std::string EatNoodles() const = 0;
};

/* Contrete Implementation 1 */
class Ramen : public INoodles {
 public:
  std::string EatNoodles() const override { return "Ramen noodles"; }
};

/* Contrete Implementation 2 */
class Udon : public INoodles {
 public:
  std::string EatNoodles() const override { return "Udon noodles"; }
};

/* Abstraction */
class IMeal {
 public:
  explicit IMeal(std::unique_ptr<INoodles> noodles)
      : m_noodles(std::move(noodles)) {}

  virtual ~IMeal() {}
  virtual void Eat() const = 0;

 protected:
  std::unique_ptr<INoodles> m_noodles;
};

/* Concrete Abstraction 1 */
class Lunch : public IMeal {
 public:
  explicit Lunch(std::unique_ptr<INoodles> noodles)
      : IMeal(std::move(noodles)) {}

  void Eat() const override {
    std::cout << PrinterState::PlainText << "It's lunchtime. "
              << "I'm eating " << this->m_noodles->EatNoodles() << ".\n";
  }
};

/* Conctrete Abstraction 2 (extended) */
class Dinner : public IMeal {
 public:
  explicit Dinner(std::unique_ptr<INoodles> noodles)
      : IMeal(std::move(noodles)) {}

  void Eat() const override {
    std::cout << PrinterState::PlainText << "It's dinnertime. "
              << "I'm eating " << this->m_noodles->EatNoodles() << " and "
              << "drinking beer =)\n";
  }
};

/* Bridge Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Bridge") {}

 private:
  using MealVector = std::vector<std::unique_ptr<IMeal>>;
  using Iterator = MealVector::const_iterator;

  void BusinessLogic() final {
    /* create meals */
    MealVector meals;
    meals.push_back(std::make_unique<Lunch>(std::make_unique<Udon>()));
    meals.push_back(std::make_unique<Lunch>(std::make_unique<Ramen>()));
    meals.push_back(std::make_unique<Dinner>(std::make_unique<Udon>()));
    meals.push_back(std::make_unique<Dinner>(std::make_unique<Ramen>()));

    /* eat */
    HaveMeal(meals.begin(), meals.end());
  };

  /* eat meals */
  static void HaveMeal(Iterator first, Iterator last) {
    while (first != last) {
      first->get()->Eat();
      first = std::next(first);
    }
  }
};

}  // namespace Bridge

#endif /* __BRIDGE_H__ */
