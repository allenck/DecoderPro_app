#ifndef XMLFILEVALIDATEACTION_H
#define XMLFILEVALIDATEACTION_H
#include "jmriabstractaction.h"

class File;
class JFileChooser;
class XmlFileValidateAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 XmlFileValidateAction(QObject* parent);
 /*public*/ XmlFileValidateAction(QString s, QWidget* who);
 /*public*/ XmlFileValidateAction(QString s, WindowInterface* wi);
 /*public*/ JmriPanel* makePanel();
// static /*public*/ void main(QStringList args);

public slots:
 /*public*/ void actionPerformed();

private:
 JFileChooser* fci;
 QWidget* _who;
 void common();
 void readFile(File* file) throw (JDOMException, IOException);
 Logger* log;

protected:
 /*protected*/ void processFile(File* file);
 /*protected*/ void showOkResults(QWidget* who, QString  text);
 /*protected*/ void showFailResults(QWidget* who, QString  text);

};

#endif // XMLFILEVALIDATEACTION_H
