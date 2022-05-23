#include "OrgChart.hpp"
using namespace ariel;
using namespace std;

int main(int argc, char const *argv[])
{
    OrgChart organization;
    organization.add_root("CEO")
        .add_sub("CEO", "CTO")    // Now the CTO is subordinate to the CEO
        .add_sub("CEO", "CFO")    // Now the CFO is subordinate to the CEO
        .add_sub("CEO", "COO")    // Now the COO is subordinate to the CEO
        .add_sub("CTO", "VP_SW")  // Now the VP Software is subordinate to the CTO
        .add_sub("COO", "VP_BI"); // Now the VP_BI is subordinate to the COO

    Node *p = new Node("CEO");
    Node *p1 = new Node("CTO");
    Node *p2 = new Node("CFO");
    Node *p3 = new Node("COO");
    Node *p4 = new Node("VP_SW");
    Node *p5 = new Node("VP_BI");


    p->AddChild(p1);
    p->AddChild(p2);
    p->AddChild(p3);
    p1->AddChild(p4);
    p3->AddChild(p5);

   

  for (auto it=organization.begin_reverse_order(); it!=organization.reverse_order(); ++it) {
    cout << (*it) << " " ;
  }  // prints: CEO CTO VP_SW CFO COO VP_BI







}
