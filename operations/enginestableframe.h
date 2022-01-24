#ifndef ENGINESTABLEFRAME_H
#define ENGINESTABLEFRAME_H

#include "operationsframe.h"
#include "propertychangelistener.h"
#include <QRadioButton>

class JActionEvent;
class QButtonGroup;
class QLabel;
class QSortFilterProxyModel;
class JButton;
class JTextField;
class JTable;
namespace Operations
{
 class RollingStock;
 class EngineEditFrame;
 class EngineManager;
 class EnginesTableModel;
 class EnginesTableFrame : public OperationsFrame, public PropertyChangeListener
 {
  Q_OBJECT
 Q_INTERFACES(PropertyChangeListener)
  public:
  explicit EnginesTableFrame(QWidget *parent = 0);
  /*public*/ QList<RollingStock*>* getSortByList();
  /*public*/ QString getClassName() override;
   QObject* self() override {return (QObject*)this; }

 signals:

 public slots:
  /* public*/ void addButton_clicked();
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void radioButtonActionPerformed(QWidget* source) override;
  /*public*/ void buttonActionPerformed(QWidget* source) override;

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
  QRadioButton* sortByDcc = new QRadioButton(tr("DCC Address"));

  QRadioButton* sortByLast; //=new JRadioButton(Bundle.getMessage("Last"));
  QButtonGroup* group; //=new ButtonGroup();

  // major buttons
  JButton* addButton; //=new JButton(Bundle.getMessage("Add"));
  JButton* findButton; //=new JButton(Bundle.getMessage("Find"));
  JButton* saveButton; //=new JButton(Bundle.getMessage("Save"));

  JTextField* findEngineTextBox; //=new JTextField(6);
  EngineEditFrame* f;// = null;
  Logger* log;

 };
}
#endif // ENGINESTABLEFRAME_H
