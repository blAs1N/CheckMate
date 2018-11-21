#include "AVLTree.h"
#include <iostream>

using std::cout;
using std::endl;

bool Choice(int& choice);
void Input(string* key, string* value);

int main() {
	AVLTree* avl = new AVLTree();
	AVLNode* root = nullptr;
	AVLNode* result = nullptr;

	string inputKey, inputValue, resultString;
	int choice;

	cout << "ġ�� ���� �� ���ĵ� �Ǵ� �������\n" << endl;

	while (Choice(choice)) {
		switch (choice) {
		case 1:
			Input(&inputKey, nullptr);
			result = avl->Search(root, inputKey);
			cout << result << endl;
			break;

		case 2:
			Input(&inputKey, &inputValue);
			root = avl->Insert(root, inputKey, inputValue);
			break;

		case 3:
			Input(&inputKey, nullptr);

			result = avl->Delete(root, inputKey);
			cout << "������ �ܾ�: " << result << endl;

			break;

		case 4:
			avl->Inorder(root);
			break;
		}

		cout << endl << endl;
	}

	if (result) {
		delete result;
		result = nullptr;
	}

	delete avl;
	avl = nullptr;

	return 0;
}

bool Choice(int& choice) {
	cout << "1. �ܾ� �˻�\n";
	cout << "2. �ܾ� �߰�\n";
	cout << "3. �ܾ� ����\n";
	cout << "4. ��ü ���\n";
	cout << "0. ����\n" << endl;

	cout << "����. ";
	std::cin >> choice;
	cout << endl;

	return choice != 0;
}

void Input(string* key, string* value) {
	if (key) {
		cout << "�ܾ �Է��ϼ���. ";
		std::cin >> (*key);
	}

	if (value) {
		cout << "���� �Է��ϼ���. ";
		std::cin >> (*value);
	}
}