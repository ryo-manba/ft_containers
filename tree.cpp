#include <fstream>
#include <iostream>
#include <queue>

/**
 * 参考URL: https://kotaro7750.hatenablog.com/entry/avl_tree
 */

template <typename T>
struct BinTreeNode
{
    T data;
    struct BinTreeNode<T> *Parent;
    struct BinTreeNode<T> *LHS;
    struct BinTreeNode<T> *RHS;
    int height;
    int bias;
};

template <typename T>
class BinTree
{
public:
    BinTree();
    ~BinTree();

    BinTreeNode<T> *getRoot();
    bool search(T data);
    bool append(T data);
    bool erase(T data);
    void graph();
    void animation(std::string dir);
    void graphDebug();
    bool checkBin();
    bool checkAVL();

private:
    struct BinTreeNode<T> *root;
    struct BinTreeNode<T> *nullNode;
    int animationCount;

    int bias(struct BinTreeNode<T> *node);
    void modHeight(struct BinTreeNode<T> *node);

    BinTreeNode<T> *searchNode(struct BinTreeNode<T> *node, T data);
    BinTreeNode<T> *searchParentNode(struct BinTreeNode<T> *node, T data);

    struct BinTreeNode<T> *LeftMax(struct BinTreeNode<T> *node);

    void Replace(struct BinTreeNode<T> *before, struct BinTreeNode<T> *after);

    struct BinTreeNode<T> *RotateR(struct BinTreeNode<T> *node);
    struct BinTreeNode<T> *RotateL(struct BinTreeNode<T> *node);
    struct BinTreeNode<T> *RotateRL(struct BinTreeNode<T> *node);
    struct BinTreeNode<T> *RotateLR(struct BinTreeNode<T> *node);

    void ToDot();

    void BalanceA(struct BinTreeNode<T> *node);
    void BalanceE(struct BinTreeNode<T> *node);

    void DumpNode(struct BinTreeNode<T> *node);
};

// root用のダミーノードを作成する。
template <typename T>
inline BinTree<T>::BinTree()
{
    nullNode         = new struct BinTreeNode<T>;
    nullNode->LHS    = nullptr;
    nullNode->RHS    = nullptr;
    nullNode->Parent = nullptr;
    nullNode->height = 0;

    root = nullNode;

    animationCount = 0;
}

// queueを用いて全ての木を辿りながら順番にdeleteしていく。
template <typename T>
BinTree<T>::~BinTree<T>()
{
    std::queue<struct BinTreeNode<T> *> queue;

    if (root == nullNode)
    {
        delete nullNode;
        return;
    }

    if (root->LHS != nullNode)
    {
        queue.push(root->LHS);
    }
    if (root->RHS != nullNode)
    {
        queue.push(root->RHS);
    }

    // BFSのようなイメージで木を辿りながらdeleteしていく
    while (!queue.empty())
    {
        struct BinTreeNode<T> *front = queue.front();
        queue.pop();

        if (front->LHS != nullNode)
        {
            queue.push(front->LHS);
        }
        if (front->RHS != nullNode)
        {
            queue.push(front->RHS);
        }
        delete front;
    }
    delete nullNode;
    delete root;
}

// ゲッター
template <typename T>
inline BinTreeNode<T> *BinTree<T>::getRoot()
{
    return root;
}

/**
 * utility
 */

// nodeはnullNodeであってはならない。
template <typename T>
inline int BinTree<T>::bias(struct BinTreeNode<T> *node)
{
    return node->LHS->height - node->RHS->height;
}

// 木の高さとバイアスを更新する
// 木の高さ = 1 + max(左の木の高さ, 右の木の高さ)
// バイアス = 左の木の高さ - 右の木の高さ
template <typename T>
inline void BinTree<T>::modHeight(struct BinTreeNode<T> *node)
{
    int lHeight  = node->LHS->height;
    int rHeight  = node->RHS->height;
    node->height = 1 + std::max(lHeight, rHeight);
    node->bias   = lHeight - rHeight;
}

// Replace(aノード,bノード)
// aノードをルートとする部分木をbノードをルートとする部分木に置き換える
template <typename T>
void BinTree<T>::Replace(struct BinTreeNode<T> *before,
                         struct BinTreeNode<T> *after)
{
    struct BinTreeNode<T> *parentNode = before->Parent;

