#include "AVLNode.h"

AVLNode::AVLNode()
	: key(""),
	value(""),
	left(nullptr),
	right(nullptr)
{}

AVLNode::~AVLNode() {
	delete left;
	left = nullptr;

	delete right;
	right = nullptr;
}

std::ostream& operator<<(std::ostream& os, AVLNode* node) {
	if (node)
		os << "�ܾ�: " << node->key << ", ��: " << node->value;

	else
		os << "�������� �ʴ� �ܾ��Դϴ�.";

	return os;
}