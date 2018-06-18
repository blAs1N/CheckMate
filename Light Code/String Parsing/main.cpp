#include <iostream>
#include <string>
#include <vector>
#include <regex>

#define MAX_INPUT 42
 
using namespace std;

// ���⸦ �������� �ڸ� ���ڿ� �ϳ� �ϳ�
class String : string {
private:
	string text;
public:
	// �Է¹��� ���� text�� �Ҵ�
	String(string input);

	// �ڽ��� key�� ������ �ִ��� Ȯ��
	bool HaveKey(const char key) const;

	// yes -> 1, no -> 0���� ��ȯ
	void BoolToInt();

	// 16���� ���ڿ� ���� 10���� ���ڿ� ������ ����
	void HexToInt();

	string Get();

	void operator+=(string userInput);

	friend ostream& operator<< (ostream& os, String& message);
};

// String ��ü�� �����ϴ� Ŭ����
class Parser : vector<String> {
private:
	vector<String> message;
private:
	// key ���� ������ �ִ� String�� vector�� ������
	vector<int> Search(const string key = " ");

	void Swap(int pos1, int pos2);

	// 16 ������ ��ġ�� ã�Ƽ� 10������ ��ȯ
	void TidyHex();

	// yes / no�� ��ġ�� ã�Ƽ� 1 / 0���� ��ȯ, �ڿ� ������ �ٲ�
	void TidyBool();

	// �ʿ��� �κ� (������ �κ�)�� ����
	void Extraction();

	// �ػ󵵸� NxN, N, N ������� ����
	void TieValue();
public:
	// ���� �Լ� 4���� ���� ĸ�� �޼���
	void Parsing();

	// ������ �ڿ� ���ο� ���ڿ��� �߰��ϴ� ������
	void operator+= (string userInput);

	// message�� ��ȯ
	vector<String> Get();

	// message�� �޸� ����
	~Parser();
};

int main() {
	Parser parser;
	string input;

	// �Է¹޴� �κ�
	for (int i = MAX_INPUT; i > 0; i--) {
		cin >> input;
		parser += input;
	}

	// �Ľ��ϴ� �κ�
	parser.Parsing();

	// ����ϴ� �κ�
	for (auto result : parser.Get())
		cout << result;

	system("pause");
	return 0;
}

String::String(string input)
	: text(input)
{}

bool String::HaveKey(const char key) const {
	if (text.find(key) != string::npos)
		return true;
	return false;
}

void String::BoolToInt() {
	if (text == "yes")
		text = "1";

	if (text == "no")
		text = "0";
}

void String::HexToInt() {
	text = to_string(strtoul(text.c_str(), NULL, 16));
}

string String::Get() {
	return text;
}

void String::operator+= (string userInput) {
	text += userInput;
}

ostream& operator<< (ostream& os, String& message) {
	cout << message.text << endl;
	return os;
}

vector<int> Parser::Search(const string key) {
	vector<int> result;
	int i = 0;

	for (auto nowString : message) {
		if (nowString.Get().find(key) != string::npos) {
			result.push_back(i);
		}
		i++;
	}

	return result;
}

void Parser::Swap(int pos1, int pos2) {
	String temp = message[pos1];
	message[pos1] = message[pos2];
	message[pos2] = temp;
}

void Parser::TidyHex() {
	vector<int> hexVal = (Search("0x"));

	for (auto hexText : hexVal)
		message[hexText].HexToInt();
}

void Parser::TidyBool() {
	vector<int> boolVal = Search("yes");

	for (auto boolText : boolVal) {
		message[boolText].BoolToInt();
		Swap(boolText, boolText + 1);
	}

	boolVal = Search("no");

	for (auto boolText : boolVal) {
		message[boolText].BoolToInt();
		Swap(boolText, boolText + 1);
	}
}

void Parser::Extraction() {
	regex number("[0-9]+");
	
	vector<String>::iterator agency = message.begin();

	while(agency != message.end()) {
		if (!(regex_match(agency->Get(), number)))
			agency = message.erase(agency);
		else
			agency++;
	}
}

void Parser::TieValue() {
	for (int index = 4; index < 21; index += 4) {
		message[index] += "x" + message[index + 1].Get() + ", "
			+ message[index + 2].Get() + ", " + message[index + 3].Get();
	}

	vector<String>::iterator agency = message.begin() + 5;

	while (agency <= message.end() - 2) {
		agency = message.erase(agency, agency + 3);
		if (agency != message.end())
			agency++;
	}
}

vector<String> Parser::Get() {
	return message;
}

void Parser::Parsing() {
	TidyHex();
	TidyBool();
	Extraction();
	TieValue();
}

void Parser::operator+= (string userInput) {
	message.push_back(userInput);
}

Parser::~Parser() {
	vector<String>().swap(message);
}