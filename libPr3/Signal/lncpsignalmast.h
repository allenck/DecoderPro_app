#ifndef LNCPSIGNALMAST_H
#define LNCPSIGNALMAST_H
#include "dccsignalmast.h"

class LocoNetMessage;
class LnTrafficController;
class LNCPSignalMast : public DccSignalMast
{
 Q_OBJECT
public:
 /*public*/ LNCPSignalMast(QString sys, QString user, QObject* parent = nullptr);
 /*public*/ LNCPSignalMast(QString sys, QObject* parent = nullptr);
 /*public*/ void setAspect(QString aspect);
 /*public*/ void setKnownState(QString aspect) ;
 /*public*/ void dispose();

public slots:
 /*public*/ void message(LocoNetMessage* l);

private:
 void init();
 char dccByteAddr1;
 char dccByteAddr2;
 /*private*/ bool myAddress(char a1, char a2) ;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("LNCPSignalMast");
 LnTrafficController* tc;

};

#endif // LNCPSIGNALMAST_H
