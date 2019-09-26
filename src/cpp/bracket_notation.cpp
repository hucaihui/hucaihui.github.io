#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Node{
	char val;
	Node *left;
	Node *right;
	Node(char _val) {
		val = _val;
		left = nullptr;
		right = nullptr;
	}
};


void midOrder(Node* root) {   //ÖÐÐò±éÀú
	if (root) {
		midOrder(root->left);
		cout << root->val << " ";
		midOrder(root->right);
	}
}

void midOrder(Node* root, vector<int> &res) {
	if (!root) {
		midOrder(root->left, res);
		res.push_back(root->val);
		midOrder(root->right, res);
	}
}

void buildTree(Node* &root, const string str) {  //´´½¨¶þ²æÊ÷
	stack<Node*> st;
	Node *node = nullptr;
	int k = 0;  // =1×óÊ÷  =2ÓÒÊ÷
	int j = 0;
	char ch = str[j];
	while (ch != '\0') {
		switch (ch)
		{
		case '(': st.push(node); k = 1; break;
		case ')': st.pop(); break;
		case ',': k = 2; break;   //ÓÒ×ÓÊ÷
		default:
			node = new Node(ch);
			if (root == nullptr) root = node;
			else  k == 1 ? st.top()->left = node : st.top()->right = node ;
		}
		ch = str[++j];
	}
}


int main() {

	string str = "A(B(D(,G)),C(E,F))";

	Node *root = nullptr;
	buildTree(root, str);
	midOrder(root);

	system("pause");
	return 0;
}
