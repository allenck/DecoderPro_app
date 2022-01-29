#include "expressionnodeassignmentoperator.h"
#include "calculateexception.h"
/**
 * A parsed expression
 */
// /*public*/ class ExpressionNodeAssignmentOperator implements ExpressionNode {



    /*public*/ ExpressionNodeAssignmentOperator::ExpressionNodeAssignmentOperator(TokenType::TTYPE tokenType, ExpressionNode* leftSide, ExpressionNode* rightSide) {
        _tokenType = tokenType;
        _leftSide = leftSide;
        _rightSide = rightSide;

        if (_leftSide == nullptr) {
            throw new IllegalArgumentException("leftSide must not be null");
        }

        if (! _leftSide->canBeAssigned()) {
            throw new IllegalArgumentException("leftSide must assignable");
        }

        // Verify that the token is of the correct type
        switch (_tokenType) {
            case TokenType::ASSIGN:
            case TokenType::ASSIGN_ADD:
            case TokenType::ASSIGN_SUBTRACKT:
                break;

            case TokenType::ASSIGN_MULTIPLY:
            case TokenType::ASSIGN_DIVIDE:
            case TokenType::ASSIGN_MODULO:
                if (_leftSide == nullptr) {
                    throw new IllegalArgumentException("leftSide must not be null for operators *, / and %");
                }
                break;

            default:
                throw new IllegalArgumentException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
        }
    }


    /*private*/ QVariant ExpressionNodeAssignmentOperator::add(QVariant left, QVariant right) /*throws CalculateException*/ {
        if (/*TypeConversionUtil.isIntegerNumber*/(left.canConvert<long>())
                && /*TypeConversionUtil.isIntegerNumber*/(right).canConvert<long>()) {
            return (left).toInt() + (right).toInt();

        } else if (/*TypeConversionUtil.isFloatingNumber*/(left.canConvert<float>())
                && /*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
            return (left).toDouble() + (right.toDouble());

        } else {
            if (/*TypeConversionUtil.isString*/(left.canConvert<QString>()) && /*TypeConversionUtil.isString*/(right.canConvert<QString>())) {
                return (left.toString()) + (right.toString());
            } else {
                throw new CalculateException(tr("The two operands \"%1\" and \"%2\" have different types").arg(left.toString(), right.toString()));
            }
        }
    }


    /*private*/ QVariant ExpressionNodeAssignmentOperator::subtract(QVariant left, QVariant right) /*throws CalculateException*/ {
        if (/*TypeConversionUtil.isIntegerNumber*/(left.canConvert<long>())) {
            if (/*TypeConversionUtil.isIntegerNumber*/(right.canConvert<long>())) {
                return (left).toInt() - (right).toInt();
            } else if (/*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
                return (left).toDouble() - (right).toDouble();
            } else {
                throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(right.toString()));
            }
        } else if (/*TypeConversionUtil.isFloatingNumber*/(left.canConvert<float>())) {
            if (/*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
                return (left).toDouble() - (right.toDouble());
            } else {
                throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(right.toString()));
            }
        } else {
            throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(left.toString()));
        }
    }


    /*private*/ QVariant ExpressionNodeAssignmentOperator::multiply(QVariant left, QVariant right) /*throws CalculateException*/ {
        if (/*TypeConversionUtil.isIntegerNumber*/(left.canConvert<long>())) {
            if (/*TypeConversionUtil.isIntegerNumber*/(right.canConvert<long>())) {
                return (left.toInt()) * (right).toInt();
            } else if (/*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
                return (left).toDouble() * (right).toDouble();
            } else {
                throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(right.toString()));
            }
        } else if (/*TypeConversionUtil.isFloatingNumber*/(left.canConvert<float>())) {
            if (/*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
                return (left).toDouble() * (right).toDouble();
            } else {
                throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" sinse it's not a number").arg(right.toString()));
            }
        } else {
            throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(left.toString()));
        }
    }


    /*private*/ QVariant ExpressionNodeAssignmentOperator::divide(QVariant left, QVariant right) /*throws CalculateException*/ {
        if (/*TypeConversionUtil.isIntegerNumber*/(left.canConvert<long>())) {
            if (/*TypeConversionUtil.isIntegerNumber*/(right.canConvert<long>())) {
                return (left).toInt() / (right).toInt();
            } else if (/*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
                return (left).toDouble() / (right.toDouble());
            } else {
                throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(right.toString()));
            }
        } else if (/*TypeConversionUtil.isFloatingNumber*/(left.canConvert<float>())) {
            if (/*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
                return (left).toDouble() / (right).toDouble();
            } else {
                throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(right.toString()));
            }
        } else {
            throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(left.toString()));
        }
    }


    /*private*/ QVariant ExpressionNodeAssignmentOperator::modulo(QVariant left, QVariant right) /*throws CalculateException*/ {
        if (/*TypeConversionUtil.isIntegerNumber*/(left.canConvert<long>())) {
            if (/*TypeConversionUtil.isIntegerNumber*/(right.canConvert<long>())) {
                return (left).toInt() % (right).toInt();
            } else {
                throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" since it's not a number").arg(right.toString()));
            }
        } else {
            throw new CalculateException(tr("Arithmetic operations cannot be done on the operand \"%1\" sinse it's not a number").arg(left.toString()));
        }
    }


    //@Override
    /*public*/ QVariant ExpressionNodeAssignmentOperator::calculate(SymbolTable* symbolTable) /*throws JmriException*/ {

        if (_tokenType == TokenType::ASSIGN) {
            QVariant value = _rightSide->calculate(symbolTable);
            _leftSide->assignValue(symbolTable, value);
            return value;
        }

        QVariant left = _leftSide->calculate(symbolTable);
        QVariant right = _rightSide->calculate(symbolTable);

        // Convert a boolean value to an integer value
        if (left.canConvert<bool>()) {
            left = (left.toBool()) ? 1 : 0;
        }
        if (right.canConvert<bool>()) {
            right = (right.toBool()) ? 1 : 0;
        }

        QVariant result;

        if (_tokenType == TokenType::ASSIGN_ADD) {
            // Add can handle String concatenation
            result = add(left, right);
        } else {
            // For the other arithmetic operators, except add, only numbers can
            // be handled. For other types, return 0.
            if (! /*TypeConversionUtil.isFloatingNumber*/(left.canConvert<float>())) {
                result = 0;
            } else if (! /*TypeConversionUtil.isFloatingNumber*/(right.canConvert<float>())) {
                result = 0;
            } else {
                switch (_tokenType) {
                    case TokenType::ASSIGN_SUBTRACKT:
                        result = subtract(left, right);
                        break;
                    case TokenType::ASSIGN_MULTIPLY:
                        result = multiply(left, right);
                        break;
                    case TokenType::ASSIGN_DIVIDE:
                        result = divide(left, right);
                        break;
                    case TokenType::ASSIGN_MODULO:
                        result = modulo(left, right);
                        break;
                    default:
                        throw new CalculateException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
                }
            }
        }

        _leftSide->assignValue(symbolTable, result);
        return result;
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionNodeAssignmentOperator::getDefinitionString() {
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
