

#include "vector"
#include "string"
#include "iostream"
#include "queue"
#include "stack"
#include "algorithm"
namespace ariel
{

    class Node
    {
    private:
        Node *Father;
        std::vector<Node *> Childrens;

    public:
        std::string name;
        Node(const std::string &name);
        ~Node();
        const std::string &getname() const;
        void set_name(const std::string &name);
        std::vector<Node *> getChilds();
        void setFather(Node *Father);
        void AddChild(Node *Child);
    };

    class OrgChart
    {
        enum Iter
        {
            Level_order,
            Pre_order,
            _reverse_order
        };
    private:
        Node *root;

    public:

        std::vector<Node *> Emp;

        OrgChart &add_root(const std::string &name);
        OrgChart &add_sub(const std::string &father, const std::string &child);

        class Iterator
        {
        private:
             Node *runner;
            std::vector<Node*> Res;
            
             unsigned int index = 0;  

        public:
            void fill_level_order();
            void fill_reverse_order();
            void fill_pre_order(Node *runner);
            Iterator(Node *ptr, Iter Type);
            std::string *operator->();
            std::string &operator*() const{ return this->Res[index]->name; }
            Iterator &operator++();
            Iterator operator++(int);
            bool operator!=(const Iterator &it1); 
            bool operator==(const Iterator &it); 

        };

        OrgChart();
        ~OrgChart();
        
        Iterator begin_level_order() const;
        Iterator end_level_order() const;
        Iterator begin_reverse_order()const;
        Iterator reverse_order() const;
        Iterator begin_preorder() const ;
        Iterator end_preorder()const;
        Iterator begin()const;
        Iterator end()const;

        friend std::ostream &operator<<(std::ostream &os, OrgChart &og);
    };

}