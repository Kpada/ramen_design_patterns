#ifndef PATTERNS_CREATIONAL_FACTORY_METHOD_FACTORYMETHOD_H_
#define PATTERNS_CREATIONAL_FACTORY_METHOD_FACTORYMETHOD_H_

/// @file factoryMethod.h
/// @brief Implements the Factory Method design pattern.

#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <utility>

#include "../../iPattern.h"

/// @namespace GoF design pattern: Factory Method
namespace FactoryMethod {

/// @class IFood
/// @brief Base interface for food items.
/// @note Represents a Food interface.
class IFood {
 public:
  /// @brief Virtual destructor for interface.
  virtual ~IFood() = default;

  /// @brief Defines how the food is consumed.
  virtual void Eat() const noexcept = 0;

 protected:
  /// @brief Sets up plain text for output display.
  void SetUpText() const noexcept { std::cout << PrinterState::PlainText; }
};

/// @class Ramen
/// @brief Represents a Ramen food item, derived from @c IFood.
/// @note Represents a Concrete food 1.
class Ramen : public IFood {
 public:
  /// @brief Consumes the Ramen, displaying a message.
  void Eat() const noexcept override {
    SetUpText();
    std::cout << "This is Ramen!\n";
  }
};

/// @class Sushi
/// @brief Represents a Sushi food item, derived from @c IFood.
/// @note Represents a Concrete food 2.
class Sushi : public IFood {
 public:
  /// @brief Consumes the Sushi, displaying a message.
  void Eat() const noexcept override {
    SetUpText();
    std::cout << "This is Sushi!\n";
  }
};

/// @class Curry
/// @brief Represents a Curry food item, derived from @c IFood.
/// @note Represents a Concrete food 3.
class Curry : public IFood {
 public:
  /// @brief Consumes the Curry, displaying a message.
  void Eat() const noexcept override {
    SetUpText();
    std::cout << "This is Curry!\n";
  }
};

/// @class IRestaurant
/// @brief Base interface for restaurant types. Acts as a creator in the
/// pattern.
/// @note Represents a Creator interface.
class IRestaurant {
 public:
  /// @brief Virtual destructor for interface.
  virtual ~IRestaurant() = default;

  /// @brief Simulates having a meal in the restaurant.
  /// @note Creator might contain some logic.
  void HaveDinner() const {
    std::unique_ptr<IFood> food = FactoryMethod();
    food->Eat();
  }

 private:
  /// @brief Factory method to produce a specific type of food.
  /// @return Unique pointer to an @c IFood object.
  virtual std::unique_ptr<IFood> FactoryMethod() const = 0;
};

/// @class RamenRestaurant
/// @brief Restaurant specializing in Ramen, derived from @c IRestaurant.
/// @note Represents a Concrete Creator 1.
class RamenRestaurant : public IRestaurant {
 private:
  /// @brief Produces a Ramen dish.
  std::unique_ptr<IFood> FactoryMethod() const override {
    return std::make_unique<Ramen>();
  }
};

/// @class SushiRestaurant
/// @brief Restaurant specializing in Sushi, derived from @c IRestaurant.
/// @note Represents a Concrete Creator 2.
class SushiRestaurant : public IRestaurant {
 private:
  /// @brief Produces a Sushi dish.
  std::unique_ptr<IFood> FactoryMethod() const override {
    return std::make_unique<Sushi>();
  }
};

/// @class IndianRestaurant
/// @brief Restaurant specializing in Curry, derived from @c IRestaurant.
/// @note Represents a Concrete Creator 3.
class IndianRestaurant : public IRestaurant {
 private:
  /// @brief Produces a Curry dish.
  std::unique_ptr<IFood> FactoryMethod() const override {
    return std::make_unique<Curry>();
  }
};

/// @class Pattern
/// @brief Factory Method Pattern demonstration.
class Pattern : public IPattern {
 public:
  /// @brief Constructor initializing the pattern name.
  Pattern() : IPattern("Factory Method") {}

 private:
  /// @brief Executes the business logic for the pattern.
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
  /// @brief Simulates a visit to a restaurant.
  /// @param restaurant Reference to the restaurant to visit.
  void VisitRestaurant(const IRestaurant& restaurant) const {
    std::cout << PrinterState::Quote
              << "[Me] Hello. I don't know what type of restaurant this is. "
              << "I don't know what dishes you serve. Give me your best meal, "
              << "please.\n";

    restaurant.HaveDinner();

    std::cout << PrinterState::Quote
              << "[Me] That was very tasty. Thank you.\n";
  }

  /// @brief Returns a random restaurant (factory).
  /// @return Unique pointer to a randomly selected @c IRestaurant object.
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
