#ifndef PATTERNS_IPATTERN_H_
#define PATTERNS_IPATTERN_H_

#include <iostream>
#include <string>
#include <utility>

#include "../printer.h"

/* Pattern Interface */
class IPattern {
 public:
  IPattern(const IPattern&) = delete;
  IPattern& operator=(const IPattern&) = delete;
  IPattern(IPattern&&) = delete;
  IPattern& operator=(IPattern&&) = delete;

  virtual ~IPattern() noexcept = default;

  void Execute() const {
    std::cout << PrinterState::Title << m_patternName;
    BusinessLogic();
  }

 protected:
  explicit IPattern(std::string title) : m_patternName(std::move(title)) {}

  // Children should override this method
  virtual void BusinessLogic() const = 0;

 private:
  const std::string m_patternName;
};

#endif  // PATTERNS_IPATTERN_H_
