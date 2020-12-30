#ifndef ENGINESTABLEFRAME_H
#define ENGINESTABLEFRAME_H

#include "operationsframe.h"

class JActionEvent;
class QButtonGroup;
class QLabel;
class QRadioButton;
class QSortFilterProxyModel;
class QPushButton;
class JTextField;
class JTable;
namespace Operations
{
 class RollingStock;
 class EngineEditFrame;
 class EngineManager;
 class EnginesTableModel;
 class EnginesTableFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  explicit EnginesTableFrame(QWidget *parent = 0);
  /*public*/ QList<RollingStock*>* getSortByList();
  /*public*/ QString getClassName();

 signals:

 public slots:
  /* public*/ void addButton_clicked();
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void radioButtonActionPerformed(QWidget* source);
  /*public*/ void buttonActionPerformed(QWidget* source);

 private:
  EnginesTableModel* enginesModel;
  QSortFilterProxyModel* sorter;
  JTable* enginesTable;
  //JScrollPane enginesPane;
  EngineManager* engineManager; //=EngineManager.instance();

  // labels
  QLabel* numEngines; //=new JLabel();
  QLabel* textEngines; //=new JLabel();
  QLabel* textSep1; //=new JLabel("          ");

  // radio buttons
  QRadioButton* sortByNumber; //=new JRadioButton(Bundle.getMessage("Number"));
  QRadioButton* sortByRoad; //=new JRadioButton(Bundle.getMessage("Road"));
  QRadioButton* sortByModel; //=new JRadioButton(Bundle.getMessage("Model"));
  QRadioButton* sortByConsist; //=new JRadioButton(Bundle.getMessage("Consist"));
  QRadioButton* sortByLocation; //=new JRadioButton(Bundle.getMessage("Location"));
  QRadioButton* sortByDestination; //=new JRadioButton(Bundle.getMessage("Destination"));
  QRadioButton* sortByTrain; //=new JRadioButton(Bundle.getMessage("Train"));
  QRadioButton* sortByMoves; //=new JRadioButton(Bundle.getMessage("Moves"));
  QRadioButton* sortByBuilt; //=new JRadioButton(Bundle.getMessage("Built"));
  QRadioButton* sortByOwner; //=new JRadioButton(Bundle.getMessage("Owner"));
  QRadioButton* sortByValue; //=new JRadioButton(Setup.getValueLabel());
  QRadioButton* sortByRfid; //=new JRadioButton(Setup.getRfidLabel());
  QRadioButton* sortByLast; //=new JRadioButton(Bundle.getMessage("Last"));
  QButtonGroup* group; //=new ButtonGroup();

  // major buttons
  QPushButton* addButton; //=new JButton(Bundle.getMessage("Add"));
  QPushButton* findButton; //=new JButton(Bundle.getMessage("Find"));
  QPushButton* saveButton; //=new JButton(Bundle.getMessage("Save"));

  JTextField* findEngineTextBox; //=new JTextField(6);
  EngineEditFrame* f;// = null;
  Logger* log;

 };
}
#endif // ENGINESTABLEFRAME_H
