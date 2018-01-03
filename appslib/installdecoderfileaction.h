#ifndef INSTALLDECODERFILEACTION_H
#define INSTALLDECODERFILEACTION_H
#include "installdecoderurlaction.h"
#include "appslib_global.h"

class Logger;
class QUrl;
class WindowInterface;
class JFileChooser;
class APPSLIBSHARED_EXPORT InstallDecoderFileAction : public InstallDecoderURLAction
{
 Q_OBJECT
public:
 explicit InstallDecoderFileAction(QObject *parent = 0);
    InstallDecoderFileAction(const InstallDecoderFileAction&) : InstallDecoderURLAction() {}
    ~InstallDecoderFileAction() {}
 Q_INVOKABLE /*public*/ InstallDecoderFileAction(QString s, WindowInterface* wi);
 Q_INVOKABLE /*public*/ InstallDecoderFileAction(QString s, QIcon i, WindowInterface* wi);
 Q_INVOKABLE /*public*/ InstallDecoderFileAction(QString s, QWidget* who);
 Q_INVOKABLE /*public*/ JmriPanel* makePanel();
 Q_INVOKABLE /*public*/ InstallDecoderFileAction(QString s,QObject *parent);

signals:

public slots:
private:
 JFileChooser* fci;
 void common();
 QUrl* pickURL(QWidget* who);
 Logger* log;

};

#endif // INSTALLDECODERFILEACTION_H
