#ifndef ABSTRACTNAMEDTABLE_H
#define ABSTRACTNAMEDTABLE_H

#include "namedtable.h"
#include "abstractnamedbean.h"
#include <QVector>

class AnonymousTable;
class AbstractNamedTable : /*public AbstractNamedBean,*/ public NamedTable
{
  Q_OBJECT
  //Q_INTERFACES(NamedTable)
 public:
  explicit AbstractNamedTable(
    /*@Nonnull*/  QString sys, /*@CheckForNull*/ QString user,
    int numRows, int numColumns, QObject *parent = nullptr);
  /*private*/ int _state = NamedBean::UNKNOWN;
  /*public*/  AbstractNamedTable(/*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
          /*@Nonnull*/  QVector<QVector<QVariant> > data, QObject *parent = nullptr)
          /*throws BadUserNameException, BadSystemNameException*/;
  /*public*/  AbstractNamedTable(
          /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
          /*@Nonnull*/  QString fileName,
          /*@Nonnull*/  QVector<QVector<QVariant> > data, QObject *parent)
          /*throws BadUserNameException, BadSystemNameException*/;
  /*public*/  static NamedTable* loadTableFromCSV_Text(
          /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
          /*@Nonnull*/  QString text,
          bool registerInManager)
          /*throws BadUserNameException, BadSystemNameException*/;
  /*public*/  static NamedTable* loadTableFromCSV_File(
          /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
          /*@Nonnull*/  QString fileName, bool registerInManager)
          /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/;
  /*public*/  static NamedTable* loadTableFromCSV_File(
    /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
    /*@Nonnull*/  File* file, bool registerInManager)
    /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/;
  /*public*/  void storeTableAsCSV(/*@Nonnull*/  File* file)
          /*throws FileNotFoundException */override;
  /*public*/  void storeTableAsCSV(
          /*@Nonnull*/  File* file,
          /*@CheckForNull*/ QString systemName, /*@CheckForNull*/ QString userName)
          /*throws FileNotFoundException*/override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString getBeanType()override;
  /*public*/  QVariant getCell(int row, int column)override;
  /*public*/  void setCell(QVariant value, int row, int column)override;
  /*public*/  int numRows()override;
  /*public*/  int numColumns()override;
  /*public*/  int getRowNumber(QString rowName)override;
  /*public*/  int getColumnNumber(QString columnName)override;

 private:
  /*private*/ static NamedTable* loadFromCSV(
    /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
    /*@CheckForNull*/ QString fileName,
    /*@Nonnull*/  QList<QString> lines,
    bool registerInManager)
    /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException*/;

 protected:
  /*protected*/ /*final*/ AnonymousTable* _internalTable;

};

#endif // ABSTRACTNAMEDTABLE_H
