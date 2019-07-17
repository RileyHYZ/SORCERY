#ifndef __CARD_H__
#define __CARD_H__

#include <string>

class Card {
  public:
    enum Value {
        BLANK = 0, 
        CURSE, 
        ENCHANTMENT, 
        FIRECOLUMN, 
        PLUSONEHP, 
        MOAT,
        DESTRUCTION, 
        RESURRECTION, 
        NONE
    };

    Card(Value = NONE);

    Value getValue();
    std::string getName() const;
    std::string getDescription();

    bool operator==(const Card&) const;
    bool operator!=(const Card&) const;

    struct CardHash {
        size_t operator()(const Card&) const;
    };

  private:
    Value v;
};

#endif
