#ifndef ADDENTRYEXITPAIRACTION_H
#define ADDENTRYEXITPAIRACTION_H
#include "abstractaction.h"
#include "liblayouteditor_global.h"

class LayoutEditor;
class LIBLAYOUTEDITORSHARED_EXPORT AddEntryExitPairAction : public AbstractAction
{
 Q_OBJECT
public:
 //explicit AddEntryExitPairAction(QObject *parent = 0);
 /*public*/ AddEntryExitPairAction(QString s, LayoutEditor* panel, QObject *parent = 0);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent *e = 0);

private:
 LayoutEditor* panel;

};

#endif // ADDENTRYEXITPAIRACTION_H
