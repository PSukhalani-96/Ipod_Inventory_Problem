#include <iostream>
#include <algorithm>

/*=====================================================================================================*/

class Inventory {

	protected:
		int stock;
		int price;
		int transPortCost;
		int cost;

	public:
		Inventory();
		virtual int CostComputation(int) = 0;
		virtual void stockUpdation(int) = 0;
		virtual int transportation(int) = 0;
		virtual bool isPresent(int) = 0;
		virtual int RemainingUnits(int) = 0;
		virtual int getStock() = 0;
		void setCost(int);
		int getCost();
};

Inventory::Inventory() : transPortCost() {}

void Inventory::setCost(int cost) {
	this->cost = cost;
}

int Inventory::getCost(){
	return cost;
}

/*=====================================================================================================*/

class Argentina : virtual public Inventory {

	public:
		Argentina(int, int, int);
		int CostComputation(int);
		void stockUpdation(int);
		int transportation(int);
		bool isPresent(int);
		int RemainingUnits(int);
		int getStock();
};

Argentina::Argentina(int transport, int stock, int price ){
	
	this->transPortCost = transport;
	this->stock = stock;
	this->price = price;
}

int Argentina::CostComputation(int units) {
	
	if ( units > stock )
		return -1;

	return units*price;
}

void Argentina::stockUpdation(int units) {
	if ( units > stock )
		stock = 0;
	else
		stock = stock - units;
}

int Argentina::transportation(int units) {

	int cost = (units / 10)*transPortCost;
	return cost + CostComputation(units);
}

bool Argentina::isPresent(int units) {
	return this->stock >= units ? true : false;
}

int Argentina::RemainingUnits(int units) {
	return units - this->stock;
}

int Argentina::getStock() {
	return stock;
}

/*=====================================================================================================*/

class Brazil: virtual public Inventory {

	public:
		Brazil(int,int, int);
		int CostComputation(int);
		void stockUpdation(int);
		int transportation(int);
		bool isPresent(int);
		int RemainingUnits(int);
		int getStock();
};

Brazil::Brazil(int transport, int stock, int price ){
	
	this->transPortCost = transport;
	this->stock = stock;
	this->price = price;
}

int Brazil::CostComputation(int units) {
	
	if ( units > stock )
		return -1;

	return units*price;
}

void Brazil::stockUpdation(int units) {
	if ( units > stock )
		stock = 0;
	else
		stock = stock - units;
}

int Brazil::transportation(int units) {

	int cost = (units / 10)*transPortCost;
	return cost + CostComputation(units);
}

bool Brazil::isPresent(int units) {
	return this->stock >= units ? true : false;
}

int Brazil::RemainingUnits(int units) {
	return units - this->stock;
}

int Brazil::getStock() {
	return stock;
}

/*=====================================================================================================*/

int validateCountry(std::string country) {

	transform(country.begin(), country.end(), country.begin(), ::tolower); 
	if ( country == "brazil")
		return 1;

	if ( country == "argentina")
		return 2;

	return 3;
}

bool isValidQuantity(int units, Argentina &a, Brazil &b) {
	
	if ( units > a.getStock() + b.getStock() ) 
		return false;
	return true;	
}

void purchases(int country, int units, Argentina &a, Brazil &b) {

	if ( country == 1 ) {

		int cost1 = 0, cost2 = 0 ;
		int diff1 = 0, diff2 = 0;
		int minCost = 0; 
		bool prevCost = false;

		/*=============================Need to be optimised=================================*/
		cost1 = b.CostComputation(units);

		if ( cost1 == -1 ) {
			diff1 = units - b.getStock(); 
			cost1 = b.CostComputation(b.getStock()) + a.transportation(diff1);
		}

		if (a.isPresent(units)) {
			if ( units % 10 == 0)
				cost2 = a.transportation(units);
			else {
				prevCost = true;
				cost2 = a.transportation(units - (units%10)) + b.CostComputation(units%10);
			}
		}

		else {
			diff2 = units - a.RemainingUnits(units);
			cost2 = a.transportation(diff2) + b.CostComputation(a.RemainingUnits(units));
		}

		if ( cost1 < cost2 ){
			minCost= cost1;
			a.stockUpdation(diff1);
			b.stockUpdation(b.getStock());
		}

		else {
			minCost = cost2;
			if ( prevCost == true ) {
				a.stockUpdation(units - (units%10));
				b.stockUpdation(units%10);
			}
			else {
				a.stockUpdation(diff2);
				b.stockUpdation(units-diff2);
			}
		}
		b.setCost(minCost);
	}

	else {

		int cost1 = 0, cost2 = 0 ;
		int diff1 = 0, diff2 = 0;
		int minCost = 0; 
		bool prevCost = false;

		/*=============================Need to be optimised=================================*/
		cost1 = a.CostComputation(units);

		if ( cost1 == -1 ) {
			diff1 = units - a.getStock(); 
			cost1 = a.CostComputation(a.getStock()) + b.transportation(diff1);
		}		

		if (b.isPresent(units)) {
			if ( units % 10 == 0)
				cost2 = b.transportation(units);
			else{
				prevCost = true;
				cost2 = b.transportation(units - (units%10)) + a.CostComputation(units%10);
			}
		}
		else {
			int diff2 = units - b.RemainingUnits(units);
			cost2 = b.transportation(diff2) + a.CostComputation(b.RemainingUnits(units));
		}

		if ( cost1 < cost2 ){
			minCost= cost1;
			b.stockUpdation(diff1);
			a.stockUpdation(units-diff1);
		}
		else {
			minCost = cost2;
			if ( prevCost == true ) {
				b.stockUpdation(units - (units%10));
				a.stockUpdation(units%10);
			}
			else {
				b.stockUpdation(diff2);
				a.stockUpdation(units-diff2);
			}
		}
		
		a.setCost(minCost);
	}

}

/*=====================================================================================================*/
void display(int country, Argentina a, Brazil b) {
	if ( country == 1 )
		std::cout <<"\n" << b.getCost() << " : " << b.getStock() << " : " << a.getStock() << "\n"; 
	
	else 
		std::cout <<"\n" << a.getCost() << " : " << b.getStock() << " : " << a.getStock() << "\n";
}

/*=====================================================================================================*/
int main() {

	std::string cntry;
	int quantity;
	int Ccode;
	char ans;

	do {

		Argentina a(400,100, 50);
		Brazil b(400,100,100);

		do {
			std::cout << "\nEnter Country 	: ";
			std::cin >> cntry;
			if ( validateCountry(cntry) == 3 )
				std::cout << "Please enter Correct Country.";
			else
				Ccode = validateCountry(cntry);
		}while(validateCountry(cntry) == 3);

		std::cout << "Enter Quantity 	: ";
		std::cin >> quantity;
	
		if ( !isValidQuantity(quantity,a,b) ) 
			std::cout << "\nRequirements Out Of Stock!!!\n";
		else {
			purchases(Ccode, quantity, a, b);
			display(Ccode, a, b); 
		}	

		std::cout << "\nDo you want to repeat the process : ";
		std::cin >> ans;
		std::cout << "\n";
	
	}while(ans == 'Y' || ans =='y');
	
	return 0;
}
/*=====================================================================================================*/