    // beforeがrootだったらそのままafterをrootにする
    if (before == root)
    {
        root = after;
        // beforeが親の左部分木だった場合
    }
    else if (parentNode->LHS == before)
    {
        parentNode->LHS = after;
    }
    else
    {
        // beforeが親の右部分木だった場合
        parentNode->RHS = after;
    }
    // afterの親を繋ぎ変える
    after->Parent = parentNode;
}

/**
 * search
 */
template <typename T>
bool BinTree<T>::search(T data)
{
    struct BinTreeNode<T> *result = searchNode(root, data);

    // dataが見つからない場合
    if (result == nullNode)
    {
        return false;
    }

    return true;
}

template <typename T>
BinTreeNode<T> *BinTree<T>::searchNode(struct BinTreeNode<T> *node, T data)
{
    // nodeに要素が存在しない場合
    if (node == nullNode)
    {
        return node;
    }

    struct BinTreeNode<T> *tmp = node;

    while (tmp != nullNode)
    {
        if (tmp->data == data)
        {
            break;
        }

        // 要素が小さい場合は左を探索する
        if (data < tmp->data)
        {
            tmp = tmp->LHS;
        }
        else
        {
            // 要素が大きい場合は右を探索する
            tmp = tmp->RHS;
        }
    }
    return tmp;
}

/**
 * append
 */
template <typename T>
bool BinTree<T>::append(T data)
{
    // 初めて要素を追加する場合
    if (root == nullNode)
    {
        struct BinTreeNode<T> *newNode = new struct BinTreeNode<T>;
        newNode->data                  = data;

        // 親と左右の部分木をnullNodeに設定する
        newNode->Parent = nullNode;
        newNode->LHS    = nullNode;
        newNode->RHS    = nullNode;
        newNode->height = 1;
        newNode->bias   = 0;

        root = newNode;
        return true;
    }

    struct BinTreeNode<T> *parent = searchParentNode(root, data);

    // 同じ値だったら追加せずにfalseを返す
    if (parent->data == data)
    {
        return false;
    }

    if (data < parent->data)
    {
        if (parent->LHS != nullNode)
        {
            // 親の値よりも小さく、既に左に部分木がある場合はfalseを返す
            return false;
        }
    }
    else
    {
        if (parent->RHS != nullNode)
        {
            // 親の値よりも大きく、既に右に部分木がある場合はfalseを返す
            return false;
        }
    }

    struct BinTreeNode<T> *newNode = new struct BinTreeNode<T>;
    newNode->data                  = data;
    newNode->Parent                = parent;
    newNode->LHS                   = nullNode;
    newNode->RHS                   = nullNode;
    newNode->height                = 1;
    newNode->bias                  = 0;

    // 値の大小比較をして適切な方向にノードを追加する
    // 追加したノードに対してBalanceAを実行する
    if (data < parent->data)
    {
        parent->LHS = newNode;
        BalanceA(parent->LHS);
    }
    else
    {
        parent->RHS = newNode;
        BalanceA(parent->RHS);
    }

    return true;
}

// 子ノードが "data" を持つ親ノードのポインタを返す．
// 引数で渡されるnodeはrootなので引数で受けなくても良いかも(メンバのrootで置き換えられる)
template <typename T>
BinTreeNode<T> *BinTree<T>::searchParentNode(struct BinTreeNode<T> *node,
                                             T data)
{
    // ノードがルートまたはnullNodeの場合、自分自身を返す。
    if (node->data == data || node == nullNode)
    {
        return node;
    }

    struct BinTreeNode<T> *parent = node;
    struct BinTreeNode<T> *canditate;
    if (data < node->data)
        canditate = node->LHS;
    else
        canditate = node->RHS;

    // 一致するまでノードを辿っていく
    while (canditate != nullNode)
    {
        if (canditate->data == data)
        {
            break;
        }
        parent = canditate;
        if (data < canditate->data)
            canditate = canditate->LHS;
        else
            canditate = canditate->RHS;
    }
    // 一致したnodeの親ノード または nullNodeを返す
    return parent;
}

/**
 * erase
 */
