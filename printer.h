#ifndef PRINTER_H_
#define PRINTER_H_

/// @file printer.h
/// @brief Defines the @c Printer class and the @c PrinterState enum for various
/// printing styles.

#include <iostream>
#include <string>

/// @brief Enum class representing various printing styles.
enum class PrinterState {
  /// @brief Represents plain text style.
  PlainText,
  /// @brief Represents quote style.
  Quote,
  /// @brief Represents title style.
  Title,
};

/// @brief Singleton class for text formatting and output.
///
/// This class manages text formatting for display in various styles, ensuring
/// consistency across all output.
class Printer {
 public:
  /// @brief Deleted copy constructor to prevent copying.
  Printer(const Printer&) = delete;

  /// @brief Deleted copy assignment operator to prevent copying.
  Printer& operator=(const Printer&) = delete;

  /// @brief Deleted move constructor to prevent moving.
  Printer(Printer&&) = delete;

  /// @brief Deleted move assignment operator to prevent moving.
  Printer& operator=(Printer&&) = delete;

  /// @brief Gets the singleton instance of the Printer.
  /// @return A reference to the Printer instance.
  static Printer& GetInstance() {
    static Printer printer;  // Meyer's Singleton
    return printer;
  }

  /// @brief Updates the current printing state.
  /// Modifies the given output stream according to the new printing state.
  /// @param os Output stream to modify.
  /// @param newState The new desired printing state.
  /// @return Modified output stream.
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
    }

    m_state = newState;
    return os;
  }

 private:
  /// @brief Private default constructor ensuring singleton behavior.
  Printer() noexcept = default;

  /// @brief Sets the state to plain text.
  /// Adjusts the output stream based on the current state to plain text format.
  /// @param os Output stream to modify.
  /// @param curState Current printing state.
  void SetStatePlainText(std::ostream& os, PrinterState curState) const {
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

  /// @brief Sets the state to quote.
  /// Adjusts the output stream based on the current state to quote format.
  /// @param os Output stream to modify.
  /// @param curState Current printing state.
  void SetQuote(std::ostream& os, PrinterState curState) const {
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

  /// @brief Sets the state to title.
  /// Adjusts the output stream based on the current state to title format.
  /// @param os Output stream to modify.
  /// @param curState Current printing state.
  void SetTitle(std::ostream& os, PrinterState curState) const {
    switch (curState) {
      case PrinterState::PlainText:
      case PrinterState::Title:
      case PrinterState::Quote:
        NewLine(os, 2);
        Title(os);
        break;
    }
  }

  /// @brief Adds new lines to the output stream.
  /// Inserts a specified number of newline characters into the output stream.
  /// @param os Output stream to modify.
  /// @param count Number of newlines to insert.
  /// @return Modified output stream.
  std::ostream& NewLine(std::ostream& os, unsigned int count = 1) const {
    return os << std::string(count, '\n');
  }

  /// @brief Formats the output stream as a title.
  /// Applies title formatting to the output stream.
  /// @param os Output stream to modify.
  /// @return Modified output stream.
  std::ostream& Title(std::ostream& os) const { return os << "### "; }

  /// @brief Formats the output stream as a quote.
  /// Applies quote formatting to the output stream.
  /// @param os Output stream to modify.
  /// @return Modified output stream.
  std::ostream& Quote(std::ostream& os) const { return os << "> "; }

 private:
  /// @brief Current state of the printer.
  PrinterState m_state = PrinterState::PlainText;
};

/// @brief Overloaded operator for the PrinterState.
/// @param os Output stream to modify.
/// @param state The new printing state to apply.
/// @return Modified output stream.
std::ostream& operator<<(std::ostream& os, PrinterState state) {
  Printer& printer = Printer::GetInstance();
  printer.Update(os, state);
  return os;
}

#endif  // PRINTER_H_
