#include "expressionnodearithmeticoperator.h"
#include "calculateexception.h"
#include "typeconversionutil.h"

/**
 * A parsed expression
 */
///*public*/  class ExpressionNodeArithmeticOperator implements ExpressionNode {



/*public*/  ExpressionNodeArithmeticOperator::ExpressionNodeArithmeticOperator(TokenType::TTYPE tokenType, ExpressionNode* leftSide, ExpressionNode* rightSide) {
    _tokenType = tokenType;
    _leftSide = leftSide;
    _rightSide = rightSide;
    setObjectName("ExpressionNodeArithmeticOperator");

    if (_rightSide == nullptr) {
        throw new IllegalArgumentException("rightSide must not be null");
    }

    // Verify that the token is of the correct type
    switch (_tokenType) {
        case TokenType::ADD:
        case TokenType::SUBTRACKT:
            break;

        case TokenType::MULTIPLY:
        case TokenType::DIVIDE:
        case TokenType::MODULO:
            if (_leftSide == nullptr) {
                throw new IllegalArgumentException("leftSide must not be null for operators *, / and %");
            }
            break;

        default:
            throw new IllegalArgumentException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
    }
}


/*private*/ QVariant ExpressionNodeArithmeticOperator::add(QVariant left, QVariant right) /*throws CalculateException*/ {
    if (TypeConversionUtil::isIntegerNumber(left)
            && TypeConversionUtil::isIntegerNumber(right)) {
        return ((left.toInt()) + ((right).toInt()));

    } else if (TypeConversionUtil::isFloatingNumber(left)
            && TypeConversionUtil::isFloatingNumber(right)) {
        return (left.toDouble() + right.toDouble());

    } else {
        if (TypeConversionUtil::isString(left) && TypeConversionUtil::isString(right)) {
            return (left.toString()) + /*(String)*/right.toString();
        } else {
            throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(left.toString(), right.toString()));
        }
    }
}


/*private*/ QVariant ExpressionNodeArithmeticOperator::subtract(QVariant left, QVariant right) /*throws CalculateException*/ {
    if (TypeConversionUtil::isIntegerNumber(left)) {
        if (TypeConversionUtil::isIntegerNumber(right)) {
            return ((left).toInt() - (right).toInt());
        } else if (TypeConversionUtil::isFloatingNumber(right)) {
            return ((left).toDouble() - (right).toDouble());
        } else {
            throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(right.toString()));
        }
    } else if (TypeConversionUtil::isFloatingNumber(left)) {
        if (TypeConversionUtil::isFloatingNumber(right)) {
            return ((left).toDouble() - (right).toDouble());
        } else {
            throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(right.toString()));
        }
    } else {
        throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(left.toString()));
    }
}


/*private*/ QVariant ExpressionNodeArithmeticOperator::multiply(QVariant left, QVariant right) /*throws CalculateException*/ {
    if (TypeConversionUtil::isIntegerNumber(left)) {
        if (TypeConversionUtil::isIntegerNumber(right)) {
            return ((left).toInt() * (right).toInt());
        } else if (TypeConversionUtil::isFloatingNumber(right)) {
            return ((left).toDouble() * (right).toDouble());
        } else {
            throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(right.toString()));
        }
    } else if (TypeConversionUtil::isFloatingNumber(left)) {
        if (TypeConversionUtil::isFloatingNumber(right)) {
            return ((left).toDouble() * (right).toDouble());
        } else {
            throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(right.toString()));
        }
    } else {
        throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(left.toString()));
    }
}


/*private*/ QVariant ExpressionNodeArithmeticOperator::divide(QVariant left, QVariant right) /*throws CalculateException*/ {
    if (TypeConversionUtil::isIntegerNumber(left)) {
        if (TypeConversionUtil::isIntegerNumber(right)) {
            return ((left).toInt() / (right).toInt());
        } else if (TypeConversionUtil::isFloatingNumber(right)) {
            return ((left).toDouble() / (right).toDouble());
        } else {
            throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(right.toString()));
        }
    } else if (TypeConversionUtil::isFloatingNumber(left)) {
        if (TypeConversionUtil::isFloatingNumber(right)) {
            return ((left).toDouble() / (right).toDouble());
        } else {
            throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(right.toString()));
        }
    } else {
        throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(left.toString()));
    }
}


/*private*/ QVariant ExpressionNodeArithmeticOperator::modulo(QVariant left, QVariant right) /*throws CalculateException*/ {
    if (TypeConversionUtil::isIntegerNumber(left)) {
        if (TypeConversionUtil::isIntegerNumber(right)) {
            return ((left).toInt() % (right).toInt());
        } else {
            throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not an integer number").arg(right.toString()));
        }
    } else {
        throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not an integer number").arg(left.toString()));
    }
}


//@Override
/*public*/  QVariant ExpressionNodeArithmeticOperator::calculate(SymbolTable* symbolTable) /*throws JmriException */{

    QVariant left = _leftSide->calculate(symbolTable);
    QVariant right = _rightSide->calculate(symbolTable);

    // Convert a boolean value to an integer value
    //if (left.canConvert<bool>()) {
    if(left.type() == QMetaType::Bool){
        left = (left.toBool()) ? 1 : 0;
    }
    //if (right.canConvert<bool>()) {
    if(right.type() == QMetaType::Bool){
        right = (right.toBool()) ? 1 : 0;
    }

    if (_tokenType == TokenType::ADD) {
        // Add can handle String concatenation
        return add(left, right);
    } else {
        // For the other arithmetic operators, except add, only numbers can
        // be handled. For other types, return 0.
        if (! TypeConversionUtil::isFloatingNumber(left)) {
            return 0;
        }
        if (! TypeConversionUtil::isFloatingNumber(right)) {
            return 0;
        }

        switch (_tokenType) {
            case TokenType::SUBTRACKT:
                return subtract(left, right);
            case TokenType::MULTIPLY:
                return multiply(left, right);
            case TokenType::DIVIDE:
                return divide(left, right);
            case TokenType::MODULO:
                return modulo(left, right);

            default:
                throw new CalculateException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
        }
    }

}


/** {@inheritDoc} */
//@Override
/*public*/  QString ExpressionNodeArithmeticOperator::getDefinitionString() {
    QString operStr;
    switch (_tokenType) {
        case TokenType::ADD:
            operStr = "+";
            break;

        case TokenType::SUBTRACKT:
            operStr = "-";
            break;

        case TokenType::MULTIPLY:
            operStr = "*";
            break;

        case TokenType::DIVIDE:
            operStr = "/";
            break;

        case TokenType::MODULO:
            operStr = "%";
            break;

        default:
            throw new UnsupportedOperationException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
    }

    QString leftSideString = _leftSide != nullptr ? _leftSide->getDefinitionString() : "null";
    QString rightSideString = _rightSide != nullptr ? _rightSide->getDefinitionString() : "null";
    return "("+leftSideString+")" + operStr + "("+rightSideString+")";
}
