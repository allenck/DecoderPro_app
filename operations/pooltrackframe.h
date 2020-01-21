#ifndef POOLTRACKFRAME_H
#define POOLTRACKFRAME_H

#include "operationsframe.h"
#include "jtextfield.h"

class QGroupBox;
class QLabel;
namespace Operations
{
 class Pool;
 class Track;
 class TrackEditFrame;
 class PoolTrackFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  PoolTrackFrame(TrackEditFrame* tef, QWidget* parent = 0);
  /*public*/ PoolTrackFrame(Track* track, QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  QLabel* name;//= new JLabel(Bundle.getMessage("Name"));
  QLabel* minimum;//= new JLabel(Bundle.getMessage("Minimum"));
  QLabel* length;//= new JLabel(Bundle.getMessage("Length"));

  // text field
  JTextField* trackPoolNameTextField;//= new JTextField(20);
  JTextField* trackMinLengthTextField;//= new JTextField(5);

  // combo box
  QComboBox* comboBoxPools;//= new JComboBox<>();

  // major buttons
  QPushButton* addButton;//= new JButton(Bundle.getMessage("Add"));
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // pool status
  QGroupBox* poolStatus;//= new JPanel();

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
