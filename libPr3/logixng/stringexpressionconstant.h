#ifndef STRINGEXPRESSIONCONSTANT_H
#define STRINGEXPRESSIONCONSTANT_H
#include "abstractstringexpression.h"


class StringExpressionConstant : public AbstractStringExpression
{
  Q_OBJECT
 public:
  StringExpressionConstant(QString sys, QString user, QObject* parent= nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/  Category* getCategory() override;
  /*public*/  void setValue(QString value);
  /*public*/  QString getValue();
  /*public*/  QString evaluate()override;
  /*public*/  FemaleSocket* getChild(int index)
          /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ QString _value = "";
};

#endif // STRINGEXPRESSIONCONSTANT_H
