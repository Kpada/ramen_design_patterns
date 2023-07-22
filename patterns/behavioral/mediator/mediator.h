#ifndef __MEDIATOR_H__
#define __MEDIATOR_H__

#include <iostream>
#include <memory>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Mediator */
namespace Mediator {

class Restaurant;

/* Supported meals */
enum class Meal {
  MisoRamen,
  TonkotsuRamen,
  Udon,
};

std::ostream& operator<<(std::ostream& os, Meal meal) {
  switch (meal) {
    case Meal::MisoRamen:
      os << "Miso Ramen";
      break;
    case Meal::TonkotsuRamen:
      os << "Tonkotsu Ramen";
      break;
    case Meal::Udon:
      os << "Udon";
      break;
    default:
      break;
  }

  return os;
}

/* Mediator Interface */
class IMediator {
 public:
  virtual ~IMediator() noexcept = default;
  virtual void Notify(const Restaurant*, Meal) = 0;
};

/* Restaurant base class */
class Restaurant {
 public:
  explicit Restaurant(std::string name) : m_name(std::move(name)) {}

  virtual ~Restaurant() noexcept = default;

  void SetMediator(std::shared_ptr<IMediator> mediator) {
    m_mediator = std::move(mediator);
  }

 protected:
  const std::string m_name;
  std::shared_ptr<IMediator> m_mediator;
};

/* Conctere restaurant 1 : Ramen */
class RamenRestaurant : public Restaurant {
 public:
  RamenRestaurant() : Restaurant("Ramen Restaurant") {}

  void OrderMisoRamen() {
    std::cout << PrinterState::PlainText << "Miso Ramen ordered from " << m_name
              << '\n';

    m_mediator->Notify(this, Meal::MisoRamen);
  }

  void OrderTonkotsuRamen() {
    std::cout << PrinterState::PlainText << "Tonkotsu Ramen ordered from "
              << m_name << '\n';
    m_mediator->Notify(this, Meal::TonkotsuRamen);
  }

  /* The Ramen restaurant buys advertising.
   * The mediator will send a notification that someone has ordered another
   * meal. They should spend more money on ad.
   */
  void SuggestToIncreaseRamenAdvertisingBudget() {
    std::cout << PrinterState::PlainText << m_name
              << ": we should increase the ad budget.";
  }
};

/* Conctere restaurant 2 : Udon */
class UdonRestaurant : public Restaurant {
 public:
  UdonRestaurant() : Restaurant("Udon Restaurant") {}

  /* The Udon restaurant buys advertising.
   * The mediator will send a notification that someone has ordered another
   * meal. They should spend more money on ad.
   */
  void SuggestToIncreaseUdonAdvertisingBudget() const {
    std::cout << PrinterState::PlainText << m_name
              << ": we should increase the ad budget.";
  }

  void OrderUdon() {
    std::cout << PrinterState::PlainText << "Udon ordered from " << m_name
              << '\n';
    m_mediator->Notify(this, Meal::Udon);
  }
};

/* Concrete mediator */
class AdAgencyMediator : public IMediator {
 public:
  AdAgencyMediator(std::shared_ptr<RamenRestaurant> ramen,
                   std::shared_ptr<UdonRestaurant> udon)
      : m_ramen(std::move(ramen)), m_udon(std::move(udon)) {}

  void Notify(const Restaurant* rest, Meal meal) override {
    std::cout << PrinterState::PlainText
              << "Mediator notified that someone ordered " << meal << '\n';

    if (rest != m_ramen.get()) {
      std::cout << PrinterState::PlainText
                << "Mediator is notifying the Ramen restaurant that they're "
                << "losing clients...\n";
      m_ramen->SuggestToIncreaseRamenAdvertisingBudget();
    }

    if (rest != m_udon.get()) {
      std::cout << PrinterState::PlainText
                << "Mediator is notifying the Udon restaurant that they're  "
                << "losing clients...\n";
      m_udon->SuggestToIncreaseUdonAdvertisingBudget();
    }
  }

 private:
  std::shared_ptr<RamenRestaurant> m_ramen;
  std::shared_ptr<UdonRestaurant> m_udon;
};

/* Mediator */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Mediator") {}

 private:
  void BusinessLogic() const final {
    std::cout
        << PrinterState::Quote
        << "We want to notify every restaurant when someone has ordered a "
           "meal. "
        << "If the restaurant sees others' orders, they will increase their "
        << "advertising budget and we will get more money :)\n";

    /* create restaurants */
    std::shared_ptr<RamenRestaurant> ramen =
        std::make_shared<RamenRestaurant>();
    std::shared_ptr<UdonRestaurant> udon = std::make_shared<UdonRestaurant>();
    /* mediator */
    std::shared_ptr<AdAgencyMediator> mediator =
        std::make_shared<AdAgencyMediator>(ramen, udon);
    /* config */
    ramen->SetMediator(mediator);
    udon->SetMediator(mediator);

    ramen->OrderMisoRamen();
  }
};

}  // namespace Mediator

#endif /* __MEDIATOR_H__*/
