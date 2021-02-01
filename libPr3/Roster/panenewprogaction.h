#ifndef PANENEWPROGACTION_H
#define PANENEWPROGACTION_H

#include "locoseltreepane.h"
#include <QAction>
#include "logger.h"
#include "paneprogframe.h"

class ProgModeSelector;
class PaneNewProgAction : public QAction
{
    Q_OBJECT
public:
    explicit PaneNewProgAction(QObject *parent);
    /*public*/ PaneNewProgAction(QString s, QObject *parent);

signals:

public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
    QObject *o1, *o2, *o3, *o4;
    Logger* log;
    void init();
};
class PNPLocoSelTreePane : public LocoSelTreePane
{
 Q_OBJECT
public:
    PNPLocoSelTreePane(QLabel*, ProgModeSelector* selector, QWidget* = 0);
protected:
  /*protected*/ void startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename);

};
class PNPPaneProgFrame : public PaneProgFrame
{
 Q_OBJECT
public:
    PNPPaneProgFrame(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle, QString programmerFile, Programmer* pProg, bool opsMode, QWidget* parent = 00);

protected:
 JPanel* getModePane() override;
};
#endif // PANENEWPROGACTION_H
