#include "node.h"


DateComparisonNode::DateComparisonNode(const Comparison comparison, const Date& date) 
	: date(date), comparison(comparison) {}


bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
	if (comparison == Comparison::Less) 
		return date < this->date;
	if (comparison == Comparison::LessOrEqual) 
		return date < this->date || date == this->date;
	if (comparison == Comparison::Greater) 
		return !((date < this->date) || (date == this->date));
	if (comparison == Comparison::GreaterOrEqual) 
		return !(date < this->date);
	if (comparison == Comparison::Equal) 
		return date == this->date;
	if (comparison == Comparison::NotEqual) 
		return !(date == this->date);
	return false;
}


EventComparisonNode::EventComparisonNode(const Comparison comparison, const std::string& event)
	: event(event), comparison(comparison) {}


bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
	if (comparison == Comparison::Less)
		return event < this->event;
	if (comparison == Comparison::LessOrEqual)
		return event < this->event || event == this->event;
	if (comparison == Comparison::Greater)
		return !((event < this->event) || (event == this->event));
	if (comparison == Comparison::GreaterOrEqual)
		return !(event < this->event);
	if (comparison == Comparison::Equal)
		return event == this->event;
	if (comparison == Comparison::NotEqual)
		return event != this->event;
	return false;
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation& o,
	std::shared_ptr<const Node> leftNode, std::shared_ptr<const Node> rightNode)
	: operation(o), leftNode(leftNode), rightNode(rightNode) {}


bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
	if (operation == LogicalOperation::And)
		return leftNode->Evaluate(date, event) && rightNode->Evaluate(date, event);
	if (operation == LogicalOperation::Or) 
		return leftNode->Evaluate(date, event) || rightNode->Evaluate(date, event);
	return false;
}

