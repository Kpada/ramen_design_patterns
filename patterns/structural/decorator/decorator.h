#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Decorator */
namespace Decorator {

/* Food interface */
class IFood {
 public:
  virtual ~IFood() {}

  virtual int GetPrice() const = 0;
  virtual std::string GetDescription() const = 0;
};

/* Simple Ramen */
class Ramen : public IFood {
 public:
  int GetPrice() const override { return 1000; }

  std::string GetDescription() const override { return "Ramen"; }
};

/* Decorator interface, contains a pointer to the IFood component */
class IDecorator : public IFood {
 public:
  explicit IDecorator(std::shared_ptr<IFood> component)
      : m_component(component) {}

  int GetPrice() const override { return this->getComponent().GetPrice(); }

  std::string GetDescription() const override {
    return this->getComponent().GetDescription();
  }

 protected:
  const IFood& getComponent() const { return *m_component; }

 private:
  std::shared_ptr<IFood> m_component;
};

/* Conctete decorator: Gyoza */
class DecoratorGyoza : public IDecorator {
 public:
  explicit DecoratorGyoza(std::shared_ptr<IFood> component)
      : IDecorator(component) {}

  int GetPrice() const override {
    return this->getComponent().GetPrice() + 500;
  }

  std::string GetDescription() const override {
    return this->getComponent().GetDescription() + " + Gyoza";
  }
};

/* Conctete decorator: Beer */
class DecoratorBeer : public IDecorator {
 public:
  explicit DecoratorBeer(std::shared_ptr<IFood> component)
      : IDecorator(component) {}

  int GetPrice() const override {
    return this->getComponent().GetPrice() + 350;
  }

  std::string GetDescription() const override {
    return this->getComponent().GetDescription() + " + Beer";
  }
};

/* Decorator Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Decorator") {}

 private:
  void BusinessLogic() final {
    /* create ramen with no decorators */
    std::shared_ptr<IFood> ramen = std::make_shared<Ramen>();

    /* add the 1st decorator: gyoza */
    std::shared_ptr<IFood> decRamenGyoza =
        std::make_shared<DecoratorGyoza>(ramen);

    /* add the 2nd decorator: beer */
    std::shared_ptr<IFood> decRamenGyozaBeer =
        std::make_shared<DecoratorBeer>(decRamenGyoza);

    /* and one more beer */
    std::shared_ptr<IFood> decRamenGyozaTwoBeers =
        std::make_shared<DecoratorBeer>(decRamenGyozaBeer);

    /* just ramen and beer */
    std::shared_ptr<IFood> decRamenBeer =
        std::make_shared<DecoratorBeer>(ramen);

    /* print */
    PrintFoodDescriptionAndPrice(ramen, "Just Ramen");
    PrintFoodDescriptionAndPrice(decRamenGyoza, "Added gyoza");
    PrintFoodDescriptionAndPrice(decRamenGyozaBeer, "Added Beer");
    PrintFoodDescriptionAndPrice(decRamenGyozaTwoBeers, "One beer more");
    PrintFoodDescriptionAndPrice(decRamenBeer, "Ramen & Beer");
  }

  void PrintFoodDescriptionAndPrice(std::shared_ptr<IFood> food,
                                    const std::string& title) {
    std::cout << PrinterState::PlainText << title << ": "
              << food->GetDescription() << ", price = " << food->GetPrice()
              << std::endl;
  }
};

}  // namespace Decorator

#endif /* __DECORATOR_H__ */
