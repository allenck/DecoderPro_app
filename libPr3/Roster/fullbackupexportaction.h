#ifndef FULLBACKUPEXPORTACTION_H
#define FULLBACKUPEXPORTACTION_H

#include "jmriabstractaction.h"
#include "libPr3_global.h"

class Logger;
class QuaZip;
class QuaZipFile;
class JmriPanel;
class WindowInterface;
class LIBPR3SHARED_EXPORT FullBackupExportAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit FullBackupExportAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE FullBackupExportAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE FullBackupExportAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE FullBackupExportAction(QString s, QWidget* parent);
~FullBackupExportAction() {}
 FullBackupExportAction(const FullBackupExportAction& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
 /*private*/ QWidget* _parent;
 /*private*/ bool copyFileToStream(QString filename, QString dirname, QuaZipFile* zipper, QString comment);
 QuaZip* zipper;
 Logger* log;
};
Q_DECLARE_METATYPE(FullBackupExportAction)
#endif // FULLBACKUPEXPORTACTION_H
