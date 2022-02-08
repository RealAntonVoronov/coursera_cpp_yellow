#include "node.h"

EmptyNode::EmptyNode() {};
bool EmptyNode::Evaluate(const Date &date, const string &event) const {return true;}

DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date) : cmp_(cmp), date_(date){};
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    switch (cmp_) {
        case Comparison::Less:
            return date < date_;
        case Comparison::LessOrEqual:
            return date <= date_;
        case Comparison::Greater:
            return date > date_;
        case Comparison::GreaterOrEqual:
            return date >= date_;
        case Comparison::Equal:
            return date == date_;
        case Comparison::NotEqual:
            return date != date_;
    }
}

EventComparisonNode::EventComparisonNode(const Comparison &cmp, const string &event) : cmp_(cmp), event_(event){};
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    switch (cmp_) {
        case Comparison::Less:
            return event < event_;
        case Comparison::LessOrEqual:
            return event <= event_;
        case Comparison::Greater:
            return event > event_;
        case Comparison::GreaterOrEqual:
            return event >= event_;
        case Comparison::Equal:
            return event == event_;
        case Comparison::NotEqual:
            return event != event_;
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node>& lhs,
                                           const shared_ptr<Node>& rhs) : op_(op), lhs_(lhs), rhs_(rhs) {};
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (op_) {
        case LogicalOperation::And:
            return lhs_->Evaluate(date, event) and rhs_->Evaluate(date, event);
        case LogicalOperation::Or:
            return lhs_->Evaluate(date, event) or rhs_->Evaluate(date, event);
    }
}
