#include <bits/stdc++.h>

using namespace std;

ifstream in;
ofstream out;

struct Node {
    int data;
    Node *left;
    Node *right;
};

Node *createNode(int data) {
    Node *node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insertNode(Node *root, int data) {
    if (!root) return createNode(data);

    else if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

bool deleteNode(Node *&root, int data) {
    if (!root) return false;  // tree is empty

    // if the data to be deleted is smaller than the root's data,
    // then it lies in the left subtree
    if (data < root->data) {
        return deleteNode(root->left, data);
    }
    // if the data to be deleted is greater than the root's data,
    // then it lies in the right subtree
    else if (data > root->data) {
        return deleteNode(root->right, data);
    }
    // if the data is same as root's data, then this is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (!root->left) {
            Node *temp = root->right;
            free(root);
            root = temp;
            return true;
        } else if (!root->right) {
            Node *temp = root->left;
            free(root);
            root = temp;
            return true;
        }
        // node with two children: get the inorder successor (smallest
        // in the right subtree)
        else {
            Node *temp = root->right;
            while (temp->left) temp = temp->left;

            // copy the inorder successor's content to this node
            root->data = temp->data;

            // delete the inorder successor
            return deleteNode(root->right, temp->data);
        }
    }
}

bool search(Node *root, int data) {
    if (!root) return false;  // tree is empty

    if (data == root->data) return true;  // data is found

    // if the data is smaller than the root's data,
    // then it lies in the left subtree
    if (data < root->data) {
        return search(root->left, data);
    }
    // otherwise, it lies in the right subtree
    else {
        return search(root->right, data);
    }
}

void preorder(Node *root) {
    if (root == NULL) return;
    out << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    out << root->data << " ";
    inorder(root->right);
}

void postorder(Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    out << root->data << " ";
}

void levelOrder(Node *root) {
    if (!root) return;  // tree is empty

    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *node = q.front();
        q.pop();

        out << node->data << " ";  // visit the node

        // add the children of the node to the queue
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

vector<int> readline2Vector(){
    vector<int> result;
    string line;
    // in.ignore();
    // WTF !!!!
    getline(in, line);
    getline(in, line);
    istringstream ss(line);
    string del;
    while (getline(ss, del, ' ')) {
        if (stoi(del)  == -1)
            break;
        result.push_back(stoi(del));
    }
    return result;
};

int main() {
    Node *root = NULL;

    char command = '\0';
    string filename = "";

    in.open("sample.txt");
    out.open("output.txt");

    // read input file

    cout << "File name: ";
    cin >> filename;
    out<< "File name: "<< filename << "\n";

    while (in >> command && !in.eof()) {
        // Usage message
        out << "\n(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint 4 kinds of orders.\n(E)xit\n";
        switch (tolower(command)) {
        case 'i': {

            out << "\nInsert:\n";

            for(auto i : readline2Vector()){
                if (!search(root, i)){
                    root = insertNode(root, i);
                    out << "Number " << i << " is inserted.\n";
                } else {
                    out << "Error !Number " << i << " exists.\n";
                }
            }
            break;
        }

        case 'd': {
            out << "\nDelete:\n";
            for (auto i : readline2Vector()) {
                if (!deleteNode(root, i))
                    out << "Number " << i << " is not exist.\n";
                else {
                    out << "Number " << i << " is deleted.\n";
                }
            }
            break;
        }
        case 's': {
            out << "\nSearch:\n";
            for (auto i : readline2Vector()) {
                if (search(root, i))
                    out << "Bingo! " << i << " is found.\n";
                else {
                    out << "Sorry! " << i << " is not found.\n";
                }
            }
            break;
        }
        case 'p': {
            out << "\nPrint:";
            // 列印出前序、中序和後序
            out << "\nThe tree in prefix order: ";
            preorder(root);
            out << "\nThe tree in infix order :";
            inorder(root);
            out << "\nThe tree in post order :";
            postorder(root);
            out << "\nThe tree in level order :";
            levelOrder(root);
            out << "\n";
            break;
        } 
        case 'e':
            out << "\nExit\n";
            return 0;
        default:
            break;
        }
    }

    out.close();
    in.close();
    return 0;
}
