
#include <iostream>
#include <vector>
#include <typeinfo>
#include <memory>
using namespace std;
namespace ariel{
template <typename T>
    class BinaryTree{
        public:
            class Node {
            public:
                shared_ptr<Node> left;
                shared_ptr<Node> right;
                T value;
                Node(const T &v):value(v){left=right=nullptr;}
            };
            shared_ptr<Node>root;
            
            BinaryTree(){
                this->root=nullptr;
            }

            ~BinaryTree()=default;
            BinaryTree(BinaryTree&& other)noexcept{
               if(other.root!=nullptr){
                    this->root= make_shared<Node>(other.root->value);
                    this->deep_copy(this->root,other.root);
                }
            }
            
            BinaryTree(BinaryTree& other){
                if(other.root!=nullptr){
                    this->root= make_shared<Node>(other.root->value);
                    this->deep_copy(this->root,other.root);
                }
            }
            
            BinaryTree & operator=(const BinaryTree & other){
                if(this->root!=other.root){
                    if(other.root!=nullptr){
                        this->root= make_shared<Node>(other.root->value);
                        this->deep_copy(this->root,other.root);
                    }
                    else{
                        this->root=nullptr;
                    }
                }
                return *this;
            }
            
            BinaryTree & operator=(BinaryTree && other)noexcept{
                if(this->root!=other.root){
                    if(other.root!=nullptr){
                        this->root= make_shared<Node>(other.root->value);
                        this->deep_copy(this->root,other.root);
                    }
                }
                return *this;
            }
            
            void deep_copy(shared_ptr<Node> this_p,shared_ptr<Node> other_p){
                if(other_p==nullptr){return;}
                if(other_p->left!=nullptr){
                    this_p->left=make_shared<Node>(other_p->value);
                    deep_copy(this_p->left,other_p->left);
                }
                if(other_p->right!=nullptr){
                    this_p->right=make_shared<Node>(other_p->value);
                    deep_copy(this_p->right,other_p->right);
                }
            }
            
            BinaryTree &add_left(T v1,T v2){
                    if(this->root==nullptr){throw "this value are not exist";}
                    bool flag=true;
                    search_l(this->root,flag,v1,v2);
                    if(flag){throw "this value are not exist";}
                    return *this;
            }
                
            BinaryTree &add_right(T v1,T v2){
                    if(this->root==nullptr){throw "this value are not exist";}
                    bool flag=true;
                    search_r(this->root,flag,v1,v2);
                    if(flag){throw "this value are not exist";}
                    return *this; 
            }
                
            BinaryTree &add_root(T v){
                    if(this->root==nullptr){
                        this->root=make_shared<Node>(v);
                    }
                    else{
                    shared_ptr<Node>n_root=make_shared<Node>(v);
                    n_root->left=this->root->left;
                    n_root->right=this->root->right;
                    this->root=n_root;
                    }
                    return *this;
            }
                
            bool search_l(shared_ptr<Node> node,bool & flag, T key,T v)
            {
                if (node == nullptr){return false;}
                if ((node->value == key)&&flag){
                    if(node->left==nullptr){node->left=make_shared<Node>(v);}
                    else{node->left->value=v;}
                    flag=false;
                    return true;
                }
                bool res1=search_l(node->left,flag,key,v);
                if(res1){return res1;}
                return search_l(node->right,flag,key,v);
            }
            
            bool search_r(shared_ptr<Node> node,bool & flag, T key,T v)
            {
                if (node == nullptr){return false;}
                if ((node->value == key)&&flag){
                    if(node->right==nullptr){node->right=make_shared<Node>(v);}
                    else{node->right->value=v;}
                    flag=false;
                    return true;
                }
                bool res1=search_r(node->left,flag,key,v);
                if(res1){return res1;}
                return search_r(node->right,flag,key,v);
            }
             
                        
            class LinkedList{
                public:
                   shared_ptr<Node> node;
                   shared_ptr<LinkedList> next;
                   LinkedList(shared_ptr<Node> n){node=n;this->next=nullptr;}
            };
            
            class Iterator{
                public:
                    shared_ptr<LinkedList> list;
                    Iterator(shared_ptr<LinkedList>l=nullptr):list(l){}

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
                    
                    void in_order(shared_ptr<Node> p1){
                        vector <shared_ptr<Node>> values;
                        i_order(p1,values);
                        if(values.size()==0){return;}
                        auto p2=make_shared<LinkedList>(values[0]);
                        this->list=p2;
                        for(unsigned long i=1;i<values.size();i++){
                            p2->next=make_shared<LinkedList>(values[i]);
                            p2=p2->next;
                        }
                    }
                    
                    void pre_order(shared_ptr<Node> p1){
                        vector <shared_ptr<Node>> values;
                        pr_order(p1,values);
                        if(values.size()==0){return;}
                        auto p2=make_shared<LinkedList>(values[0]);
                        this->list=p2;
                        for(unsigned long i=1;i<values.size();i++){
                            p2->next=make_shared<LinkedList>(values[i]);
                            p2=p2->next;
                        }
                    }
                    
                    void post_order(shared_ptr<Node> p1){
                        vector <shared_ptr<Node>> values;
                        ps_order(p1,values);
                        if(values.size()==0){return;}
                        auto p2=make_shared<LinkedList>(values[0]);
                        this->list=p2;
                        for(unsigned long i=1;i<values.size();i++){
                            p2->next=make_shared<LinkedList>(values[i]);
                            p2=p2->next;
                        }
                    }
                    
                    void i_order(shared_ptr<Node>p1,vector<shared_ptr<Node>>& vec){
                        if(p1==nullptr){return;}
                        i_order(p1->left,vec);
                        vec.push_back(p1);
                        i_order(p1->right,vec);
                    }
                    
                    void pr_order(shared_ptr<Node>p1,vector<shared_ptr<Node>>& vec){
                        if(p1==nullptr){return;}
                        vec.push_back(p1);
                        pr_order(p1->left,vec);
                        pr_order(p1->right,vec);
                    }
    
                    void ps_order(shared_ptr<Node>p1,vector<shared_ptr<Node>>& vec){
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



