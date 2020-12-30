#ifndef BLOCKPATHEDITFRAME_H
#define BLOCKPATHEDITFRAME_H
#include "jmrijframe.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "jcombobox.h"
#include "jspinner.h"
#include <QRadioButton>
#include "instancemanager.h"
#include "oblockmanager.h"
#include "tableframes.h"
#include "portalmanager.h"
#
class BlockPathEditFrame : public JmriJFrameX
{
  Q_OBJECT
 public:
/*public*/ BlockPathEditFrame(QString title, OBlock* block, OPath* path,
                          TableFrames::PathTurnoutJPanel* turnouttable, BlockPathTableModel* pathmodel, TableFrames* parent);
/*public*/ void layoutFrame();
/*public*/ void resetFrame();
/*public*/ void populateFrame(OPath* p);


 private:
  static Logger* log;
  // UI components for Add/Edit Path
  JLabel* blockLabel = new JLabel(tr("%1").arg(tr("OBlock")), JLabel::TRAILING);
  JLabel* blockName = new JLabel();
  JLabel* pathLabel = new JLabel(tr("%1").arg(tr("Path Name")), JLabel::TRAILING);
  JTextField* pathUserName = new JTextField(15);
  JLabel* fromPortalLabel = new JLabel(tr("%1").arg(tr("From Portal")), JLabel::TRAILING);
  JLabel* toPortalLabel = new JLabel(tr("%1").arg(tr("To Portal")), JLabel::TRAILING);
  QStringList p0 = {""};
  /*private*/ /*final*/ JComboBox* fromPortalComboBox = new JComboBox(p0);
  /*private*/ /*final*/ JComboBox* toPortalComboBox = new JComboBox(p0);
  JLabel* statusBar = new JLabel(tr("To create a new %1, enter its definition, then click [%2].").arg(tr("Path")).arg(tr("OK")), JLabel::LEADING);
  // the following 3 items copied from beanedit, place in separate static method?
  /*private*/ /*final*/ JSpinner* lengthSpinner = new JSpinner(); // 2 digit decimal format field, initialized later as instance
  /*private*/ /*final*/ QRadioButton* inch = new QRadioButton(tr("LengthInches"));
  /*private*/ /*final*/ QRadioButton* cm = new QRadioButton(tr("LengthCentimeters"));

  /*private*/ /*final*/ BlockPathEditFrame* frame = this;
  /*private*/ bool _newPath = false;
  PortalManager* pm;
  /*private*/ /*final*/ OBlock* _block;
  /*private*/ OPath* _path;
  TableFrames* _core;
  BlockPathTableModel* _pathmodel;
  PathTurnoutTableModel* _tomodel;
  TableFrames::PathTurnoutJPanel* _turnoutTablePane;
  /*private*/ void updateLength();
  void status(QString message, bool warn);
  void addCloseListener(JmriJFrame* frame);

  private slots:
  /*private*/ void createPressed(/*JActionEvent e*/);


protected:
  /*protected*/ UserPreferencesManager* pref;
  /*protected*/ bool isDirty = false;  // true to fire reminder to save work
  /*protected*/ /*final*/ OBlockManager* obm = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
  /*protected*/ void closeFrame();
  /*protected*/ void showReminderMessage();

  friend class BPEFCloseListener;
};

class BPEFCloseListener : public WindowAdapter
{
  Q_OBJECT
  BlockPathEditFrame* f;
 public:
  BPEFCloseListener(BlockPathEditFrame* f){this->f = f;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* e) {
      f->_core->setPathEdit(false);
      f->log->debug("BlockPathEditFrame.closeFrame pathEdit=False");
      f->frame->dispose();
  }
};
#endif // BLOCKPATHEDITFRAME_H
