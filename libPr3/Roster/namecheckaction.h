#ifndef NAMECHECKACTION_H
#define NAMECHECKACTION_H
#include "abstractaction.h"
#include "exceptions.h"
#include <QtXml>

class Logger;
class File;
class JFileChooser;
class NameCheckAction : public AbstractAction
{
 Q_OBJECT
public:
 //NameCheckAction();
 /*public*/ NameCheckAction(QString s, QWidget* who);

 public slots:
 /*public*/ void actionPerformed();
private:
 JFileChooser* fci;
 QDomElement readFile(File* file) throw(JDOMException, IOException);
 Logger* log;
 QWidget* _who;

};

#endif // NAMECHECKACTION_H
