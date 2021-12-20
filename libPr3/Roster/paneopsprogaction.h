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
  explicit PaneOpsProgAction(QObject *parent = 0) : AbstractAction(parent) {}
  ~PaneOpsProgAction(){}
  PaneOpsProgAction(const PaneOpsProgAction&) : AbstractAction() {}
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
Q_DECLARE_METATYPE(PaneOpsProgAction)
#endif // PANEOPSPROGACTION_H
