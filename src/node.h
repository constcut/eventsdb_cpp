#pragma once

#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <string>
#include <cstdint>

#include "date.h"

using namespace std;


enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};


enum class LogicalOperation {
    And,
    Or
};


struct Node {
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};



struct EmptyNode : Node {
    bool Evaluate(const Date& date, const std::string& event) const override {
        return true;
    }
};


class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison comparison, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    const Comparison comparison;
    const Date date;
};



class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison comparison, const std::string& event);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    const Comparison comparison;
    const std::string event;
};



class LogicalOperationNode : public Node {
public:

    LogicalOperationNode(const LogicalOperation& o, 
        std::shared_ptr<const Node> leftNode, std::shared_ptr<const Node> rightNode);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:

    const LogicalOperation operation;
    const std::shared_ptr<const Node> leftNode;
    const std::shared_ptr<const Node> rightNode;
};