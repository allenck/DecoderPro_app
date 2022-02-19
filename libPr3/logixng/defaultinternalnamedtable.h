#ifndef DEFAULTINTERNALNAMEDTABLE_H
#define DEFAULTINTERNALNAMEDTABLE_H

#include "abstractnamedtable.h"

class DefaultInternalNamedTable : public AbstractNamedTable
{
 public:
  /*public*/  DefaultInternalNamedTable(
          /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
          int numRows, int numColumns, QObject* parent = nullptr)
          /*throws BadUserNameException, BadSystemNameException*/;
  /*public*/  DefaultInternalNamedTable(
          /*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName,
          /*@Nonnull*/ QVector<QVector<QVariant> >data, QObject* parent = nullptr)
          /*throws BadUserNameException, BadSystemNameException*/;
  QObject* self() override{return (QObject*)this;}
};

#endif // DEFAULTINTERNALNAMEDTABLE_H
