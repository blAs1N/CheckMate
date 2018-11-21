#include "AVLNode.h"

AVLNode::AVLNode()
	: key(""),
	value(""),
	left(nullptr),
	right(nullptr)
{}

AVLNode::~AVLNode() {
	if (left) {
		delete left;
		left = nullptr;
	}

	if (right) {
		delete right;
		right = nullptr;
	}
}

std::ostream& operator<<(std::ostream& os, AVLNode* node) {
	if (node)
		os << "�ܾ�: " << node->key << ", ��: " << node->value;

	else
		os << "�������� �ʴ� �ܾ��Դϴ�.";

	return os;
}