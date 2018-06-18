#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "fsm.hpp"
#include "network.hpp"

class Client : public NetworkNode {
public:
    void on_recv_msg(network_address_t src, Message msg) override;
    void send_request(network_address_t dst, std::string o);
};

class Node : public NetworkNode {
    std::vector<network_address_t> other_nodes_;
    struct key_t {
        network_address_t c; // client
        int o; // operation
        time_t t; // timestamp
    };
    std::map<key_t, NodeFSM> state_;
    size_t seq_ = 0;
    size_t view_ = 0;

public:
    void set_all_nodes(const std::vector<std::unique_ptr<Node>>& all_nodes);
    void on_recv_msg(network_address_t src, Message msg) override;
    void send_all(Message msg);
};
