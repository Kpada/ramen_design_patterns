#ifndef __CHAIN_OF_RESPONSIBILITY
#define __CHAIN_OF_RESPONSIBILITY

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../../iPattern.h"

/* GoF design pattern: Chain of Responsibility */
namespace ChainOfResponsibility {

/* Base Handler */
class Handler {
 public:
  explicit Handler(int price) : m_price(price) {}

  virtual ~Handler() {}

  void SetNext(std::unique_ptr<Handler> next) {
    m_nextHandler = std::move(next);
  }

  /* Chilnder mush override this */
  virtual void Process(int money) const = 0;

 protected:
  /* pass to the next handler */
  void PassOn(int money) const {
    if (m_nextHandler) m_nextHandler->Process(money);
  }

  bool HaveEnoughtMoney(int money) const { return money >= m_price; }

  void PrintMoney(int money) const {
    std::cout << "Your money = " << money << ", price = " << m_price << ". ";
  }

  const int m_price;
  std::unique_ptr<Handler> m_nextHandler;
};

/* Concrete Handler 1: Ramen */
class Ramen : public Handler {
 public:
  explicit Ramen(int price) : Handler(price) {}

  void Process(int money) const override {
    std::cout << PrinterState::PlainText;
    PrintMoney(money);

    /* handle */
    if (HaveEnoughtMoney(money)) {
      std::cout << "You can buy ramen\n";
    } else {
      std::cout << "You can NOT buy ramen\n";
    }

    /* next */
    PassOn(money);
  }
};

/* Concrete Handler 2: Gyoza */
class Gyoza : public Handler {
 public:
  explicit Gyoza(int price) : Handler(price) {}

  void Process(int money) const override {
    std::cout << PrinterState::PlainText;
    PrintMoney(money);

    /* handle */
    if (HaveEnoughtMoney(money)) {
      std::cout << "You can buy gyoza\n";
    } else {
      std::cout << "You can NOT buy gyoza\n";
    }

    /* next */
    PassOn(money);
  }
};

/* Concrete Handler 3: Udon */
class Udon : public Handler {
 public:
  explicit Udon(int price) : Handler(price) {}

  void Process(int money) const override {
    /* handle */
    std::cout << PrinterState::PlainText
              << "You can NOT buy udon. We don't have it. "
              << "This is a ramen restaurant.\n";

    /* next */
    PassOn(money);
  }
};

/* Concrete Handler 4: Beer */
class Beer : public Handler {
 public:
  explicit Beer(int price) : Handler(price) {}

  void Process(int money) const override {
    std::cout << PrinterState::PlainText;
    PrintMoney(money);

    /* handle */
    if (HaveEnoughtMoney(money)) {
      std::cout << "You can buy beer\n";
    } else {
      std::cout << "You can NOT buy beer\n";
    }

    /* next */
    PassOn(money);
  }
};

/* Builder */
class MenuBuilder {
 public:
  static std::unique_ptr<Handler> Build() {
    std::vector<std::unique_ptr<Handler>> chain;

    /* create items */
    chain.push_back(std::make_unique<Ramen>(1000));
    chain.push_back(std::make_unique<Gyoza>(500));
    chain.push_back(std::make_unique<Beer>(750));
    chain.push_back(std::make_unique<Udon>(1200));

    /* build a chain: use SetNext in the reverse order */
    for (int i = static_cast<int>(chain.size()) - 1; i >= 1; --i) {
      const int idx = i - 1;
      chain[idx]->SetNext(std::move(chain[i]));
    }

    return std::move(chain[0]);
  }
};

/* Chain of Responsibility */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Chain of Responsibility") {}

 private:
  void BusinessLogic() final {
    std::unique_ptr<Handler> chain = MenuBuilder::Build();

    std::cout << PrinterState::Quote
              << "What can I buy in this restaurant? My money = 100.\n";
    chain->Process(100);

    std::cout << PrinterState::Quote
              << "What can I buy in this restaurant? Money = 1000.\n";
    chain->Process(1000);
  }
};

}  // namespace ChainOfResponsibility

#endif /* __CHAIN_OF_RESPONSIBILITY */
