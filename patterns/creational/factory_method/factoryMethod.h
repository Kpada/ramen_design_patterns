#pragma once

#include <iostream>
#include <memory>
#include <exception>

#include "../../iPattern.h"

/* GoF design pattern: Factory method */

namespace FactoryMethod {

/* Food interface */
class IFood {
public:
    virtual ~IFood() = default;
    virtual void Eat() const = 0;
};

/* Contrete food 1 */
class Ramen : public IFood {
public:
    void Eat() const override {
        std::cout << "This is Ramen!" << std::endl;
    }
};

/* Contrete food 2 */
class Sushi : public IFood {
public:
    void Eat() const override {
        std::cout << "This is Sushi!" << std::endl;
    }
};

/* Contrete food 3 */
class Curry : public IFood {
public:
    void Eat() const override {
        std::cout << "This is Curry!" << std::endl;
    }
};

/* Creator */
class IRestaurant {
public:
    virtual ~IRestaurant() = default;

    void HaveDinner() const {
        std::unique_ptr<IFood> food = CreateFood();
        food->Eat();
    }

private:
    virtual std::unique_ptr<IFood> CreateFood() const = 0;
};

/* Concrete Creator 1 */
class RamenRestaurant : public IRestaurant {
private:
    std::unique_ptr<IFood> CreateFood() const override {
        return std::make_unique<Ramen>();
    }
};

/* Concrete Creator 2 */
class SushiRestaurant : public IRestaurant {
private:
    std::unique_ptr<IFood> CreateFood() const override {
        return std::make_unique<Sushi>();
    }
};

/* Concrete Creator 3 */
class IndianRestaurant : public IRestaurant {
private:
    std::unique_ptr<IFood> CreateFood() const override {
        return std::make_unique<Curry>();
    }
};

/* Factory Method Pattern */
class Pattern : public IPattern {
public:
    Pattern()
    : IPattern("Factory Method")
    {}

private:
    void BusinessLogic() final {
        std::cout << 
            "It's dinner time. I'm so hungry. " <<
            "I don't know what exactly I want to eat. " <<
            "I'm just going to visit the closest restaurant and " <<
            "order their best meal." << std::endl << std::endl;

        std::unique_ptr<IRestaurant> restaurant;

        /* The closest restaurant today is a ramen restaurant */
        if (1) {
            restaurant = std::make_unique<RamenRestaurant>();
        }

        VisitRestaurant(move(restaurant));
    }

    void VisitRestaurant(std::unique_ptr<IRestaurant> restaurant) {
        if (!restaurant) {
            throw std::runtime_error("");
        }

        std::cout <<
            "[Me] Hello. I don't know that kind of restaurant is this. " <<
            "I don't know what dishes you have. " <<
            "So give me your best meal, please." << std::endl << std::endl;

        restaurant->HaveDinner();

        std::cout << std::endl << "[Me] It was very tasty. Thanks." << std::endl;
    }
};

} /* namespace */
