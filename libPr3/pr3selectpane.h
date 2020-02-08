#ifndef PR3SELECTPANE_H
#define PR3SELECTPANE_H
#include "lnpanel.h"
#include "logger.h"
#include "libPr3_global.h"
#include "loconetlistener.h"

class LocoNetMessage;
class QLabel;
class LIBPR3SHARED_EXPORT Pr3SelectPane : public LnPanel, public LocoNetListener
{
 Q_OBJECT
 Q_INTERFACES(LocoNetListener)
public:
 Q_INVOKABLE explicit Pr3SelectPane(QWidget *parent = 0);
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
Q_DECLARE_METATYPE(Pr3SelectPane)
#endif // PR3SELECTPANE_H
