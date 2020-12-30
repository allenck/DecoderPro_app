#ifndef STARTUPACTIONSPREFERENCESPANEL_H
#define STARTUPACTIONSPREFERENCESPANEL_H
#include "preferencespanel.h"
#include "abstracttablemodel.h"
#include <QMenu>
#include "jtable.h"
#include <QPushButton>
#include <QLabel>

class JActionEvent;
class ListSelectionEvent;
class StartupActionsManager;
class StartupActionsPreferencesPanel : public QWidget, public PreferencesPanel
{
 Q_OBJECT
 Q_INTERFACES(PreferencesPanel)

public:
 Q_INVOKABLE StartupActionsPreferencesPanel(QWidget* parent = 0);
 ~StartupActionsPreferencesPanel() {}
 StartupActionsPreferencesPanel(const StartupActionsPreferencesPanel&) : QWidget() {}
 /*public*/ QString getPreferencesItem();
 /*public*/ QString getPreferencesItemText();
 /*public*/ QString getTabbedPreferencesTitle();
 /*public*/ QString getLabelKey();
 /*public*/ QWidget* getPreferencesComponent();
 /*public*/ bool isPersistant();
 /*public*/ QString getPreferencesTooltip();
 /*public*/ void savePreferences();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired();
 /*public*/ bool isPreferencesValid();
 /*public*/ QString className();
 /*public*/ QObject* self() {return (QObject*)this;}

  public slots:

private:
 // Variables declaration - do not modify
 QMenu* actionsMenu;
 JTable* actionsTbl;
 QPushButton* addBtn;
 QPushButton* downBtn;
 //JScrollPane jScrollPane1;
 QLabel* moveLbl;
 QLabel* recommendationsLbl;
 QPushButton* removeBtn;
 QLabel* startupLbl;
 QPushButton* upBtn;
 // End of variables declaration
 /*private*/ void initComponents();

private slots:
 void on_listSelected(QModelIndex);
 void on_getAction(QObject* factory);
 /*private*/ void addBtnActionPerformed(JActionEvent* evt = 0);
 /*private*/ void removeBtnActionPerformed(JActionEvent* evt = 0);
 /*private*/ void upBtnActionPerformed(JActionEvent* evt = 0);
 /*private*/ void downBtnActionPerformed(JActionEvent* evt = 0);

};
Q_DECLARE_METATYPE(StartupActionsPreferencesPanel)

/*private*/ /*static*/ class SATableModel : public AbstractTableModel //implements PropertyChangeListener
{
 Q_OBJECT
    /*private*/ /*final*/ StartupActionsManager* manager;
public:
    /*public*/ SATableModel(StartupActionsManager* manager) ;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt) ;

};
#endif // STARTUPACTIONSPREFERENCESPANEL_H
