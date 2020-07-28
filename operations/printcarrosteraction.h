#ifndef PRINTCARROSTERACTION_H
#define PRINTCARROSTERACTION_H

#include "abstractaction.h"
#include "operationsframe.h"

class HardcopyWriter;
class QPushButton;
class QCheckBox;
class JComboBox;
//class JFrame;
namespace Operations
{
 class CarsTableFrame;
 class CarPrintOptionFrame;
 class PrintCarRosterAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ PrintCarRosterAction(QString actionName, JFrame* frame, bool preview, QWidget* pWho);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  /**
   * Frame hosting the printing
   */
  JFrame* mFrame;
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool isPreview;
  CarsTableFrame* panel;
  CarPrintOptionFrame* cpof;// = null;
  int numberCharPerLine;
  /*private*/ void printCars();
  JComboBox* sortByComboBox;// = new JComboBox<>();
  JComboBox* manifestOrientationComboBox;// = new JComboBox<>();
  JComboBox* fontSizeComboBox;// = new JComboBox<>();


  /*private*/ void printTitleLine(HardcopyWriter* writer);// //throws IOException
  static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
  /*private*/ QString padAttribute(QString attribute, int length);
  friend class CarPrintOptionFrame;
 };

 /*public*/ class CarPrintOptionFrame : public OperationsFrame
 {
  Q_OBJECT
     /**
      *
      */
     //private static final long serialVersionUID = -7320807344781148331L;
     PrintCarRosterAction* pcr;
public:
     /*public*/ CarPrintOptionFrame(PrintCarRosterAction* pcr);
     /*public*/ void initComponents();
     /*public*/ QString getClassName();

 public slots:
     /*public*/ void buttonActionPerformed(QWidget* ae) ;
     /*public*/ void comboBoxActionPerformed(QWidget* ae);
 private:
     /*private*/ void loadSortByComboBox(JComboBox* box);
     QCheckBox* printCarsWithLocation;// = new JCheckBox(Bundle.getMessage("PrintCarsWithLocation"));
     QCheckBox* printCarLength;// = new JCheckBox(Bundle.getMessage("PrintCarLength"));
     QCheckBox* printCarWeight;// = new JCheckBox(Bundle.getMessage("PrintCarWeight"));
     QCheckBox* printCarColor;// = new JCheckBox(Bundle.getMessage("PrintCarColor"));
     QCheckBox* printCarOwner;// = new JCheckBox(Bundle.getMessage("PrintCarOwner"));
     QCheckBox* printCarBuilt;// = new JCheckBox(Bundle.getMessage("PrintCarBuilt"));
     QCheckBox* printCarLoad;// = new JCheckBox(Bundle.getMessage("PrintCarLoad"));
     QCheckBox* printCarKernel;// = new JCheckBox(Bundle.getMessage("PrintKernel"));
     QCheckBox* printCarValue;// = new JCheckBox(MessageFormat.format(Bundle.getMessage("PrintCar"), new Object[]{Setup
   //      .getValueLabel()}));
     QCheckBox* printCarRfid;// = new JCheckBox(MessageFormat.format(Bundle.getMessage("PrintCar"), new Object[]{Setup
   //      .getRfidLabel()}));
     QCheckBox* printCarLast;// = new JCheckBox(Bundle.getMessage("PrintCarLastMoved"));
     QCheckBox* printCarWait;// = new JCheckBox(Bundle.getMessage("PrintCarWait"));
     QCheckBox* printCarPickup;// = new JCheckBox(Bundle.getMessage("PrintCarPickup"));
     QCheckBox* printCarLocation;// = new JCheckBox(Bundle.getMessage("PrintCarLocation"));
     QCheckBox* printCarTrain;// = new JCheckBox(Bundle.getMessage("PrintCarTrain"));
     QCheckBox* printCarDestination;// = new JCheckBox(Bundle.getMessage("PrintCarDestination"));
     QCheckBox* printCarFinalDestination;// = new JCheckBox(Bundle.getMessage("PrintCarFinalDestination"));
     QCheckBox* printCarRWE;// = new JCheckBox(Bundle.getMessage("PrintCarReturnWhenEmpty"));
     QCheckBox* printCarComment;// = new JCheckBox(Bundle.getMessage("PrintCarComment"));
     QCheckBox* printSpace;// = new JCheckBox(Bundle.getMessage("PrintSpace"));
     QCheckBox* printPage;// = new JCheckBox(Bundle.getMessage("PrintPage"));

     QPushButton* okayButton;// = new JButton(Bundle.getMessage("ButtonOkay"));
     friend class PrintCarRosterAction;
 };

}
#endif // PRINTCARROSTERACTION_H
