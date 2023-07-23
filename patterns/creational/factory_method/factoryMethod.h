#ifndef PATTERNS_CREATIONAL_FACTORY_METHOD_FACTORYMETHOD_H_
#define PATTERNS_CREATIONAL_FACTORY_METHOD_FACTORYMETHOD_H_

#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <utility>

#include "../../iPattern.h"

// GoF design pattern: Factory method
namespace FactoryMethod {

// Food interface
class IFood {
 public:
  virtual ~IFood() = default;
  virtual void Eat() const noexcept = 0;

 protected:
  void SetUpText() const noexcept { std::cout << PrinterState::PlainText; }
};

// Concrete food 1
class Ramen : public IFood {
 public:
  void Eat() const noexcept override {
    SetUpText();
    std::cout << "This is Ramen!\n";
  }
};

// Concrete food 2
class Sushi : public IFood {
 public:
  void Eat() const noexcept override {
    SetUpText();
    std::cout << "This is Sushi!\n";
  }
};

// Concrete food 3
class Curry : public IFood {
 public:
  void Eat() const noexcept override {
    SetUpText();
    std::cout << "This is Curry!\n";
  }
};

// Creator
class IRestaurant {
 public:
  virtual ~IRestaurant() = default;

  // Creator may have some logic
  void HaveDinner() const {
    std::unique_ptr<IFood> food = FactoryMethod();
    food->Eat();
  }

 private:
  virtual std::unique_ptr<IFood> FactoryMethod() const = 0;
};

// Concrete Creator 1
class RamenRestaurant : public IRestaurant {
 private:
  std::unique_ptr<IFood> FactoryMethod() const override {
    return std::make_unique<Ramen>();
  }
};

// Concrete Creator 2
class SushiRestaurant : public IRestaurant {
 private:
  std::unique_ptr<IFood> FactoryMethod() const override {
    return std::make_unique<Sushi>();
  }
};

// Concrete Creator 3
class IndianRestaurant : public IRestaurant {
 private:
  std::unique_ptr<IFood> FactoryMethod() const override {
    return std::make_unique<Curry>();
  }
};

// Factory Method Pattern
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Factory Method") {}

 private:
  void BusinessLogic() const final {
    std::cout
        << PrinterState::PlainText
        << "It's dinner time. I'm so hungry. I don't know what exactly "
        << "I want to eat. I'm just going to visit the nearest restaurant "
        << "and order their best meal.\n";

    // get a random restaurant
    std::unique_ptr<IRestaurant> restaurant = GetRandomRestaurant();

    // and visit it
    VisitRestaurant(*restaurant);
  }

 private:
  void VisitRestaurant(const IRestaurant& restaurant) const {
    std::cout << PrinterState::Quote
              << "[Me] Hello. I don't know what type of restaurant this is. "
              << "I don't know what dishes you serve. Give me your best meal, "
              << "please.\n";

    restaurant.HaveDinner();

    std::cout << PrinterState::Quote
              << "[Me] That was very tasty. Thank you.\n";
  }

  // Returns a random factory (restaurant)
  std::unique_ptr<IRestaurant> GetRandomRestaurant() const {
    static constexpr int numOfRestaurants{3};

    std::random_device rd;
    const int idx = rd() % numOfRestaurants;

    switch (idx) {
      case 0:
        return std::make_unique<RamenRestaurant>();
      case 1:
        return std::make_unique<SushiRestaurant>();
      case 2:
        return std::make_unique<IndianRestaurant>();
      default:
        throw std::runtime_error("Unsupported fabric index");
    }
  }
};

}  // namespace FactoryMethod

#endif  // PATTERNS_CREATIONAL_FACTORY_METHOD_FACTORYMETHOD_H_
