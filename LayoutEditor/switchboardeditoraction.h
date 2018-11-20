#ifndef SWITCHBOARDEDITORACTION_H
#define SWITCHBOARDEDITORACTION_H
#include "abstractaction.h"

class SwitchboardEditorAction : public AbstractAction
{
public:
 SwitchboardEditorAction(QString s, QObject* parent);
 /*public*/ SwitchboardEditorAction(QObject* parent);

public slots:
 //@Override
 /*public*/ void actionPerformed(ActionEvent* /*e*/ = nullptr);

};

#endif // SWITCHBOARDEDITORACTION_H
