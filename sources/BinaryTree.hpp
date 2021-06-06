
#include <iostream>
#include <vector>
#include <typeinfo>
#include <memory>
namespace ariel{
template <typename T>
    class BinaryTree{
        public:
            class Node {
            public:
                Node* left;
                Node* right;
                T value;
                Node(T v):value(v){left=right=nullptr;}
            };
            Node* root;
               
        BinaryTree():root(nullptr){}
        ~BinaryTree(){
            
        }
        BinaryTree(BinaryTree&& other)noexcept{
            if(this!=&other){
                this->root = other.root;
            other.root=nullptr;
            }
        }
        BinaryTree(const BinaryTree& other){
            if(this!=&other){
                this->root = other.root;
            }
        }
        BinaryTree& operator=(BinaryTree&& other) noexcept{
            if(root){
                delete root;
            }
            this->root = other.root;
            other.root = nullptr;
            return *this;
        }

        BinaryTree& operator=(BinaryTree const& other){
            if(this ==&other){
                return *this;
            }
            if(root){
                delete root; 
            }
            if(other.root){
    
            root = &(tree(this->root,other.root));
            
            }
            return *this;
        }
        Node& tree(Node * root1,Node * other){
            if(!other){
                return *root1;
            }
            root1=new Node(other->value);
            root1->left = &(tree(root1->left,other->left));
            root1->right = &(tree(root1->right,other->right));
            return *root1;
        }

        BinaryTree& add_root(const T a){
            if(!this->root){
                root = (Node*)new Node(a);
            }
            else{
                root->value = a;
            }
            return *this;
        }
        BinaryTree& add_left(const T a,const T b){
            Node * temp = binarySearch(root,a);
            if(temp==nullptr){
                throw "cant from the left";           
            }
            if(temp->left){
                temp->left->value = b;
            }
            else{
                temp->left = (Node *)new Node(b);
            }
            return *this;
        }

        BinaryTree& add_right(const T &a,const T &b){
            Node * temp = binarySearch(root,a);
            if(temp==nullptr){
                throw"cant from the right";           
            }
            if(temp->right){
                temp->right->value = b; 
            }
            else{
                 temp->right = (Node *)new Node(b);
            }
            return *this;
        }

    Node* binarySearch(Node* node, T name){
        if(node != nullptr){
            if(node->value==name){
                return node;
            } 
            Node * temp = binarySearch( node->left,name);
            if(temp == nullptr) {
                temp = binarySearch(node->right,name);
            }
            return temp;
        } 
        return nullptr;

    }            
            class LinkedList{
                public:
                   Node* node;
                   std::shared_ptr<LinkedList> next;
                   LinkedList(Node* n){node=n;this->next=nullptr;}
            };
            
            class Iterator{
                public:
                    std::shared_ptr<LinkedList> list;
                    Iterator(std::shared_ptr<LinkedList>l=nullptr):list(l){}

                    T& operator*() {
                    return list->node->value;
                    }
                    

                    T* operator->() const{
                    return &list->node->value;
                    }

                    Iterator& operator++(){
                        this->list=this->list->next;
                        return *this;
                    }
                    
                    Iterator operator++(int){
                        auto p=*this;
                        this->list=this->list->next;
                        return p;
                    }
                    
                    bool operator==(const Iterator& rhs) const{
                    return this->list==rhs.list;
                    }
                    
                    bool operator!=(const Iterator& rhs) const{
                        return (!(*this==rhs));
                    }
                    
                    void in_order(Node* p1){
                        std::vector <Node*> values;
                        i_order(p1,values);
                        if(values.size()==0){return;}
                        auto p2=std::make_shared<LinkedList>(values[0]);
                        this->list=p2;
                        for(unsigned long i=1;i<values.size();i++){
                            p2->next=std::make_shared<LinkedList>(values[i]);
                            p2=p2->next;
                        }
                    }
                    
                    void pre_order(Node* p1){
                        std::vector <Node*> values;
                        pr_order(p1,values);
                        if(values.size()==0){return;}
                        auto p2=std::make_shared<LinkedList>(values[0]);
                        this->list=p2;
                        for(unsigned long i=1;i<values.size();i++){
                            p2->next=std::make_shared<LinkedList>(values[i]);
                            p2=p2->next;
                        }
                    }
                    
                    void post_order(Node* p1){
                        std::vector <Node*> values;
                        ps_order(p1,values);
                        if(values.size()==0){return;}
                        auto p2=std::make_shared<LinkedList>(values[0]);
                        this->list=p2;
                        for(unsigned long i=1;i<values.size();i++){
                            p2->next=std::make_shared<LinkedList>(values[i]);
                            p2=p2->next;
                        }
                    }
                    
                    void i_order(Node* p1,std::vector<Node*>& vec){
                        if(p1==nullptr){return;}
                        i_order(p1->left,vec);
                        vec.push_back(p1);
                        i_order(p1->right,vec);
                    }
                    
                    void pr_order(Node* p1,std::vector<Node*>& vec){
                        if(p1==nullptr){return;}
                        vec.push_back(p1);
                        pr_order(p1->left,vec);
                        pr_order(p1->right,vec);
                    }
    
                    void ps_order(Node *p1,std::vector<Node*>& vec){
                        if(p1==nullptr){return;}
                        ps_order(p1->left,vec);
                        ps_order(p1->right,vec);
                        vec.push_back(p1);                    
                    }
                };
                
                Iterator begin_preorder(){
                    Iterator iter{};
                    iter.pre_order(this->root);
                    return iter;
                }
                
                Iterator end_preorder(){
                    return Iterator{nullptr};
                }
                
                Iterator begin_inorder(){
                    Iterator iter{};
                    iter.in_order(this->root);
                    return iter;
                }
                
                Iterator end_inorder(){
                return end_preorder();
                }
                
                Iterator begin_postorder(){
                    Iterator iter{};
                    iter.post_order(this->root);
                    return iter;
                }
                Iterator end_postorder(){
                    return end_preorder();
                }
                Iterator begin(){return this->begin_inorder();}
                Iterator end(){return this->end_inorder();}
                friend std::ostream& operator<<(std::ostream& output,const BinaryTree<T> &BT){return output;}
        
    };

}



