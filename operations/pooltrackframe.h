#ifndef POOLTRACKFRAME_H
#define POOLTRACKFRAME_H

#include "operationsframe.h"
#include "jtextfield.h"
#include "propertychangelistener.h"
class QGroupBox;
class QLabel;
namespace Operations
{
 class Pool;
 class Track;
 class TrackEditFrame;
 class PoolTrackFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  PoolTrackFrame(TrackEditFrame* tef, QWidget* parent = 0);
  /*public*/ PoolTrackFrame(Track* track, QWidget* parent = 0);
  /*public*/ void initComponents() override;
  /*public*/ void dispose() override;
  /*public*/ QString getClassName() override;
  QObject* pself() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void buttonActionPerformed(QWidget* ae) override;

 private:
  QLabel* name;//= new JLabel(Bundle.getMessage("Name"));
  QLabel* minimum;//= new JLabel(Bundle.getMessage("Minimum"));
  QLabel* length;//= new JLabel(Bundle.getMessage("Length"));

  // text field
  JTextField* trackPoolNameTextField;//= new JTextField(20);
  JTextField* trackMinLengthTextField;//= new JTextField(5);

  // combo box
  JComboBox* comboBoxPools;//= new JComboBox<>();

  // major buttons
  JButton* addButton;//= new JButton(Bundle.getMessage("Add"));
  JButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // pool status
  JPanel* poolStatus;//= new JPanel();

  /*private*/ TrackEditFrame* _tefx;
  void common();
  Logger* log;
  /*private*/ void updatePoolsComboBox();
  /*private*/ void updatePoolStatus();

 protected:
  /*protected*/ Track*_track;
  /*protected*/ Pool* _pool;

 };
}
#endif // POOLTRACKFRAME_H
