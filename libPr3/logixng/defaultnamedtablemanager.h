#ifndef DEFAULTNAMEDTABLEMANAGER_H
#define DEFAULTNAMEDTABLEMANAGER_H

#include <abstractmanager.h>
#include "decimalformat.h"
#include "namedtablemanager.h"

class File;
class DefaultNamedTableManager : public AbstractManager, public NamedTableManager
{
  Q_OBJECT
  Q_INTERFACES(NamedTableManager)
 public:
  explicit DefaultNamedTableManager(QObject *parent = nullptr) : AbstractManager(parent){}
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter()const override;
  /*public*/  NameValidity validSystemNameFormat(QString systemName)override;
  /*public*/  NamedTable* newCSVTable(QString systemName, QString userName, QString fileName)
          /*throws IllegalArgumentException*/override;
  /*public*/  NamedTable* newInternalTable(QString systemName, QString userName, int numRows, int numColumns)
          /*throws IllegalArgumentException*/override;
  /*public*/  AnonymousTable* newAnonymousTable(int numRows, int numColumns)
          /*throws IllegalArgumentException */override;
  /*public*/  NamedTable* loadTableFromCSVData(
          /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, /*@Nonnull*/ QString text)
          /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException*/override;
  /*public*/  NamedTable* loadTableFromCSV(
          /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
          /*@Nonnull*/ QString fileName)
          /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/override;
  /*public*/  NamedTable* loadTableFromCSV(
          /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
          /*@Nonnull*/ File* file)
          /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException */override;
  /*public*/  NamedTable* getNamedTable(QString name)override;
  /*public*/  NamedTable* getByUserName(QString name) override;
  /*public*/  NamedTable* getBySystemName(QString name)override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteNamedTable(NamedTable* x)override;
  /*public*/  void printTree(PrintWriter* writer, QString indent)override;
  /*public*/  void printTree(QLocale locale, PrintWriter* writer, QString indent)override;
  static /*public*/  DefaultNamedTableManager* instance();
  /*public*/  /*Class<NamedTable>*/QString getNamedBeanClass() const override;
  /*public*/  void fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException*/;
  /*public*/  /*final*/ void deleteBean(/*@Nonnull*/ NamedTable* namedTable, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/;

  QObject* self() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  QObject* mself() override {return (QObject*)this;}

 private:
  DecimalFormat* paddedNumber = new DecimalFormat("0000");
  static /*volatile*/ DefaultNamedTableManager* _instance;// = null;
  static Logger* log;

};


#endif // DEFAULTNAMEDTABLEMANAGER_H
