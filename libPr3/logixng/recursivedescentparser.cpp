#include "recursivedescentparser.h"
#include "invalidsyntaxexception.h"
#include "tokenizer.h"
#include "expressionnodeassignmentoperator.h"
#include "expressionnodeternaryoperator.h"
#include "expressionnodebooleanoperator.h"
#include "expressionnodecomparingoperator.h"
#include "expressionnodearithmeticoperator.h"
#include "functionnotexistsexception.h"
#include "expressionnodeidentifier.h"
#include "expressionnodeintegernumber.h"
#include "expressionnodefloatingnumber.h"
#include "expressionnodestring.h"
#include "expressionnodefunction.h"
/**
 * A recursive descent parser
 *
 * @author Daniel Bergqvist 2019
 */
///*public*/ class RecursiveDescentParser {



/*public*/ RecursiveDescentParser::RecursiveDescentParser(QMap<QString, Variable*> variables, QObject *parent) : QObject(parent) {
    setObjectName("RecursiveDescentParser");
 _variables = variables;
}

/*private*/ RecursiveDescentParser::State* RecursiveDescentParser::next(State* state) {
    int newTokenIndex = state->_tokenIndex+1;
    return new State(newTokenIndex, _tokens.value(newTokenIndex), state->_tokenIndex, state->_token);
}


/*private*/ RecursiveDescentParser::State* RecursiveDescentParser::accept(TokenType::TTYPE tokenType, RecursiveDescentParser::State* state) /*throws ParserException*/ {
    if (state->_token == nullptr) {
        return nullptr;
    }
    if (state->_token->_tokenType == tokenType) {
        int newTokenIndex = state->_tokenIndex+1;
        Token* newToken;
        int lastTokenPos = state->_lastTokenPos;
        if (newTokenIndex < _tokens.size()) {
            newToken = _tokens.value(newTokenIndex);
        } else {
            lastTokenPos = state->_token->_pos + state->_token->_string.length();
            newToken = nullptr;
        }
        return new State(newTokenIndex, newToken, lastTokenPos, state->_token);
    } else {
        return nullptr;
    }
}


/*private*/ RecursiveDescentParser::State* RecursiveDescentParser::expect(TokenType::TTYPE tokenType, State* state) /*throws ParserException*/ {
    State* newState = accept(tokenType, state);
    if (newState == nullptr) {
        throw new InvalidSyntaxException(tr("Invalid syntax error"));
    }
    return newState;
}


/*public*/ ExpressionNode* RecursiveDescentParser::parseExpression(QString expression) /*throws ParserException */{
    _tokens = Tokenizer::getTokens(expression);

    if (_tokens.isEmpty()) {
        return nullptr;
    }

    ExpressionNodeAndState* exprNodeAndState = firstRule->parse(new State(0, _tokens.value(0), 0, new Token()));

    if (exprNodeAndState == nullptr) {
        return nullptr;
    }

//        if (exprNodeAndState->_exprNode != null) {
//            System.err.format("Expression: \"%s\"%n", exprNodeAndState->_exprNode.getDefinitionString());
//        } else {
//            System.err.format("Expression: null%n");
//        }

    if ((exprNodeAndState->_state != nullptr)
            && (exprNodeAndState->_state->_tokenIndex < _tokens.size())) {

        throw new InvalidSyntaxException(tr("Invalid syntax error. The expression is not fully parsed. It failed at column %1").arg(exprNodeAndState->_state->_tokenIndex));
    }
    return exprNodeAndState->_exprNode;
}


// Assignment
// <rule1> ::= <rule2> ||
//             <rule2> = <rule1> ||
//             <rule2> += <rule1> ||
//             <rule2> -= <rule1> ||
//             <rule2> *= <rule1> ||
//             <rule2> /= <rule1> ||
//             <rule2> %= <rule1> ||
//             <rule2> &= <rule1> ||
//             <rule2> ^= <rule1> ||
//             <rule2> |= <rule1> ||
//             <rule2> <<= <rule1> ||
//             <rule2> >>= <rule1> ||
//             <rule2> >>>= <rule1>
//    /*private*/ class Rule1 : public Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule1::parse(State* state) /*throws ParserException*/ {
        ExpressionNodeAndState* leftSide =rdp->rule2->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        if ((newState->_token != nullptr)
                && (
                    (newState->_token->_tokenType == TokenType::ASSIGN)
                    || (newState->_token->_tokenType == TokenType::ASSIGN_ADD)
                    || (newState->_token->_tokenType == TokenType::ASSIGN_SUBTRACKT)
                    || (newState->_token->_tokenType == TokenType::ASSIGN_MULTIPLY)
                    || (newState->_token->_tokenType == TokenType::ASSIGN_DIVIDE)
                    || (newState->_token->_tokenType == TokenType::ASSIGN_MODULO)
                )) {

            TokenType::TTYPE operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* rightSide =rdp->rule2->parse(newState);

            ExpressionNode* exprNode = new ExpressionNodeAssignmentOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
            leftSide = new ExpressionNodeAndState(exprNode, rightSide->_state);
        }
        return leftSide;
    }