template <typename T>
bool BinTree<T>::erase(T data)
{
    struct BinTreeNode<T> *deleteNode = searchNode(root, data);

    // 消したい要素が見つからない場合はfalseを返す
    if (deleteNode == nullNode)
    {
        return false;
    }

    // 削除対象ノードが左部分木を持たない場合
    if (deleteNode->LHS == nullNode)
    {
        // 削除対象ノードと右の子ノードを入れ替える
        Replace(deleteNode, deleteNode->RHS);
        BalanceE(deleteNode->RHS);
        delete deleteNode;
    }
    else
    {
        // 削除対象ノードが左部分木を持つ場合
        // 左部分木構造の中の最大ノードを探す
        struct BinTreeNode<T> *leftMaxNode = LeftMax(deleteNode);
        deleteNode->data                   = leftMaxNode->data;

        // 削除対象ノードと左部分木の中の最大要素を入れ替える
        Replace(leftMaxNode, leftMaxNode->LHS);
        BalanceE(leftMaxNode->LHS);
        delete leftMaxNode;
    }
    return true;
}

template <typename T>
struct BinTreeNode<T> *BinTree<T>::LeftMax(struct BinTreeNode<T> *node)
{
    struct BinTreeNode<T> *leftMaxNode = node->LHS;

    // 左部分木の中で最大要素まで辿る
    while (leftMaxNode->RHS != nullNode)
    {
        leftMaxNode = leftMaxNode->RHS;
    }
    return leftMaxNode;
}

/**
 * rotate
 */

// 右回転: 傾き “-1” よりも小さい(左部分木の方が高い場合)
//      node            LHS
//   LHS    Z   -->    X   node
//  X   Y                 Y    Z
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateR(struct BinTreeNode<T> *node)
{
    struct BinTreeNode<T> *LHS = node->LHS;
    struct BinTreeNode<T> *Y   = node->LHS->RHS;

    // 回転後のルートをLHSに設定する
    struct BinTreeNode<T> *partitionRoot = LHS;

    node->LHS = Y;
    if (Y != nullNode)
    {
        Y->Parent = node;
    }

    partitionRoot->RHS = node;
    // nodeをルートとする部分木をLHSをルートとする部分木に置き換える
    Replace(node, LHS);
    node->Parent = LHS;

    modHeight(partitionRoot->RHS);
    modHeight(partitionRoot);

    // 戻り値は回転後のルート
    return partitionRoot;
}

// 左回転: 傾き “1” よりも大きい(右部分木の方が高い)
//   node                RHS
//  X    RHS   -->   node   Z
//     Y    Z       X    Y
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateL(struct BinTreeNode<T> *node)
{
    struct BinTreeNode<T> *RHS = node->RHS;
    struct BinTreeNode<T> *Y   = node->RHS->LHS;

    struct BinTreeNode<T> *partitionRoot = RHS;

    node->RHS = Y;
    if (Y != nullNode)
    {
        Y->Parent = node;
    }

    partitionRoot->LHS = node;
    // nodeをルートとする部分木をRHSをルートとする部分木に置き換える
    Replace(node, RHS);
    node->Parent = RHS;

    modHeight(partitionRoot->LHS);
    modHeight(partitionRoot);

    // 戻り値は回転後のルート
    return partitionRoot;
}

// 2重回転（右->左）
// 傾き “1” より大きい（右部分木の方が高い）
// 右の子ノードの傾き “-1” 以下（左部分木の方が高い）

//   node                   LHS
// W      RHS          node     RHS
//     LHS   Z  -->   W    X   Y   Z
//    X   Y
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateRL(struct BinTreeNode<T> *node)
{
    RotateR(node->RHS);
    return RotateL(node);
}

// 2重回転（左->右）
// 傾き “-1” より小さい（左部分木の方が高い）
// 左の子ノードの傾き “1” 以上（右部分木の方が高い）
//       node            RHS
//   LHS      Z      LHS     node
//  W   RHS     --> W   X   Y    Z
//     X   Y
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateLR(struct BinTreeNode<T> *node)
{
    RotateL(node->LHS);
    return RotateR(node);
}

/**
 * balance
 */

