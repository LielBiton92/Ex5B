#include <string>
#include "OrgChart.hpp"
using namespace ariel;

OrgChart::OrgChart()
{
    this->root = nullptr;
}

// start Node Implementation

Node::Node(const std::string &name)
{
    this->name = name;
    this->Childrens.resize(0);
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

Node Node::getFather(Node *Child)
{
    return *(Child->Father);
}

void Node::AddChild(Node *Child)
{
    Child->setFather(this);
    this->Childrens.push_back(Child);
}
void Node::set_name(const std::string &name) { this->name = name; }

// end Node implementation

// start iterator implementation

// end Iterator implementation

OrgChart &OrgChart::add_root(const std::string &name)
{
    if (this->root == nullptr)
    {
        this->root = new Node(name);
        this->Emp.push_back(root);
        this->root->set_name(name);
        this->root->setlevel(0);
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
            c->setlevel(p->getlevel() + 1);
            this->Emp.push_back(c);
            return *this;
        }
    }
    throw std::invalid_argument(" not exist");
}



OrgChart::Iterator OrgChart::begin_level_order()
{
    return Iterator(this->root , Level_order);
    
}

OrgChart::Iterator OrgChart::end_level_order()
{
    return Iterator(nullptr , Level_order);
}

OrgChart::Iterator OrgChart::begin_reverse_order()
{
    return Iterator(root , _reverse_order);
}

OrgChart::Iterator OrgChart::reverse_order()
{
    return Iterator(nullptr , _reverse_order);

}

OrgChart::Iterator OrgChart::begin_preorder()
{
    return Iterator(root , Pre_order);

}
OrgChart::Iterator OrgChart::end_preorder()
{
    return Iterator(nullptr , Pre_order);

}

OrgChart::Iterator OrgChart::begin()
{
    return Iterator(root, Level_order);

}

OrgChart::Iterator OrgChart::end()
{
    return Iterator(nullptr,Level_order);

}

namespace ariel
{
    std::ostream &operator<<(std::ostream &os, OrgChart &og) { 
        std::string res = " ";
        for (unsigned int i = 0 ; i < og.Emp.size();i++){
                    res = res+ og.Emp[i]->getname()+ " ";
                }
                os << res;
                return os;
    }
}
