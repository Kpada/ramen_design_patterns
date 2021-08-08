#pragma once

#include <iostream>
#include <string>

/* Common Pattern Interface */

class IPattern {
public:
    IPattern(std::string title)
    : patternName(move(title))
    {}

    virtual ~IPattern() {};

    void Execute() {
        std::cout << "#### " << patternName << std::endl << std::endl;
        std::cout << "```" << std::endl;

        BusinessLogic();

        std::cout << std::endl << "```" <<  std::endl;
    }

protected:
    /* Children should override this method */
    virtual void BusinessLogic() = 0;

private:
    const std::string patternName;
};
