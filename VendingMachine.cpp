#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Product
{
public:
	Product(const string& newName, int newPrice, int newQuantity)
		: name(newName), price(newPrice), quantity(newQuantity) {}

	const string& getName() const { return name; }
	int getPrice() const { return price; }
	int getQuantity() const { return quantity; }

	void dispense() { quantity--; }

private:
	string name;
	int price;
	int quantity;
};

class Dispenser
{
public:
	void addProduct(const Product& product) { products.push_back(product); }

	void displayProducts() const
	{
		cout << "* * * Vending machine products * * *\n";
		cout << "#" << setw(27) << "Name" << setw(10) << "Price" << setw(13) << "Quantity\n";
		for (int i = 1; i <= products.size(); i++)
		{
			cout << "Enter " << i << " for: " << setw(15) << products[i - 1].getName() << setw(10) << products[i - 1].getPrice() << setw(13) << products[i - 1].getQuantity() << "\n";
		}
		cout << "Or enter 0 to exit\n";
	}

	void dispenseProduct(int selection)
	{
		if (selection > 0 && selection <= products.size())
		{
			Product& product = products[selection - 1];

			if (product.getQuantity() > 0)
			{
				int amount;
				cout << "Insert " << product.getPrice() << ((product.getPrice() > 1) ? " coins." : " coin.") << "\n";
				cin >> amount;

				if (amount >= product.getPrice())
				{
					product.dispense();
					cout << "Dispensing " << product.getName() << ". Enjoy!\n";

					int change = amount - product.getPrice();
					if (change > 0)
					{
						cout << "Returning change: " << change << ((change > 1) ? " coins." : " coin.") << "\n";
					}
					cout << "\n";
				}
				else
				{
					cout << "Sorry! That item costs" << product.getName() << " costs " << product.getPrice() << "\n";
					cout << "Refunding " << amount << ((amount > 1) ? " coins." : " coin.") << "\n\n";
				}
			}
			else
			{
				cout << "Sorry! " << product.getName() << " is sold out.\n\n";
			}
		}
		else
		{
			cout << "Sorry! " << selection << " is an invalid selection.\n\n";
		}
	}

private:
	vector<Product> products;
};

int main()
{
	Dispenser dispenser;
	dispenser.addProduct(Product("Bottled water", 8, 5));
	dispenser.addProduct(Product("Soda", 8, 2));
	dispenser.addProduct(Product("Chips", 6, 4));
	dispenser.addProduct(Product("Candy bar", 8, 11));
	dispenser.addProduct(Product("Gum", 3, 20));
	dispenser.addProduct(Product("Mixed nuts", 6, 7));
	dispenser.addProduct(Product("Granola bar", 6, 5));
	dispenser.addProduct(Product("Cookie", 4, 0));
	dispenser.addProduct(Product("Sandwich", 20, 8));

	dispenser.displayProducts();

	int selection;
	cin >> selection;
	while (selection != 0)
	{
		dispenser.dispenseProduct(selection);

		dispenser.displayProducts();
		cin >> selection;
	}

	return 0;
}