#include "tokenizer.h"
#include "invalidsyntaxexception.h"
#include <QRegularExpression>
#include "runtimeexception.h"

/**
 * Parses and calculates an expression, for example "sin(2*pi*x)/3"
 *
 * @author Daniel Bergqvist 2019
 */
///*public*/ class Tokenizer {

    /*private*/ /*static*/ void Tokenizer::addToken(Token* currentToken, QList<Token*>* tokens) {
        if ((currentToken->_tokenType == TokenType::FLOATING_NUMBER) && isIntegerNumber(currentToken->_string)) {
            currentToken->_tokenType = TokenType::INTEGER_NUMBER;
        }

        tokens->append(currentToken);
    }

    /*public*/ /*static*/ QList<Token*>* Tokenizer::getTokens(QString expression) /*throws InvalidSyntaxException*/ {

        QList<Token*>* tokens = new QList<Token*>();
        Token* currentToken = new Token();

//        System.out.format("%n%n%n");
//        System.out.format("getTokens(): %s%n", expression);

        AtomicBoolean* eatNextChar = new AtomicBoolean(false);

        QChar ch = ' ';
        QChar lastChar;

        for (int i=0; i < expression.length(); i++) {
            lastChar = ch;
            ch = expression.at(i);
            QChar nextChar = ' ';    // An extra space at the end of the _string doesn't matter
            if (i+1 < expression.length()) {
                nextChar = expression.at(i+1);
            }

//            System.out.format("index %d: %s, %s, %c, %c%n", i, currentToken->_tokenType.name(), currentToken->_string, ch, nextChar);



            // Check for token type STRING
            if (ch == '\"') {
                if (QChar(lastChar).isLetterOrNumber()) {
                    throw new InvalidSyntaxException(tr("Invalid syntax at index %1").arg(i));
                }

                if (currentToken->_tokenType == TokenType::SPACE) {
                    currentToken = new Token();
                } else if (currentToken->_tokenType != TokenType::NONE) {
//                    System.out.format("Add: index %d: %s, %s, %c, %c%n", i, currentToken->_tokenType.name(), currentToken->_string, ch, nextChar);
                    addToken(currentToken, tokens);
                    currentToken = new Token();
                }
                currentToken->_tokenType = TokenType::STRING;

                bool done = false;
                while (!done) {
                    i++;
                    if (i >= expression.length()) {
                        throw new InvalidSyntaxException(tr("Unexpected end of string. Possible cause is a string that's not terminated."));
                    }
                    ch = expression.at(i);
                    nextChar = ' ';    // An extra space at the end of the _string doesn't matter
                    if (i+1 < expression.length()) {
                        nextChar = expression.at(i+1);
                    }
                    // Handle escaped characters
                    if ((ch == '\\') && ((nextChar == '\\') || (nextChar == '"'))) {

                        currentToken->_string += nextChar;
                        i++;
                    } else if (ch != '\"') {
                        currentToken->_string += ch;
                    }

                    done = (ch == '\"');
                }

                if (QChar(nextChar).isLetterOrNumber()) {
                    throw new InvalidSyntaxException(tr("Invalid syntax at index %1").arg(i));
                }

//                System.out.format("Add: index %d: %s, %s, %c, %c%n", i, currentToken->_tokenType.name(), currentToken->_string, ch, nextChar);
                addToken(currentToken, tokens);
                currentToken = new Token();

                // Continue for loop
                continue;
            }


            TokenType::TTYPE nextToken = getTokenType(currentToken, ch, nextChar, eatNextChar);
//            System.out.format("index %d: %s, %c%n", i, nextToken.name(), ch);

            if (nextToken == TokenType::SAME_AS_LAST) {
                currentToken->_string += ch;
                continue;
            }

            switch (nextToken) {
                case TokenType::ERROR:
                    throw new InvalidSyntaxException(tr("Invalid syntax at index %1").arg(i));

                case TokenType::LEFT_PARENTHESIS:
                case TokenType::RIGHT_PARENTHESIS:
                case TokenType::LEFT_SQUARE_BRACKET:
                case TokenType::RIGHT_SQUARE_BRACKET:
                case TokenType::LEFT_CURLY_BRACKET:
                case TokenType::RIGHT_CURLY_BRACKET:
                case TokenType::DOT_DOT:
                case TokenType::COMMA:
                case TokenType::EQUAL:
                case TokenType::NOT_EQUAL:
                case TokenType::LESS_THAN:
                case TokenType::LESS_OR_EQUAL:
                case TokenType::GREATER_THAN:
                case TokenType::GREATER_OR_EQUAL:
                case TokenType::ADD:
                case TokenType::SUBTRACKT:
                case TokenType::MULTIPLY:
                case TokenType::DIVIDE:
                case TokenType::MODULO:
                case TokenType::BOOLEAN_AND:
                case TokenType::BOOLEAN_OR:
                case TokenType::BOOLEAN_NOT:
                case TokenType::BINARY_AND:
                case TokenType::BINARY_OR:
                case TokenType::BINARY_NOT:
                case TokenType::IDENTIFIER:
                case TokenType::SPACE:
                case TokenType::NONE:
                    if ((currentToken->_tokenType != TokenType::NONE) && (currentToken->_tokenType != TokenType::SPACE)) {
                        addToken(currentToken, tokens);
                        currentToken = new Token();
                    }
                    currentToken->_tokenType = nextToken;
                    break;

                case TokenType::FLOATING_NUMBER:
                    if ((currentToken->_tokenType == TokenType::FLOATING_NUMBER) && !currentToken->_string.isEmpty() && !isFloatingNumber(currentToken->_string)) {
//                        System.out.format("Not a number: '%s'%n", currentToken->_string);
                        throw new InvalidSyntaxException(tr("Invalid syntax at index %1").arg(i));
                    }
                    if ((currentToken->_tokenType != TokenType::NONE) && (currentToken->_tokenType != TokenType::SPACE)) {
                        addToken(currentToken, tokens);
                        currentToken = new Token();
                    }
                    currentToken->_tokenType = nextToken;
                    break;

                case TokenType::STRING:
                    if (!currentToken->_string.endsWith("\"")) {
//                        System.err.format("String: %s%n", currentToken->_string);
                        throw new InvalidSyntaxException(tr("Invalid syntax at index %1").arg(i));
                    }
                    if ((currentToken->_tokenType != TokenType::NONE) && (currentToken->_tokenType != TokenType::SPACE)) {
                        addToken(currentToken, tokens);
                        currentToken = new Token();
                    }
                    currentToken->_tokenType = nextToken;
                    break;

                default:
                    throw new RuntimeException("unknown token type: "+TokenType::toString(nextToken));
            }

            if (currentToken->_tokenType != TokenType::SPACE) {
                currentToken->_string += ch;
            }

            if (eatNextChar->get()) {
                i++;
            }
//            System.out.format("New string: '%s'%n", currentToken->_string);
        }

        if (currentToken->_tokenType != TokenType::NONE) {
            addToken(currentToken, tokens);
        }

        return tokens;
    }

    /*private*/ /*static*/ TokenType::TTYPE Tokenizer::getTokenType(Token* currentToken, QChar ch, QChar nextChar, AtomicBoolean* eatNextChar) {

        eatNextChar->set(false);

        if (ch == '"') {
            return TokenType::STRING;
        }

        if (QChar(ch).isSpace()) {
            return TokenType::SPACE;
        }

        if (currentToken->_tokenType == TokenType::STRING) {
            return TokenType::SAME_AS_LAST;
        }

        if ((ch == '.') && (nextChar == '.')) {
            if ((currentToken->_tokenType != TokenType::DOT_DOT)) {
                eatNextChar->set(true);
                return TokenType::DOT_DOT;
            } else {
                // Three dots in a row is an error
                return TokenType::ERROR;
            }
        }

        if (ch == '?') {
            return TokenType::TERNARY_QUESTION_MARK;
        }

        if (ch == ':') {
            return TokenType::TERNARY_COLON;
        }

        if ((ch == '=') && (nextChar != '=')) {
            return TokenType::ASSIGN;
        }

        if (nextChar == '=') {
            switch (ch.toLatin1()) {
                case '+':
                    eatNextChar->set(true);
                    return TokenType::ASSIGN_ADD;
                case '-':
                    eatNextChar->set (true);
                    return TokenType::ASSIGN_SUBTRACKT;
                case '*':
                    eatNextChar->set (true);
                    return TokenType::ASSIGN_MULTIPLY;
                case '/':
                    eatNextChar->set (true);
                    return TokenType::ASSIGN_DIVIDE;
                case '%':
                    eatNextChar->set (true);
                    return TokenType::ASSIGN_MODULO;
//                default:
                    // Do nothing
            }
        }

        if (ch == '<') {
            switch (nextChar.toLatin1()) {
                case '=':
                    eatNextChar->set (true);
                    return TokenType::LESS_OR_EQUAL;
                case '<':
                    eatNextChar->set (true);
                    return TokenType::SHIFT_LEFT;
                default:
                    return TokenType::LESS_THAN;
            }
        }

        if (ch == '>') {
            switch (nextChar.toLatin1()) {
                case '=':
                    eatNextChar->set (true);
                    return TokenType::GREATER_OR_EQUAL;
                case '>':
                    eatNextChar->set (true);
                    return TokenType::SHIFT_RIGHT;
                default:
                    return TokenType::GREATER_THAN;
            }
        }

        if (ch == '=') {
            if (nextChar == '=') {
                eatNextChar->set (true);
                return TokenType::EQUAL;
            } else {
                return TokenType::ERROR;
            }
        }

        if (ch == '!') {
            if (nextChar == '=') {
                eatNextChar->set (true);
                return TokenType::NOT_EQUAL;
            } else {
                return TokenType::BOOLEAN_NOT;
            }
        }

        if (ch == '|') {
            if (nextChar == '|') {
                eatNextChar->set (true);
                return TokenType::BOOLEAN_OR;
            } else {
                return TokenType::BINARY_OR;
            }
        }

        if (ch == '&') {
            if (nextChar == '&') {
                eatNextChar->set (true);
                return TokenType::BOOLEAN_AND;
            } else {
                return TokenType::BINARY_AND;
            }
        }

        if (ch == '~') {
            return TokenType::BINARY_NOT;
        }

        if (ch == ',') {
            return TokenType::COMMA;
        }

        if (ch == '+') {
            return TokenType::ADD;
        }

        if (ch == '-') {
            return TokenType::SUBTRACKT;
        }

        if (ch == '*') {
            return TokenType::MULTIPLY;
        }

        if (ch == '/') {
            return TokenType::DIVIDE;
        }

        if (ch == '%') {
            return TokenType::MODULO;
        }

        if (ch == '^') {
            return TokenType::BINARY_XOR;
        }

        if (ch == '(') {
            return TokenType::LEFT_PARENTHESIS;
        }

        if (ch == ')') {
            return TokenType::RIGHT_PARENTHESIS;
        }

        if (ch == '[') {
            return TokenType::LEFT_SQUARE_BRACKET;
        }

        if (ch == ']') {
            return TokenType::RIGHT_SQUARE_BRACKET;
        }

        if (ch == '{') {
            return TokenType::LEFT_CURLY_BRACKET;
        }

        if (ch == '}') {
            return TokenType::RIGHT_CURLY_BRACKET;
        }

        if ((currentToken->_tokenType == TokenType::FLOATING_NUMBER) &&
                (isFloatingNumber(currentToken->_string+ch) || isFloatingNumber(currentToken->_string+ch+nextChar))) {
            return TokenType::SAME_AS_LAST;
        }

        if ((currentToken->_tokenType == TokenType::IDENTIFIER) && ((ch.isLetterOrNumber()) || (ch == '_'))) {
            return TokenType::SAME_AS_LAST;
        }

        if ((ch.isDigit())) {
            return TokenType::FLOATING_NUMBER;
        }

        if ((currentToken->_tokenType == TokenType::FLOATING_NUMBER) &&
                ((ch.isLetterOrNumber()))) {
            return TokenType::ERROR;
        }

        if (QChar(ch).isDigit()) {
            return TokenType::FLOATING_NUMBER;
        }

        if (QChar(ch).isLetter() || (ch == '_')) {
            return TokenType::IDENTIFIER;
        }

        return TokenType::ERROR;
    }

    /*private*/ /*static*/ bool Tokenizer::isIntegerNumber(QString str) {
        //return str.matches("\\d+");
     QRegularExpression re("\\d+");
     QRegularExpressionMatch match = re.match(str);
     return match.hasMatch() && match.capturedLength() == str.length();
    }

    /*private*/ /*static*/ bool Tokenizer::isFloatingNumber(QString str) {
        //return str.matches("\\d+") || str.matches("\\d+\\.\\d+");
        QRegularExpression red("\\d+");
        QRegularExpression  ref("\\d+\\.\\d+");
        QRegularExpressionMatch matchd = red.match(str);
        QRegularExpressionMatch matchf = ref.match(str);
        return matchd.hasMatch() || matchf.hasMatch();
    }
