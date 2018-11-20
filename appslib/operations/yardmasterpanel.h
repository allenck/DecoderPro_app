#ifndef YARDMASTERPANEL_H
#define YARDMASTERPANEL_H
#include "commonconductoryardmasterpanel.h"
#include "appslib_global.h"

class JTextPane;
namespace Operations
{
 class Location;
 class APPSLIBSHARED_EXPORT YardmasterPanel : public CommonConductorYardmasterPanel
 {
  Q_OBJECT
 public:
  YardmasterPanel(QWidget* parent = 0);
  /*public*/ YardmasterPanel(Location* location ,QWidget* parent = 0);

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  void common(Location* location);
  int _visitNumber;// = 1;

   // text panes
  HtmlTextEdit* textSwitchListComment;// = new JTextPane();

   // combo boxes
   QComboBox* trainComboBox;// = new JComboBox<>();
   QComboBox* trainVisitComboBox;// = new JComboBox<>();

   // buttons
   QPushButton* nextButton;// = new JButton(Bundle.getMessage("Next"));

   // panels
   QGroupBox* pTrainVisit;// = new JPanel();
   Logger* log;
   /*private*/ void addTrainListeners();
   /*private*/ void update();
   /*private*/ void nextButtonAction();
   /*private*/ void clearAndUpdate();

  protected:
   /*protected*/ static /*final*/ bool IS_MANIFEST;// = false;
   /*private*/ void updateTrainsComboBox();
 protected slots:
   /*protected*/ void comboBoxActionPerformed(QWidget* ae);

 };
}
#endif // YARDMASTERPANEL_H
