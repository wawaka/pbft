#include <sstream>

#include "pbft.hpp"
#include "message.hpp"


Message::Message(msg_type_t _type) : type(_type) {
}

size_t Message::digest() {
    std::ostringstream oss;
    oss << o << t << c;
    return std::hash<std::string>{}(oss.str());
}

std::string Message::str() const {
    std::ostringstream oss;
    oss
        << "Message("
        << "type="
    ;
    switch (type) {
        case REQUEST: oss << "REQUEST"; break;
        case PRE_PREPARE: oss << "PRE_PREPARE"; break;
        case PREPARE: oss << "PREPARE"; break;
        case COMMIT: oss << "COMMIT"; break;
        case REPLY: oss << "REPLY"; break;
    }
    oss
        << ", o=" << o
        << ", t=" << t
        << ", v=" << v
        << ", d=" << d
        << ", n=" << n
        << ", c=" << c
        << ")";
    return oss.str();
}
