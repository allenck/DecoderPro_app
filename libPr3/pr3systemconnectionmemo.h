#ifndef PR3SYSTEMCONNECTIONMEMO_H
#define PR3SYSTEMCONNECTIONMEMO_H

#include "loconetsystemconnectionmemo.h"

class PR3SystemConnectionMemo : public LocoNetSystemConnectionMemo
{
    Q_OBJECT
public:
//    PR3SystemConnectionMemo(LnTrafficController lt,     SlotManager sm);
 explicit PR3SystemConnectionMemo(QObject *parent = 0);
 void configureManagersPR2();
 /**
   * Configure the subset of LocoNet managers valid for the PR3 in MS100 mode.
   */
 void configureManagersMS100();
 /*public*/ void dispose();

signals:
    
public slots:
private:
 int PR3MODE;
 int MS100MODE;

 int mode;
 Logger* log;
};

#endif // PR3SYSTEMCONNECTIONMEMO_H
