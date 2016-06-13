#ifndef PANEPROGACTION_H
#define PANEPROGACTION_H

#include <QAction>
#include "logger.h"
#include "combinedlocoseltreepane.h"
#include "libPr3_global.h"

class JmriJFrame;
class ProgModeSelector;
class QLabel;
class LIBPR3SHARED_EXPORT PaneProgAction : public QAction
{
    Q_OBJECT
public:
    //explicit PaneProgAction(QObject *parent);
    /*public*/ PaneProgAction(QString s, QObject* parent);
    void windowClosing(QCloseEvent*);
signals:

public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);

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

#endif // PANEPROGACTION_H
