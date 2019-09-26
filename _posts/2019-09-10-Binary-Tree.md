---
title: 二叉树
tag: tree c++ 
layout: post
---

## 二叉树的性质
性质1：在二叉树的第$i$层上至多有$2^{i-1}$个结点($i>=1$)

性质2：深度为$k$的二叉树至多有$2^{k}-1$个结点($k>=1$)

性质3：对任何一棵二叉树，终端结点（叶子结点）数为$n_0$，度为2的结点数为$n_2$,则$n_0=n_2+1$

性质4：具有$n$个结点的完全二叉树的深度为$\lfloor log_2n \rfloor+1$

性质5：对一棵有n个结点的完全二叉树按层序编号，对作一结点$i$：
- 1、$i=1$，则结点$i$是根结点。
- 2、$i>1$，其双亲结点是$\lfloor i/2 \rfloor$.
- 3、$i$有左或右孩子的情况下，$i$的左孩子是$2i$，右孩子是$2i+1$

## 二叉树的遍历
### 前序
<img src="https://github.com/hucaihui/hucaihui.github.io/tree/master/img/preOrder.png" width="240" align="middle" />  

> 遍历的顺序为：ABDGHCEIF
### 中序
> 遍历的顺序为：GDHBAEICF

```
void midOrder(Node* root) {   //中序遍历
    if (root) {
        midOrder(root->left);
        cout << root->val << " ";
        midOrder(root->right);
    }
}
```
### 后序
> 遍历的顺序为：GHDBIEFCA
### 层序
> 遍历的顺序为：ABCDEFGHI

## 二叉树的还原-代码实现
### 括号表示法还原
二叉树括号表示规则：
- 1、若树T为空树，则其括号表示为空
- 2、若树T只包含一个结点，则其括号表示即为该结点本身
- 3、若树T由根结点A和它的m棵子树T1,T2,...,Tm构成，则其括号表示为：A(T1的括号表示，T2的括号表示,... ,Tm的括号表示)
<img src="https://github.com/hucaihui/hucaihui.github.io/tree/master/img/bracketNotation.png" height="200" align="middle"/>

表示：A(B,C(F,G,H),D,E(I,J))

实现方法：
- 1、从左到右扫描树的括号表示；
- 2、每当遇到左括号时，其前一个结点进栈，并读入下一个符号；
- 3、每当遇到右括号时，栈顶元素出栈。说明以栈顶元素为根的树（子树）构造完毕，此时若栈为空，算法结束，否则读入下一个符号
- 4、每当遇到结点时，则它一定为栈顶元素的子女，将其挂到栈顶元素的某子女位置上，并读入下一个符号；
- 5、每当遇到“，”，则略过该符号，并读入下一个符号。

二叉树括号表示例：A(B(D(,G)),C(E,F))

[cpp实现](https://github.com/hucaihui/hucaihui.github.io/tree/master/src/cpp/bracket_notation.cpp)
```
//节点定义
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

//建树
void buildTree(Node* &root, const string str) {  //创建二叉树
    stack<Node*> st;
    Node *node = nullptr;
    int k = 0;  // =1左树  =2右树
    int j = 0;
    char ch = str[j];
    while (ch != '\0') {
        switch (ch)
        {
        case '(': st.push(node); k = 1; break;
        case ')': st.pop(); break;
        case ',': k = 2; break;   //右子树
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
```

### 完全二叉树还原（层序遍历）

[cpp实现](https://github.com/hucaihui/hucaihui.github.io/tree/master/src/cpp/symbol_notation1.cpp)
```
//对于不带#号的层序遍历， 
Node* buildTree(vector<int> nums) {
	if (0 == nums.size()) return nullptr;
	
	Node* root = new Node(nums[0]);
	queue<Node *> q;
	q.push(root);
	for (int i = 1; i <= nums.size() - 1; ++i) {
		Node *node = q.front();
		q.pop();   //删除头元素
		node->left = new Node(nums[i]);;
		node->right = new Node(nums[++i]);
		q.push(node->left);
		q.push(node->right);
	}
	return root;
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
```

### #号表示法还原（层序遍历）

实现方法：
- 1、对每个结点写入队列；
- 2、flag=1，为左孩子，遇#号，flag变为2，转为右孩子；
- 3、flag=2，为右孩子，遇#号，flag++,至下一步弹出下一个父结点。

[cpp实现](https://github.com/hucaihui/hucaihui.github.io/tree/master/src/cpp/symbol_notation2.cpp)
```
Node* buildTree(string seq) {
    //if (0 == seq.length()) return nullptr;
    int flag = 1;    // =1：左孩子   =2：右孩子
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

int main() {
    string seq = "#1#234567";
    Node *root = buildTree(seq);
    midOrder(root);

    system("pause");
    return 0;
}
```

### 根据**前序+中序**还原

### 根据**前序+后序**还原