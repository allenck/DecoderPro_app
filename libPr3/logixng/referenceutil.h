#ifndef REFERENCEUTIL_H
#define REFERENCEUTIL_H

#include <QObject>
#include "symboltable.h"

class IntRef;
class ReferenceUtil : public QObject
{
  Q_OBJECT
 public:
  explicit ReferenceUtil(QObject *parent = nullptr);
  static /*public*/  bool isReference(QString value);
  static /*public*/  QString getReference(SymbolTable* symbolTable, QString reference);

 signals:

 protected:
  static /*protected*/ QString unescapeString(QString value, int startIndex, int endIndex);
  static /*protected*/ QString getValue(QString reference, int startIndex, IntRef* endIndex);
  static /*protected*/ QString getReferenceOrValue(SymbolTable* symbolTable, QString reference, int startIndex, IntRef* endIndex);
  static /*protected*/ QString getReference(
          SymbolTable* symbolTable, QString reference, int startIndex, IntRef* endIndex);

};
/**
 * Reference to an integer.
 * This class is cheaper to use than AtomicInteger.
 */
/*protected*/ /*static*/ class IntRef {
 public:
    /*public*/  int v;
};

#endif // REFERENCEUTIL_H
