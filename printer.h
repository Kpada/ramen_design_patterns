#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <iostream>
#include <string>

enum class PrinterState { PlainText, Quote, Title };

/* Text formatter
 * By the way, this is a singleton.
 */
class Printer {
 public:
  /* delete copy/move */
  Printer(const Printer&) = delete;
  Printer& operator=(const Printer&) = delete;
  Printer(Printer&&) = delete;
  Printer& operator=(Printer&&) = delete;

  static Printer& GetInstance() {
    static Printer printer;
    return printer;
  }

  std::ostream& Update(std::ostream& os, PrinterState newState) {
    switch (newState) {
      case PrinterState::PlainText:
        SetStatePlainText(os, m_state);
        break;
      case PrinterState::Quote:
        SetQuote(os, m_state);
        break;
      case PrinterState::Title:
        SetTitle(os, m_state);
        break;
      default:
        throw std::runtime_error("Unknown printer state");
        break;
    }

    m_state = newState;
    return os;
  }

 private:
  /* hide the costructor */
  Printer() noexcept = default;

  inline void SetStatePlainText(std::ostream& os, PrinterState curState) const {
    switch (curState) {
      case PrinterState::PlainText:
        NewLine(os);
        break;
      case PrinterState::Quote:
        NewLine(os);
        break;
      case PrinterState::Title:
        NewLine(os, 2);
        break;
    }
  }

  inline void SetQuote(std::ostream& os, PrinterState curState) const {
    switch (curState) {
      case PrinterState::PlainText:
        NewLine(os);
        Quote(os);
        break;
      case PrinterState::Title:
        NewLine(os, 2);
        Quote(os);
        break;
      case PrinterState::Quote:
        NewLine(os);
        Quote(os);
        break;
    }
  }

  inline void SetTitle(std::ostream& os, PrinterState curState) const {
    switch (curState) {
      case PrinterState::PlainText:
      case PrinterState::Title:
      case PrinterState::Quote:
        NewLine(os, 2);
        Title(os);
        break;
    }
  }

  std::ostream& NewLine(std::ostream& os, unsigned int count = 1) const {
    return os << std::string(count, '\n');
  }

  std::ostream& Title(std::ostream& os) const { return os << "### "; }

  std::ostream& Quote(std::ostream& os) const { return os << "> "; }

 private:
  PrinterState m_state = PrinterState::PlainText;
};

std::ostream& operator<<(std::ostream& os, PrinterState state) {
  Printer& printer = Printer::GetInstance();
  printer.Update(os, state);
  return os;
}

#endif /* __PRINTER_H__ */
