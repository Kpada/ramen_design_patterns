#ifndef __VISITOR_H__
#define __VISITOR_H__

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../../iPattern.h"

/* GoF design pattern: Visitor */
namespace Visitor {

class RamenRestaurant;
class SushiRestaurant;

/* Visitor interface.
 * We must declare a method for each component (double dispatch)
 */
class IVisitor {
 public:
  virtual ~IVisitor() noexcept = default;
  virtual void VisitRamenRestaurant(const RamenRestaurant&) const = 0;
  virtual void VisitSushiRestaurant(const SushiRestaurant&) const = 0;
};

/* Component interface
 * Here we must declare a method to accept a visitor
 */
class IComponent {
 public:
  virtual ~IComponent() noexcept = default;
  virtual void Accept(const IVisitor&) const = 0;
};

/* Concrete component 1: Ramen restaurant */
class RamenRestaurant : public IComponent {
 public:
  void Accept(const IVisitor& visitor) const override {
    visitor.VisitRamenRestaurant(*this);
  }

  int GetPriceRamen() const { return 1000; }

  int GetPriceBeer() const { return 500; }
};

/* Concrete component 2: Sushi restaurant */
class SushiRestaurant : public IComponent {
 public:
  void Accept(const IVisitor& visitor) const override {
    visitor.VisitSushiRestaurant(*this);
  }

  int GetPriceSushi() const { return 2000; }

  int GetPriceSake() const { return 800; }
};

/* Concrete visitors implement several version of the same algorithm
 * for each component.
 */

/* Concrete Visitor 1 */
class ThursdayVisitor : public IVisitor {
 public:
  void VisitRamenRestaurant(const RamenRestaurant& component) const override {
    Print("Ramen", component.GetPriceRamen());
  }

  void VisitSushiRestaurant(const SushiRestaurant& component) const override {
    Print("Sushi", component.GetPriceSushi());
  }

 private:
  void Print(const std::string& name, int price) const {
    std::cout << PrinterState::PlainText << "Today is Thursday. I'm visiting a "
              << name << " restaurant to dine without drinks. "
              << "The cost of the dinner = " << price << '\n';
  }
};

/* Concrete Visitor 2 */
class FridayVisitor : public IVisitor {
 public:
  void VisitRamenRestaurant(const RamenRestaurant& component) const override {
    Print("Ramen", component.GetPriceRamen() + component.GetPriceBeer());
  }

  void VisitSushiRestaurant(const SushiRestaurant& component) const override {
    Print("Sushi", component.GetPriceSushi() + component.GetPriceSake());
  }

 private:
  void Print(const std::string& name, int price) const {
    std::cout << PrinterState::PlainText << "Today is Friday. I'm visiting a "
              << name << " restaurant to dine with drinks. "
              << "The cost of the dinner = " << price << '\n';
  }
};

/* Visitor Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Visitor") {}

 private:
  void BusinessLogic() const final {
    std::cout << PrinterState::Quote
              << "Each restaurant visitor has his own food preferences. "
              << "For example, on Thursday I just want to have lunch, and "
              << "on Friday I also want to drink a little alcohol.\n\n";

    /* restaurants */
    std::vector<std::unique_ptr<IComponent>> components;
    components.push_back(std::make_unique<RamenRestaurant>());
    components.push_back(std::make_unique<SushiRestaurant>());

    /* visitors allow us to change the behavior of the components */
    std::unique_ptr<IVisitor> visitor1 = std::make_unique<ThursdayVisitor>();
    std::unique_ptr<IVisitor> visitor2 = std::make_unique<FridayVisitor>();

    VisitRestaurants(components, *visitor1);
    VisitRestaurants(components, *visitor2);
  }

  static void VisitRestaurants(
      const std::vector<std::unique_ptr<IComponent>>& components,
      const IVisitor& visitor) {
    for (const auto& comp : components) {
      comp->Accept(visitor);
    }
  }
};

}  // namespace Visitor

#endif /* __VISITOR_H__ */
