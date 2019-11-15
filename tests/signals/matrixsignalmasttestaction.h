#ifndef MATRIXSIGNALMASTTESTACTION_H
#define MATRIXSIGNALMASTTESTACTION_H
#include "abstractaction.h"

class Logger;
class MatrixSignalMastTestAction : public AbstractAction
{
 Q_OBJECT
public:
 MatrixSignalMastTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // MATRIXSIGNALMASTTESTACTION_H
