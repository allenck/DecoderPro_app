#ifndef LIGHTEDITACTION_H
#define LIGHTEDITACTION_H

#include <beaneditaction.h>
#include <QWidget>
#include "lightcontrolpane.h"

class LightIntensityPane;
class LightEditAction : public BeanEditAction
{
  Q_OBJECT
 public:
  LightEditAction();
  /*public*/ QString helpTarget() override;
  /*public*/ NamedBean* getByUserName(QString name)override;

 private:
  /*private*/ LightControlPane* lcp;
  /*private*/ LightIntensityPane* lip;
  /*private*/ QString getBeanManagerSystemUserName();
  BeanItemPanel* propertiesDetails() override;
  BeanItemPanel* lightControlPanel();
  BeanItemPanel* lightIntensityPanel();

 protected:
  /*protected*/ void initPanels()override;
  /*protected*/ void cancelButtonAction(/*ActionEvent e*/);

  friend class LEAResetAction;
  friend class LEASaveAction;
};
class LEAResetAction : public AbstractAction
{
  Q_OBJECT
  LightEditAction* lea;
 public:
  LEAResetAction(LightEditAction* lea) {this->lea = lea;}
 public slots:
    //@Override
    /*public*/ void actionPerformed(JActionEvent* /*e*/) override{
        lea->lcp->setToLight((Light*)lea->bean);
    }
};

class LEASaveAction : public AbstractAction
{
  Q_OBJECT
  LightEditAction* lea;
 public:
  LEASaveAction(LightEditAction* lea) {this->lea = lea;}
 public slots:
    //@Override
    /*public*/ void actionPerformed(JActionEvent* /*e*/) override{
        lea->lcp->setLightFromControlTable((Light*)lea->bean);
    }
};

#endif // LIGHTEDITACTION_H
