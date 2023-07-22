#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__

#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Composite */
namespace Composite {

/* Component is a base class for Compotises and Leafs */
class Component {
 public:
  explicit Component(std::string name) : Component(std::move(name), 0) {}
  virtual ~Component() noexcept = default;

  /* this is the main method, must be overridden */
  virtual int GetPrice() const = 0;

  /* add and remove */
  virtual void Add(std::shared_ptr<Component>) {}
  virtual void Remove(std::shared_ptr<Component>) {}

  virtual bool IsComposite() const { return false; }

  const std::string& GetName() const { return m_name; }

 protected:
  Component(std::string name, int price)
      : m_name(std::move(name)), m_price(price) {}

  std::string m_name;
  int m_price = 0;
};

/* Leaf has its own price */
class Leaf : public Component {
 public:
  Leaf(std::string name, int price) : Component(std::move(name), price) {}

  int GetPrice() const override { return m_price; }
};

/* Composite contains leafes and other composites */
class Composite : public Component {
 public:
  explicit Composite(std::string name) : Component(std::move(name)) {}

  void Add(std::shared_ptr<Component> component) override {
    /* check to avoid a loop */
    if (component.get() == this) {
      throw std::runtime_error("You cannot add the same component");
    }
    m_children.push_back(std::move(component));
  }

  void Remove(std::shared_ptr<Component> component) override {
    m_children.remove(component);
  }

  bool IsComposite() const override { return true; }

  int GetPrice() const override {
    return std::accumulate(
        m_children.begin(), m_children.end(), 0,
        [](int sum, auto item) { return sum += item->GetPrice(); });
  }

 protected:
  std::list<std::shared_ptr<Component>> m_children;
};

/* Composite Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Composite") {}

 private:
  /*                         TOTAL ORDER
   *                       /             \
   *  friend's ramen (1000)     _____    MY ORDER    _______
   *                           /        |      \            \
   *                 ramen(1200)   gyoza(500)  beer(400)    MY GF's ORDER
   *                                                         /       \
   *                                                   mochi (350)  coffe (250)
   */
  void BusinessLogic() const final {
    std::cout << PrinterState::Quote
              << "We're going to visit a restauran. When we finish dinner, we "
              << "have to pay the check. But how do we calculate who spent how "
              << "much? Fortunately, the check is a composite.\n";

    /* create the order */
    std::shared_ptr<Component> totalOrder =
        std::make_shared<Composite>("TotalOrder");
    std::shared_ptr<Component> myOrder =
        std::make_shared<Composite>("My Order");
    std::shared_ptr<Component> gfOrder =
        std::make_shared<Composite>("My GF's order");

    std::shared_ptr<Component> friendsRamen =
        std::make_shared<Leaf>("Friend's ramen", 1000);

    std::shared_ptr<Component> myRamen =
        std::make_shared<Leaf>("My ramen", 1200);
    std::shared_ptr<Component> myGyoza =
        std::make_shared<Leaf>("My gyoza", 500);
    std::shared_ptr<Component> myBeer = std::make_shared<Leaf>("My beer", 400);

    std::shared_ptr<Component> gfMochi =
        std::make_shared<Leaf>("Gf's mochi", 350);
    std::shared_ptr<Component> gfCoffe =
        std::make_shared<Leaf>("Gf's coffe", 250);

    /* build the tree */
    totalOrder->Add(friendsRamen);
    totalOrder->Add(myOrder);

    myOrder->Add(myRamen);
    myOrder->Add(myGyoza);
    myOrder->Add(myBeer);
    myOrder->Add(gfOrder);

    gfOrder->Add(gfMochi);
    gfOrder->Add(gfCoffe);

    /* print */
    PrintPrice(totalOrder);
    PrintPrice(myOrder);
    PrintPrice(gfOrder);
    PrintPrice(myRamen);
  }

  static void PrintPrice(std::shared_ptr<Component> component) {
    std::cout << PrinterState::PlainText << "Price of " << component->GetName()
              << " = " << component->GetPrice() << "\n";
  }
};

}  // namespace Composite

#endif /* __COMPOSITE_H__ */
