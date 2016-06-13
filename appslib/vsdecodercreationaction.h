#ifndef VSDDECODERCREATIONACTION_H
#define VSDDECODERCREATIONACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

class Logger;
class APPSLIBSHARED_EXPORT VSDecoderCreationAction : public AbstractAction
{
public:
 VSDecoderCreationAction(QObject* parent=0);
 /*public*/ VSDecoderCreationAction(QString s, bool ng, QObject* parent=0);

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);


private:
 bool _useNewGUI;// = false;
 void common();
 Logger* log;
};

#endif // VSDDECODERCREATIONACTION_H
