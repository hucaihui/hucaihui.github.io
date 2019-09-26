#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
	int val;
	Node *left;
	Node *right;
	Node(int d) {
		val = d;
		left = NULL;
		right = NULL;
	}
};

Node* buildTree(vector<int> nums) {
	if (0 == nums.size()) return nullptr;
	
	Node* root = new Node(nums[0]);
	queue<Node *> q;
	q.push(root);
	for (int i = 1; i <= nums.size() - 1; ++i) {
		Node *node = q.front();
		q.pop();   //É¾³ýÍ·ÔªËØ

		node->left = new Node(nums[i]);;
		node->right = new Node(nums[++i]);

		q.push(node->left);
		q.push(node->right);
	}
	return root;
}

void mid(Node* root,vector<int> &res) {
	if (root) {
		mid(root->left, res);
		res.push_back(root->val);
		mid(root->right, res);
	}
}

vector<int> solution(vector<int> nums) {
	vector<int> res;
	Node *root = buildTree(nums);
	mid(root, res);
	return res;
}

int main() {
	vector<int> nums = { 1,2,3,4,5,6,7 };     
	vector<int> res = solution(nums);    

	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	system("pause");
	return 0;
}
