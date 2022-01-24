#ifndef SIGNALEDITFRAME_H
#define SIGNALEDITFRAME_H
#include "jmrijframe.h"
#include "signaltablemodel.h"
#include "oblockmanager.h"
#include "jlabel.h"
#include "namedbeancombobox.h"
#include "signalmastmanager.h"
#include "instancemanager.h"
#include <QRadioButton>
#include "jspinner.h"
#include "jbutton.h"
#include "windowadapter.h"


class SignalEditFrame : public JmriJFrame
{
  Q_OBJECT
 public:
  /*public*/ SignalEditFrame(/*@Nonnull*/ QString title,
                         /*@CheckForNull*/ NamedBean* signal,
                         /*@CheckForNull*/ SignalTableModel::SignalRow *sr,
                         /*@CheckForNull*/ SignalTableModel* model, QWidget* parent = nullptr);
  /*public*/ void layoutFrame();
  /*public*/ void resetFrame();
  /*public*/ void populateFrame(SignalTableModel::SignalRow* sr);
  QString getClassName() {return "jmri.jmrix.beantable.olock.SignalEditFrame";}


 private:
  static Logger* log;
  JPanel* main = new JPanel();

  SignalTableModel* model;
  NamedBean* signal;
  PortalManager* pm;
  OBlockManager* obm;
  /*private*/ /*final*/ SignalEditFrame* frame = this;
  /*private*/ Portal* _portal;
  SignalTableModel::SignalRow* _sr;
  ///*private*/ /*final*/ Object lock = new Object();

  // UI components for Add/Edit Signal (head or mast)
  JLabel* portalLabel = new JLabel(tr("Placed at Portal:"), JLabel::TRAILING);

  JLabel* signalMastLabel = new JLabel(tr("%1").arg(tr("SignalMast")));
  JLabel* signalHeadLabel = new JLabel(tr("%1").arg(tr("SignalHead")));
  JLabel* fromBlockLabel = new JLabel(tr("%1").arg(tr("From (Approach) Block")));
  JLabel* fromBlock = new JLabel();
  JLabel* toBlockLabel = new JLabel(tr("%1").arg(tr("To (Protected) Block")));
  JLabel* toBlock = new JLabel();
  JLabel* mastName = new JLabel();
  JLabel* headName = new JLabel();
  QStringList p0 = {""};
  /*private*/ /*final*/ JComboBox/*<String>*/* portalComboBox = new JComboBox(p0);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalMast>*/* sigMastComboBox = new NamedBeanComboBox((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* sigHeadComboBox = new NamedBeanComboBox((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
//    /*private*/ /*final*/ NamedBeanComboBox<OBlock> fromBlockComboBox = new NamedBeanComboBox<>(InstanceManager.getDefault(OBlockManager.class),
//            null, NamedBean.DisplayOptions.DISPLAYNAME);
//    /*private*/ /*final*/ NamedBeanComboBox<OBlock> toBlockComboBox = new NamedBeanComboBox<>(InstanceManager.getDefault(OBlockManager.class),
//            null, NamedBean.DisplayOptions.DISPLAYNAME);
  /*private*/ /*final*/ JButton* flipButton = new JButton(tr("Flip OBlocks"));
  // the following 3 items copied from beanedit, place in separate static method?
  JSpinner* lengthSpinner = new JSpinner(); // 2 digit decimal format field, initialized later as instance
  QRadioButton* inch = new QRadioButton(tr("Length in Inches"));
  QRadioButton* cm = new QRadioButton(tr("Length in Centimeters"));
  JLabel* statusBar = new JLabel(tr("To create a new %1, enter its definition, then click [%2].").arg(
          tr("SignalMast") + "/" + tr("SignalHead")).arg(
          tr("OK")));

  /*private*/ bool _newSignal;
  /*private*/ void updateLength();
  void status(QString message, bool warn);
  void addCloseListener(JmriJFrame* frame);

 private slots:
  /*private*/ void applyPressed(/*ActionEvent e*/);

 protected:
  /*protected*/ void closeFrame();

  friend class SEFWindowListener;
};

class SEFWindowListener : public WindowAdapter
{
  Q_OBJECT
  SignalEditFrame* frame;
 public:
  SEFWindowListener(SignalEditFrame* frame) {this->frame = frame;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* e) {
      frame->model->setEditMode(false);
      frame->log->debug("SignalEditFrame.closeFrame signalEdit=False");
      frame->dispose();
  }

};
#endif // SIGNALEDITFRAME_H
