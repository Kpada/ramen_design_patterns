#ifndef PATTERNS_IPATTERN_H_
#define PATTERNS_IPATTERN_H_

/// @file iPattern.h
/// @brief File containing the IPattern interface for design patterns.
///
/// This file defines the @c IPattern interface, which serves as a base class
/// for all design patterns in this project. It establishes the fundamental
/// structure and required methods for design pattern implementation.

#include <iostream>
#include <string>
#include <utility>

#include "../printer.h"

/// @brief Interface for design patterns.
///
/// Represents a generic interface for design patterns. All concrete design
/// patterns should inherit from this class and implement the required business
/// logic.
class IPattern {
 public:
  /// @brief Deleted copy constructor to ensure unique instances.
  IPattern(const IPattern&) = delete;

  /// @brief Deleted copy assignment operator to prevent assignment.
  IPattern& operator=(const IPattern&) = delete;

  /// @brief Deleted move constructor to ensure unique instances.
  IPattern(IPattern&&) = delete;

  /// @brief Deleted move assignment operator to prevent assignment.
  IPattern& operator=(IPattern&&) = delete;

  /// @brief Virtual destructor to ensure correct derived class destruction.
  virtual ~IPattern() noexcept = default;

  /// @brief Executes the design pattern.
  ///
  /// Prints the name of the design pattern and executes its specific business
  /// logic.
  void Execute() const {
    std::cout << PrinterState::Title << m_patternName;
    BusinessLogic();
  }

 protected:
  /// @brief Constructs a new @c IPattern object.
  /// @param title Name of the design pattern.
  explicit IPattern(std::string title) : m_patternName(std::move(title)) {}

  /// @brief Represents the core business logic of the design pattern.
  ///
  /// Derived classes should override this method to provide the actual
  /// implementation for the design pattern.
  virtual void BusinessLogic() const = 0;

 private:
  /// @brief Name of the design pattern.
  const std::string m_patternName;
};

#endif  // PATTERNS_IPATTERN_H_
