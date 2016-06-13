#ifndef PRINTTRAINMANIFESTACTION_H
#define PRINTTRAINMANIFESTACTION_H

#include "abstractaction.h"

class JFrame;
namespace Operations
{
 class PrintTrainManifestAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintTrainManifestAction(QString actionName, bool preview, JFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool isPreview;
  JFrame* frame;
 };
}
#endif // PRINTTRAINMANIFESTACTION_H
