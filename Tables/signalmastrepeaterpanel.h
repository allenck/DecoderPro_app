#ifndef SIGNALMASTREPEATERPANEL_H
#define SIGNALMASTREPEATERPANEL_H
#include "jmripanel.h"
#include "abstracttablemodel.h"
#include "propertychangelistener.h"


class SignalMastRepeater;
class PropertyChangeEvent;
class QPushButton;
class JmriBeanComboBox;
class SignalMastRepeaterModel;
class QScrollarea;
class DefaultSignalMastManager;
class SignalMastRepeaterPanel : public JmriPanel
{
public:
    SignalMastRepeaterPanel(QWidget* parent = 0);

private:
    DefaultSignalMastManager* dsmm;

    SignalMastRepeaterModel* _RepeaterModel;
    QScrollarea* _SignalAppearanceScrollPane;
    JmriBeanComboBox* _MasterBox;
    JmriBeanComboBox* _SlaveBox;
    QPushButton* _addRepeater;
    /*private*/ QList<SignalMastRepeater*>* _signalMastRepeaterList;
    /*private*/ void updateDetails();

    friend class SignalMastRepeaterModel;
};

/*public*/ class SignalMastRepeaterModel : public  AbstractTableModel, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
    SignalMastRepeaterPanel* panel;
public:
 SignalMastRepeaterModel(SignalMastRepeaterPanel* panel);
 /*public*/ void configureTable(JTable* table);
 /*public*/ int getPreferredWidth(int col);
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ void dispose();
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 enum COLUMNS
 {
  MASTER_COLUMN = 0,
  DIR_COLUMN = 1,
  SLAVE_COLUMN = 2,
  ENABLE_COLUMN = 3,
  DEL_COLUMN = 4
 };
 /*public*/ void setSetToState(QString x) ;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 QObject* self() override {return (QObject*)this;}

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e)  override;

private:
 Logger* log;


protected:
 /*protected*/ void configEditColumn(JTable* table);
 ///*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* sample);
 /*protected*/ void deleteRepeater(int r);

};
#endif // SIGNALMASTREPEATERPANEL_H
