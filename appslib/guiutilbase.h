#ifndef GUIUTILBASE_H
#define GUIUTILBASE_H

#include <QObject>
#include <QtXml>
#include "xmlfile.h"
#include "abstractaction.h"
#include "appslib_global.h"


class AbstractAction;
class JmriAbstractAction;
class QMetaMethod;
class JActionEvent;
class Action;
class WindowInterface;
class APPSLIBSHARED_EXPORT GuiUtilBase : public QObject
{
 Q_OBJECT
public:
 explicit GuiUtilBase(QObject *parent = 0);

signals:

public slots:
private:
 static Action* createEmptyMenuItem(QIcon* icon, QString name);
 static Action* actionFromNode(QDomElement child, WindowInterface* wi, QObject* context);
 static Action* createActionInCallingWindow(QObject* obj, /*final*/ QStringList args, QString name, QIcon* icon);
 static void setParameters(JmriAbstractAction* act, QHash<QString, QString> parameters);
 static /*protected*/  QDomElement rootFromName(QString name);
 static QString getLocaleAttribute(QDomElement element, QString attrName, QString locale = "en");

friend class JMenuUtil;
friend class JToolBarUtil;

};
/*static*/ class CallingAbstractAction : public  AbstractAction
{
 Q_OBJECT
    /**
     *
     */
    //private static final long serialVersionUID = -6063626025483350164L;
 QMetaMethod method;
 QObject* obj;
 QStringList args;

public:
 /*public*/  CallingAbstractAction(QString name, QIcon* icon, QObject* parent) ;
 /*public*/  void setMethod(QMetaMethod method) ;
 /*public*/  void setObject(QObject* obj);
 /*public*/ void setArgs(QStringList args);
public slots:
 /*public*/  void actionPerformed(ActionEvent* e = 0) ;
};
class GUAbstractAction : public AbstractAction
{
 Q_OBJECT
public slots:
 /*public*/  void actionPerformed(ActionEvent* /*e*/) ;
public:
 GUAbstractAction(QString name, QIcon* icon = NULL);
 /*public*/  QString toString();

};

#endif // GUIUTILBASE_H
