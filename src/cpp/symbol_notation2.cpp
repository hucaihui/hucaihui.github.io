#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
	char val;
	Node *left;
	Node *right;
	Node(char d) {
		val = d;
		left = NULL;
		right = NULL;
	}
};

Node* buildTree(string seq) {
	if (0 == seq.length()) return nullptr;

	int flag = 1;    // =1£º×óº¢×Ó   =2£ºÓÒº¢×Ó
	queue<Node *> q;
	Node *root = nullptr;
	for (int i = 0; i < seq.length(); ++i) {
		if ('#'==seq[i]){
			flag++;
			continue;
		}
		if (nullptr == root) {
			root = new Node(seq[i]);
			q.push(root);
			flag = 1;
			continue;
		}
		
		Node *node = q.front();
		switch (flag)
		{
		case 1:
			node->left = new Node(seq[i]);
			q.push(node->left);
			flag = 2;
			break;
		case 2:
			node->right = new Node(seq[i]);
			q.push(node->right);
			flag = 1;
			q.pop();
			break;
		default:
			flag = 1;
			q.pop();
			break;
		}
	}
	return root;
}

void midOrder(Node* root) {
	if (root) {
		midOrder(root->left);
		cout << root->val << " ";
		midOrder(root->right);
	}
}


int main() {

	string seq = "#1#234567";
	Node *root = buildTree(seq);
	midOrder(root);

	//system("pause");
	return 0;
}
