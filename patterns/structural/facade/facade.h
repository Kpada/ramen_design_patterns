#ifndef __FACADE_H__
#define __FACADE_H__

#include <iostream>
#include <memory>
#include <set>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Facade */
namespace Facade {

/* Subsystem 1: Menu (a list of food and beverages) */
class Menu {
 public:
  using Items = std::set<std::string>;

  explicit Menu(const Items& menu) : m_menu(menu) {}
  Menu() {}

  void Add(const std::string& item) { m_menu.insert(item); }

  bool IsItemInMenu(const std::string& item) const {
    return m_menu.count(item) ? true : false;
  }

  const Items& Read() const { return m_menu; }

 private:
  Items m_menu;
};

/* Subsystem 2: Ticket */
class Ticket {
 public:
  explicit Ticket(std::string name) : m_name(std::move(name)) { PrintInfo(); }

  Ticket(const Ticket&) = delete;
  Ticket& operator=(const Ticket&) = delete;
  Ticket& operator=(const std::string&) = delete;

  const std::string& GetName() const { return m_name; }

 private:
  void PrintInfo() const {
    std::cout << PrinterState::PlainText << "Ticket created: " << m_name
              << '\n';
  }

 private:
  const std::string m_name;
};

/* Subsystem 3: Vending Machine */
class VendingMachine {
 public:
  explicit VendingMachine(std::shared_ptr<Menu> menu) : m_menu(menu) {}

  void InsertMoney() {
    if (!m_money) {
      std::cout << PrinterState::PlainText << "Inseted money\n";
      m_money = true;
    }
  }

  bool SelectItem(const std::string& menuItemName) {
    if (IsMenuItemAvailable(menuItemName)) {
      std::cout << PrinterState::PlainText << "Chosen " << menuItemName << '\n';
      m_selectedItemName = menuItemName;
      return true;
    } else {
      return false;
    }
  }

  std::unique_ptr<Ticket> GetTicket() {
    if (!m_money || m_selectedItemName.empty()) {
      throw std::runtime_error("");
    }

    m_money = false;
    return std::make_unique<Ticket>(m_selectedItemName);
  }

  bool IsMenuItemAvailable(const std::string& menuItemName) const {
    return m_menu->IsItemInMenu(menuItemName);
  }

 private:
  std::shared_ptr<Menu> m_menu;
  std::string m_selectedItemName;
  bool m_money = false;
};

/* Subsystem 4: Chef */
class Chef {
 public:
  bool StartCooking(std::unique_ptr<Ticket> ticket) const {
    if (!ticket || ticket->GetName().empty()) {
      throw std::runtime_error("");
    }

    std::cout << PrinterState::PlainText
              << "Chef got a ticket and started cooking " << ticket->GetName()
              << '\n';

    return true;
  }
};

/* Facade */
class RamenOrderFacade {
 public:
  explicit RamenOrderFacade(std::shared_ptr<Menu> menu)
      : m_vending(std::move(menu)) {}

  bool MakeOrder(const std::string& ramenName) {
    /* choose a dish, insert money, get a ticket and bring it to the chef */
    if (m_vending.SelectItem(ramenName)) {
      m_vending.InsertMoney();
      auto ticket = m_vending.GetTicket();
      return m_chef.StartCooking(std::move(ticket));
    }
    return false;
  }

 private:
  VendingMachine m_vending;
  Chef m_chef;
};

/* Facade Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Facade") {}

 private:
  void BusinessLogic() final {
    std::cout << PrinterState::Quote
              << "Ordering at a ramen restaurant is not easy. "
              << "They usually use vending machines, so you have to: "
              << "choose a dish (if you can read Japanese), "
              << "put some money, "
              << "get a ticket, "
              << "give it to the chef. "
              << "This facade will help me not to starve to death.\n";

    /* create the menu */
    auto menu = GetMenu();

    /* create our facade */
    RamenOrderFacade facade(menu);

    /* order the 1st ramen from the menu */
    facade.MakeOrder(*menu->Read().begin());
  }

  static inline std::shared_ptr<Menu> GetMenu() {
    std::shared_ptr<Menu> menu = std::make_shared<Menu>();

    menu->Add("shoyu ramen");
    menu->Add("shio ramen");
    menu->Add("miso ramen");
    menu->Add("tonkotsu ramen");

    return menu;
  }
};

}  // namespace Facade

#endif /* __FACADE_H__ */
