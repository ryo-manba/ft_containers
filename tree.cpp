#include <iostream>

//*********************
using namespace std;
//********************

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

// 木の高さを返す
int height(Node *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return N->height;
}

Node* newNode(int key)
{
    Node* node   = new Node();
    node->key    = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return (node);
}

// 右回転
Node *rightRotate(Node *y)
{
    Node* x  = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left  = T2;
    // heightはleft, rightの大きい方 + 1
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

// 左回転
Node* leftRotate(Node *x)
{
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// 各ノードの平衡係数を取得
int  getBalanceFactor(Node* N)
{
    if (N == NULL) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

Node* insertNode(Node* node, int key)
{
    // 正しい位置を見つけてノードを挿入する
    if (node == NULL)
    {
        return newNode(key);
    }
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // 各ノードの平衡係数を更新しツリーのバランスをとる
    node->height = 1 + max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);

    // 平行係数が1より大きい場合
    if (balanceFactor > 1)
    {
        if (key < node->left->key)
        {
            return rightRotate(node);
        }
        else if (key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    // 平行係数が-1より小さい場合
    if (balanceFactor < -1)
    {
        if (key > node->right->key)
        {
            return leftRotate(node);
        }
        else if (key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

// 最小値を持つノード
// 左をたどっていく
Node* nodeWithMinValue(Node* node)
{
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key)
{
    // nodeを見つけて削除する
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Node* temp = nodeWithMinValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    if (root == NULL) {
        return root;
    }
    // 各ノードの平行係数を更新しツリーのバランスをとる
    root->height = 1 + max(height(root->left), height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(root->left) >= 0)
        {
            return rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1)
    {
        if (getBalanceFactor(root->right) <= 0)
        {
            return leftRotate(root);
        }
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

// Treeの中身を出力する
void printTree(Node* root, string indent, bool last)
{
    if (root != NULL)
    {
        cout << indent;
        if (last)
        {
            cout << "R----";
            indent += "   ";
        }
        else
        {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main()
{
    Node* root = NULL;
    root       = insertNode(root, 1);
    root       = insertNode(root, 2);
    root       = insertNode(root, 3);
    root       = insertNode(root, 4);
    root       = insertNode(root, 5);
    root       = insertNode(root, 6);
    root       = insertNode(root, 7);
    root       = insertNode(root, 8);

    printTree(root, "", true);

    const int delete_key = 4;
    root = deleteNode(root, delete_key);
    cout << "Delete : " << delete_key << endl;
    cout << "After deleting " << endl;
    printTree(root, "", true);
}
