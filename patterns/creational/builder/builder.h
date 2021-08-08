#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <cstdint>

#include "../../iPattern.h"

/* GoF design pattern: Builder */

namespace Builder {


enum class RamenType {
    Shoyu,
    Shio,
    Miso,
    Tonkotsu
};

enum class Pungency {
    Mild,
    Hot
};

struct Gyoza {
    std::uint8_t number;
};

std::ostream& operator << (std::ostream& os, RamenType type) {
    if (type == RamenType::Shoyu) {
        os << "Shoyu";
    } else if (type == RamenType::Shio) {
        os << "Shio";
    } else if (type == RamenType::Miso) {
        os << "Miso";
    } else if (type == RamenType::Tonkotsu) {
        os << "Tonkonsu";
    } else {
        throw std::runtime_error("");
    }

    return os;
}

std::ostream& operator << (std::ostream& os, Pungency type) {
    if (type == Pungency::Mild) {
        os << "Mild";
    } else if (type == Pungency::Hot) {
        os << "Hot";
    } else {
        throw std::runtime_error("");
    }

    return os;
}

std::ostream& operator << (std::ostream& os, const Gyoza& gyoza) {
    if (gyoza.number == 0) {
        os << "None";
    } else {
        os << std::to_string(gyoza.number);
    }

    return os;
}

/* This is a big class with a lot of possible constructor arguments */
class Ramen {
public:
    Ramen()
    {}

    Ramen& SetType(RamenType type) {
        m_type = type;
        return *this;
    }

    Ramen& SetPurgency(Pungency purgency) {
        m_purgency = purgency;
        return *this;
    }

    Ramen& SetBeverage(std::string beverage) {
        m_beverage = move(beverage);
        return *this;
    }

    Ramen& SetGyozaNumber(std::uint8_t gyoza) {
        m_gyoza.number = gyoza;
        return *this;
    }

    Ramen& SetWeight(std::uint16_t weight) {
        m_weight = weight;
        return *this;
    }

    Ramen& SetEuroFork(bool needFork) {
        m_europeanFork = needFork;
        return *this;
    }

    void Eat() const {
        std::cout << "This is my ramen:" << std::endl;
        std::cout <<
            "Type = " << m_type <<
            ", Weight = " << m_weight <<
            ", Purgency = " << m_purgency <<
            ", Beverage = " << (m_beverage.empty() ? "None" : m_beverage) <<
            ", Gyoza = "    << m_gyoza <<
            ", Fork = " << (m_europeanFork ? "Yes" : "No");
        std::cout << std::endl;
    }

private:
    RamenType m_type = RamenType::Shio;
    Pungency m_purgency = Pungency::Mild;
    std::string m_beverage;
    Gyoza m_gyoza{0};
    std::uint16_t m_weight = 500;
    bool m_europeanFork = false;
};

/* Builder Interface */
class IBuilder {
public:
    virtual ~IBuilder() {}

    Ramen GetRamen() {
        return ramen;
    }

    virtual void BuildRamenBase() = 0;
    virtual void BuildGyoza() = 0;
    virtual void BuildBeverage() = 0;

protected:
    Ramen ramen;
};

/* Conctere Builder 1 */
class BuildDefaultRamen : public IBuilder {
public:
    BuildDefaultRamen() : IBuilder() {}

    void BuildRamenBase() override {
        ramen.SetType(RamenType::Shio).
              SetWeight(500).
              SetPurgency(Pungency::Mild).
              SetEuroFork(false);
    }

    void BuildGyoza() override {
        ramen.SetGyozaNumber(0);
    }

    void BuildBeverage() override {
        ramen.SetBeverage("Water");
    }
};

/* Conctere Builder 2 */
class BuildEuropeanRamen : public BuildDefaultRamen {
public:
    BuildEuropeanRamen() : BuildDefaultRamen() {}

    void BuildRamenBase() override {
        BuildDefaultRamen::BuildRamenBase();
        ramen.SetEuroFork(true);
    }
};

/* Conctere Builder 3 */
class BuildBigTonkotsuRamenWithGyozaAndBeer : public IBuilder {
public:
    void BuildRamenBase() override {
        ramen.SetType(RamenType::Tonkotsu).
              SetWeight(1000).
              SetPurgency(Pungency::Hot).
              SetEuroFork(false);
    }

    void BuildGyoza() override {
        ramen.SetGyozaNumber(10);
    }

    void BuildBeverage() override {
        ramen.SetBeverage("Beer");
    }
};

/* Director */
class Waiter {
public:
    Waiter(std::unique_ptr<IBuilder> builder) {
        SetBuilder(move(builder));
    }

    void SetBuilder(std::unique_ptr<IBuilder> builder) {
        m_builder = move(builder);
    }

    Ramen MakeOrder() {
        m_builder->BuildRamenBase();
        m_builder->BuildGyoza();
        m_builder->BuildBeverage();
        return m_builder->GetRamen();
    }

private:
    std::unique_ptr<IBuilder> m_builder;
};

/* Builder Pattern */
class Pattern : public IPattern {
public:
    Pattern()
    : IPattern("Builder")
    {}

private:
    void BusinessLogic() final {
        std::cout <<
            "It's dinner time. I'm so hungry." <<
            "I'm going to visit my favorite ramen restaurant." << std::endl <<
            "They have so many possible options." << std::endl <<
            "Fortunately, I don't need to explain to the waiter what I want " <<
            "for each possible parameter." << std::endl <<
            "I can just use their menu." <<
            std::endl;

        std::cout <<
            std::endl <<
            "[Me] I want to have a big tonkotsu ramen with gyoza and beer." <<
            std::endl << std::endl;

        Waiter waiter(std::make_unique<BuildBigTonkotsuRamenWithGyozaAndBeer>());
        Ramen ramen = waiter.MakeOrder();
        ramen.Eat();
    }
};

} /* namespace */
