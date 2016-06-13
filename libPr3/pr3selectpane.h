#ifndef PR3SELECTPANE_H
#define PR3SELECTPANE_H
#include "lnpanel.h"
#include "logger.h"
#include "libPr3_global.h"

class LocoNetMessage;
class QLabel;
class LIBPR3SHARED_EXPORT Pr3SelectPane : public LnPanel
{
 Q_OBJECT
public:
 explicit Pr3SelectPane(QWidget *parent = 0);
 ~Pr3SelectPane() {}
 Pr3SelectPane(const Pr3SelectPane&) : LnPanel() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);

signals:

public slots:
 void selectPR2mode();
 void selectMS100mode();
 /*public*/ void message(LocoNetMessage* msg);

private:
 Logger* log;
 QLabel* status;// = new JLabel(res.getString("StatusUnknown"));

};

#endif // PR3SELECTPANE_H
