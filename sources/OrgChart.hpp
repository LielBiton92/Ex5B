

#include "vector"
#include "string"
#include "iostream"
#include "queue"
#include "stack"
#include "algorithm"
#include <algorithm>
namespace ariel
{

    class Node
    {
    private:
        Node *Father;
        std::vector<Node *> Childrens;
        int level;
        bool visited = false;

    public:
        std::string name;
        Node(const std::string &name);
        const std::string &getname() const;
        void set_name(const std::string &name);
        std::vector<Node *> getChilds();
        void setFather(Node *Father);
        Node getFather(Node *Child);
        void AddChild(Node *Child);
        int getlevel() { return this->level; }
        void setlevel(int lev) { this->level = lev; };
        Node *getnode(const std::string &name);
        void set_visited(bool visit){
        this->visited=visit;
        }
        bool get_visited(){return this->visited;}
    };

    class OrgChart
    {
    private:
        Node *root;

    public:
        enum Iter
        {
            Level_order,
            Pre_order,
            _reverse_order
        };
        std::vector<Node *> Emp;

        OrgChart &add_root(const std::string &name);
        OrgChart &add_sub(const std::string &father, const std::string &child);

        class Iterator
        {
        private:
            // std::queue<Node *> Res;
            std::vector<Node*> Res;
            unsigned int index = 0;

        public:
            void fill_level_order()
            {

                if (runner == nullptr)
                {
                    return;
                }
                std::queue<Node *> queue;

                queue.push(runner);
                while (!queue.empty())
                {
                    Node *temp = queue.front();
                    Res.push_back(temp);
                    queue.pop();
                    for (unsigned int i = 0; i < temp->getChilds().size(); i++)
                    {
                        queue.push(temp->getChilds().at(i));
                    }
                }
            }

            void fill_reverse_order()
            {
                Res.clear();
                std::vector<Node *> temp_vec;
                if (runner == nullptr)
                {
                    return;
                }
                std::queue<Node *> queue;

                queue.push(runner);
                while (!queue.empty())
                {
                    Node *temp = queue.front();
                    Res.push_back(temp);
                    queue.pop();
                    for (int i = temp->getChilds().size() - 1; i >= 0; --i)
                    {
                        queue.push(temp->getChilds()[(unsigned int)i]);
                    }
                }

                std::reverse(Res.begin() , Res.end());

                


            }

            void ReverseVector(){
                for(unsigned int i = 0 ; i < (int)Res.size()/2;i++){
                    swap(i , Res.size()-i);
                }
            }

            void swap(int Index1 , int Index2){
                Node *temp = Res[Index1];
                Res[Index1]=Res[Index2];
                Res[Index2]=temp;
            }



            void fill_pre_order(Node *p){
                if(p==nullptr){
                    return;
                }
                p->set_visited(true);
                Res.push_back(p);
                for(Node *temp : p->getChilds()){
                    if(!temp->get_visited()){
                        fill_pre_order(temp);
                    }
                }

                
                
            }



            // void ReverseQueue(){
            //     std::stack<Node*>stack;
            //     while(!Res.empty()){
                   
            //         stack.push(Res.front());
            //         Res.pop();
            //     }
            //     while(!stack.empty()){
            //         Res.push(stack.top());
            //         stack.pop();
            //     }
            // }



            Node *runner;

            Iterator(Node *ptr, Iter Type)
            {

                runner = ptr;
                if (Type == Level_order)
                {
                    this->fill_level_order();
                }

                else if (Type == _reverse_order)
                {
                    this->fill_reverse_order();
                }
                else
                {
                    this->fill_pre_order(runner);
                }

            }

            int size() { return 1; }
            std::string *operator->() { return &(this->runner->name); }
            std::string &operator*() const{ return this->runner->name; }
            Iterator &operator++()
            {
                runner  = Res[++index];
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }
            bool operator!=(const Iterator &it1) { return !(runner == it1.runner); }
            bool operator==(const Iterator &it) { return runner == it.runner; }
        };

        OrgChart();
        Iterator begin_level_order();
        Iterator end_level_order();
        Iterator begin_reverse_order();
        Iterator reverse_order();
        Iterator begin_preorder();
        Iterator end_preorder();
        Iterator begin();
        Iterator end();
        int size();

        friend std::ostream &operator<<(std::ostream &output, OrgChart &org);
    };

}