#ifndef PRINTROSTERENTRY_H
#define PRINTROSTERENTRY_H
#include "panecontainer.h"
#include "logger.h"

class JPanel;
class HardcopyWriter;
class JFrame;
class PaneProgPane;
class QCheckBox;
class JmriJFrame;
class RosterMediaPane;
class FunctionLabelPane;
class RosterEntry;
class PrintRosterEntry : public QObject, PaneContainer
{
    Q_OBJECT
 Q_INTERFACES(PaneContainer)
public:
    explicit PrintRosterEntry(QObject *parent = 0);
    /*public*/ PrintRosterEntry(RosterEntry* rosterEntry, JmriJFrame* parent, QString filename);
    /*public*/ BusyGlassPane* getBusyGlassPane();
    /*public*/ void prepGlassPane(QAbstractButton* activeButton);
    /*public*/ void enableButtons(bool enable);
    /*public*/ void paneFinished();
    /*public*/ bool isBusy();
    /*public*/ PrintRosterEntry(RosterEntry* rosterEntry, QList<JPanel *> paneList, FunctionLabelPane* flPane, RosterMediaPane* rMPane, JmriJFrame* parent);
    /*public*/ void doPrintPanes(bool preview);
    /*public*/ void printPanes(/*final*/ bool preview);
    /*public*/ void printInfoSection(HardcopyWriter* w);

signals:

public slots:
    void On_selectAll_toggled(bool);
    void On_ok_clicked();
private:
    RosterEntry* _rosterEntry;

    QList<JPanel*>        _paneList;//        = new ArrayList<JPanel>();
    FunctionLabelPane*   _flPane;//         = null;
    RosterMediaPane*     _rMPane;//        = null;
    JmriJFrame*          _parent;//         = null;
    Logger* log;
    QCheckBox* funct;
    QHash<QCheckBox*, PaneProgPane*> printList;
    JFrame* frame;
    bool preview;
};

#endif // PRINTROSTERENTRY_H
