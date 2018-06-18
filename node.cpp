#include "node.hpp"


void Client::on_recv_msg(network_address_t src, Message msg) {
    std::cout << msg.str() << std::endl;
}

void Client::send_request(network_address_t dst, std::string o) {
    Message request(Message::REQUEST);
    request.t = std::time(nullptr);
    request.o = o;
    send_msg(dst, request);
}

void Node::set_all_nodes(const std::vector<std::unique_ptr<Node>>& all_nodes) {
    for (auto& node : all_nodes) {
        if (node->get_address() == get_address()) {
            continue;
        }
        other_nodes_.push_back(node->get_address());
    }
}

NodeFSM& Node::get_state(Message msg) {
    switch (msg.type) {
        case Message::REQUEST: {
        }
        break;

        case Message::PRE_PREPARE: {
        }
        break;
    }
}

void Node::on_recv_msg(network_address_t src, Message msg) {
    std::lock_guard<std::mutex> console_guard(console_mutex);
    std::cout << "Node() " << src << " -> " << get_address() << ": " << msg.str() << std::endl;

    auto& state = get_state(msg);
    state.handle_message(msg, *this);
}

void Node::send_all(Message msg) {
    for (auto addr : other_nodes_) {
        send_msg(addr, msg);
    }
}
