#ifndef TRACKEDITCOMMENTSFRAME_H
#define TRACKEDITCOMMENTSFRAME_H

#include "operationsframe.h"
#include "appslib_global.h"

class JTextArea;
class QSize;
class QPushButton;
namespace Operations
{
 class Track;
 class APPSLIBSHARED_EXPORT TrackEditCommentsFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrackEditCommentsFrame(Track* track, QWidget* parent =0);
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  JTextArea* commentBothTextArea;// = new JTextArea(5, 100);
 // JScrollPane commentBothScroller = new JScrollPane(commentBothTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
 //         JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  JTextArea* commentPickupTextArea;// = new JTextArea(5, 100);
 // JScrollPane commentPickupScroller = new JScrollPane(commentPickupTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
 //         JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  JTextArea* commentSetoutTextArea;// = new JTextArea(5, 100);
 // JScrollPane commentSetoutScroller = new JScrollPane(commentSetoutTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
 //         JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
  QSize minScrollerDim;// = new Dimension(1200, 300);
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));
  Track* _track;
  /*private*/ void initComponents(Track* track);
  Logger* log;
 };
}
#endif // TRACKEDITCOMMENTSFRAME_H
