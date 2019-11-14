#ifndef MATRIXSIGNALMASTADDPANETESTACTION_H
#define MATRIXSIGNALMASTADDPANETESTACTION_H
#include "abstractaction.h"

class Logger;
class MatrixSignalMastAddPaneTestAction : public AbstractAction
{
 Q_OBJECT
public:
 MatrixSignalMastAddPaneTestAction(QObject* parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;

};

#endif // MATRIXSIGNALMASTADDPANETESTACTION_H
