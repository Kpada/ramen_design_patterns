#ifndef PATTERNS_CREATIONAL_BUILDER_BUILDER_H_
#define PATTERNS_CREATIONAL_BUILDER_BUILDER_H_

/// @file builder.h
/// @brief Implements the Builder design pattern.

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../../iPattern.h"

/// @namespace GoF design pattern: Builder
namespace Builder {

/// @brief Enum class for different types of Ramen.
enum class RamenType {
  Shoyu,     ///< Soy sauce based ramen.
  Shio,      ///< Salt based ramen.
  Miso,      ///< Miso based ramen.
  Tonkotsu,  ///< Pork bone based ramen.
};

/// @brief Enum class for the level of spiciness of the Ramen.
enum class Pungency {
  Mild,  ///< Mild level of spiciness.
  Hot,   ///< Hot level of spiciness.
};

/// @brief Struct representing the number of Gyoza dumplings.
struct Gyoza {
  std::uint8_t number;  ///< Number of Gyoza dumplings.
};

/// @brief Stream operator for printing @c RamenType.
/// @param os Output stream.
/// @param type Type of Ramen.
/// @return Modified output stream.
std::ostream& operator<<(std::ostream& os, RamenType type) {
  switch (type) {
    case RamenType::Shoyu:
      os << "Shoyu";
      break;
    case RamenType::Shio:
      os << "Shio";
      break;
    case RamenType::Miso:
      os << "Miso";
      break;
    case RamenType::Tonkotsu:
      os << "Tonkotsu";
      break;
    default:
      throw std::runtime_error("Unsupported type");
  }
  return os;
}

/// @brief Stream operator for printing @c Pungency level.
/// @param os Output stream.
/// @param type Pungency level of the Ramen.
/// @return Modified output stream.
std::ostream& operator<<(std::ostream& os, Pungency type) {
  switch (type) {
    case Pungency::Mild:
      os << "Mild";
      break;
    case Pungency::Hot:
      os << "Hot";
      break;
    default:
      throw std::runtime_error("Unsupported type");
  }

  return os;
}

/// @brief Stream operator for printing @c Gyoza information.
/// @param os Output stream.
/// @param gyoza Gyoza object.
/// @return Modified output stream.
std::ostream& operator<<(std::ostream& os, const Gyoza& gyoza) {
  if (gyoza.number == 0) {
    os << "None";
  } else {
    os << std::to_string(gyoza.number);
  }

  return os;
}

/// @brief Class representing a Ramen dish.
/// This class demonstrates the Builder pattern for constructing complex
/// objects.
class Ramen {
 public:
  /// @brief Default constructor.
  Ramen() noexcept = default;

  /// @brief Sets the type of Ramen.
  /// @param type The Ramen type to be set.
  /// @return Reference to the modified Ramen object.
  Ramen& SetType(RamenType type) {
    m_type = type;
    return *this;
  }

  /// @brief Sets the pungency level of the Ramen.
  /// @param pungency The desired pungency level.
  /// @return Reference to the modified Ramen object.
  Ramen& SetPungency(Pungency pungency) {
    m_pungency = pungency;
    return *this;
  }

  /// @brief Sets the beverage accompanying the Ramen.
  /// @param beverage The name of the beverage.
  /// @return Reference to the modified Ramen object.
  Ramen& SetBeverage(std::string beverage) {
    m_beverage = std::move(beverage);
    return *this;
  }

  /// @brief Sets the number of Gyoza dumplings with the Ramen.
  /// @param gyoza_number Number of Gyoza dumplings.
  /// @return Reference to the modified Ramen object.
  Ramen& SetGyozaNumber(std::uint8_t gyoza_number) {
    m_gyoza.number = gyoza_number;
    return *this;
  }

  /// @brief Sets the weight of the Ramen dish.
  /// @param weight The weight of the Ramen in grams.
  /// @return Reference to the modified Ramen object.
  Ramen& SetWeight(std::uint16_t weight) {
    m_weight = weight;
    return *this;
  }

  /// @brief Determines if a European fork is needed with the Ramen.
  /// @param needFork 'true' if a fork is needed, 'false' otherwise.
  /// @return Reference to the modified Ramen object.
  Ramen& SetEuroFork(bool needFork) {
    m_europeanFork = needFork;
    return *this;
  }

  /// @brief Simulates eating the Ramen dish.
  /// Prints the details of the Ramen dish to the standard output.
  void Eat() const {
    std::cout << PrinterState::PlainText << "This is my ramen:\n"
              << "Type = " << m_type << ", Weight = " << m_weight
              << ", Pungency = " << m_pungency
              << ", Beverage = " << (m_beverage.empty() ? "None" : m_beverage)
              << ", Gyoza = " << m_gyoza
              << ", Fork = " << (m_europeanFork ? "Yes" : "No") << "\n";
  }

