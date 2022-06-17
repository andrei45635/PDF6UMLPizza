#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;

class Pizza {
private:
	int price;
public:
	Pizza(int price) : price{ price } {};

	virtual string descriere() = 0;

	virtual int getPret() {
		return price;
	}

	virtual ~Pizza() = default;
};

class BasicPizza : public Pizza {
private:
	string name;
public:
	BasicPizza(const string& name, int price) : Pizza{ price }, name{ name }{};

	string descriere() override {
		return name;
	}

	~BasicPizza() = default;
};

class PeperoniPizza : public Pizza {
private:
	Pizza& p;
public:
	PeperoniPizza(Pizza& p) : Pizza{ p.getPret() }, p{ p }{};

	string descriere() override {
		return p.descriere() + " cu peperoni";
	}

	int getPret() override {
		return p.getPret() + 2;
	}

	~PeperoniPizza() = default;
};

class CiupiPizza : public Pizza {
private:
	Pizza& p;
public:
	CiupiPizza(Pizza& p) : Pizza{ p.getPret() }, p{ p }{};

	string descriere() override {
		return p.descriere() + " cu ciuperci";
	}

	int getPret() override {
		return p.getPret() + 3;
	}

	~CiupiPizza() = default;
};

vector<Pizza*> fun() {
	vector<Pizza*> pizzas;

	BasicPizza* bp1 = new BasicPizza{ "salami", 15 };
	pizzas.push_back(bp1);

	BasicPizza* bp2 = new BasicPizza{ "salami", 15 };
	CiupiPizza* ciup1 = new CiupiPizza{ *bp2 };
	pizzas.push_back(ciup1);

	BasicPizza* bp3 = new BasicPizza{ "diavola", 20 };
	PeperoniPizza* pep = new PeperoniPizza{ *bp3 };
	CiupiPizza* ciup2 = new CiupiPizza{ *pep };
	pizzas.push_back(ciup2);

	return pizzas;
}

int main() {
	auto orders = fun();
	
	sort(orders.begin(), orders.end(), [](Pizza* p1, Pizza* p2) {return p1->getPret() > p2->getPret(); });
	
	for (auto order : orders) {
		cout << order->descriere() << " " << order->getPret() << '\n';
	}

	return 0;
}