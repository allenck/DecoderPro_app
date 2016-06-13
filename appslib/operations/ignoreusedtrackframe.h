#ifndef IGNOREUSEDTRACKFRAME_H
#define IGNOREUSEDTRACKFRAME_H

#include "operationsframe.h"
namespace Operations
{
 class Track;
 class TrackEditFrame;
 class IgnoreUsedTrackFrame : public OperationsFrame
 {
 public:
  IgnoreUsedTrackFrame(TrackEditFrame* tef);
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  QRadioButton* zeroPercent;//= new JRadioButton(Bundle.getMessage("Disabled"));
  QRadioButton* twentyfivePercent;//= new JRadioButton("25%");	// NOI18N
  QRadioButton* fiftyPercent;//= new JRadioButton("50%");		// NOI18N
  QRadioButton* seventyfivePercent;//= new JRadioButton("75%");	// NOI18N
  QRadioButton* hundredPercent;//= new JRadioButton("100%");		// NOI18N

  // major buttons
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  /*private*/ TrackEditFrame* _tef;
  Logger* log;
 protected:
  /*protected*/ Track* _track;

 };
}
#endif // IGNOREUSEDTRACKFRAME_H
