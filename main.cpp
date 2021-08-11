
#include <iostream>
#include <memory>
#include <exception>
#include <vector>

#include "patterns/iPattern.h"
#include "patterns/creational/factory_method/factoryMethod.h"
#include "patterns/creational/abstract_factory/abstractFactory.h"
#include "patterns/creational/builder/builder.h"
#include "patterns/creational/prototype/prototype.h"
#include "patterns/creational/singleton/singleton.h"


static void execute() {
    std::vector<std::unique_ptr<IPattern>> patterns;

    patterns.push_back(std::make_unique<FactoryMethod::Pattern>());
    patterns.push_back(std::make_unique<AbtractFactory::Pattern>());
    patterns.push_back(std::make_unique<Builder::Pattern>());
    patterns.push_back(std::make_unique<Prototype::Pattern>());
    patterns.push_back(std::make_unique<Singleton::Pattern>());

    for (const auto& item : patterns) {
        item->Execute();
    }
}

int main() {
    try {
        execute();
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
