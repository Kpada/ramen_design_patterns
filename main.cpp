#include <exception>
#include <iostream>
#include <memory>
#include <vector>

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
#include "patterns/iPattern.h"
#include "patterns/structural/adapter/adapter.h"
#include "patterns/structural/bridge/bridge.h"
#include "patterns/structural/composite/composite.h"
#include "patterns/structural/decorator/decorator.h"
#include "patterns/structural/facade/facade.h"
#include "patterns/structural/flyweight/flyweight.h"
#include "patterns/structural/proxy/proxy.h"
#include "printer.h"

namespace {

void AddCreational(std::vector<std::unique_ptr<IPattern>>& patterns) {
  patterns.push_back(std::make_unique<FactoryMethod::Pattern>());
  patterns.push_back(std::make_unique<AbstractFactory::Pattern>());
  patterns.push_back(std::make_unique<Builder::Pattern>());
  patterns.push_back(std::make_unique<Prototype::Pattern>());
  patterns.push_back(std::make_unique<Singleton::Pattern>());
}

void AddStructural(std::vector<std::unique_ptr<IPattern>>& patterns) {
  patterns.push_back(std::make_unique<Adapter::Pattern>());
  patterns.push_back(std::make_unique<Bridge::Pattern>());
  patterns.push_back(std::make_unique<Decorator::Pattern>());
  patterns.push_back(std::make_unique<Facade::Pattern>());
  patterns.push_back(std::make_unique<Proxy::Pattern>());
  patterns.push_back(std::make_unique<Flyweight::Pattern>());
  patterns.push_back(std::make_unique<Composite::Pattern>());
}

void AddBehavioral(std::vector<std::unique_ptr<IPattern>>& patterns) {
  patterns.push_back(std::make_unique<ChainOfResponsibility::Pattern>());
  patterns.push_back(std::make_unique<Command::Pattern>());
  patterns.push_back(std::make_unique<Mediator::Pattern>());
  patterns.push_back(std::make_unique<Memento::Pattern>());
  patterns.push_back(std::make_unique<State::Pattern>());
  patterns.push_back(std::make_unique<Strategy::Pattern>());
  patterns.push_back(std::make_unique<TemplateMethod::Pattern>());
  patterns.push_back(std::make_unique<Visitor::Pattern>());
  patterns.push_back(std::make_unique<Observer::Pattern>());
}

void Execute() {
  std::vector<std::unique_ptr<IPattern>> patterns;

  AddCreational(patterns);
  AddStructural(patterns);
  AddBehavioral(patterns);

  for (const auto& item : patterns) {
    item->Execute();
  }
}

}  // namespace

int main() {
  try {
    Execute();
  } catch (const std::exception& ex) {
    std::cout << std::endl << ex.what() << std::endl;
  } catch (...) {
    std::cout << std::endl << "Unknown exception" << std::endl;
  }

  return 0;
}
