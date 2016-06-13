#ifndef PRINTROSTERENTRY_H
#define PRINTROSTERENTRY_H
#include "panecontainer.h"
#include "logger.h"

class HardcopyWriter;
class JFrame;
class PaneProgPane;
class QCheckBox;
class JmriJFrame;
class RosterMediaPane;
class FunctionLabelsPane;
class RosterEntry;
class PrintRosterEntry : public PaneContainer
{
    Q_OBJECT
public:
    explicit PrintRosterEntry(QObject *parent = 0);
    /*public*/ PrintRosterEntry(RosterEntry* rosterEntry, JmriJFrame* parent, QString filename);
    /*public*/ BusyGlassPane* getBusyGlassPane();
    /*public*/ void prepGlassPane(QAbstractButton* activeButton);
    /*public*/ void enableButtons(bool enable);
    /*public*/ void paneFinished();
    /*public*/ bool isBusy();
    /*public*/ PrintRosterEntry(RosterEntry* rosterEntry, QList<QWidget*> paneList, FunctionLabelsPane* flPane,RosterMediaPane* rMPane, JmriJFrame* parent);
    /*public*/ void doPrintPanes(bool preview);
    /*public*/ void printPanes(/*final*/ bool preview);
    /*public*/ void printInfoSection(HardcopyWriter* w);

signals:

public slots:
    void On_selectAll_toggled(bool);
    void On_ok_clicked();
private:
    RosterEntry* _rosterEntry;

    QList<QWidget*>        _paneList;//        = new ArrayList<JPanel>();
    FunctionLabelsPane*   _flPane;//         = null;
    RosterMediaPane*     _rMPane;//        = null;
    JmriJFrame*          _parent;//         = null;
    Logger* log;
    QCheckBox* funct;
    QHash<QCheckBox*, PaneProgPane*> printList;
    JFrame* frame;
    bool preview;
};

#endif // PRINTROSTERENTRY_H
