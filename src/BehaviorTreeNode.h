#ifndef BEHAVIORTREENODE_H
#define BEHAVIORTREENODE_H

enum Status { SUCCESS, FAIL, RUNNING };


class BehaviorTreeNode
{

public:
    BehaviorTreeNode();

    Status update(float seconds);
    void reset();
};

#endif // BEHAVIORTREENODE_H
