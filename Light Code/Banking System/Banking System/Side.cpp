#ifndef SIDE_H__
#include "Side.h"

Acc* accArr[100];
int accNum;

void Showmenu()
{
	cout << "-----Menu-----" << endl;
	cout << "1. ���°���" << endl;
	cout << "2. �Ա�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �������� ���" << endl;
	cout << "5. ����" << endl;
}

void MakeAcc()
{
	int id, balance;
	char name[NAME_LEN];

	cout << "[���°���]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "�̸�: "; cin >> name;
	cout << "�Աݾ�: "; cin >> balance;
	accArr[accNum++] = new Acc(id, balance, name);
}

void DepositMoney()
{
	int money, id;
	cout << "[��  ��]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "�Աݾ�: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			accArr[i]->Deposit(money);
			cout << "�ԱݿϷ�" << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl;
}

void WithdrawMoney()
{
	int money, id;
	cout << "[��  ��]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "�Աݾ�: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "�ܾ׺���" << endl;
				return;
			}
			cout << "��ݿϷ�" << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID �Դϴ�." << endl;
}

void ShowAccInfo()
{
	int id;
	cout << "[���� ����]" << endl;
	cout << "����ID: "; cin >> id;
	for(int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			accArr[i]->ShowAcc();
		}
	}
}

void EndAcc()
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
}
#endif