#ifndef PANEEDITACTION_H
#define PANEEDITACTION_H

#include <QAction>
#include "logger.h"
#include "knownlocoselpane.h"
#include "paneprogframe.h"

class JPanel;
class PaneEditAction : public QAction
{
    Q_OBJECT
public:
    explicit PaneEditAction(QObject *parent);
    /*public*/ PaneEditAction(QString s, QObject *parent);

signals:

public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
    QObject *o1, *o2, *o3, *o4;
    Logger* log;
    void init();
};
class PEKnownLocoSelPane : public KnownLocoSelPane
{
 Q_OBJECT
 PaneEditAction* self;
public:
 PEKnownLocoSelPane(bool b, PaneEditAction* self);
protected:
 /*protected*/ void startProgrammer(DecoderFile* decoderFile, RosterEntry* re,
                                             QString filename);

};
class PEPaneProgFrame : public PaneProgFrame
{
    Q_OBJECT
public:
    PEPaneProgFrame(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle, QString programmerFile, Programmer* pProg, bool opsMode, QWidget* parent = 0);
protected:
    /*protected*/ JPanel* getModePane() override { return NULL; }
};

#endif // PANEEDITACTION_H
