#include <ctime>

#include <vector>
#include <functional>
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <string>
#include <sstream>
#include <list>
#include <map>

#include "node.hpp"

std::mutex console_mutex;

int main() {
    Client client;
    std::vector<std::unique_ptr<Node>> nodes;
    for (int i = 0; i < N; ++i) {
        nodes.push_back(std::make_unique<Node>());
    }

    for (auto& node : nodes) {
        node->set_all_nodes(nodes);
    }

    client.send_request(nodes[0]->get_address(), "Hello, world!");
    while (!Network::instance().empty()) {
        std::this_thread::sleep_for(1s);
    }
    // client.check_replies();

    return 0;
}
