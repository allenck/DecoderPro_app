#ifndef LIGHTCONTROLPANE_H
#define LIGHTCONTROLPANE_H

#include <jpanel.h>
#include "lightcontroltablemodel.h"
#include "jbutton.h"
#include "addeditsinglelightcontrolframe.h"

class AddEditSingleLightControlFrame;
class LightControlTableModel;
class LightControlPane : public JPanel
{
  Q_OBJECT
 public:
  LightControlPane();
  /*public*/ LightControlPane(Light* l);
  /*public*/ void setLightFromControlTable(Light* g);
  /*public*/ QList<LightControl*> getControlList();
  /*public*/ /*final*/ void setToLight(Light* l);
  /*public*/ void dispose();

 private:
  /*private*/ LightControlTableModel* lightControlTableModel;
  /*private*/ JButton* addControl;
  /*private*/ int defaultControlIndex = Light::NO_CONTROL;
  /*private*/ void init();
  /*private*/ AddEditSingleLightControlFrame* addEditCtrlFrame;
  /*private*/ void addEditControlWindow(LightControl* lc);

 protected:
  /*protected*/ void updateControlPressed(LightControl* oldControl, LightControl* newControl);
  /*protected*/ void editControlAction(/*@Nonnull*/ LightControl* lc);
  /*protected*/ void addControlToTable(LightControl* lc);
  /*protected*/ int getLastSelectedControlIndex();
  /*protected*/ void setLastSelectedControlIndex(int newIndex);
  /*protected*/ void closeEditControlWindow();

 protected slots:
  /*protected*/ void addControlPressed(/*ActionEvent e*/);

  friend class LightControlTableModel;
  friend class AddEditSingleLightControlFrame;
};

#endif // LIGHTCONTROLPANE_H
