#ifndef PANEPROGACTION_H
#define PANEPROGACTION_H

#include "abstractaction.h"
#include "logger.h"
#include "combinedlocoseltreepane.h"
#include "libPr3_global.h"
#include "windowlistener.h"

class JFrame;
class JmriJFrame;
class ProgModeSelector;
class QLabel;
class LIBPR3SHARED_EXPORT PaneProgAction : public AbstractAction
{
    Q_OBJECT
public:
    //explicit PaneProgAction(QObject *parent);
    /*public*/ PaneProgAction(QString s, QObject* parent);
    void windowClosing(QCloseEvent*);
signals:

public slots:
    /*public*/ void actionPerformed();

private:
    //Object o1, o2, o3, o4;
    QLabel* statusLabel;
    Logger* log;
    JmriJFrame* f;
    ProgModeSelector* modePane;// = new ProgServiceModeComboBox();
    class MyCombinedLocoSelTreePane : public CombinedLocoSelTreePane
    {
     PaneProgAction* act;
    public:
     MyCombinedLocoSelTreePane(PaneProgAction* act, QLabel*, QWidget* = 0);
    private:

    protected:
     /*protected*/ void startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename);
    };
    //friend class PaneProgAction;
};
#if 0
class PPAWindowListener : public WindowListener
{
 Q_OBJECT
 JFrame* p;
 PaneProgAction* ppa;

public:
 PPAWindowListener(JFrame* p, PaneProgAction* ppa);
 void windowClosing(QCloseEvent *e);

};
#endif
#endif // PANEPROGACTION_H
