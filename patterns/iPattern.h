#ifndef __INTERFACE_PATTERN_H__
#define __INTERFACE_PATTERN_H__

#include <iostream>
#include <string>

#include "../printer.h"

/* Pattern Interface */
class IPattern {
 public:
  explicit IPattern(std::string title) : m_patternName(std::move(title)) {}

  virtual ~IPattern(){};

  void Execute() {
    std::cout << PrinterState::Title << m_patternName;
    BusinessLogic();
  }

 protected:
  /* Children should override this method */
  virtual void BusinessLogic() = 0;

 private:
  const std::string m_patternName;
};

#endif /* __INTERFACE_PATTERN_H__ */
