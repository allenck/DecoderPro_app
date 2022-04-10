#ifndef ANTECEDENT_H
#define ANTECEDENT_H

#include "abstractdigitalexpression.h"
#include "../../JavaQt/bitset.h"
#include "femaledigitalexpressionsocket.h"
#include "femalesocketlistener.h"

class DataPair;
class ExpressionEntry;
class Antecedent : public AbstractDigitalExpression, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  explicit Antecedent(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, QObject *parent = nullptr);
  /* This class is public  since ExpressionAntecedentXml needs to access it. */
  /*public*/  /*static*/ class ExpressionEntry {
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleDigitalExpressionSocket* _socket;
      public:
      /*public*/  ExpressionEntry(FemaleDigitalExpressionSocket* socket, QString socketSystemName) {
          _socketSystemName = socketSystemName;
          _socket = socket;
      }
      private:
      /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket* socket) {
          this->_socket = socket;
      }
    friend class Antecedent;
  };
  /*public*/  Antecedent(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
          QList<QMap<QString, QString>> expressionSystemNames, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames,QMap<QString, QString>* userNames) /*throws JmriException */override;
  /*public*/  QString getExpressionSystemName(int index);
  /*public*/  Category* getCategory()override;
  /*public*/  bool evaluate()/* throws JmriException */override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  void setChildCount(int count);
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  QString getAntecedent();
  /*public*/  /*final*/ void setAntecedent(QString antecedent) /*throws JmriException */;
  /*public*/  bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  void setup()override;
  /*public*/  QString validateAntecedent(QString ant, QList<ExpressionEntry*> expressionEntryList) /*throws JmriException */;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}


 private:
  static Logger* log;
  /*private*/ QString _antecedent = "";
  /*private*/ /*final*/ QList<ExpressionEntry*> _expressionEntries = QList<ExpressionEntry*>();
  /*private*/ bool disableCheckForUnconnectedSocket = false;
  /*static*/ class DataPair {
   public:
      bool result = false;
      int indexCount = 0;         // index reached when parsing completed
      BitSet* argsUsed = nullptr;     // error detection for missing arguments
  };
  /**
   * Parses and computes one parenthesis level of a boolean statement.
   * <p>
   * Recursively calls inner parentheses levels. Note that all logic operators
   * are detected by the parsing, therefore the internal negation of a
   * variable is washed.
   *
   * @param s            The expression to be parsed
   * @param expressionEntryList ExpressionEntries for R1, R2, etc
   * @return a data pair consisting of the truth value of the level a count of
   *         the indices consumed to parse the level and a bitmap of the
   *         variable indices used.
   * @throws jmri.JmriException if unable to compute the logic
   */
  DataPair* parseCalculate(QString s, QList<ExpressionEntry*> expressionEntryList)
          /*throws JmriException*/ ;
  /*private*/ void setExpressionSystemNames(QList<QMap<QString, QString>> systemNames);
  /*private*/ void setNumSockets(int num) ;
  /*private*/ void checkFreeSocket();
  /*private*/ void insertNewSocket(int index);
  /*private*/ void removeSocket(int index);
  /*private*/ void moveSocketDown(int index);

};

#endif // ANTECEDENT_H
