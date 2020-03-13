#ifndef LAYOUTEDITORTOOLSTESTACTION_H
#define LAYOUTEDITORTOOLSTESTACTION_H
#include "abstractaction.h"

class Logger;
class LayoutEditorToolsTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LayoutEditorToolsTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // LAYOUTEDITORTOOLSTESTACTION_H