//    };


// Rule2 is ternary. <rule3> | <rule3> ? <rule2> : <rule2>
//    /*private*/ class Rule2 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule2::parse(State* state) /*throws ParserException*/ {
        ExpressionNodeAndState* leftSide =rdp->rule3->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        if ((newState->_token != nullptr)
                && ((newState->_token->_tokenType == TokenType::TERNARY_QUESTION_MARK))) {

            if (! leftSide->_exprNode->canBeAssigned()) {
                throw new InvalidSyntaxException(tr("Left side cannot be assigned a value"));
            }

//                TokenType operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* middleSide =rdp->rule3->parse(newState);

//                ExpressionNode* exprNode = new ExpressionNodeBooleanOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
//                leftSide = new ExpressionNodeAndState(exprNode, middleSide->_state);
            newState = middleSide->_state;

            if ((newState->_token != nullptr)
                    && ((newState->_token->_tokenType == TokenType::TERNARY_COLON))) {

//                    TokenType operatorTokenType = newState->_token->_tokenType;
                newState = rdp->next(newState);
                ExpressionNodeAndState* rightRightSide =rdp->rule3->parse(newState);

                ExpressionNode* exprNode = new ExpressionNodeTernaryOperator(
                        leftSide->_exprNode, middleSide->_exprNode, rightRightSide->_exprNode);
                leftSide = new ExpressionNodeAndState(exprNode, rightRightSide->_state);
            } else {
                throw new InvalidSyntaxException(tr("Invalid syntax error"));
            }
        }
        return leftSide;
    }




// Logical OR
// <rule3> ::= <rule4> | <rule4> || <rule4>
//    /*private*/ class Rule3 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule3::parse(State* state) /*throws ParserException*/ {
        ExpressionNodeAndState* leftSide =rdp->rule4->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        while ((newState->_token != nullptr)
                && ((newState->_token->_tokenType == TokenType::BOOLEAN_OR))) {

            TokenType::TTYPE operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* rightSide =rdp->rule4->parse(newState);

            ExpressionNode* exprNode = new ExpressionNodeBooleanOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
            leftSide = new ExpressionNodeAndState(exprNode, rightSide->_state);
            newState = rightSide->_state;
        }
        return leftSide;
    }



// Logical AND
// <rule4> ::= <rule5> | <rule5> && <rule5>
//    /*private*/ class Rule4 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule4::parse(State* state) /*throws ParserException*/ {

        ExpressionNodeAndState* leftSide =rdp->rule5->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        while ((newState->_token != nullptr)
                && ((newState->_token->_tokenType == TokenType::BOOLEAN_AND))) {

            TokenType::TTYPE operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* rightSide =rdp->rule5->parse(newState);

            ExpressionNode* exprNode = new ExpressionNodeBooleanOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
            leftSide = new ExpressionNodeAndState(exprNode, rightSide->_state);
            newState = rightSide->_state;
        }
        return leftSide;
    }

//    }


// Bitwise OR
// <rule5> ::= <rule6> | <rule6> | <rule6>
//    /*private*/ class Rule5 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule5::parse(State* state) /*throws ParserException*/ {

        return rdp->rule6->parse(state);
    }

//    }


// Bitwise XOR
// <rule6> ::= <rule7> | <rule7> ^ <rule7>
//    /*private*/ class Rule6 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule6::parse(State* state) /*throws ParserException*/ {

        return rdp->rule7->parse(state);
    }

//    }


// Bitwise AND
// <rule7> ::= <rule8> | <rule8> & <rule8>
//    /*private*/ class Rule7 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule7::parse(State* state) /*throws ParserException*/ {

        return rdp->rule8->parse(state);
    }

//    }


// Equality
// <rule8> ::= <rule9> | <rule9> == <rule9> | <rule9> != <rule9>
//    /*private*/ class Rule8 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule8::parse(State* state) /*throws ParserException*/ {

        ExpressionNodeAndState* leftSide =rdp->rule9->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        while ((newState->_token != nullptr)
                && ((newState->_token->_tokenType == TokenType::EQUAL)
                        || (newState->_token->_tokenType == TokenType::NOT_EQUAL))) {

            TokenType::TTYPE operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* rightSide =rdp->rule9->parse(newState);

            ExpressionNode* exprNode = new ExpressionNodeComparingOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
            leftSide = new ExpressionNodeAndState(exprNode, rightSide->_state);
            newState = rightSide->_state;
        }
        return leftSide;
    }

