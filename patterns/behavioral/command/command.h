#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <iostream>
#include <memory>
#include <stack>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Command */
namespace Command {

/* Receiver cooks meals */
class ReceiverChef {
 public:
  void Cook(const std::string& meal) const {
    std::cout << PrinterState::PlainText << "Cooking " << meal << '\n';
  }

  void StopCooking(const std::string& meal) const {
    std::cout << PrinterState::PlainText << "Stop cooking " << meal << '\n';
  }
};

/* Command Interface */
class ICommand {
 public:
  virtual ~ICommand() noexcept = default;
  virtual void Execute() const = 0;
  virtual void Undo() const = 0;
};

/* Concrete Command: cook ramen */
class CommandCookRamen : public ICommand {
 public:
  explicit CommandCookRamen(std::shared_ptr<ReceiverChef> receiver)
      : m_chef(std::move(receiver)), m_meal("Ramen") {}

  void Execute() const override { m_chef->Cook(m_meal); }

  void Undo() const override { m_chef->StopCooking(m_meal); }

 private:
  std::shared_ptr<ReceiverChef> m_chef;
  const std::string m_meal;
};

/* Concrete Command: cook gyoza */
class CommandCookGyoza : public ICommand {
 public:
  explicit CommandCookGyoza(std::shared_ptr<ReceiverChef> receiver)
      : m_chef(std::move(receiver)), m_meal("Gyoza") {}

  void Execute() const override { m_chef->Cook(m_meal); }

  void Undo() const override { m_chef->StopCooking(m_meal); }

 private:
  std::shared_ptr<ReceiverChef> m_chef;
  const std::string m_meal;
};

/* Command History allows us do undo*/
class CommandHistory {
 public:
  void Push(std::unique_ptr<ICommand> cmd) { m_history.push(std::move(cmd)); }

  std::unique_ptr<ICommand> Pop() {
    if (m_history.empty()) {
      throw std::runtime_error("Command history is empty");
    }

    auto lastCommand = std::move(m_history.top());
    m_history.pop();
    return lastCommand;
  }

 private:
  std::stack<std::unique_ptr<ICommand>> m_history;
};

/* Invoker */
class Waiter {
 public:
  Waiter() : m_chef(std::make_shared<ReceiverChef>()) {}

  void OrderRamen() { Execute(std::make_unique<CommandCookRamen>(m_chef)); }

  void OrderGyoza() { Execute(std::make_unique<CommandCookGyoza>(m_chef)); }

  void CancelLastOrder() { m_history.Pop()->Undo(); }

 private:
  void Execute(std::unique_ptr<ICommand> cmd) {
    cmd->Execute();
    m_history.Push(std::move(cmd));
  }

 private:
  std::shared_ptr<ReceiverChef> m_chef;
  CommandHistory m_history;
};

/* Command */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Command") {}

 private:
  void BusinessLogic() const final {
    std::cout << PrinterState::Quote << "We're visiting a ramen restaurant. "
              << "We're going to order 2 bowls or ramen\n";

    Waiter waiter;
    waiter.OrderRamen();
    waiter.OrderRamen();

    std::cout << PrinterState::Quote
              << "A friend of mine also decided to order some gyoza\n";

    waiter.OrderGyoza();

    std::cout
        << PrinterState::Quote
        << "But we don't have enough money and cannot afford these gyoza. "
        << "So we asked the waiter for a cancelation\n";

    waiter.CancelLastOrder();
  }
};

}  // namespace Command

#endif /* __COMMAND_H__ */
