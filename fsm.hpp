class Node;

class NodeFSM {
    enum state_t {
        NO_STATE,
        PREPARED,
        COMMITTED,
        REPLIED,
    } state_;
    size_t accepted_prepares_ = 0;
    size_t accepted_commits_ = 0;
    // std::vector<Message> log_;

public:
    void handle_message(Message msg, Node& node);
};
