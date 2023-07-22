#ifndef __TEMPLATE_METHOD_H__
#define __TEMPLATE_METHOD_H__

#include <iostream>
#include <memory>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Template Method */
namespace TemplateMethod {

/* Dinner base class
 * There are Base operations, Required operations, and Hooks here
 */
class Dinner {
 public:
  virtual ~Dinner() {}

  /* Template Method */
  void HaveDinner() {
    WashHand();      /* base */
    MakeOrder();     /* base */
    SayBonAppetit(); /* hook */
    TakeUtensils();  /* required */
    Eat();           /* base */
    Finish();        /* base */
    ClearTable();    /* hook */
  }

  const std::string& GetName() const { return m_name; }

  /* Base operations are implemented right here */
 private:
  void WashHand() const { Print("Wash hands"); }

  void MakeOrder() const { Print("Make the order"); }

  void Eat() const { Print("Eat"); }

  void Finish() const { Print("Finish"); }

  /* Required operations are abstract and must be implemented in inheritors */
 protected:
  virtual void TakeUtensils() const = 0;

  /* Hooks are empty but they can be reimplemented in inheritors */
 protected:
  virtual void SayBonAppetit() const {}
  virtual void ClearTable() const {}

 protected:
  explicit Dinner(std::string name) : m_name(std::move(name)) {}

  void Print(const std::string& text) const {
    std::cout << PrinterState::PlainText << text << '\n';
  }

  const std::string m_name;
};

class Ramen : public Dinner {
 public:
  Ramen() : Dinner("Ramen") {}

 private:
  /* Required */
  void TakeUtensils() const override { Print("Take chopsticks"); }

  /* Hooks */
  void SayBonAppetit() const override { Print("Itadakimasu"); }
};

class KFC : public Dinner {
 public:
  KFC() : Dinner("KFC") {}

 private:
  /* Required */
  void TakeUtensils() const override {
    /* nothing to do here, we will use our hands */
  }

  /* Hooks */
  void ClearTable() const override {
    /* There is no waiter, we should clear the table */
    Print("Clear the table");
  }
};

/* Template Method Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Template Method") {}

 private:
  void BusinessLogic() final {
    std::cout << PrinterState::Quote
              << "Eating dinner consists of the same steps. However, depending "
              << "on the dish or restaurant, the implementation of these steps "
              << "may differ.\n\n";

    /* Eat Ramen */
    HaveDinner(std::make_unique<Ramen>());

    /* Eat KFC */
    HaveDinner(std::make_unique<KFC>());
  }

  static void HaveDinner(std::unique_ptr<Dinner> dinner) {
    /* print */
    std::cout << PrinterState::Quote << "I'm going to eat " << dinner->GetName()
              << '\n';

    /* just call the template method */
    dinner->HaveDinner();
  }
};

}  // namespace TemplateMethod

#endif /* __TEMPLATE_METHOD_H__ */
