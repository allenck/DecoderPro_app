#ifndef LAYOUTXOVEREDITOR_H
#define LAYOUTXOVEREDITOR_H
#include "layoutturnouteditor.h"

class LayoutXOverEditor : public LayoutTurnoutEditor
{
  Q_OBJECT
 public:
  /*public*/ LayoutXOverEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack) override;

  private:
   static Logger* log;
 protected:
   /*protected*/ void extendAddContinuingStateChoice(QWidget* contentPane) override;
   /*protected*/ void extendBlockBCDSetup(QWidget* contentPane) override;
   /*protected*/ void configureCheckBoxes(BlockManager* bm) override;
   /*protected*/ void setUpForEdit() override;
   /*protected*/ void setUpContinuingSense() override;
   /*protected*/ void donePressedSecondTurnoutName(QString newName) override;
   /*protected*/ void setContinuingRouteTurnoutState() override;
   /*protected*/ void checkBlock234Changed()override;

};

#endif // LAYOUTXOVEREDITOR_H
