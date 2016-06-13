#ifndef CLOCKMONPANE_H
#define CLOCKMONPANE_H
#include "lnpanel.h"
#include "logger.h"
#include "libPr3_global.h"

class LocoNetSlot;
class JTextField;
class QPushButton;
class LIBPR3SHARED_EXPORT ClockMonPane : public LnPanel
{
 Q_OBJECT
public:
 explicit ClockMonPane(QWidget *parent = 0);
 ~ClockMonPane() {}
 ClockMonPane(const ClockMonPane&) : LnPanel() {}
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();

 /*public*/ void initComponents(/*final*/ LocoNetSystemConnectionMemo* memo);
 /*public*/ void dispose();
signals:

public slots:
void On_readButton_clicked();
/*public*/ void notifyChangedSlot(LocoNetSlot* s);

private:
 JTextField* days;// = new JTextField("00");
 JTextField* hours;// = new JTextField("00");
 JTextField* minutes;// = new JTextField("00");
 JTextField* frac_mins;// = new JTextField("00");

 JTextField* rate;// = new JTextField(4);

 QPushButton* readButton;// = new JButton("Read");
 Logger* log;
};

#endif // CLOCKMONPANE_H
