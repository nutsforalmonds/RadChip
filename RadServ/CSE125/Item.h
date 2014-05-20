#ifndef _ITEM_H_
#define _ITEM_H_



class Item
{
public:
	Item();
	~Item();
	int getHealth();
	void setHealth(int val);
	bool isWeapon();
	bool isBoots();

protected:
	int health;
};


#endif