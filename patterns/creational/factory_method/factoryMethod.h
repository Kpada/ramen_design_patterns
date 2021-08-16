#ifndef __FACTORY_METHOD_H__
#define __FACTORY_METHOD_H__

#include <iostream>
#include <memory>
#include <exception>
#include <random>

#include "../../iPattern.h"

/* GoF design pattern: Factory method */

namespace FactoryMethod {

/* Food interface */
class IFood {
public:
    virtual ~IFood() = default;
    virtual void Eat() const = 0;

protected:
    void SetUpText() const {
        std::cout << PrinterState::PlainText;
    }
};

/* Contrete food 1 */
class Ramen : public IFood {
public:
    void Eat() const override {
        SetUpText();
        std::cout << "This is Ramen!\n";
    }
};

/* Contrete food 2 */
class Sushi : public IFood {
public:
    void Eat() const override {
        SetUpText();
        std::cout << "This is Sushi!\n";
    }
};

/* Contrete food 3 */
class Curry : public IFood {
public:
    void Eat() const override {
        SetUpText();
        std::cout << "This is Curry!\n";
    }
};

/* Creator */
class IRestaurant {
public:
    virtual ~IRestaurant() = default;

    /* Creator may have some logic */
    void HaveDinner() const {
        std::unique_ptr<IFood> food = FactoryMethod();
        food->Eat();
    }

private:
    virtual std::unique_ptr<IFood> FactoryMethod() const = 0;
};

/* Concrete Creator 1 */
class RamenRestaurant : public IRestaurant {
private:
    std::unique_ptr<IFood> FactoryMethod() const override {
        return std::make_unique<Ramen>();
    }
};

/* Concrete Creator 2 */
class SushiRestaurant : public IRestaurant {
private:
    std::unique_ptr<IFood> FactoryMethod() const override {
        return std::make_unique<Sushi>();
    }
};

/* Concrete Creator 3 */
class IndianRestaurant : public IRestaurant {
private:
    std::unique_ptr<IFood> FactoryMethod() const override {
        return std::make_unique<Curry>();
    }
};

/* Factory Method Pattern */
class Pattern : public IPattern {
public:
    Pattern() : IPattern("Factory Method") {}

private:
    void BusinessLogic() final {
        std::cout <<
            PrinterState::PlainText <<
            "It's dinner time. I'm so hungry. I don't know what exactly " <<
            "I want to eat. I'm just going to visit the closest restaurant " <<
            "and order their best meal.\n";

        /* get a random restaurant */
        std::unique_ptr<IRestaurant> restaurant = GetRandomRestaurant();

        /* and visit it */
        VisitRestaurant(std::move(restaurant));
    }

private:
    void VisitRestaurant(std::unique_ptr<IRestaurant> restaurant) {
        if (!restaurant) {
            throw std::runtime_error("");
        }

        std::cout <<
            PrinterState::Quote <<
            "[Me] Hello. I don't know that kind of restaurant is this. " <<
            "I don't know what dishes you have. Give me your best meal, " <<
            "please.\n";

        restaurant->HaveDinner();

        std::cout <<
            PrinterState::Quote <<
            "[Me] It was very tasty. Thanks.\n";
    }

    /* Returns a random factory (restaurant) */
    std::unique_ptr<IRestaurant> GetRandomRestaurant() {
        const unsigned int numOfRestaurants = 3;

        std::random_device rd;
        const int idx = rd() % numOfRestaurants;

        switch (idx) {
        case 0:
            return std::make_unique<RamenRestaurant>();
            break;
        case 1:
            return std::make_unique<SushiRestaurant>();
            break;
        case 2:
            return std::make_unique<IndianRestaurant>();
            break;
        default:
            throw std::runtime_error("Unsupported fabric index");
            break;
        }
    }
};

} /* namespace */

#endif /* __FACTORY_METHOD_H__ */
