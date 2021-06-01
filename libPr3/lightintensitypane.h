#ifndef LIGHTINTENSITYPANE_H
#define LIGHTINTENSITYPANE_H

#include <jpanel.h>
#include <QObject>
#include "jspinner.h"
#include "jlabel.h"
#include "variablelight.h"

class Logger;
class LightIntensityPane : public JPanel
{
  Q_OBJECT
 public:
  LightIntensityPane();
  /*public*/ LightIntensityPane( bool vertical);
  /*public*/ void setToLight(Light* light);
  /*public*/ void setLightFromPane(VariableLight* light);

 private:
  static Logger* log;
  /*private*/ JPanel* minPan;
  /*private*/ JPanel* maxPan;
  /*private*/ JPanel* transitionPan;

  /*private*/ JSpinner* minIntensity;
  /*private*/ JSpinner* maxIntensity;
  /*private*/ JSpinner* transitionTime;

  /*private*/ /*final*/ JLabel* status1 = new JLabel();
  /*private*/ void init(bool vertical);
  /*private*/ void setupVariableDisplay(bool showIntensity, bool showTransition);
};

#endif // LIGHTINTENSITYPANE_H
