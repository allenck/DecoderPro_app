#ifndef COLORCHOOSERPANELTESTACTION_H
#define COLORCHOOSERPANELTESTACTION_H
#include "abstractaction.h"

class Logger;
class ColorChooserPanelTestAction : public AbstractAction
{
 Q_OBJECT
public:
 ColorChooserPanelTestAction(QObject* parent);
public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // COLORCHOOSERPANELTESTACTION_H
