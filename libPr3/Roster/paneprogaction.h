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
  Q_INVOKABLE explicit PaneProgAction(QObject *parent=nullptr) {}
  ~PaneProgAction() {}
  PaneProgAction(const PaneProgAction&) : AbstractAction() {}
    /*public*/ PaneProgAction(QString s, QObject* parent);
    void windowClosing(QCloseEvent*);
signals:

public slots:
    /*public*/ void actionPerformed(JActionEvent* =0);

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
     MyCombinedLocoSelTreePane(PaneProgAction* act, QLabel*, ProgModeSelector* modePane, QWidget* = 0);
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
Q_DECLARE_METATYPE(PaneProgAction)
#endif // PANEPROGACTION_H
