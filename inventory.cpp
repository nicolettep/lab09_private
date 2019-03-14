#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Product {
	string title;
	string manufacturer;
	double price;
};

struct InventoryNode {
	Product p;
	int quantity;
	InventoryNode *next;
};

struct Inventory {
	//bunch of (product, quantity) pairs
	//representated as a list
	InventoryNode *head;
};
struct CartNode {
	Product p;
	int quantity;
	CartNode *next;
};

struct Cart {
	//here will be list of Products
	CartNode *head;
};

bool product_equality(Product p1, Product p2) {
	return p1.title == p2.title &&
		p1.manufacturer == p2.manufacturer &&
		p1.price == p2.price;
}

string ProductToString(Product p) {
	ostringstream oss;
	oss << p.title << " " <<p.manufacturer << " "<< p.price;
	string s= oss.str();
	return s;
}


void add_to_cart(Cart *cart, Product p, Inventory *i) {
	//find product in the inventory
	InventoryNode *n = NULL;
	for (n= i->head; n != NULL; n= n->next){
		if(product_equality(n->p, p)) {
			//found product
			break;
		}
	}
	//n is either the proper nOde containing the product
	//or its NULL because the product wasnt in the inventory
	if (n ==NULL){
		cerr << "Product wasn't in inventory" << endl;
		return;
	}
	//n is definetley the proper Node
	
	//make sure we have one more product to sell
	if (n->quantity <= 0){
		cerr<< "Not enough"<< ProductToString(p)<<" in inventory" << endl;
		return;
	}
	//make a CartNode and put the product inside
	CartNode *cn = new CartNode;
	cn->p = p;
	cn->quantity = cn->quantity + 1;
	cn->next = NULL;
	//put at end of current cart
	CartNode *iter = cart->head;
	if (iter == NULL) {
		cart->head = cn;
	}else{
		while (iter->next != NULL) {
			iter= iter->next;
		}
		//iter is pointing to last element of the list
		//set its next
		iter->next = cn;
	}
	n->quantity= n->quantity - 1;
	//subtract one from correct inventory item
}

void printInventory(Inventory *i){
	for (InventoryNode *n = i->head; n!= NULL; n = n->next) {
		cout << ProductToString(n->p) << " "<< n->quantity << endl;
	}
}

void printCart(Cart *c){
	for (CartNode *n = c->head; n!= NULL; n = n->next) {
		cout << ProductToString(n->p) << " "<< n->quantity << endl;
	}
}
int main(){
	Product hat = {"Hat", "Target", 60};
	Product orange_chicken= {"Orange Chicken", "Trader Joes", 4.99};
	Product my_soul = {"Lawton's Soul", "UCSB", 0.01};
	InventoryNode *first_node = new InventoryNode;
	(*first_node).p= hat;
	(*first_node).quantity = 4;

	InventoryNode *second_node = new InventoryNode;
	(*second_node).p= orange_chicken;
	(*second_node).quantity = 10;

	InventoryNode *third_node = new InventoryNode;
	(*third_node).p= my_soul;
	(*third_node).quantity = 1;
	
	first_node->next = second_node;
	second_node->next = third_node;
	third_node->next = NULL;

	Inventory *i = new Inventory;
	i->head = first_node;

	Cart *c = new Cart;
	c->head = NULL;


	add_to_cart(c, hat, i);
	add_to_cart(c, hat, i);
	add_to_cart(c, hat, i);
	add_to_cart(c, orange_chicken, i);
	add_to_cart(c, my_soul, i);

	printInventory(i);
	printCart(c);

	return 0;
}
