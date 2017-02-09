#ifndef INSTALLDECODERURLACTION_H
#define INSTALLDECODERURLACTION_H

#include "jmriabstractaction.h"
#include "appslib_global.h"

class File;
class APPSLIBSHARED_EXPORT InstallDecoderURLAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit InstallDecoderURLAction(QObject *parent = 0);
 Q_INVOKABLE /*public*/ InstallDecoderURLAction(QString s, WindowInterface* wi);
 Q_INVOKABLE /*public*/ InstallDecoderURLAction(QString s, QIcon i, WindowInterface* wi);
 Q_INVOKABLE /*public*/ InstallDecoderURLAction(QString s, QObject* parent =0);
 Q_INVOKABLE /*public*/ InstallDecoderURLAction(QString s, QWidget* who);
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 QWidget* _who;
 Logger* log;
 void common();
 void copyAndInstall(QUrl* from, QWidget* who);
 bool copyfile(QUrl* from, File* toFile, QWidget* who);
 bool checkFile(QUrl* url, QWidget* who);
 QUrl* pickURL(QWidget* who);

};

#endif // INSTALLDECODERURLACTION_H
