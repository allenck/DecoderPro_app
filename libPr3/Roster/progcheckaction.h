#ifndef PROGCHECKACTION_H
#define PROGCHECKACTION_H
#include "abstractaction.h"
#include <QtXml>
#include "exceptions.h"
#include <QRegularExpression>

class Pattern;
class File;
class Logger;
class JFileChooser;
class ProgCheckAction : public AbstractAction
{
 Q_OBJECT
public:
 ProgCheckAction();
 /*public*/ ProgCheckAction(QString s, QWidget* who);

public slots:
 /*public*/ void actionPerformed();

private:
 JFileChooser* fci;
 QWidget* _who;
 Logger* log;
 static /*protected*/ void expandElement(QDomElement el, QList<QDomElement>* list);
 void warnMissingNames(File* file);
 static QString checkMissingNames(File* file);
 void warnIncompleteComprehensive(File* file);
 static QString checkIncompleteComprehensive(File* file);
 static bool functionMapName(QString name);
 static QDomElement readFile(File* file) throw (JDOMException, IOException);
 static /*final*/ QString numericRegex;// = "^F(\\d++) controls output (\\d++)$";
 //static Pattern* numericPattern;
 static QRegularExpression* numericPattern;
 static /*final*/ QString ffRegex;// = "^FL\\(f\\) controls output (\\d++)$";
 //static Pattern* ffPattern;
 static QRegularExpression* ffPattern;
 static /*final*/ QString frRegex;// = "^FL\\(r\\) controls output (\\d++)$";
 //static Pattern* frPattern;
 static QRegularExpression* frPattern;

};

#endif // PROGCHECKACTION_H
