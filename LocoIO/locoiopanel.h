#ifndef LOCOIOPANEL_H
#define LOCOIOPANEL_H
#include "lnpanel.h"
#include "locoio_global.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class LnTrafficController;
class LocoIOTableModel;
class JTable;
class LocoIOData;
class QPushButton;
class QLabel;
class JTextField;
class LOCOIOSHARED_EXPORT LocoIOPanel : public LnPanel, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
 Q_INVOKABLE explicit LocoIOPanel(QWidget *parent = 0);
 ~LocoIOPanel() {}
 LocoIOPanel(const LocoIOPanel&) : LnPanel() {}
 /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo)override;
 /*public*/ QString getHelpTarget() override;
 /*public*/ QString getTitle() override;
 /*public*/ void dispose() override;
 QObject* self() override {return (QObject*)this;}

signals:

public slots:
 void on_probeButtonClicked();
 /*public*/ void propertyChange(PropertyChangeEvent* evt) override;
 void on_readAllButtonClicked();
 void on_writeAllButtonClicked();
 void on_al4UnitAddress();

private:
 JTextField* addrField;// = new JTextField("00");
 JTextField* subAddrField;// = new JTextField("00");
 QLabel* status;// = new QLabel("<unknown>");
 QLabel* firmware;// = new QLabel("<unknown>");
 QLabel* locobuffer;// = new QLabel("<unknown>");

 QPushButton* addrSetButton;// = NULL;
 QPushButton* probeButton;// = NULL;
 QPushButton* readAllButton;// = NULL;
 QPushButton* writeAllButton;// = NULL;
 QPushButton* saveButton;// = NULL;
 QPushButton* openButton;// = NULL;

 LocoIOData* data;
 LocoIOTableModel* model;
 JTable* table;
 //JScrollPane scroll;
 Logger* log;
 LnTrafficController* ln;

protected:
 /*protected*/ int cautionAddrSet();
protected slots:
 /*protected*/ void addrSet();

};
Q_DECLARE_METATYPE(LocoIOPanel)
#endif // LOCOIOPANEL_H
