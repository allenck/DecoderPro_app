#ifndef STAGINGEDITFRAME_H
#define STAGINGEDITFRAME_H
#include "trackeditframe.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT StagingEditFrame : public TrackEditFrame
 {
  Q_OBJECT
 public:
  StagingEditFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Location* location, Track* track);
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void checkBoxActionPerformed(QWidget* ae);

 private:
  // check boxes
  QCheckBox* swapLoadsCheckBox;// = new JCheckBox(Bundle.getMessage("SwapCarLoads"));
  QCheckBox* emptyCheckBox;// = new JCheckBox(Bundle.getMessage("EmptyDefaultCarLoads"));
  QCheckBox* emptyCustomCheckBox;// = new JCheckBox(Bundle.getMessage("EmptyCarLoads"));
  QCheckBox* loadCheckBox;// = new JCheckBox(Bundle.getMessage("LoadCarLoads"));
  QCheckBox* loadAnyCheckBox;// = new JCheckBox(Bundle.getMessage("LoadAnyCarLoads"));
  QCheckBox* loadAnyStagingCheckBox;// = new JCheckBox(Bundle.getMessage("LoadsStaging"));
  QCheckBox* blockCarsCheckBox;// = new JCheckBox(Bundle.getMessage("BlockCars"));

  JPanel* panelLoad;// = panelOpt4;

 protected:
  /*protected*/ void saveTrack(Track* track);
  /*protected*/ void enableButtons(bool enabled);

 };
}
#endif // STAGINGEDITFRAME_H
