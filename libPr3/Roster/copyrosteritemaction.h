#ifndef COPYROSTERITEMACTION_H
#define COPYROSTERITEMACTION_H
#include "abstractrosteritemaction.h"
#include "libPr3_global.h"

class WindowInterface;
class LIBPR3SHARED_EXPORT CopyRosterItemAction : public AbstractRosterItemAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CopyRosterItemAction(QObject *parent = 0);
    /*public*/ Q_INVOKABLE CopyRosterItemAction(QString s, WindowInterface* wi);
    /*public*/ Q_INVOKABLE CopyRosterItemAction(QString s, QIcon i, WindowInterface* wi) ;
    /*public*/ Q_INVOKABLE CopyRosterItemAction(QString pName, QWidget* pWho);
 ~CopyRosterItemAction() {}
 CopyRosterItemAction(const CopyRosterItemAction&) : AbstractRosterItemAction() {}

    /*public*/ JmriPanel* makePanel();

signals:

public slots:
private:
    bool selectTo();
    bool doTransfer();
    Logger* log;
protected:
    /*protected*/ bool selectFrom() ;

};
Q_DECLARE_METATYPE(CopyRosterItemAction)
#endif // COPYROSTERITEMACTION_H
