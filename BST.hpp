#ifndef BST_HPP
#define BST_HPP
#include <string>

class UnknownValueException {
    public:
        std::string getMessage() const{
            return message;
        }
    private:
        std::string message = "Node doesnt exist";
};

class UserTryingBSGame { 
    public:
        std::string getMessage() const{
            return message;
        }
    private:
        std::string message = "Don't BS the game :)";
};

template <typename T>
class BST {
    private:
        struct Node {
            T datum;
            Node* left;
            Node* right;

            Node(const T& data) : datum(data), left(nullptr), right(nullptr) {}
            Node(const T& data, Node* left_in, Node* right_in) : datum(data), left(left_in), right(right_in) {} 
        };

        Node* root;

        Node* current;

        Node* copy(Node* root){
            if(!root){
                return nullptr;
            }
            return new Node(root->datum, copy(root->left), copy(root->right));
        }

        void destroy(Node* root){
            if(!root){
                return;
            }
            destroy(root->left);
            destroy(root->right);
            delete root;
        }

        Node* build_balanced_range(const T& low, const T& high){
            if(low > high){
                return nullptr;
            }
            T mid = (low + high) / 2;
            Node* middle = new Node(mid, build_balanced_range(low, mid - 1), build_balanced_range(mid + 1, high));
            return middle;
        }
    public:
        BST() : root(nullptr), current(nullptr) {}
        BST(T root_in) : root(new Node(root_in)), current(root) {}
        BST(const BST<T>& rhs){
            root = copy(rhs.root);
            current = root;
        }
        ~BST(){
            destroy(root);
            current = nullptr;
        }
        BST<T>& operator=(const BST<T>& rhs){
            if(this == &rhs){
                return *this;
            }
            destroy(root);
            root = copy(rhs.root);
            current = root;
            return *this;
        }

        void balanced_rng(const T& low, const T& high){
            destroy(root);
            root = build_balanced_range(low, high);
            current = root;
        }

        void build_around_root(const T& lhs, const T& rhs){
            if(!root){
                return;
            }

            destroy(root->left);
            destroy(root->right);

            root->left = build_balanced_range(lhs, root->datum - 1);
            root->right = build_balanced_range(root->datum + 1, rhs);

            current = root;
        }

        T get_current() const{
            if(!current) {
                throw UnknownValueException();
            }
            return current->datum;
        }

        bool go_left(){
            if(!current) {
                return false;
            }
            current = current->left;
            return current;
        }

        bool go_right(){
            if(!current) {
                return false;
            }
            current = current->right;
            return current;
        }

        void reset(){
            current = root;
        }

        void check_user(const T& value, const std::string& response){
            if(current->datum == value and response == "n"){
                throw UserTryingBSGame();
            }
        }
};

#endif