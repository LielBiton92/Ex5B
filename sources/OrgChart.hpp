

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
            std::vector<Node *> Childrens;
            Node *Next_ptr;
            std::string name;

        public:
           
            Node(const std::string &name);
            Node(const Node *other);
            const std::string &getname() const;
            void set_name(const std::string &name);
            std::vector<Node *> getChilds();
            void AddChild(Node *Child);
            Node *get_Nextptr();
            void set_Nextptr(Node *ptr);
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
        void fill_level_order();
        Node* fill_reverse_order();
        void fill_pre_order();
        void DFS(std::vector<Node*>&reverse , Node *run);
        std::vector<Node *> Emp;


    public:

        class Iterator
        {
            private:
                Node *runner;
                

        public:

            Iterator(Node *ptr);
            const std::string* operator->() const ;
            const std::string &operator*() const{ return runner->getname(); }
            Iterator &operator++();
            Iterator operator++(int);
            bool operator!=(const Iterator &it1)const; 
            bool operator==(const Iterator &it)const ; 

        };
        OrgChart &add_root(const std::string &name);
        OrgChart &add_sub(const std::string &father, const std::string &child);
        OrgChart();
        OrgChart(const OrgChart &other);
        OrgChart(OrgChart &&other)noexcept;
        OrgChart& operator=(OrgChart &&) noexcept; 
        ~OrgChart();
        Iterator begin_level_order() ;
        Iterator end_level_order() const;
        Iterator begin_reverse_order();
        Iterator reverse_order() const;
        Iterator begin_preorder();
        Iterator end_preorder()const;
        Iterator begin();
        Iterator end()const;

        OrgChart &operator=(const OrgChart &other);
        friend std::ostream &operator<<(std::ostream &os, OrgChart &og);
    };

}