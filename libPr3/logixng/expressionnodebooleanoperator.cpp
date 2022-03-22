#include "expressionnodebooleanoperator.h"
#include "calculateexception.h"
#include "typeconversionutil.h"

/**
 * A parsed expression
 */
// /*public*/ class ExpressionNodeBooleanOperator implements ExpressionNode {

    
    /*public*/ ExpressionNodeBooleanOperator::ExpressionNodeBooleanOperator(TokenType::TTYPE tokenType, ExpressionNode* leftSide, ExpressionNode* rightSide) {
        _tokenType = tokenType;
        _leftSide = leftSide;
        _rightSide = rightSide;
        
        if (_rightSide == nullptr) {
            throw new IllegalArgumentException("rightSide must not be null");
        }
        
        // Verify that the token is of the correct type
        switch (_tokenType) {
            case TokenType::TTYPE::BOOLEAN_OR:
            case TokenType::TTYPE::BOOLEAN_AND:
                if (_leftSide == nullptr) {
                    throw new IllegalArgumentException("leftSide must not be null for operators AND and OR");
                }
                break;
                
            case TokenType::TTYPE::BOOLEAN_NOT:
                if (_leftSide != nullptr) {
                    throw new IllegalArgumentException("leftSide must be null for operator NOT");
                }
                break;
                
            default:
                throw new IllegalArgumentException("Unsupported boolean operator: "+TokenType::toString(_tokenType));
        }
    }
    
    //@Override
    /*public*/ QVariant ExpressionNodeBooleanOperator::calculate(SymbolTable* symbolTable) /*throws JmriException */{
        
        QVariant rightValue = _rightSide->calculate(symbolTable);
        if (!(rightValue.canConvert<bool>())) {
            if (TypeConversionUtil::isIntegerNumber(rightValue)) {
                // Convert to true or false
                rightValue = rightValue.toInt() != 0;
            } else {
                throw new CalculateException(tr("Boolean operations cannot be done on the operand \"%1\" since it's not a boolean or an integer number").arg(rightValue.toString()));
            }
        }
        bool right = rightValue.toBool();
        
        if (_tokenType == TokenType::BOOLEAN_NOT) {
            return ! right;
        }
        
        QVariant leftValue = _leftSide->calculate(symbolTable);
        if (!(leftValue.canConvert<bool>())) {
            if (TypeConversionUtil::isIntegerNumber(leftValue))  {
                // Convert to true or false
                leftValue = leftValue.toBool() != 0;
            } else {
                throw new CalculateException(tr("Boolean operations cannot be done on the operand \"%1\" sinse it's not a boolean or an integer number").arg(leftValue.toString()));
            }
        }
        bool left = leftValue.toBool();
        
        switch (_tokenType) {
            case TokenType::BOOLEAN_OR:
                return left || right;
                
            case TokenType::BOOLEAN_AND:
                return left && right;
                
            default:
                throw new CalculateException("Unknown boolean operator: "+TokenType::toString(_tokenType));
        }
    }
    
    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionNodeBooleanOperator::getDefinitionString() {
        QString operStr;
        switch (_tokenType) {
            case TokenType::BOOLEAN_OR:
                operStr = "||";
                break;
                
            case TokenType::BOOLEAN_AND:
                operStr = "&&";
                break;
                
            case TokenType::BOOLEAN_NOT:
                operStr = "!";
                break;
                
            default:
                throw new UnsupportedOperationException("Unknown arithmetic operator: "+TokenType::toString(_tokenType));
        }
        if (_leftSide != nullptr) {
            return "("+_leftSide->getDefinitionString()+")" + operStr + "("+_rightSide->getDefinitionString()+")";
        } else {
            return operStr + "("+_rightSide->getDefinitionString()+")";
        }
    }
    