template <typename T>
void BinTree<T>::BalanceA(struct BinTreeNode<T> *node)
{
    struct BinTreeNode<T> *targetNode = node;

    while (targetNode->Parent != nullNode)
    {
        struct BinTreeNode<T> *parentNode = targetNode->Parent;
        int height                        = parentNode->height;

        // ターゲットが左部分木の場合
        if (parentNode->LHS == targetNode)
        {
            // 傾きが "2" の場合、回転する
            if (bias(parentNode) == 2)
            {
                if (bias(parentNode->LHS) >= 0)
                {
                    parentNode = RotateR(parentNode);
                }
                else
                {
                    parentNode = RotateLR(parentNode);
                }
            }
            else
            {
                // 傾きが1以下の場合は高さを更新するだけ
                modHeight(parentNode);
            }
        }
        else
        {
            // ターゲットが右部分木の場合
            // 傾きが "-2" の場合、回転する
            if (bias(parentNode) == -2)
            {
                if (bias(parentNode->RHS) <= 0)
                {
                    parentNode = RotateL(parentNode);
                }
                else
                {
                    parentNode = RotateRL(parentNode);
                }
            }
            else
            {
                // 傾きが-1以上の場合は高さを更新するだけ
                modHeight(parentNode);
            }
        }

        // 高さが親ノードの高さと同じになったら終了する
        if (height == parentNode->height)
        {
            break;
        }

        // 親ノードを辿っていく
        targetNode = parentNode;
    }
}

// BalanceAとほぼ同じ処理をする
// biasで確認する向きが変わっただけ
template <typename T>
void BinTree<T>::BalanceE(struct BinTreeNode<T> *node)
{
    struct BinTreeNode<T> *targetNode = node;

    while (targetNode->Parent != nullNode)
    {
        struct BinTreeNode<T> *parentNode = targetNode->Parent;
        int height                        = parentNode->height;

        // ターゲットが右部分木の場合
        if (parentNode->RHS == targetNode)
        {
            // 傾きが "2" の場合、回転する
            if (bias(parentNode) == 2)
            {
                if (bias(parentNode->LHS) >= 0)
                {
                    parentNode = RotateR(parentNode);
                }
                else
                {
                    parentNode = RotateLR(parentNode);
                }
            }
            else
            {
                // 傾きが1以下の場合は高さを更新するだけ
                modHeight(parentNode);
            }
        }
        else
        {
            // ターゲットが左部分木の場合
            // 傾きが "-2" の場合、回転する
            if (bias(parentNode) == -2)
            {
                if (bias(parentNode->RHS) <= 0)
                {
                    parentNode = RotateL(parentNode);
                }
                else
                {
                    parentNode = RotateRL(parentNode);
                }
            }
            else
            {
                // 傾きが-1以上の場合は高さを更新するだけ
                modHeight(parentNode);
            }
        }
        // 高さが親ノードの高さと同じになったら終了する
        if (height == parentNode->height)
        {
            break;
        }

        // 親ノードを辿っていく
        targetNode = parentNode;
    }
}

/**
 * debug
 */

template <typename T>
void BinTree<T>::graph()
{
    ToDot();
    //    system("rm bintree.dot");
    //    system("code bintree.png");
    //    system("rm bintree.png");
}

template <typename T>
void BinTree<T>::graphDebug()
{
    std::ofstream ofs("bintree.dot");

    ofs << "digraph BinTree {" << std::endl;
    ofs << "graph [centering=\"false\",ranksep=0.2,ordering=out,nodesep=0.5];"
        << std::endl;
    ofs << "node [shape=circle,width = 0.2, height = 0.2, margin = "
           "0.01];"
        << std::endl;

    std::queue<struct BinTreeNode<T> *> queue;
    queue.push(root);

    int nullCount = 0;

    while (!queue.empty() && root != nullNode)
    {
        struct BinTreeNode<T> *front = queue.front();
        queue.pop();

        ofs << front->data << "[label=\"" << front->data << "("
            << front->Parent->data << "," << front->height << "," << bias(front)
            << ")\"];" << std::endl;
        if (front != root)
        {
            ofs << front->data << " -> " << front->Parent->data << ";"
                << std::endl;
        }

        if (front->LHS != nullNode)
        {
            ofs << front->data << " -> " << front->LHS->data << ";"
                << std::endl;
            queue.push(front->LHS);
        }
        else
        {
            ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
                << std::endl;
            ofs << front->data << " -> "
                << "nullNode" << nullCount << ";" << std::endl;
            nullCount++;
        }
        if (front->RHS != nullNode)
        {
            ofs << front->data << " -> " << front->RHS->data << ";"
                << std::endl;
            queue.push(front->RHS);
        }
        else
        {
            ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
                << std::endl;
            ofs << front->data << " -> "
                << "nullNode" << nullCount << ";" << std::endl;
            nullCount++;
        }
    }

    ofs << "}" << std::endl;
    system("dot -Kdot -Tpng bintree.dot -obintree.png");
    system("rm bintree.dot");
    system("eog bintree.png");
    system("rm bintree.png");
}

