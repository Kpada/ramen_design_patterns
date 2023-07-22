#ifndef __ABSTRACT_FACTORY_H__
#define __ABSTRACT_FACTORY_H__

#include <iostream>
#include <memory>

#include "../../iPattern.h"

/* GoF design pattern: Abstract Facroty */
namespace AbtractFactory {

/* Beverage interface */
class IBeverage {
 public:
  virtual ~IBeverage() noexcept = default;
  void Drink() const {
    std::cout << PrinterState::PlainText;
    DrinkImplementation();
  }

 protected:
  virtual void DrinkImplementation() const = 0;
};

/* Food interface */
class IFood {
 public:
  virtual ~IFood() noexcept = default;

  void Eat() const {
    std::cout << PrinterState::PlainText;
    EatImplementation();
  }

  virtual void EatAndDrink(const IBeverage& beverage) const {
    Eat();
    beverage.Drink();
  }

 protected:
  virtual void EatImplementation() const = 0;
};

/* Concrete beverage 1: Beer */
class BeverageBeer : public IBeverage {
 protected:
  void DrinkImplementation() const override {
    std::cout << "I'm drinking Beer :)\n";
  }
};

/* Concrete beverage 2: Sake */
class BeverageSake : public IBeverage {
 public:
  void DrinkImplementation() const override {
    std::cout << "I'm drinking Sake :)\n";
  }
};

/* Concrete beverage 3: Coke */
class BeverageCoke : public IBeverage {
 public:
  void DrinkImplementation() const override {
    std::cout << "I'm drinking Coke :)\n";
  }
};

/* Concrete food 1: Ramen */
class FoodRamen : public IFood {
 protected:
  void EatImplementation() const override {
    std::cout << "I'm eating Ramen :)\n";
  }
};

/* Concrete food 2: Sushi */
class FoodSushi : public IFood {
 protected:
  void EatImplementation() const override {
    std::cout << "I'm eating Sushi :)\n";
  }
};

/* Concrete food 3: Chicken wings */
class FoodChickenWings : public IFood {
 protected:
  void EatImplementation() const override {
    std::cout << "I'm eating Chicken Wings :)\n";
  }
};

/* Abstract factory */
class IAbstractFactory {
 public:
  virtual ~IAbstractFactory() noexcept = default;
  virtual std::unique_ptr<IFood> CreateFood() const = 0;
  virtual std::unique_ptr<IBeverage> CreateBeverage() const = 0;
  virtual std::string GetName() const = 0;
};

/* Concrete Factory 1: Ramen Restaurant */
class RamenRestaurant : public IAbstractFactory {
 public:
  std::unique_ptr<IFood> CreateFood() const override {
    return std::make_unique<FoodRamen>();
  }

  std::unique_ptr<IBeverage> CreateBeverage() const override {
    return std::make_unique<BeverageBeer>();
  }

  std::string GetName() const override { return "Ramen"; }
};

/* Concrete Factory 2: Sushi Restaurant */
class SushiRestaurant : public IAbstractFactory {
 public:
  std::unique_ptr<IFood> CreateFood() const override {
    return std::make_unique<FoodSushi>();
  }

  std::unique_ptr<IBeverage> CreateBeverage() const override {
    return std::make_unique<BeverageSake>();
  }

  std::string GetName() const override { return "Sushi"; }
};

/* Concrete Factory 3: KFC */
class KFCRestaurant : public IAbstractFactory {
 public:
  std::unique_ptr<IFood> CreateFood() const override {
    return std::make_unique<FoodChickenWings>();
  }

  std::unique_ptr<IBeverage> CreateBeverage() const override {
    return std::make_unique<BeverageCoke>();
  }

  std::string GetName() const override { return "KFC"; }
};

/* Abstract Factory Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Abstract Factory") {}

 private:
  enum class Restaurant { Ramen, Sushi, KFC };

  void BusinessLogic() const final {
    std::cout << PrinterState::PlainText
              << "It's dinner time. I'm so hungry. I don't know what exactly "
              << "I want to eat. I'm just going to visit a restaurant and "
              << "order their best meal.\n";

    /* I'm going to visit a ramen restaurant tonight */
    VisitRestaurant(Restaurant::Ramen);
  }

  void VisitRestaurant(Restaurant restaurant) const {
    std::unique_ptr<IAbstractFactory> factory =
        GetRestaurantFactory(restaurant);

    std::cout << PrinterState::PlainText << "It seems I'm visiting a "
              << factory->GetName() << " restaurant today\n";

    std::cout << PrinterState::Quote
              << "[Me] Hello. I'd like to order some food and a beverage\n";

    auto food = factory->CreateFood();
    auto beverage = factory->CreateBeverage();
    food->EatAndDrink(*beverage);

    std::cout << PrinterState::Quote << "[Me] It was very tasty. Thanks\n";
  }

  /* Returns a factory */
  std::unique_ptr<IAbstractFactory> GetRestaurantFactory(
      Restaurant restaurant) const {
    switch (restaurant) {
      case Restaurant::Ramen:
        return std::make_unique<RamenRestaurant>();
        break;
      case Restaurant::Sushi:
        return std::make_unique<SushiRestaurant>();
        break;
      case Restaurant::KFC:
        return std::make_unique<KFCRestaurant>();
        break;
      default:
        throw std::runtime_error("Unsupported restaurant");
        break;
    }
  }
};

}  // namespace AbtractFactory

#endif /* __ABSTRACT_FACTORY_H__ */
