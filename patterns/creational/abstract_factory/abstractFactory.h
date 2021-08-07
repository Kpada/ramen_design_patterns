#pragma once

#include <iostream>
#include <memory>

#include "../../iPattern.h"


/* GoF design pattern: Abstract Facroty */

namespace AbtractFactory {

/* Beverage interface */
class IBeverage {
public:
    virtual ~IBeverage() {}
    virtual void Drink() const = 0;
};

/* Food interface */
class IFood {
public:
    virtual ~IFood() {}

    virtual void Eat() const = 0;

    virtual void EatAndDrink(const IBeverage& beverage) const {
        Eat();
        beverage.Drink();
    }
};

/* Concrete beverage 1: Beer */
class BeverageBeer : public IBeverage {
public:
    void Drink() const override {
        std::cout << "I'm drinking beer :)" << std::endl;
    }
};

/* Concrete beverage 2: Sake */
class BeverageSake : public IBeverage {
public:
    void Drink() const override {
        std::cout << "I'm drinking Sake :)" << std::endl;
    }
};

/* Concrete beverage 3: Coke */
class BeverageCoke : public IBeverage {
public:
    void Drink() const override {
        std::cout << "I'm drinking Coke" << std::endl;
    }
};

/* Concrete food 1: Ramen */
class FoodRamen : public IFood {
public:
    void Eat() const override {
        std::cout << "I'm eating Ramen" << std::endl;
    }
};

/* Concrete food 2: Sushi */
class FoodSushi : public IFood {
public:
    void Eat() const override {
        std::cout << "I'm eating Sushi" << std::endl;
    }
};

/* Concrete food 3: Chicken wings */
class FoodChickenWings : public IFood {
public:
    void Eat() const override {
        std::cout << "I'm eating Chicken Wings" << std::endl;
    }
};

/* Abstract factory */
class IAbstractFactory {
public:
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

    std::string GetName() const override {
        return "Ramen";
    }
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

    std::string GetName() const override {
        return "Sushi";
    }
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

    std::string GetName() const override {
        return "KFC";
    }
};


/* Abstract Factory Pattern */
class Pattern : public IPattern {
public:
    Pattern()
    : IPattern("Abstract Factory")
    {}

private:
    enum class Restaurant {
        Ramen,
        Sushi,
        KFC
    };

    void BusinessLogic() final {
        std::cout <<
            "It's dinner time. I'm so hungry. " <<
            "I don't know what exactly I want to eat. " <<
            "I'm just going to visit a restaurant and " <<
            "order their best meal." << std::endl << std::endl;

        /* I'm going to visit a ramen restaurant tonight */
        VisitRestaurant(Restaurant::Ramen);
    }

    void VisitRestaurant(Restaurant restaurant) {
        std::unique_ptr<IAbstractFactory> factory;

        /* create */
        switch (restaurant) {
        case Restaurant::Ramen:
            factory = std::make_unique<RamenRestaurant>();
            break;
        case Restaurant::Sushi:
            factory = std::make_unique<SushiRestaurant>();
            break;
        case Restaurant::KFC:
            factory = std::make_unique<KFCRestaurant>();
            break;
        default:
            throw std::runtime_error("");
            break;
        }

        std::cout <<
            "It seems I'm visiting a " << factory->GetName() <<
            " restaurant today." << std::endl << std::endl;
        std::cout <<
            "[Me] Hello. I'd like to order some food and a beverage." <<
            std::endl << std::endl;

        auto food = factory->CreateFood();
        auto beverage = factory->CreateBeverage();
        food->EatAndDrink(*beverage);

        std::cout << std::endl;
        std::cout <<
            "[Me] It was very tasty. Thanks." << std::endl;
    }
};

} /* namespace */
