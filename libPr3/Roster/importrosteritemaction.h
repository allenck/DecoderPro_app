#ifndef IMPORTROSTERITEMACTION_H
#define IMPORTROSTERITEMACTION_H
#include "abstractrosteritemaction.h"
#include "libPr3_global.h"

class QDomElement;
class LIBPR3SHARED_EXPORT ImportRosterItemAction : public AbstractRosterItemAction
{
 Q_OBJECT
public:
Q_INVOKABLE  explicit ImportRosterItemAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE ImportRosterItemAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE ImportRosterItemAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE ImportRosterItemAction(QString pName, QWidget* pWho) ;
 ~ImportRosterItemAction() {}
 ImportRosterItemAction(const ImportRosterItemAction& other) : AbstractRosterItemAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
private:
 bool selectTo();
 bool doTransfer();
 Logger* log;

protected:
 /*protected*/ bool selectFrom();
 /*protected*/ bool loadEntryFromElement(QDomElement lroot);

};
Q_DECLARE_METATYPE(ImportRosterItemAction)
#endif // IMPORTROSTERITEMACTION_H