//    }


// Relational
// <rule9> ::= <rule10> | <rule10> < <rule10> | <rule10> <= <rule10> | <rule10> > <rule10> | <rule10> >= <rule10>
//    /*private*/ class Rule9 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule9::parse(State* state) /*throws ParserException*/ {

        ExpressionNodeAndState* leftSide =rdp->rule10->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        while ((newState->_token != nullptr)
                && ((newState->_token->_tokenType == TokenType::LESS_THAN)
                        || (newState->_token->_tokenType == TokenType::LESS_OR_EQUAL)
                        || (newState->_token->_tokenType == TokenType::GREATER_THAN)
                        || (newState->_token->_tokenType == TokenType::GREATER_OR_EQUAL))) {

            TokenType::TTYPE operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* rightSide =rdp->rule10->parse(newState);

            ExpressionNode* exprNode = new ExpressionNodeComparingOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
            leftSide = new ExpressionNodeAndState(exprNode, rightSide->_state);
            newState = rightSide->_state;
        }
        return leftSide;
    }

//    }


// Shift. Not implemented yet.
// <rule10> ::= <rule11> | <rule11> << <rule11> | <rule11> >> <rule11> | <rule11> >>> <rule11>
//    /*private*/ class Rule10 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule10::parse(State* state) /*throws ParserException*/ {

        return rdp->rule11->parse(state);
    }

//    }


// Additive
// <rule11> ::= <rule12> | <rule12> + <rule12> | <rule12> - <rule12>
//    /*private*/ class Rule11 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule11::parse(State* state) /*throws ParserException*/ {

        ExpressionNodeAndState* leftSide =rdp->rule12->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        while ((newState->_token != nullptr)
                && ((newState->_token->_tokenType == TokenType::ADD)
                        || (newState->_token->_tokenType == TokenType::SUBTRACKT))) {

            TokenType::TTYPE operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* rightSide =rdp->rule12->parse(newState);

            ExpressionNode* exprNode = new ExpressionNodeArithmeticOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
            leftSide = new ExpressionNodeAndState(exprNode, rightSide->_state);
            newState = rightSide->_state;
        }
        return leftSide;
    }

//    }


// Multiplicative
// <rule12> ::= <rule13> | <rule13> * <rule13> | <rule13> / <rule13> | <rule13> % <rule13>
//    /*private*/ class Rule12 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule12::parse(State* state) /*throws ParserException*/ {

        ExpressionNodeAndState* leftSide =rdp->rule14->parse(state);
        if (leftSide == nullptr) {
            return nullptr;
        }
        State* newState = leftSide->_state;
        while ((newState->_token != nullptr)
                && ((newState->_token->_tokenType == TokenType::MULTIPLY)
                        || (newState->_token->_tokenType == TokenType::DIVIDE)
                        || (newState->_token->_tokenType == TokenType::MODULO))) {

            TokenType::TTYPE operatorTokenType = newState->_token->_tokenType;
            newState = rdp->next(newState);
            ExpressionNodeAndState* rightSide =rdp->rule14->parse(newState);

            ExpressionNode* exprNode = new ExpressionNodeArithmeticOperator(operatorTokenType, leftSide->_exprNode, rightSide->_exprNode);
            leftSide = new ExpressionNodeAndState(exprNode, rightSide->_state);
            newState = rightSide->_state;
        }
        return leftSide;
    }

//    }


// Rule3 in Java is cast object and object creation. Not relevant here.


// Unary pre-increment, unary pre-decrement, unary plus, unary minus, unary logical NOT, unary bitwise NOT
// <rule14> ::= <rule16> | ! <rule16> | ~ <rule16>
//    /*private*/ class Rule14 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule14::parse(State* state) /*throws ParserException*/ {


        State* newState = rdp->accept(TokenType::BOOLEAN_NOT, state);

        if (newState != nullptr) {
            ExpressionNodeAndState* exprNodeAndState =rdp->rule14->parse(newState);
            if (exprNodeAndState->_exprNode == nullptr) {
                throw new InvalidSyntaxException(tr("Invalid syntax error"));
            }

            ExpressionNode* exprNode = new ExpressionNodeBooleanOperator(newState->_lastToken->_tokenType, nullptr, exprNodeAndState->_exprNode);
            return new ExpressionNodeAndState(exprNode, exprNodeAndState->_state);

        } else {
            newState = rdp->accept(TokenType::BINARY_NOT, state);

            if (newState != nullptr) {
                ExpressionNodeAndState* exprNodeAndState =rdp->rule14->parse(newState);
                if (exprNodeAndState->_state->_token == nullptr) {
                    throw new InvalidSyntaxException(tr("Invalid syntax error"));
                }

                ExpressionNode* exprNode = new ExpressionNodeArithmeticOperator(newState->_lastToken->_tokenType, nullptr, exprNodeAndState->_exprNode);
                return new ExpressionNodeAndState(exprNode, exprNodeAndState->_state);

            } else {
                return rdp->rule16->parse(state);
            }
        }
    }

