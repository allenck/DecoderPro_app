#ifndef CHANGETRACKFRAME_H
#define CHANGETRACKFRAME_H

#include "operationsframe.h"

class QButtonGroup;
namespace Operations
{
 class TrackEditFrame;
 class ChangeTrackFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  ChangeTrackFrame(TrackEditFrame* tef);
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  // radio buttons
  QRadioButton* spurRadioButton;//= new JRadioButton(Bundle.getMessage("Spur"));
  QRadioButton* yardRadioButton;//= new JRadioButton(Bundle.getMessage("Yard"));
  QRadioButton* interchangeRadioButton;//= new JRadioButton(Bundle.getMessage("Interchange"));
  QButtonGroup* group;//= new ButtonGroup();

  // major buttons
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  /*private*/ TrackEditFrame* _tef;
  QString _trackType;//= "";
  /*private*/ void changeTrack(QString type);
  Logger* log;

 };
}
#endif // CHANGETRACKFRAME_H
