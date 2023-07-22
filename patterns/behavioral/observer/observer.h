#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Observer */
namespace Observer {

/* Observer interface. If we use the inreface we  */
class IObserver {
 public:
  virtual ~IObserver() noexcept = default;
  virtual void Update(const std::string& message) = 0;
};

/* Subject interface */
class ISubject {
 public:
  virtual ~ISubject() noexcept = default;
  virtual void Attach(std::shared_ptr<IObserver>) = 0;
  virtual void Detach(std::shared_ptr<IObserver>) = 0;

 private:
  virtual void Notify() = 0;
};

/* Concrete Subject */
class Subject : public ISubject {
 public:
  void Attach(std::shared_ptr<IObserver> observer) override {
    m_observers.push_back(observer);
  }

  void Detach(std::shared_ptr<IObserver> observer) override {
    m_observers.remove(observer);
  }

  void RestoreRamenStocks() {
    std::cout << PrinterState::PlainText << "Ramen stocks restored!\n";
    m_message = "Ramen stocks restored";
    Notify();
  }

 private:
  void Notify() override {
    for (auto& item : m_observers) {
      item->Update(m_message);
    }
  }

 private:
  std::list<std::shared_ptr<IObserver>> m_observers;
  std::string m_message;
};

/* Concrete Observer 1 */
class RamenFan : public IObserver {
 public:
  explicit RamenFan(std::string name) : m_name(std::move(name)) {}

  void Update(const std::string&) override {
    std::cout << PrinterState::PlainText << "A ramen fan named " << m_name
              << " received a message from the Observer.\n";

    VisitRestaurantImmideately();
  }

 private:
  void VisitRestaurantImmideately() {
    std::cout << PrinterState::Quote
              << "I'm going to visit a ramen restaurant immideately!\n";
  }

 private:
  const std::string m_name;
};

/* Observer */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Observer") {}

 private:
  void BusinessLogic() const final {
    std::cout << PrinterState::Quote
              << "Due to the global crisis, the country ran out of stocks of "
              << "ramen. But when the stocks are restored, we want to notify "
              << "our customers immediately.\n";

    Subject restaurant;
    std::shared_ptr<IObserver> observer1 = std::make_shared<RamenFan>("Nik");
    std::shared_ptr<IObserver> observer2 = std::make_shared<RamenFan>("Alex");

    restaurant.Attach(observer1);
    restaurant.Attach(observer2);

    restaurant.RestoreRamenStocks();
  }
};

}  // namespace Observer

#endif /* __OBSERVER_H__*/