template <typename T>
void BinTree<T>::ToDot()
{
    std::ofstream ofs("bintree.dot");

    ofs << "digraph BinTree {" << std::endl;
    ofs << "graph [centering=\"false\",ranksep=0.2,ordering=out,nodesep=0.5];"
        << std::endl;
    ofs << "node [shape=circle,width = 0.2, height = 0.2, margin = "
           "0.01];"
        << std::endl;

    std::queue<struct BinTreeNode<T> *> queue;
    queue.push(root);

    int nullCount = 0;

    while (!queue.empty() && root != nullNode)
    {
        struct BinTreeNode<T> *front = queue.front();
        queue.pop();

        ofs << front->data << "[label=\"" << front->data << "\"];" << std::endl;

        if (front->LHS != nullNode)
        {
            ofs << front->data << " -> " << front->LHS->data << ";"
                << std::endl;
            queue.push(front->LHS);
        }
        else
        {
            ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
                << std::endl;
            ofs << front->data << " -> "
                << "nullNode" << nullCount << "[style=invis];" << std::endl;
            nullCount++;
        }

        if (front->RHS != nullNode)
        {
            ofs << front->data << " -> " << front->RHS->data << ";"
                << std::endl;
            queue.push(front->RHS);
        }
        else
        {
            ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
                << std::endl;
            ofs << front->data << " -> "
                << "nullNode" << nullCount << "[style=invis];" << std::endl;
            nullCount++;
        }
    }

    ofs << "}" << std::endl;

    system("dot -Kdot -Tpng bintree.dot -obintree.png");
}

template <typename T>
void BinTree<T>::animation(std::string dir)
{
    ToDot();
    system("rm bintree.dot");

    std::string moveQuery =
        "mv bintree.png " + dir + "/" + std::to_string(animationCount) + ".png";
    system(moveQuery.c_str());

    animationCount++;
}

template <typename T>
bool BinTree<T>::checkBin()
{
    if (root == nullNode)
    {
        return true;
    }

    std::queue<struct BinTreeNode<T> *> queue;
    queue.push(root);

    while (!queue.empty())
    {
        struct BinTreeNode<T> *tmp = queue.front();
        queue.pop();
        T left  = tmp->LHS == nullNode ? tmp->data - 1 : tmp->LHS->data;
        T right = tmp->RHS == nullNode ? tmp->data + 1 : tmp->RHS->data;

        if (tmp->data <= left || right <= tmp->data)
        {
            DumpNode(tmp);
            return false;
        }

        if (tmp->LHS != nullNode)
        {
            queue.push(tmp->LHS);
        }

        if (tmp->RHS != nullNode)
        {
            queue.push(tmp->RHS);
        }
    }
    return true;
}

template <typename T>
bool BinTree<T>::checkAVL()
{
    if (root == nullNode)
    {
        return true;
    }

    std::queue<struct BinTreeNode<T> *> queue;
    queue.push(root);

    while (!queue.empty())
    {
        struct BinTreeNode<T> *tmp = queue.front();
        queue.pop();

        int tmpBias = bias(tmp);

        if (tmpBias <= -2 || 2 <= tmpBias)
        {
            DumpNode(tmp);
            return false;
        }

        if (tmp->LHS != nullNode)
        {
            queue.push(tmp->LHS);
        }

        if (tmp->RHS != nullNode)
        {
            queue.push(tmp->RHS);
        }
    }
    return true;
}

template <typename T>
void BinTree<T>::DumpNode(struct BinTreeNode<T> *node)
{
    if (node == nullNode)
    {
        std::cout << "nullNode" << std::endl;
        return;
    }
    std::cout << "data:" << node->data << ",height:" << node->height
              << ",bias:" << bias(node) << ",LHS:" << node->LHS->data
              << ",RHS:" << node->RHS->data << std::endl;

    if (node->LHS == nullNode)
    {
        std::cout << "LHS is nullNode" << std::endl;
    }
    if (node->RHS == nullNode)
    {
        std::cout << "RHS is nullNode" << std::endl;
    }
    if (node == root)
    {
        std::cout << "root node" << std::endl;
    }
}

int main()
{
    BinTree<int> tree;

    tree.append(1);
    tree.append(2);
    tree.append(3);
    tree.append(4);
    tree.append(5);
    tree.append(6);
    tree.append(7);
    tree.graph();

    return (0);
}
