#ifndef SIGNALLINGSOURCEPANEL_H
#define SIGNALLINGSOURCEPANEL_H

#include <QWidget>
#include "logger.h"
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include "QAbstractTableModel"
#include "jtable.h"

class SignalMastLogic;
class SignalMast;
class JmriJFrame;
class SignalMastAppearanceModel;
class PropertyChangeEvent;

class SignallingSourcePanel : public QWidget
{
    Q_OBJECT
public:
    //explicit SignallingSourcePanel(QWidget *parent = 0);
    /*public*/ SignallingSourcePanel(/*final*/ SignalMast* sourceMast, QWidget* parent = 0);

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
 void discoverPressed(/*ActionEvent e*/);
 void on_addLogic_pressed();

private:
    Logger* log;
    SignalMastLogic* sml;
    SignalMast* sourceMast;
    QLabel* fixedSourceMastLabel;// = new JLabel();

    QPushButton* discoverPairs;// = new QPushButton(rb.getString("ButtonDiscover"));

    SignalMastAppearanceModel* _AppearanceModel;
    QScrollArea* _SignalAppearanceScrollPane;
    JmriJFrame* signalMastLogicFrame;// = NULL;
    QLabel* sourceLabel;// = new JLabel();
    /*private*/ QList <SignalMast*> _signalMastList;
    /*private*/ void updateDetails();
 friend class SignalMastAppearanceModel;
};
/*public*/ class SignalMastAppearanceModel : public QAbstractTableModel //implements PropertyChangeListener
{
 Q_OBJECT
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
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ void configureTable(JTable* table);
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QString getColumnName(int col);
    /*public*/ void dispose();
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
    void updateSignalMastLogic(SignalMastLogic* smlOld, SignalMastLogic* smlNew);
    Logger* log;
    SignallingSourcePanel* self;
    void fireTableDataChanged();
protected:
    /*protected*/ void configEditColumn(JTable* table);
    /*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* sample);
    /*protected*/ void editPair(int r);
    /*protected*/ void deletePair(int r);
friend class SignallingSourcePanel;
};
#endif // SIGNALLINGSOURCEPANEL_H
