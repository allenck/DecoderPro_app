#ifndef DEFAULTLOGIXNGMANAGERTESTACTION_H
#define DEFAULTLOGIXNGMANAGERTESTACTION_H

#include <abstractaction.h>

class Logger;
class DefaultLogixNGManagerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    explicit DefaultLogixNGManagerTestAction(QObject *parent = nullptr);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // DEFAULTLOGIXNGMANAGERTESTACTION_H
