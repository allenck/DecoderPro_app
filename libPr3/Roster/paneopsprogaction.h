#ifndef PANEOPSPROGACTION_H
#define PANEOPSPROGACTION_H

#include "abstractaction.h"
#include "logger.h"
#include "knownlocoselpane.h"
#include "libPr3_global.h"

class QLabel;
class LIBPR3SHARED_EXPORT PaneOpsProgAction : public AbstractAction
{
    Q_OBJECT
public:
    //explicit paneOpsProgAction(QObject *parent = 0);
    /*public*/ PaneOpsProgAction(QString s, QObject* parent );

signals:

public slots:
    /*public*/ void actionPerformed();

private:
    QLabel* statusLabel;
    Logger* log;
 class MyKnownLocoSelPane : public KnownLocoSelPane
 {
 public:
     MyKnownLocoSelPane(bool, QWidget* = 0);
  protected:
     /*protected*/ void startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename);

 };
};

#endif // PANEOPSPROGACTION_H
