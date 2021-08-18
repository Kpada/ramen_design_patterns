#include <iostream>
#include <memory>
#include <exception>
#include <vector>

#include "printer.h"
#include "patterns/iPattern.h"
#include "patterns/creational/factory_method/factoryMethod.h"
#include "patterns/creational/abstract_factory/abstractFactory.h"
#include "patterns/creational/builder/builder.h"
#include "patterns/creational/prototype/prototype.h"
#include "patterns/creational/singleton/singleton.h"
#include "patterns/structural/adapter/adapter.h"
#include "patterns/structural/bridge/bridge.h"
#include "patterns/structural/decorator/decorator.h"
#include "patterns/structural/facade/facade.h"
#include "patterns/structural/proxy/proxy.h"
#include "patterns/structural/flyweight/flyweight.h"
#include "patterns/structural/composite/composite.h"

static void execute() {
    std::vector<std::unique_ptr<IPattern>> patterns;

    /* creational */
    patterns.push_back(std::make_unique<FactoryMethod::Pattern>());
    patterns.push_back(std::make_unique<AbtractFactory::Pattern>());
    patterns.push_back(std::make_unique<Builder::Pattern>());
    patterns.push_back(std::make_unique<Prototype::Pattern>());
    patterns.push_back(std::make_unique<Singleton::Pattern>());
    /* structural */
    patterns.push_back(std::make_unique<Adapter::Pattern>());
    patterns.push_back(std::make_unique<Bridge::Pattern>());
    patterns.push_back(std::make_unique<Decorator::Pattern>());
    patterns.push_back(std::make_unique<Facade::Pattern>());
    patterns.push_back(std::make_unique<Proxy::Pattern>());
    patterns.push_back(std::make_unique<Flyweight::Pattern>());
    patterns.push_back(std::make_unique<Composite::Pattern>());

    for (const auto& item : patterns) {
        item->Execute();
    }
}

int main() {
    try {
        execute();
    } catch (std::exception& ex) {
        std::cout << std::endl << ex.what() << std::endl;
    }
    return 0;
}
