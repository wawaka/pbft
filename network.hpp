#pragma once

#include <list>
#include <string>
#include <mutex>
#include <thread>

#include "pbft.hpp"
#include "message.hpp"

using namespace std::chrono_literals;

struct MessageAddressed {
    network_address_t src;
    network_address_t dst;
    Message msg;
};

class Network {
    std::list<MessageAddressed> messages_;
    network_address_t next_address = 0;
    std::mutex mutex_;

public:
    static Network& instance();
    bool empty();
    void send_msg(network_address_t src, network_address_t dst, Message msg);
    MessageAddressed recv_msg(network_address_t dst);
    network_address_t assign_address();
};

class NetworkNode {
    const network_address_t address_;
    std::mutex mutex_;

public:
    NetworkNode();
    network_address_t get_address() const;
    virtual void on_recv_msg(network_address_t src, Message msg) = 0;
    void send_msg(network_address_t dst, Message msg);
};
