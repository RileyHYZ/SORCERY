#ifndef __CARD_H__
#define __CARD_H__

enum CardType {BLANK, CURSE, ENCHANTMENT, FIRECOLUMN, PLUSONEHP, MOAT,
                DESTRUCTION, RESURRECTION, NONE};

class Card {
		CardType cardType;
	public:
		Card(CardType);
		~Card();
};

#endif