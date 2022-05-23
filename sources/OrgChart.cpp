#include <string>
#include "OrgChart.hpp"
using namespace ariel;

OrgChart::OrgChart()
{
    this->root = nullptr;
}
OrgChart::~OrgChart(){delete root;}

Node::Node(const std::string &name)
{
    this->name = name;
    this->Childrens.resize(0);
    this->Father = nullptr;
}

Node::~Node()
{

    for (Node *node : this->Childrens)
    {
        delete node;
    }
}

const std::string &Node::getname() const
{
    return this->name;
}

std::vector<Node *> Node::getChilds()
{
    return this->Childrens;
}

void Node::setFather(Node *F)
{
    this->Father = F;
}

void Node::AddChild(Node *Child)
{
    Child->setFather(this);
    this->Childrens.push_back(Child);
}
void Node::set_name(const std::string &name) { this->name = name; }

void OrgChart::Iterator::fill_level_order()
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

void OrgChart::Iterator::fill_reverse_order()
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
        for (unsigned int i = temp->getChilds().size(); i > 0; --i)
        {

            queue.push(temp->getChilds()[i - 1]);
        }
    }

    std::reverse(Res.rbegin(), Res.rend());
}

void OrgChart::Iterator::fill_pre_order(Node *runner)
{
    if (runner == nullptr)
    {
        return;
    }
    Res.push_back(runner);
    for (Node *temp : runner->getChilds())
    {
        fill_pre_order(temp);
    }
}

OrgChart::Iterator::Iterator(Node *ptr, Iter Type)
{
    runner = ptr;
    if (Type == Level_order)
    {
        this->fill_level_order();
    }

    else if (Type == _reverse_order)
    {
        this->fill_reverse_order();
        runner = ptr;
    }
    else
    {
        this->fill_pre_order(runner);
    }
}

std::string *OrgChart::Iterator::operator->() { return &(this->Res[index]->name); }

OrgChart::Iterator &OrgChart::Iterator::operator++()
{
    runner = Res[++index];
    if (index >= Res.size())
    {
        runner = nullptr;
    }
    return *this;
}

OrgChart::Iterator OrgChart::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool OrgChart::Iterator::operator!=(const Iterator &it1) { return !(runner == it1.runner); }
bool OrgChart::Iterator::operator==(const Iterator &it) { return runner == it.runner; }

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
        // this->root->setlevel(0);
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
        if (p->name == father)
        {
            Node *c = new Node(child);
            p->AddChild(c);
            c->setFather(p);
            // c->setlevel(p->getlevel() + 1);
            this->Emp.push_back(c);
            return *this;
        }
    }
    throw std::invalid_argument(" not exist");
}

OrgChart::Iterator OrgChart::begin_level_order() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(this->root, Level_order);
}

OrgChart::Iterator OrgChart::end_level_order() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr, Level_order);
}

OrgChart::Iterator OrgChart::begin_reverse_order() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(root, _reverse_order);
}

OrgChart::Iterator OrgChart::reverse_order() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr, _reverse_order);
}

OrgChart::Iterator OrgChart::begin_preorder() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(root, Pre_order);
}
OrgChart::Iterator OrgChart::end_preorder() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr, Pre_order);
}

OrgChart::Iterator OrgChart::begin() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(root, Level_order);
}

OrgChart::Iterator OrgChart::end() const
{
    if (root == nullptr)
    {
        throw std::logic_error("Chart is empty");
    }
    return Iterator(nullptr, Level_order);
}

namespace ariel
{
    std::ostream &operator<<(std::ostream &os, OrgChart &og)
    {
        std::string res = " ";
        for (unsigned int i = 0; i < og.Emp.size(); i++)
        {
            res += res + og.Emp[i]->getname() + " ";
        }
        os << res;
        return os;
    }
}
