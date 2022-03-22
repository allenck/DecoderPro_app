#include "tokenizertest.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "assert1.h"
#include "token.h"
#include "atomicboolean.h"
#include "invalidsyntaxexception.h"
#include "loggerfactory.h"

/**
 * Test Tokenizer
 *
 * @author Daniel Bergqvist 2019
 */
// /*public*/  class TokenizerTest {

    //@Test
    /*public*/  void TokenizerTest::testCtor() {
        Tokenizer* t = new Tokenizer();
        Assert::assertNotNull("not null", t, __FILE__, __LINE__);
    }

    /*private*/ void TokenizerTest::checkFirstToken(
            QList<Token*>* tokens,
            TokenType::TTYPE tokenType, QString string) {

        Assert::assertTrue("list is not empty", tokens->size() > 0, __FILE__, __LINE__);
        log->debug(tr("Type: %1, String: '%2'").arg(TokenType::toString(tokens->at(0)->getTokenType()), tokens->at(0)->getString()));
        //Assert::assertTrue("token type matches", tokens->at(0)->getTokenType() == tokenType, __FILE__, __LINE__);
        Assert::assertEquals("token type matches", TokenType::toString(tokens->at(0)->getTokenType()) , TokenType::toString(tokenType), __FILE__, __LINE__);
        Assert::assertEquals("string matches", string,(tokens->at(0)->getString()), __FILE__, __LINE__);

        tokens->removeAt(0);
    }

    //@Test
    /*public*/  void TokenizerTest::testGetTokens() /*throws InvalidSyntaxException*/ {

        QList<Token*>* tokens = new QList<Token*>();
        AtomicBoolean* exceptionIsThrown = new AtomicBoolean();

        tokens = Tokenizer::getTokens("");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

//        tokens = Tokenizer::getTokens("1");
//        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "1");
//        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("R1ABC");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1ABC");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("R1ABC");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1ABC");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("321");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "321");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("32.221");
        checkFirstToken(tokens, TokenType::FLOATING_NUMBER, "32.221");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("321 353");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "321");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "353");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("321   353");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "321");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "353");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("321354");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "321354");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("\"A_String\"");
        checkFirstToken(tokens, TokenType::STRING, "A_String");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("\"A_Str\\\"ing\"");
        checkFirstToken(tokens, TokenType::STRING, "A_Str\"ing");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("\"A_Str\\\\ing\"");
        checkFirstToken(tokens, TokenType::STRING, "A_Str\\ing");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("\"A string\"");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("1223 \"A string\"");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "1223");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("   \"A string\" 1234");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "1234");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("1223*\"A string\"");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "1223");
        checkFirstToken(tokens, TokenType::MULTIPLY, "*");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        exceptionIsThrown->set(false);
        try {
            Tokenizer::getTokens("\"A string\"1234");
        } catch (InvalidSyntaxException* e) {
            Assert::assertTrue("exception message matches", "Invalid syntax at index 9" == (e->getMessage()), __FILE__, __LINE__);
            exceptionIsThrown->set(true);
        }
        Assert::assertTrue("exception is thrown", exceptionIsThrown->get(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("\"A string\"*232");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        checkFirstToken(tokens, TokenType::MULTIPLY, "*");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "232");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("1223+\"A string\"*232");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "1223");
        checkFirstToken(tokens, TokenType::ADD, "+");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        checkFirstToken(tokens, TokenType::MULTIPLY, "*");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "232");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("1223 \"A string\"/\" \"");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "1223");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        checkFirstToken(tokens, TokenType::DIVIDE, "/");
        checkFirstToken(tokens, TokenType::STRING, " ");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("\"A string\"+\"Another string\"");
        checkFirstToken(tokens, TokenType::STRING, "A string");
        checkFirstToken(tokens, TokenType::ADD, "+");
        checkFirstToken(tokens, TokenType::STRING, "Another string");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("(");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens(")");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("(R1)");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("&&");
        checkFirstToken(tokens, TokenType::BOOLEAN_AND, "&");    // The second & is eaten by the parser and not included in the _string.
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("R1 && R2");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1");
        checkFirstToken(tokens, TokenType::BOOLEAN_AND, "&");    // The second & is eaten by the parser and not included in the _string.
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R2");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("!(12 < 2)");
        checkFirstToken(tokens, TokenType::BOOLEAN_NOT, "!");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "12");
        checkFirstToken(tokens, TokenType::LESS_THAN, "<");
        checkFirstToken(tokens, TokenType::INTEGER_NUMBER, "2");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("R1(x)");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("R1[x]");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1");
        checkFirstToken(tokens, TokenType::LEFT_SQUARE_BRACKET, "[");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::RIGHT_SQUARE_BRACKET, "]");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("{x,y,z}[a]");
        checkFirstToken(tokens, TokenType::LEFT_CURLY_BRACKET, "{");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "y");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "z");
        checkFirstToken(tokens, TokenType::RIGHT_CURLY_BRACKET, "}");
        checkFirstToken(tokens, TokenType::LEFT_SQUARE_BRACKET, "[");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "a");
        checkFirstToken(tokens, TokenType::RIGHT_SQUARE_BRACKET, "]");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("{x,y,z}[a..b]");
        checkFirstToken(tokens, TokenType::LEFT_CURLY_BRACKET, "{");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "y");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "z");
        checkFirstToken(tokens, TokenType::RIGHT_CURLY_BRACKET, "}");
        checkFirstToken(tokens, TokenType::LEFT_SQUARE_BRACKET, "[");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "a");
        checkFirstToken(tokens, TokenType::DOT_DOT, ".");    // The second dot is eaten by the parser and not included in the _string.
        checkFirstToken(tokens, TokenType::IDENTIFIER, "b");
        checkFirstToken(tokens, TokenType::RIGHT_SQUARE_BRACKET, "]");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("{x,y,z}[a..b,c]");
        checkFirstToken(tokens, TokenType::LEFT_CURLY_BRACKET, "{");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "y");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "z");
        checkFirstToken(tokens, TokenType::RIGHT_CURLY_BRACKET, "}");
        checkFirstToken(tokens, TokenType::LEFT_SQUARE_BRACKET, "[");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "a");
        checkFirstToken(tokens, TokenType::DOT_DOT, ".");    // The second dot is eaten by the parser and not included in the _string.
        checkFirstToken(tokens, TokenType::IDENTIFIER, "b");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "c");
        checkFirstToken(tokens, TokenType::RIGHT_SQUARE_BRACKET, "]");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("{x,y,z}[a,b..c]");
        checkFirstToken(tokens, TokenType::LEFT_CURLY_BRACKET, "{");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "y");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "z");
        checkFirstToken(tokens, TokenType::RIGHT_CURLY_BRACKET, "}");
        checkFirstToken(tokens, TokenType::LEFT_SQUARE_BRACKET, "[");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "a");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "b");
        checkFirstToken(tokens, TokenType::DOT_DOT, ".");    // The second dot is eaten by the parser and not included in the _string.
        checkFirstToken(tokens, TokenType::IDENTIFIER, "c");
        checkFirstToken(tokens, TokenType::RIGHT_SQUARE_BRACKET, "]");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("{x,y,z}[a,b..c,d,e,f..g]");
        checkFirstToken(tokens, TokenType::LEFT_CURLY_BRACKET, "{");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "y");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "z");
        checkFirstToken(tokens, TokenType::RIGHT_CURLY_BRACKET, "}");
        checkFirstToken(tokens, TokenType::LEFT_SQUARE_BRACKET, "[");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "a");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "b");
        checkFirstToken(tokens, TokenType::DOT_DOT, ".");    // The second dot is eaten by the parser and not included in the _string.
        checkFirstToken(tokens, TokenType::IDENTIFIER, "c");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "d");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "e");
        checkFirstToken(tokens, TokenType::COMMA, ",");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "f");
        checkFirstToken(tokens, TokenType::DOT_DOT, ".");    // The second dot is eaten by the parser and not included in the _string.
        checkFirstToken(tokens, TokenType::IDENTIFIER, "g");
        checkFirstToken(tokens, TokenType::RIGHT_SQUARE_BRACKET, "]");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("(R1(x))");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

        tokens = Tokenizer::getTokens("R1(x)*(y+21.2)-2.12/R12");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R1");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "x");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        checkFirstToken(tokens, TokenType::MULTIPLY, "*");
        checkFirstToken(tokens, TokenType::LEFT_PARENTHESIS, "(");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "y");
        checkFirstToken(tokens, TokenType::ADD, "+");
        checkFirstToken(tokens, TokenType::FLOATING_NUMBER, "21.2");
        checkFirstToken(tokens, TokenType::RIGHT_PARENTHESIS, ")");
        checkFirstToken(tokens, TokenType::SUBTRACKT, "-");
        checkFirstToken(tokens, TokenType::FLOATING_NUMBER, "2.12");
        checkFirstToken(tokens, TokenType::DIVIDE, "/");
        checkFirstToken(tokens, TokenType::IDENTIFIER, "R12");
        Assert::assertTrue("list is empty", tokens->isEmpty(), __FILE__, __LINE__);

    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void TokenizerTest::setUp() {
        JUnitUtil::setUp();
    }

    //@After
    /*public*/  void TokenizerTest::tearDown() {
        JUnitUtil::tearDown();
    }
Logger* TokenizerTest::log = LoggerFactory::getLogger("TokenizerTest");
