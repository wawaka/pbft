#include "fsm.hpp"
#include "node.hpp"

void NodeFSM::handle_message(Message msg, Node& node) {
    switch (state_) {
        
    }



    // if (prepared) {
    //     for (auto addr : other_nodes_) {
    //         node.send_commit();
    //     }
    // }
    // 
    // if (committed_local) {
    //     node.execute_operation();
    //     node.send_reply();
    // }
}
