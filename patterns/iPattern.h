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
        std::cout << " + + + + Start " << patternName << std::endl << std::endl;

        BusinessLogic();

        std::cout << std::endl << " + + + + Finish " << patternName << std::endl;
    }

protected:
    /* Children should override this method */
    virtual void BusinessLogic() = 0;

private:
    const std::string patternName;
};
