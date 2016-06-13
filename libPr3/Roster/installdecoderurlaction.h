#ifndef INSTALLDECODERURLACTION_H
#define INSTALLDECODERURLACTION_H
#include "jmriabstractaction.h"
#include "libPr3_global.h"

class QDomElement;
class File;
class QUrl;
class JPanel;
class LIBPR3SHARED_EXPORT InstallDecoderURLAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit InstallDecoderURLAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE InstallDecoderURLAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE InstallDecoderURLAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE InstallDecoderURLAction(QString s, QWidget* who);
 ~InstallDecoderURLAction() {}
 InstallDecoderURLAction(const InstallDecoderURLAction&) :JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
 QWidget* _who;
 QUrl* pickURL(QWidget* who);
 void copyAndInstall(QUrl* from, QWidget* who);
 Logger* log;
 bool copyfile(QUrl* from, File* toFile, QWidget* who);
 bool checkFile(QUrl* url, QWidget* who);
 QDomElement readFile(QUrl* url) /*throw (JDOMException, IOException)*/;

};
Q_DECLARE_METATYPE(InstallDecoderURLAction)
#endif // INSTALLDECODERURLACTION_H
