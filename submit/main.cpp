    #include <iostream>

    struct Node {
    public:
        int key;
        Node* left;
        Node* right;
        int height;
        int size;

        Node() : left(nullptr), right(nullptr), height(0), size(1) {}
    };

    int height(Node* T) {
        return T ? T->height : 0;
    }

    int size(Node* T) {
        return T ? T->size : 0;
    }

    Node* getNodeBST() {
        return new Node();
    }

    Node* maxNode(Node* T) {
        while(T && T->right != nullptr)
            T = T->right;
        return T;
    }

    Node* minNode(Node* T) {
        while(T && T->left != nullptr)
            T = T->left;
        return T;
    }

    Node* searchBST(Node* T, int searchKey) {
        Node* p = T;

        while(p != nullptr) {
            if(searchKey == p->key)
                return p;
            else if(searchKey < p->key)
                p = p->left;
            else
                p = p->right;
        }

        return nullptr;
    }

    Node* searchParent(Node* T, int searchKey) {
        Node* p = T;
        Node* q = nullptr;

        while(p != nullptr) {
            if(searchKey == p->key)
                return q;
            
            q = p;
            if(searchKey < p->key)
                p = p->left;
            else
                p = p->right;
        }

        return nullptr;
    }

    bool insertBST(Node*& T, int newKey) {
        Node* p = T;
        Node* q = nullptr;
        
        while(p != nullptr) {
            if(newKey == p->key)
                return false;

            q = p;
            if(newKey < p->key)
                p = p->left;
            else
                p = p->right;
        }

        Node* newNode = getNodeBST();
        newNode->key = newKey;

        if(T == nullptr)
            T = newNode;
        else if(newKey < q->key)
            q->left = newNode;
        else
            q->right = newNode;
        
        while(q != nullptr) {
            q->size = size(q->left) + size(q->right) + 1;
            q->height = 1;
            if(height(q->left) >= height(q->right))
                q->height += height(q->left);
            else
                q->height += height(q->right);
            q = searchParent(T, q->key);
        }

        return true;
    }

    Node* eraseBST(Node*& T, int deleteKey) {
        Node* p = searchBST(T, deleteKey);
        Node* q = searchParent(T, deleteKey);

        if(p == nullptr)
            return q;

        if(p->left == nullptr && p->right == nullptr) {
            if(q == nullptr)
                T = nullptr;
            else if(q->left == p)
                q->left = nullptr;
            else
                q->right = nullptr;
            delete p;
        }
        else if(p->left == nullptr || p->right == nullptr) {
            Node* r = (p->left != nullptr) ? p->left : p->right;

            if(q == nullptr)
                T = r;
            else if(q->left == p)
                q->left = r;
            else
                q->right = r;
            delete p;
        }
        else {
            Node* r;
            std::string flag;

            if(q == nullptr)
                q = p;
            
            if(height(p->left) > height(p->right))
                r = maxNode(p->left), flag = "LEFT";
            else if(height(p->left) < height(p->right))
                r = minNode(p->right), flag = "RIGHT";
            else {
                if(size(p->left) >= size(p->right))
                    r = maxNode(p->left), flag = "LEFT";
                else
                    r = minNode(p->right), flag = "RIGHT";
            }

            p->key = r->key;
            if(flag == "LEFT")
                eraseBST(p->left, r->key);
            else
                eraseBST(p->right, r->key);
        }

        while(q != nullptr) {
            q->size = size(q->left) + size(q->right) + 1;
            q->height = 1;
            if(height(q->left) >= height(q->right))
                q->height += height(q->left);
            else
                q->height += height(q->right);
            q = searchParent(T, q->key);
        }

        return p;
    }

    void inorder(Node* T) {
        if(T != nullptr) {
            std::cout << '<';
            if(T->left != nullptr)
                inorder(T->left);

            std::cout << ' ' << T->key << ' ';
            
            if(T->right != nullptr)
                inorder(T->right);
            std::cout << '>';
        }
    }

    void clear(Node* T) {
        if(T != nullptr) {
            clear(T->left);
            clear(T->right);
            delete T;
        }
    }

    int main() {
        Node* tree = nullptr;

        char command;
        int key;
        
        while(std::cin >> command >> key) {
            if(command == 'i') {
                if(insertBST(tree, key) == false) {
                    std::cout << "i " << key << ": The key already exists" << std::endl;
                    continue;
                }
            }
            else if(command == 'd') {
                if(eraseBST(tree, key) == nullptr) {
                    std::cout << "d " << key << ": The key does not exist" << std::endl;
                    continue;
                }
            }

            inorder(tree);
            std::cout << std::endl;
        }
        
        clear(tree);

        return 0;
    }
