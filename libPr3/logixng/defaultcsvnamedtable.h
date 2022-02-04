#ifndef DEFAULTCSVNAMEDTABLE_H
#define DEFAULTCSVNAMEDTABLE_H
#include "abstractnamedtable.h"
#include <QVariant>
#include <QVector>

class DefaultCsvNamedTable : public AbstractNamedTable
{
  Q_OBJECT
 public:
  /*public*/  DefaultCsvNamedTable(
          /*@Nonnull*/  QString sys, /*@CheckForNull*/ QString user,
          /*@CheckForNull*/ QString fileName,
          /*@Nonnull*/  QVector<QVector<QVariant> > data,
          QObject* parent = nullptr);
  /*public*/  QString getFileName();
  /*public*/  void setFileName(QString fileName);
  QObject* self() override{return (QObject*)this;}
 private:
  /*private*/ QString _fileName;

};

#endif // DEFAULTCSVNAMEDTABLE_H
