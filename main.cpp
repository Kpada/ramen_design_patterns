/// @file main.cpp
/// @brief Demonstrates various design patterns in C++. This file includes main
/// functions to execute Creational, Structural, and Behavioral patterns.

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "patterns/iPattern.h"
#include "printer.h"

// Includes for various design patterns
#include "patterns/behavioral/chain_of_responsibility/chainOfResponsibility.h"
#include "patterns/behavioral/command/command.h"
#include "patterns/behavioral/mediator/mediator.h"
#include "patterns/behavioral/memento/memento.h"
#include "patterns/behavioral/observer/observer.h"
#include "patterns/behavioral/state/state.h"
#include "patterns/behavioral/strategy/strategy.h"
#include "patterns/behavioral/template_method/templateMetod.h"
#include "patterns/behavioral/visitor/visitor.h"
#include "patterns/creational/abstract_factory/abstractFactory.h"
#include "patterns/creational/builder/builder.h"
#include "patterns/creational/factory_method/factoryMethod.h"
#include "patterns/creational/prototype/prototype.h"
#include "patterns/creational/singleton/singleton.h"
#include "patterns/structural/adapter/adapter.h"
#include "patterns/structural/bridge/bridge.h"
#include "patterns/structural/composite/composite.h"
#include "patterns/structural/decorator/decorator.h"
#include "patterns/structural/facade/facade.h"
#include "patterns/structural/flyweight/flyweight.h"
#include "patterns/structural/proxy/proxy.h"

namespace {

/// @brief Returns a collection of Creational Design Patterns.
/// @return Vector of unique pointers to Creational Design Patterns.
std::vector<std::unique_ptr<IPattern>> GetCreational() {
  std::vector<std::unique_ptr<IPattern>> patterns;

  patterns.push_back(std::make_unique<FactoryMethod::Pattern>());
  patterns.push_back(std::make_unique<AbstractFactory::Pattern>());
  patterns.push_back(std::make_unique<Builder::Pattern>());
  patterns.push_back(std::make_unique<Prototype::Pattern>());
  patterns.push_back(std::make_unique<Singleton::Pattern>());

  return patterns;
}

/// @brief Returns a collection of Structural Design Patterns.
/// @return Vector of unique pointers to Structural Design Patterns.
std::vector<std::unique_ptr<IPattern>> GetStructural() {
  std::vector<std::unique_ptr<IPattern>> patterns;

  patterns.push_back(std::make_unique<Adapter::Pattern>());
  patterns.push_back(std::make_unique<Bridge::Pattern>());
  patterns.push_back(std::make_unique<Decorator::Pattern>());
  patterns.push_back(std::make_unique<Facade::Pattern>());
  patterns.push_back(std::make_unique<Proxy::Pattern>());
  patterns.push_back(std::make_unique<Flyweight::Pattern>());
  patterns.push_back(std::make_unique<Composite::Pattern>());

  return patterns;
}

/// @brief Returns a collection of Behavioral Design Patterns.
/// @return Vector of unique pointers to Behavioral Design Patterns.
std::vector<std::unique_ptr<IPattern>> GetBehavioral() {
  std::vector<std::unique_ptr<IPattern>> patterns;

  patterns.push_back(std::make_unique<ChainOfResponsibility::Pattern>());
  patterns.push_back(std::make_unique<Command::Pattern>());
  patterns.push_back(std::make_unique<Mediator::Pattern>());
  patterns.push_back(std::make_unique<Memento::Pattern>());
  patterns.push_back(std::make_unique<State::Pattern>());
  patterns.push_back(std::make_unique<Strategy::Pattern>());
  patterns.push_back(std::make_unique<TemplateMethod::Pattern>());
  patterns.push_back(std::make_unique<Visitor::Pattern>());
  patterns.push_back(std::make_unique<Observer::Pattern>());

  return patterns;
}

/// @brief Executes each design pattern demonstration.
void Execute() {
  for (auto& item : GetCreational()) {
    item->Execute();
  }
  for (auto& item : GetStructural()) {
    item->Execute();
  }
  for (auto& item : GetBehavioral()) {
    item->Execute();
  }
}

}  // namespace

/// @brief The main entry point for the program.
/// @return Returns zero on success, non-zero on failure.
int main() {
  try {
    Execute();
  } catch (const std::exception& ex) {
    std::cout << std::endl << ex.what() << std::endl;
    return 1;
  } catch (...) {
    std::cout << std::endl << "Unknown exception" << std::endl;
    return 2;
  }

  return 0;
}
