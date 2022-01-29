#include "expressionnodeternaryoperator.h"
#include "calculateexception.h"

/**
 * A parsed expression
 */
//public class ExpressionNodeTernaryOperator implements ExpressionNode {

    
    /*public*/ ExpressionNodeTernaryOperator::ExpressionNodeTernaryOperator(
            ExpressionNode* leftSide, ExpressionNode* middleSide, ExpressionNode* rightSide) {
        _leftSide = leftSide;
        _middleSide = middleSide;
        _rightSide = rightSide;
        
        if (_leftSide == nullptr) {
            throw new IllegalArgumentException("leftSide must not be null");
        }
    }
    
    //@Override
    /*public*/ QVariant ExpressionNodeTernaryOperator::calculate(SymbolTable* symbolTable) /*throws JmriException*/ {
        
        QVariant leftValue = _leftSide->calculate(symbolTable);
        if (!(leftValue.canConvert<bool>())) {
         if (/*TypeConversionUtil.isIntegerNumber*/(leftValue.canConvert<int>())) {
                // Convert to true or false
                leftValue = (/*(Number)*/leftValue).toInt() != 0;
            } else {
                throw new CalculateException(tr("Boolean operations cannot be done on the operand \"%1\" since it's not a boolean or an integer number").arg(leftValue.toString()));
            }
        }
        bool left = leftValue.toBool();
        
        if (left) {
            return _middleSide->calculate(symbolTable);
        } else {
            return _rightSide->calculate(symbolTable);
        }
    }
    
    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionNodeTernaryOperator::getDefinitionString() {
        return _rightSide->getDefinitionString() + " ? ("
                + _middleSide->getDefinitionString() + ") : ("
                + _rightSide->getDefinitionString()+")";
    }
    
