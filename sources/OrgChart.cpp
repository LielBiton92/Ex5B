#include <string>
#include "OrgChart.hpp"
using namespace ariel;

Node::Node(const Node *other)
{
    this->name = other->name;
    this->Next_ptr = other->Next_ptr;
    for (Node *c : other->Childrens)
    {
        Node t = new Node(c);
        this->AddChild(&t);
        this->Next_ptr=other->Next_ptr;
    }
}

Node *Node::get_Nextptr() { return this->Next_ptr; }

void Node::set_Nextptr(Node *ptr)
{
    this->Next_ptr = ptr;
}

OrgChart::OrgChart()
{
    this->root = nullptr;
}

OrgChart::OrgChart(const OrgChart &other){
    
    this->root = new Node(other.root->getname()); 
    Emp.push_back(this->root);
    for(Node *NewN : other.Emp){
        for(Node *t : NewN->getChilds()){
           this->add_sub(NewN->getname(),t->getname());
        }
    }

}


OrgChart::~OrgChart()
{
    for (Node *p : this->Emp)
    {
        delete p;
    }
}

OrgChart& OrgChart::operator=(OrgChart &&other)noexcept{
    if(this != &other){
        this->root = other.root;
        other.root = nullptr;
    }
    return *this;

}

OrgChart::OrgChart(OrgChart &&other) noexcept{
    this->root = other.root;    
    other.root = nullptr;
    
}



OrgChart &OrgChart::operator=(const OrgChart &other)
{
  if (this != &other) {
      this->~OrgChart();
    }
    this->root = new Node(other.root->getname()); 
    Emp.push_back(this->root);
    for(Node *NewN : other.Emp){
        for(Node *t : NewN->getChilds()){
           this->add_sub(NewN->getname(),t->getname());
        }
    }
        return *this;

    }






Node::Node(const std::string &name)
{
    this->name = name;
    this->Next_ptr=nullptr;
}

const std::string &Node::getname() const
{
    return this->name;
}

std::vector<Node *> Node::getChilds()
{
    return this->Childrens;
}

void Node::AddChild(Node *Child)
{
    this->Childrens.push_back(Child);
}
void Node::set_name(const std::string &name) { this->name = name; }

void OrgChart::fill_level_order()
{
    std::vector<Node *> Res;
    std::queue<Node *> queue;

    queue.push(root);
    while (!queue.empty())
    {
        Node *temp = queue.front();
        Res.push_back(temp);
        queue.pop();
        for (Node *p : temp->getChilds())
        {
            queue.push(p);
        }
    }
    for (unsigned int i = 0; i < Res.size() - 1; i++)
    {
        Res[i]->set_Nextptr(Res[i + 1]);
    }
    Res[Res.size() - 1]->set_Nextptr(nullptr);
}

Node *OrgChart::fill_reverse_order()
{
    std::vector<Node *> Res;
    std::vector<Node *> temp_vec;

    std::queue<Node *> queue;

    queue.push(root);
    while (!queue.empty())
    {
        Node *temp = queue.front();
        Res.push_back(temp);
        queue.pop();
        for (unsigned int i = temp->getChilds().size(); i > 0; --i)
        {

            queue.push(temp->getChilds()[i - 1]);
        }
    }

    std::reverse(Res.rbegin(), Res.rend());

    for (unsigned int i = 0; i < Res.size() - 1; i++)
    {
        Res[i]->set_Nextptr(Res[i + 1]);
    }
    Res[Res.size() - 1]->set_Nextptr(nullptr);
    return Res[0];
}

void OrgChart::fill_pre_order()
{
    std::vector<Node *> Res;
    DFS(Res, root);

    for (unsigned int i = 0; i < Res.size() - 1; i++)
    {
        Res[i]->set_Nextptr(Res[i + 1]);
    }
    Res[Res.size() - 1]->set_Nextptr(nullptr);
}

void OrgChart::DFS(std::vector<Node *> &reverse, Node *run)
{
    reverse.push_back(run);
    for (Node *temp : run->getChilds())
    {
        DFS(reverse, temp);
    }
}

OrgChart::Iterator::Iterator(Node *ptr)
{
    runner = ptr;
}

 const std::string* OrgChart::Iterator::operator->() const { return &(this->runner->getname()); }

OrgChart::Iterator &OrgChart::Iterator::operator++()
{
    this->runner = this->runner->get_Nextptr();
    return *this;
}

OrgChart::Iterator OrgChart::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool OrgChart::Iterator::operator!=(const Iterator &it1) const { return !(runner == it1.runner); }
bool OrgChart::Iterator::operator==(const Iterator &it) const  { return runner == it.runner; }

OrgChart &OrgChart::add_root(const std::string &name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Name cannot be empty");
    }

    if (this->root == nullptr)
    {
        this->root = new Node(name);
        this->Emp.push_back(root);
        this->root->set_name(name);
    }
    else
    {
        this->root->set_name(name);
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string &father, const std::string &child)
{
    for (Node *p : this->Emp)
    {
        if (p->getname() == father)
        {
            Node *c = new Node(child);
            p->AddChild(c);
            this->Emp.push_back(c);
            return *this;
        }
    }
    throw std::invalid_argument(" not exist");
}

OrgChart::Iterator OrgChart::begin_level_order()
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    this->fill_level_order();
    return Iterator(this->root);
}

OrgChart::Iterator OrgChart::end_level_order() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr);
}

OrgChart::Iterator OrgChart::begin_reverse_order()
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    Node *t = fill_reverse_order();
    return Iterator(t);
}

OrgChart::Iterator OrgChart::reverse_order() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr);
}

OrgChart::Iterator OrgChart::begin_preorder() 
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    this->fill_pre_order();
    return Iterator(root);
}
OrgChart::Iterator OrgChart::end_preorder() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr);
}

OrgChart::Iterator OrgChart::begin() 
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    this->fill_level_order();
    return Iterator(root);
}

OrgChart::Iterator OrgChart::end() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr);
}

namespace ariel
{
    std::ostream &operator<<(std::ostream &os, OrgChart &og)
    {
        for(auto it = og.begin_level_order();it!=og.end_level_order();++it){
            os << *it + " ";
        }
        return os;
    }
}
