#ifndef INSTALLDECODERFILEACTION_H
#define INSTALLDECODERFILEACTION_H
#include "libPr3_global.h"

#include "installdecoderurlaction.h"

class JFileChooser;
class LIBPR3SHARED_EXPORT InstallDecoderFileAction : public InstallDecoderURLAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit InstallDecoderFileAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE InstallDecoderFileAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE InstallDecoderFileAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE InstallDecoderFileAction(QString s, QObject *parent);
 /*public*/ Q_INVOKABLE InstallDecoderFileAction(QString s, QWidget* who);
 ~InstallDecoderFileAction() {}
 InstallDecoderFileAction(const InstallDecoderFileAction&) : InstallDecoderURLAction() {}
 /*public*/ JmriPanel* makePanel();

signals:
private:
 void common();
 Logger* log;
 JFileChooser* fci;
 QUrl* pickURL(QWidget* who);

public slots:

};
Q_DECLARE_METATYPE(InstallDecoderFileAction)
#endif // INSTALLDECODERFILEACTION_H
