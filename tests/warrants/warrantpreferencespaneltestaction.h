#ifndef WARRANTPREFERENCESPANELTESTACTION_H
#define WARRANTPREFERENCESPANELTESTACTION_H

#include "abstractaction.h"

class Logger;
class WarrantPreferencesPanelTestAction : public AbstractAction
{
 Q_OBJECT
public:
 WarrantPreferencesPanelTestAction(QObject *parent);

public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // WARRANTPREFERENCESPANELTESTACTION_H
