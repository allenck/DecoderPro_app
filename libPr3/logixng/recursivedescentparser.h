#ifndef RECURSIVEDESCENTPARSER_H
#define RECURSIVEDESCENTPARSER_H

#include <QObject>
#include "token.h"
#include "variable.h"
#include "tokentype.h"
#include "expressionnode.h"

class State;
class RecursiveDescentParser : public QObject
{
  Q_OBJECT
 public:
  explicit RecursiveDescentParser(QMap<QString, Variable*> variables, QObject *parent = nullptr);
  /*public*/ ExpressionNode *parseExpression(QString expression) /*throws ParserException */;

 signals:

 private:
  /*private*/ QList<Token*> _tokens;
  /*private*/ /*final*/ QMap<QString, Variable*> _variables;
  /*private*/ /*static*/ class State
  {
    /*private*/ /*final*/ int _tokenIndex;
    /*private*/ /*final*/ Token* _token;
    /*private*/ /*final*/ int _lastTokenPos;
    /*private*/ /*final*/ Token* _lastToken;

   public:
    /*public*/ State(int tokenIndex, Token* token, int lastTokenPos, Token* lastToken) {
        _tokenIndex = tokenIndex;
        _token = token;
        _lastTokenPos = lastTokenPos;
        _lastToken = lastToken;
    }
    friend class RecursiveDescentParser;
  };
  /*private*/ State* next(State* state);
  /*private*/ State* accept(TokenType::TTYPE tokenType, State* state) /*throws ParserException*/ ;
  /*private*/ State* expect(TokenType::TTYPE tokenType, State* state) /*throws ParserException*/ ;


  /*private*/ /*static*/ class ExpressionNodeAndState {
      /*private*/ /*final*/ ExpressionNode* _exprNode;
      /*private*/ /*final*/ State* _state;

      /*private*/ ExpressionNodeAndState(ExpressionNode* exprNode, State* state) {
          _exprNode = exprNode;
          _state = state;
      }
    friend class RecursiveDescentParser;
  };

  /*private*/ /*interface*/ class Rule {
   public:
    /*public*/ virtual ExpressionNodeAndState* parse(State* state) /*throws ParserException*/ {return nullptr;}
    /*public*/ virtual ExpressionNodeAndState* parse2(State* state, QString txt) /*throws ParserException*/ {return nullptr;}

  };
  // The rules below are numbered from the list on this page:
  // https://introcs.cs.princeton.edu/java/11precedence/

  /*private*/ /*final*/ Rule* rule1 = new Rule1(this);
  /*private*/ /*final*/ Rule* rule2 = new Rule2(this);
  /*private*/ /*final*/ Rule* rule3 = new Rule3(this);
  /*private*/ /*final*/ Rule* rule4 = new Rule4(this);
  /*private*/ /*final*/ Rule* rule5 = new Rule5(this);
  /*private*/ /*final*/ Rule* rule6 = new Rule6(this);
  /*private*/ /*final*/ Rule* rule7 = new Rule7(this);
  /*private*/ /*final*/ Rule* rule8 = new Rule8(this);
  /*private*/ /*final*/ Rule* rule9 = new Rule9(this);
  /*private*/ /*final*/ Rule* rule10 = new Rule10(this);
  /*private*/ /*final*/ Rule* rule11 = new Rule11(this);
  /*private*/ /*final*/ Rule* rule12 = new Rule12(this);
  /*private*/ /*final*/ Rule* rule14 = new Rule14(this);
  /*private*/ /*final*/ Rule* rule16 = new Rule16(this);
  /*private*/ /*final*/ Rule* rule20 = new Rule20(this);
  /*private*/ /*final*/ Rule* rule21 = new Rule21(this);

  /*private*/ /*final*/ Rule* firstRule = rule1;
  /*private*/ class Rule1 : public Rule {
    RecursiveDescentParser* rdp;
   public:
    Rule1(RecursiveDescentParser* rdp){this->rdp = rdp;}
      //@Override
      /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule2 : public Rule {
      RecursiveDescentParser* rdp;
     public:
      Rule2(RecursiveDescentParser* rdp){this->rdp = rdp;}
    //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule3 : public Rule {
      RecursiveDescentParser* rdp;
     public:
      Rule3(RecursiveDescentParser* rdp){this->rdp = rdp;}
      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule4 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule4(RecursiveDescentParser* rdp){this->rdp = rdp;}
      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule5 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule5(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule6 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule6(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
      /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule7 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule7(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
      /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule8 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule8(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule9 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule9(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule10 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule10(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule11 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule11(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule12 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule12(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule13 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule13(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule14 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule14(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule16 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule16(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule20 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule20(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse(State* state) /*throws ParserException*/;
  };
  /*private*/ class Rule21 : public Rule {

      RecursiveDescentParser* rdp;
     public:
      Rule21(RecursiveDescentParser* rdp){this->rdp = rdp;}

      //@Override
    /*public*/ ExpressionNodeAndState* parse2(State* state, QString identifier) /*throws ParserException*/;

  };
  friend class Rule1;
  friend class Rule2;
  friend class Rule3;
  friend class Rule4;
  friend class Rule5;
  friend class Rule6;
  friend class Rule7;
  friend class Rule8;
  friend class Rule9;
  friend class Rule10;
  friend class Rule11;
  friend class Rule12;
  friend class Rule13;
  friend class Rule14;
  friend class Rule16;
  friend class Rule20;
  friend class Rule21;

};
//Q_DECLARE_INTERFACE(RecursiveDescentParser::ule, "Rule")

#endif // RECURSIVEDESCENTPARSER_H
