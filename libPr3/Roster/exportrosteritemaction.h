#ifndef EXPORTROSTERITEMACTION_H
#define EXPORTROSTERITEMACTION_H
#include "abstractrosteritemaction.h"

class ExportRosterItemAction : public AbstractRosterItemAction
{
 Q_OBJECT
public:
 //explicit ExportRosterItemAction(QObject *parent = 0);
 /*public*/ ExportRosterItemAction(QString pName, QWidget* pWho);

signals:

public slots:
private:
 bool selectTo();
 bool doTransfer();
 void updateRoster();
 Logger* log;

protected:
 /*protected*/ bool selectFrom();

};

#endif // EXPORTROSTERITEMACTION_H
