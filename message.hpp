#pragma once

#include "pbft.hpp"

struct Message {
    enum msg_type_t {
        REQUEST,
        PRE_PREPARE,
        PREPARE,
        COMMIT,
        REPLY,
    } type;
    std::string o;
    std::string r;
    time_t t = 0;
    size_t v = 0;
    size_t d = 0;
    size_t n = 0;
    network_address_t c = 0;

    Message(msg_type_t _type);
    size_t digest();
    std::string str() const;
};

