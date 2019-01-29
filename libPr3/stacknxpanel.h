#ifndef STACKNXPANEL_H
#define STACKNXPANEL_H
#include "jpanel.h"
#include <QMap>

class JList;
class EntryExitPairs;
class DefaultListModel;
class DestinationPoints;
class StackNXPanel : public JPanel
{
 Q_OBJECT
public:
 StackNXPanel(QWidget *parent = nullptr);
 /*public*/ void updateGUI();

public slots:
 /*public*/ void onCancel();

private:
 QMap<QString, DestinationPoints*> listToDest;// = new Hashtable<String, DestinationPoints>();
 /*transient*/ EntryExitPairs* manager;// = jmri.InstanceManager.getDefault(jmri.jmrit.entryexit.EntryExitPairs.class);

 /*private*/ JPanel* entryExitPanel;

 /*private*/ DefaultListModel/*<QString>*/* listModel;
 /*private*/ JList/*<QString>*/* list;// = new JList<String>();
 //JScrollPane listScrollPane = new JScrollPane(list);
 /*private*/ void initGUI();

};

#endif // STACKNXPANEL_H
