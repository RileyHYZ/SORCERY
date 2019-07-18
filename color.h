#ifndef __COLOR_H__
#define __COLOR_H__

#include <string>

class Color {
  public:
    enum Value {
        WHITE = 0,
        BLACK,
        NONE
    };

    Color(Value = NONE);

    std::string getName();

    bool operator==(const Color&) const;
    bool operator!=(const Color&) const;

    struct ColorHash {
        size_t operator()(const Color&) const;
    };

  private:
    Value v;
};

#endif
