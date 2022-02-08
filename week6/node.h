#pragma once
#include "date.h"
#include "string"
#include "memory"
using std::string, std::shared_ptr;
enum Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};
enum LogicalOperation{
    And,
    Or
};
class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};
class EmptyNode : public Node {
public:
    EmptyNode();
    bool Evaluate(const Date& date, const string& event) const override;
};
class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Date date_;
    const Comparison cmp_;
};
class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& event);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const string event_;
    const Comparison cmp_;
};
class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs);
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const LogicalOperation op_;
    const shared_ptr<Node> lhs_;
    const shared_ptr<Node> rhs_;
};