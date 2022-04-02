#include "expressionnodecomparingoperator.h"
#include "runtimeexception.h"
/**
 * A parsed expression
 */
///*public*/  class ExpressionNodeComparingOperator implements ExpressionNode {


/*public*/  ExpressionNodeComparingOperator::ExpressionNodeComparingOperator(TokenType::TTYPE tokenType, ExpressionNode* leftSide, ExpressionNode* rightSide)
 : QObject(){
    _tokenType = tokenType;
    _leftSide = leftSide;
    _rightSide = rightSide;
    setObjectName("ExpressionNodeComparingOperator");

    if (_leftSide == nullptr) {
        throw new IllegalArgumentException("leftSide must not be null");
    }
    if (_rightSide == nullptr) {
        throw new IllegalArgumentException("rightSide must not be null");
    }

    // Verify that the token is of the correct type
    switch (_tokenType) {
        case TokenType::EQUAL:
        case TokenType::NOT_EQUAL:
        case TokenType::LESS_THAN:
        case TokenType::LESS_OR_EQUAL:
        case TokenType::GREATER_THAN:
        case TokenType::GREATER_OR_EQUAL:
            break;

        default:
            throw new RuntimeException("Unknown comparing operator: "+TokenType::toString(_tokenType));
    }
}

/*public*/  QVariant ExpressionNodeComparingOperator::calculateNull(QVariant left, QVariant right) /*throws JmriException*/ {
    if ((left != QVariant()) && (right != QVariant())) {
        throw new RuntimeException("This method is only valid if left and/or right is null");
    }

    switch (_tokenType) {
        case TokenType::EQUAL:
            return left == right;
        case TokenType::NOT_EQUAL:
            return left != right;
        case TokenType::LESS_THAN:
            return (left == QVariant()) && (right != QVariant());
        case TokenType::LESS_OR_EQUAL:
            return left == QVariant();
        case TokenType::GREATER_THAN:
            return (left != QVariant()) && (right == QVariant());
        case TokenType::GREATER_OR_EQUAL:
            return right == QVariant();

        default:
            throw new RuntimeException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
    }
}

//@Override
/*public*/  QVariant ExpressionNodeComparingOperator::calculate(SymbolTable* symbolTable)/* throws JmriException*/ {
    QVariant left = _leftSide->calculate(symbolTable);
    QVariant right = _rightSide->calculate(symbolTable);

    if ((left == QVariant()) || (right == QVariant())) return calculateNull(left, right);

    // Convert a boolean value to an integer value. false = 0 and true = 1.
    if (left.canConvert<bool>()) {
        left = (left.toBool()) ? 1 : 0;
    }
    if (right.canConvert<bool>()) {
        right = (right.toBool()) ? 1 : 0;
    }

    // If the operands are not numbers, ensure that they are strings
    if ((!(left.canConvert<int>())) && (!(left.canConvert<QString>()))) {
        left = left.toString();
    }
    if ((!(right.canConvert<int>())) && (!(right.canConvert<QString>()))) {
        right = right.toString();
    }

    // A number is always less than a String. If one operand is a number
    // and the other operand is a String, we can change the operands to
    // two integers to make the check easier.
    if ((left.canConvert<int>()) && (!(right.canConvert<int>()))) {
        left = 1;
        right = 2;
    } else if (!(left.canConvert<int>()) && ((right.canConvert<int>()))) {
        left = 2;
        right = 1;
    }

    if (left.canConvert<int>()) {
        switch (_tokenType) {
            case TokenType::EQUAL:
                return left ==(right);
            case TokenType::NOT_EQUAL:
                return left != (right);
            case TokenType::LESS_THAN:
                return ( left).toDouble() < ( right).toDouble();
            case TokenType::LESS_OR_EQUAL:
                return ( left).toDouble() <= ( right).toDouble();
            case TokenType::GREATER_THAN:
                return ( left).toDouble() > ( right).toDouble();
            case TokenType::GREATER_OR_EQUAL:
                return ( left).toDouble() >= ( right).toDouble();

            default:
                throw new RuntimeException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
        }
    } else {
        switch (_tokenType) {
            case TokenType::EQUAL:
                return left ==(right);
            case TokenType::NOT_EQUAL:
                return  left !=(right);
            case TokenType::LESS_THAN:
                return (left.toString()).compare((right.toString())) < 0;
            case TokenType::LESS_OR_EQUAL:
                return (left.toString()).compare((right.toString())) <= 0;
            case TokenType::GREATER_THAN:
                return (left.toString().compare(right.toString())) > 0;
            case TokenType::GREATER_OR_EQUAL:
                return (left.toString()).compare((right.toString())) >= 0;

            default:
                throw new RuntimeException("Unknown comparing operator: "+TokenType::toString(_tokenType));
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString ExpressionNodeComparingOperator::getDefinitionString() {
    QString operStr;
    switch (_tokenType) {
        case TokenType::EQUAL:
            operStr = "==";
            break;

        case TokenType::NOT_EQUAL:
            operStr = "!=";
            break;

        case TokenType::LESS_THAN:
            operStr = "<";
            break;

        case TokenType::LESS_OR_EQUAL:
            operStr = "<=";
            break;

        case TokenType::GREATER_THAN:
            operStr = ">";
            break;

        case TokenType::GREATER_OR_EQUAL:
            operStr = ">=";
            break;

        default:
            throw new RuntimeException("Unknown comparing operator: "+TokenType::toString(_tokenType));
    }
    return "("+_leftSide->getDefinitionString()+")" + operStr + "("+_rightSide->getDefinitionString()+")";
}
