#ifndef DCCSIGNALMAST_H
#define DCCSIGNALMAST_H
#include "abstractsignalmast.h"
#include "libPr3_global.h"

class CommandStation;
class LIBPR3SHARED_EXPORT DccSignalMast : public AbstractSignalMast
{
 Q_OBJECT
public:
 //explicit DccSignalMast(QObject *parent = 0);
 /*public*/ DccSignalMast(QString sys, QString user, QObject *parent = 0);
 /*public*/ DccSignalMast(QString sys,QObject *parent = 0);
 /*public*/ DccSignalMast(QString sys, QString user, QString mastSubType,QObject *parent = 0);
   /*public*/ void setOutputForAppearance(QString appearance, int number);
   /*public*/ int getOutputForAppearance(QString appearance);
   /*public*/ void setAspect(QString aspect);
   /*public*/ void setLit(bool newLit);
   /*public*/ void setUnlitId(int i);
   /*public*/ int getUnlitId() ;
   /*public*/ int getDccSignalMastAddress() ;
   /*public*/ CommandStation* getCommandStation();
   /*public*/ static QString isDCCAddressUsed(int addr);
   /*public*/ QString className();

signals:

public slots:
private:
 void common();
 Logger* log;
 int unLitId;// = 31;

protected:
 /*protected*/ QString mastType;// = "F$dsm";
 /*protected*/ void configureFromName(QString systemName);
 /*protected*/ QMap<QString, int> appearanceToOutput;// = new QMap<QString, Integer>();
 /*
  0.  "Stop"
  1.  "Take Siding"
  2.  "Stop-Orders"
  3.  "Stop-Proceed"
  4.  "Restricting"
  5.  "Permissive"
  6.  "Slow-Approach"
  7.  "Slow"
  8.  "Slow-Medium"
  9.  "Slow-Limited"
  10. "Slow-Clear"
  11. "Medium-Approach"
  12. "Medium-Slow"
  13. "Medium"
  14. "Medium-Ltd"
  15. "Medium-Clr"
  16. "Limited-Approach"
  17. "Limited-Slow"
  18. "Limited-Med"
  19. "Limited"
  20. "Limited-Clear"
  21. "Approach"
  22. "Advance-Appr"
  23. "Appr-Slow"
  24. "Adv-Appr-Slow"
  25. "Appr-Medium"
  26. "Adv-Appr-Med"
  27. "Appr-Limited"
  28. "Adv-Appr-Ltd"
  29. "Clear"
  30. "Cab-Speed"
  31. "Dark" */
 /*protected*/ int packetRepeatCount;// = 3;
 /*protected*/ CommandStation* c;

 /*protected*/ int dccSignalDecoderAddress;
};

#endif // DCCSIGNALMAST_H
