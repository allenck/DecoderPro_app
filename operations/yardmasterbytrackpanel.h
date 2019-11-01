#ifndef YARDMASTERBYTRACKPANEL_H
#define YARDMASTERBYTRACKPANEL_H
#include "commonconductoryardmasterpanel.h"
#include "track.h"


namespace Operations
{


 class YardmasterByTrackPanel : public CommonConductorYardmasterPanel
 {
  Q_OBJECT
 public:
  YardmasterByTrackPanel(QWidget* parent = nullptr);
  /*public*/ YardmasterByTrackPanel(Location* location, QWidget* parent = nullptr);
  /*public*/ void dispose();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae) ;
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  void common();
/*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("YardmasterByTrackPanel");
  // text panes
  HtmlTextEdit* textSwitchListCommentPane;// = new JTextPane();
  HtmlTextEdit* textTrackCommentPane;// = new JTextPane();
  HtmlTextEdit* textTrackCommentWorkPane;// = new JTextPane();

  // combo boxes
  QComboBox* trackComboBox;// = new QComboBox(); // <Track>

  // buttons
  QPushButton* nextButton;// = new JButton(Bundle.getMessage("Next"));

  // panel
  QWidget* pTrack;// = new JPanel();
  QVBoxLayout* pTrackLayout;
  QScrollArea* pTrackPane;
  /*private*/ void updateTrackComboBox();
  /*private*/ void nextButtonAction();

 private slots:
  /*private*/ void runUpdate();

 protected:
  /*protected*/ Track* _track;// = null;
  /*protected*/ static /*final*/ bool IS_MANIFEST;// = false;
  /*protected*/ void comboBoxActionPerformed(QWidget* source);
  /*protected*/ void update();
  friend class YardmasterByTrackPanelUpdate;
 };
 class YardmasterByTrackPanelUpdate : public QObject
 {
  Q_OBJECT
  YardmasterByTrackPanel* panel;
 public:
  YardmasterByTrackPanelUpdate(YardmasterByTrackPanel* panel) {this->panel = panel;}
 public slots:
  void process() { panel->runUpdate(); emit finished();}
 signals:
  void finished();

 };
}
#endif // YARDMASTERBYTRACKPANEL_H
