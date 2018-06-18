#include "network.hpp"

Network& Network::instance() {
    static Network inst;
    return inst;
}

bool Network::empty() {
    std::lock_guard<std::mutex> guard(mutex_);
    return messages_.empty();
}

void Network::send_msg(network_address_t src, network_address_t dst, Message msg) {
    std::lock_guard<std::mutex> guard(mutex_);
    messages_.push_back({src, dst, msg});
}

MessageAddressed Network::recv_msg(network_address_t dst) {
    std::lock_guard<std::mutex> guard(mutex_);
    for (auto it = messages_.begin(); it != messages_.end(); ++it) {
        if (it->dst == dst) {
            auto msg = *it;
            messages_.erase(it);
            return msg;
        }
    }
    throw std::runtime_error("no message for you"); // not production solution obviously
}

network_address_t Network::assign_address() {
    std::lock_guard<std::mutex> guard(mutex_);
    return next_address++;
}

network_address_t NetworkNode::get_address() const {
    return address_;
}

NetworkNode::NetworkNode() : address_(Network::instance().assign_address()) {
    std::thread([this](){
        while (true) {
            try {
                auto msg = Network::instance().recv_msg(get_address());
                on_recv_msg(msg.src, msg.msg);
            } catch (...) {
                std::this_thread::sleep_for(1s);
            }
        }
    }).detach();
}

void NetworkNode::send_msg(network_address_t dst, Message msg) {
    Network::instance().send_msg(get_address(), dst, msg);
}
