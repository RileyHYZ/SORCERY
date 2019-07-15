#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>
#include <string>

class Card {
  public:
    enum Value {
        BLANK, 
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
    std::string getName();
    std::string getDescription();

    bool operator==(const Card&);
    bool operator!=(const Card&);

  private:
    Value v;
};

#endif
