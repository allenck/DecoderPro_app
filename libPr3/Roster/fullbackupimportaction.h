#ifndef FULLBACKUPIMPORTACTION_H
#define FULLBACKUPIMPORTACTION_H

#include "importrosteritemaction.h"
#include "libPr3_global.h"

class Logger;
class WindowInterface;
class LIBPR3SHARED_EXPORT FullBackupImportAction : public ImportRosterItemAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit FullBackupImportAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE FullBackupImportAction(QString s, WindowInterface* wi) ;
 /*public*/ Q_INVOKABLE FullBackupImportAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE FullBackupImportAction(QString title, QWidget* parent);
~FullBackupImportAction() {}
 FullBackupImportAction(const FullBackupImportAction& other) : ImportRosterItemAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
 QWidget* _parent;
 Logger* log;
 bool selectFrom();

};
Q_DECLARE_METATYPE(FullBackupImportAction)
#endif // FULLBACKUPIMPORTACTION_H
