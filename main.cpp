
#include <iostream>
#include <memory>
#include <exception>

#include "patterns/iPattern.h"
#include "patterns/creational/factory_method/factoryMethod.h"
#include "patterns/creational/abstract_factory/abstractFactory.h"
#include "patterns/creational/builder/builder.h"
#include "patterns/creational/prototype/prototype.h"
#include "patterns/creational/singleton/singleton.h"


static void execute() {
    /* Exetuce the concrete pattern */
    std::unique_ptr<IPattern> pattern = std::make_unique<Prototype::Pattern>();
    pattern->Execute();
}

int main() {
    try {
        execute();
    } catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
