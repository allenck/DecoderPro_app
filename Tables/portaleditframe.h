#ifndef PORTALEDITFRAME_H
#define PORTALEDITFRAME_H
#include "jmrijframe.h"
#include "portaltablemodel.h"
#include "portalmanager.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "namedbeancombobox.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include "actionevent.h"

class PortalEditFrame : public JmriJFrame
{
  Q_OBJECT
 public:
  /*public*/ PortalEditFrame(/*@Nonnull*/ QString title, Portal* portal, PortalTableModel* model, QWidget* parent = nullptr) ;
  QString getClassName() {return "jmri.jmrix.beantable.olock.PortalEditFrame";}
  /*public*/ void layoutFrame();
  /*public*/ void resetFrame();
  /*public*/ void populateFrame(Portal* p);

 private:
  static Logger* log;
  JPanel* main = new JPanel();
  PortalTableModel* model;
  PortalManager* pm;
  // UI components for Add/Edit Portal
  /*private*/ /*final*/ JLabel* portalLabel = new JLabel(tr("Portal Name:"), JLabel::TRAILING);
  /*private*/ /*final*/ JTextField* portalUserName = new JTextField(15);
  /*private*/ /*final*/ JLabel* fromBlockLabel = new JLabel(tr("%1").arg(tr("From (Approach) Block")), JLabel::TRAILING);
  /*private*/ /*final*/ JLabel* toBlockLabel = new JLabel(tr("%1").arg(tr("OppBlockName")), JLabel::TRAILING);
  /*private*/ /*final*/ NamedBeanComboBox/*<OBlock>*/* fromBlockComboBox = new NamedBeanComboBox((OBlockManager*)InstanceManager::getDefault("OBlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<OBlock>*/* toBlockComboBox = new NamedBeanComboBox((OBlockManager*)InstanceManager::getDefault("OBlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ JLabel* statusBar = new JLabel(tr("Enter a unique Name"), JLabel::LEADING);

  /*private*/ /*final*/ PortalEditFrame* frame = this;
  /*private*/ Portal* _portal;
  /*private*/ bool _newPortal = false;
  void status(QString message, bool warn);

 private slots:
  /*private*/ void applyPressed(JActionEvent* e =0);

};

#endif // PORTALEDITFRAME_H
