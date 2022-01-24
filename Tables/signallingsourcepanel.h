#ifndef SIGNALLINGSOURCEPANEL_H
#define SIGNALLINGSOURCEPANEL_H

#include <QWidget>
#include "logger.h"
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include "QAbstractTableModel"
#include "jtable.h"
#include "jmripanel.h"
#include "propertychangelistener.h"

class SignalMastLogic;
class SignalMast;
class JmriJFrame;
class SignalMastAppearanceModel;
class PropertyChangeEvent;

class SignallingSourcePanel : public JmriPanel, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    //explicit SignallingSourcePanel(QWidget *parent = 0);
    /*public*/ SignallingSourcePanel(/*final*/ SignalMast* sourceMast, QWidget* parent = 0);
 /*public*/ void dispose() override;
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
 void discoverPressed(/*ActionEvent e*/);
 void on_addLogic_pressed();

private:
    Logger* log;
    SignalMastLogic* sml;
    SignalMast* sourceMast;
    QLabel* fixedSourceMastLabel;// = new JLabel();

    QPushButton* discoverPairs;// = new QPushButton(rb.getString("ButtonDiscover"));

    SignalMastAppearanceModel* _AppearanceModel;
    //QScrollArea* _SignalAppearanceScrollPane;
    JmriJFrame* signalMastLogicFrame;// = NULL;
    QLabel* sourceLabel;// = new JLabel();
    /*private*/ QList <SignalMast*> _signalMastList;
    /*private*/ void updateDetails();
 friend class SignalMastAppearanceModel;
};
/*public*/ class SignalMastAppearanceModel : public QAbstractTableModel, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    enum COLUMNS
    {
        SYSNAME_COLUMN = 0,
        USERNAME_COLUMN = 1,
        ACTIVE_COLUMN = 2,
        ENABLE_COLUMN = 3,
        EDIT_COLUMN = 4,
        DEL_COLUMN = 5
    };
    SignalMastAppearanceModel(SignallingSourcePanel* self, QObject* parent = 0);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ void configureTable(JTable* table);
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QString getColumnName(int col);
    /*public*/ void dispose();
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QObject* self() override {return (QObject*)this;}
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
private:
    void updateSignalMastLogic(SignalMastLogic* smlOld, SignalMastLogic* smlNew);
    Logger* log;
    SignallingSourcePanel* _self;
    void fireTableDataChanged();
protected:
    /*protected*/ void configEditColumn(JTable* table);
    /*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* sample);
    /*protected*/ void editPair(int r);
    /*protected*/ void deletePair(int r);
friend class SignallingSourcePanel;
};
#endif // SIGNALLINGSOURCEPANEL_H
