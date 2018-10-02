#ifndef JYNSTRUMENT_H
#define JYNSTRUMENT_H
#include <QWidget>
#include <QMenu>

class QDomElement;
class Logger;
class Jynstrument : public QWidget
{
 Q_OBJECT
public:
 explicit Jynstrument(QWidget *parent = nullptr);
 /*public*/ QObject* getContext();
 /*public*/ void setContext(QObject* context);
 /*public*/ QString getJythonFile();
 /*public*/ void setJythonFile(QString jythonFile);
 /*public*/ QString getFolder();
 /*public*/ void setFolder(QString jynstrumentFolder);
 /*public*/ QString getClassName();
 /*public*/ void setClassName(QString className);
 /*public*/ void exit();
 /*public*/ bool validateContext();
 /*public*/ virtual /*abstract*/ QString getExpectedContextClassName() {return "";}
 /*public*/ virtual /*abstract*/ void init() {}
 /*public*/ QMenu* getPopUpMenu();
 /*public*/ void setPopUpMenu(QMenu* myPopUpMenu);
 /*public*/ void setXml(QDomElement e);
 /*public*/ QDomElement getXml();

signals:

public slots:

private:
 /*private*/ QObject* mContext;  // Object being extended
 /*private*/ QString jythonFile;  // Name of the Jython file being run
 /*private*/ QString jynstrumentFolder; // Folder where the script seats (to retrieve resources)
 /*private*/ QString className; // name of the JYnstrument class
 /*private*/ QMenu* myPopUpMenu; // a popup menu
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("Jynstrument");

protected:
 virtual /*protected*/ /*abstract*/ void quit() {}

};

#endif // JYNSTRUMENT_H