//    }


// Rule15 in Java is unary post-increment, unary post-decrement. I.e. ++ and --. Don't implement here.


// Parentheses
// <rule16> ::= <rule20> ( <firstRule> )
//    /*private*/ class Rule16 implements Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule16::parse(State* state) /*throws ParserException*/ {


        State* newState = rdp->accept(TokenType::LEFT_PARENTHESIS, state);

        if (newState != nullptr) {
            ExpressionNodeAndState* exprNodeAndState = rdp->firstRule->parse(newState);
            if (exprNodeAndState->_state->_token == nullptr) {
                throw new InvalidSyntaxException(tr("Invalid syntax error"));
            }
            newState = rdp->expect(TokenType::RIGHT_PARENTHESIS, exprNodeAndState->_state);
            return new ExpressionNodeAndState(exprNodeAndState->_exprNode, newState);
        } else {
            return rdp->rule20->parse(state);
        }
    }

//    }


// Identifiers and constants
// <rule20> ::= <identifier> | <identifier> ( <rule21> ) | <integer number> | <floating number> | <string>
//    /*private*/ class Rule20 : public Rule {

    //@Override
    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule20::parse(State* state) /*throws ParserException*/ {

        ExpressionNode* exprNode;

        State* newState;
        if ((newState = rdp->accept(TokenType::IDENTIFIER, state)) != nullptr) {
            State* newState2;
            if ((newState2 = rdp->accept(TokenType::LEFT_PARENTHESIS, newState)) != nullptr) {
                ExpressionNodeAndState* exprNodeAndState =
                       rdp->rule21->parse2(newState2, newState->_lastToken->_string);
                if (exprNodeAndState->_state->_token == nullptr) {
                    throw new InvalidSyntaxException(tr("Invalid syntax error"));
                }
                newState2 = rdp->expect(TokenType::RIGHT_PARENTHESIS, exprNodeAndState->_state);
                return new ExpressionNodeAndState(exprNodeAndState->_exprNode, newState2);
            } else {
                exprNode = new ExpressionNodeIdentifier(newState->_lastToken, rdp->_variables);
            }
        } else if ((newState = rdp->accept(TokenType::INTEGER_NUMBER, state)) != nullptr) {
            exprNode = new ExpressionNodeIntegerNumber(newState->_lastToken);
        } else if ((newState = rdp->accept(TokenType::FLOATING_NUMBER, state)) != nullptr) {
            exprNode = new ExpressionNodeFloatingNumber(newState->_lastToken);
        } else if ((newState = rdp->accept(TokenType::STRING, state)) != nullptr) {
            exprNode = new ExpressionNodeString(newState->_lastToken);
        } else {
            return nullptr;
        }

        return new ExpressionNodeAndState(exprNode, newState);
    }

//    };


// <rule21> ::= <empty> | <rule21> | <rule21> , <rule3>
//    /*private*/ class Rule21 {

    /*public*/ RecursiveDescentParser::ExpressionNodeAndState* RecursiveDescentParser::Rule21::parse2(State* state, QString identifier) /*throws ParserException*/ {

        QList<ExpressionNode*> parameterList = QList<ExpressionNode*>();

        State* newState = state;
        State* newState2;
        if ((rdp->accept(TokenType::RIGHT_PARENTHESIS, newState)) == nullptr) {
            ExpressionNodeAndState* exprNodeAndState =rdp->rule3->parse(state);
            parameterList.append(exprNodeAndState->_exprNode);

            while ((newState2 = rdp->accept(TokenType::COMMA, exprNodeAndState->_state)) != nullptr) {
                exprNodeAndState =rdp->rule3->parse(newState2);
                parameterList.append(exprNodeAndState->_exprNode);
            }

            newState = exprNodeAndState->_state;
        }
        ExpressionNode* exprNode = new ExpressionNodeFunction(identifier, parameterList);
        return new ExpressionNodeAndState(exprNode, newState);
    }