 private:
  RamenType m_type = RamenType::Shio;    ///< Type of Ramen.
  Pungency m_pungency = Pungency::Mild;  ///< Pungency level of the Ramen.
  std::string m_beverage;                ///< Accompanying beverage name.
  Gyoza m_gyoza{0};                      ///< Number of Gyoza dumplings.
  std::uint16_t m_weight{500};           ///< Weight of the Ramen dish in grams.
  bool m_europeanFork{false};  ///< Indicates if a European fork is needed.
};

/// @brief Builder Interface for creating Ramen dishes.
class IBuilder {
 public:
  /// @brief Virtual destructor.
  virtual ~IBuilder() noexcept = default;

  /// @brief Retrieves the constructed Ramen object.
  /// @return The constructed Ramen object.
  Ramen GetRamen() { return ramen; }

  /// @brief Pure virtual method to build the base of the Ramen.
  virtual void BuildRamenBase() = 0;

  /// @brief Pure virtual method to build Gyoza accompaniment.
  virtual void BuildGyoza() = 0;

  /// @brief Pure virtual method to build the beverage accompaniment.
  virtual void BuildBeverage() = 0;

 protected:
  Ramen ramen;  ///< The Ramen object being built.
};

/// @brief Concrete builder class for creating a default Ramen dish.
/// @note Concrete builder 1.
class BuildDefaultRamen : public IBuilder {
 public:
  /// @brief Constructor for BuildDefaultRamen.
  BuildDefaultRamen() : IBuilder() {}

  /// @brief Builds the base of the default Ramen.
  void BuildRamenBase() override {
    ramen.SetType(RamenType::Shio)
        .SetWeight(500)
        .SetPungency(Pungency::Mild)
        .SetEuroFork(false);
  }

  /// @brief Builds the default Gyoza accompaniment (none).
  void BuildGyoza() override { ramen.SetGyozaNumber(0); }

  /// @brief Builds the default beverage accompaniment (water).
  void BuildBeverage() override { ramen.SetBeverage("Water"); }
};

/// @brief Concrete builder class for creating a European-style Ramen dish.
/// @note Concrete builder 2.
class BuildEuropeanRamen : public BuildDefaultRamen {
 public:
  /// @brief Constructor for BuildEuropeanRamen.
  BuildEuropeanRamen() : BuildDefaultRamen() {}

  /// @brief Builds the base of the European Ramen with a fork.
  void BuildRamenBase() override {
    BuildDefaultRamen::BuildRamenBase();
    ramen.SetEuroFork(true);
  }
};

/// @brief Concrete builder class for creating a large Tonkotsu Ramen dish with
/// Gyoza and Beer.
/// @note Concrete builder 3.
class BuildBigTonkotsuRamenWithGyozaAndBeer : public IBuilder {
 public:
  /// @brief Builds the base of the Tonkotsu Ramen.
  void BuildRamenBase() override {
    ramen.SetType(RamenType::Tonkotsu)
        .SetWeight(1000)
        .SetPungency(Pungency::Hot)
        .SetEuroFork(false);
  }

  /// @brief Builds the Gyoza accompaniment (10 pieces).
  void BuildGyoza() override { ramen.SetGyozaNumber(10); }

  /// @brief Builds the beverage accompaniment (Beer).
  void BuildBeverage() override { ramen.SetBeverage("Beer"); }
};

/// @class Waiter
/// @brief Director class that directs the building process of Ramen dishes.
class Waiter {
 public:
  /// @brief Constructor for Waiter.
  /// @param builder The builder to be used by the Waiter.
  explicit Waiter(std::unique_ptr<IBuilder> builder) {
    SetBuilder(std::move(builder));
  }

  /// @brief Sets the builder to be used for creating Ramen.
  /// @param builder The builder to be set.
  void SetBuilder(std::unique_ptr<IBuilder> builder) {
    m_builder = std::move(builder);
  }

  /// @brief Makes an order for a Ramen dish using the builder.
  /// @return The ordered Ramen dish.
  Ramen MakeOrder() {
    m_builder->BuildRamenBase();
    m_builder->BuildGyoza();
    m_builder->BuildBeverage();
    return m_builder->GetRamen();
  }

 private:
  /// @brief The builder for creating the Ramen dish.
  std::unique_ptr<IBuilder> m_builder;
};

/// @brief Concrete pattern class implementing the Builder design pattern.
class Pattern : public IPattern {
 public:
  /// @brief Constructor initializing the pattern name.
  Pattern() : IPattern("Builder") {}

 private:
  /// @brief Contains the business logic for demonstrating the Builder pattern.
  /// Simulates a customer ordering at a ramen restaurant using various
  /// builders.
  void BusinessLogic() const final {
    std::cout
        << PrinterState::PlainText
        << "It's dinner time. I'm so hungry. I'm going to visit my favorite "
        << "ramen restaurant. They have so many possible options. "
        << "Fortunately, I don't need to explain to the waiter what I want "
        << "for each possible parameter. I can just use their menu.\n";

    std::cout
        << PrinterState::Quote
        << "[Me] I want to have a big tonkotsu ramen with gyoza and beer.\n";

    Waiter waiter(std::make_unique<BuildBigTonkotsuRamenWithGyozaAndBeer>());
    Ramen ramen = waiter.MakeOrder();
    ramen.Eat();
  }
};

}  // namespace Builder

#endif  // PATTERNS_CREATIONAL_BUILDER_BUILDER_H_
