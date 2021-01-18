#ifndef SLOTMONPANE_H
#define SLOTMONPANE_H
#include "lnpanel.h"
#include "logger.h"
#include "libPr3_global.h"

class QCheckBox;
class QPushButton;
class SlotMonDataModel;
class JTable;
class LIBPR3SHARED_EXPORT SlotMonPane : public LnPanel
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit SlotMonPane(QWidget *parent = 0);
 ~SlotMonPane() {}
 SlotMonPane(const SlotMonPane&) : LnPanel() {}
 /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ void dispose();

signals:

public slots:
 void On_showAllCheckBox_clicked();
 void On_showSystemCheckBox_clicked();
private:
 /**
  * Controls whether not-in-use slots are shown
  */
 QCheckBox* showUnusedCheckBox;// = new QCheckBox();
 /**
  * Controls whether system slots (120-127) are shown
  */
 QCheckBox* showSystemCheckBox;// = new QCheckBox();

 QPushButton* estopAllButton;// = new QPushButton(LocoNetBundle.bundle().getString("ButtonSlotMonEStopAll"));

 //Added by Jeffrey Machacek 2013
 QPushButton* clearAllButton;// = new QPushButton(LocoNetBundle.bundle().getString("ButtonSlotMonClearAll"));
 SlotMonDataModel* slotModel;
 JTable* slotTable;
 //JScrollPane slotScroll;
 Logger* log;
 // /*private*/ void filter();

};
Q_DECLARE_METATYPE(SlotMonPane)
#endif // SLOTMONPANE_H
