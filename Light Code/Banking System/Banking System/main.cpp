#include "Acc.h"
#include "Bank.h"

int main() {
	AccHandler manager;
	int choice;

	while (true) {
		manager.ShowMenu();
		cout << "����: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case MAKE:
			manager.makeAcc();
			break;
		case DEPOSIT:

		default:
			cout << "�߸��� �Է�.." << endl;
			break;
		}
	}
	
	system("pause");
	return 0;
}