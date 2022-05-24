#include "sources/OrgChart.hpp"
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


    OrgChart mo(organization);



    // for(auto it = organization.begin_level_order();it!=organization.end_level_order();++it){
    //     cout << *it+ " ";
    // }


}





// //     Node *p = new Node("CEO");
// //     Node *p1 = new Node("CTO");
// //     Node *p2 = new Node("CFO");
// //     Node *p3 = new Node("COO");
// //     Node *p4 = new Node("VP_SW");
// //     Node *p5 = new Node("VP_BI");


 
   

// //   for (auto it=organization.begin_reverse_order(); it!=organization.reverse_order(); ++it) {
// //     cout << (*it) << " " ;
// //   } 
// //   cout <<endl;
// //     for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
// //     cout << it->size();
// //   }

// //    // prints: CEO CTO VP_SW CFO COO VP_BI
//         OrgChart org;
//             org.add_root("dana");
//     org.add_root("shir");
//     org.add_sub("shir", "tal");
//     org.add_sub("shir", "sapir");
//     org.add_sub("sapir", "dan");
//     org.add_sub("dan", "ziv");
//     org.add_sub("tal", "avi");
//     org.add_sub("tal", "yossi");
//     org.add_sub("shir", "ido");
//     org.add_sub("ziv", "shaked");
//     org.add_sub("ziv", "ofer");


//         std::vector<std::string> v = {"shir", "tal", "sapir", "ido", "avi", "yossi", "dan", "ziv", "shaked", "ofer"};


//         vector<int> nums = {4, 3, 5, 3, 3, 5, 3, 3, 6, 4};
//         int j = 0;
//         for(auto it = org.begin_level_order(); it != org.end_level_order(); ++it){
//           // cout << " it size : "<< it->size()<<endl;
//           cout  <<nums.at((size_t)j)<< " : " << it->size()<<endl;
//             j++;
//         }






// }
