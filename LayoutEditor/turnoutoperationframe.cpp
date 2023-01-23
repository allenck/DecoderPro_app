#include "turnoutoperationframe.h"
#include "turnoutoperationconfig.h"
#include "turnoutoperationmanager.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include "propertychangeevent.h"
#include <QPushButton>
#include "QMessageBox"

/**
 * @author John Harper
 *
 */
// /*public*/ class TurnoutOperationFrame extends JDialog {


/*public*/ TurnoutOperationFrame::TurnoutOperationFrame(QWidget* parent) : QDialog(parent)
{
 //super(parent, "Turnout Operation Editor");
 _self = this;
 currentConfig = NULL;
 currentOperation = NULL;
 setWindowTitle(tr("Turnout Operation Editor"));
 QWidget* contentPane = /*getContentPane()*/this;
 contentPane->setLayout(new QVBoxLayout);
 resize(400,150);
 //Box outerBox = Box.createVerticalBox();
 QWidget* outerBox = new QWidget();
 outerBox->setLayout(new QVBoxLayout);
 contentPane->layout()->addWidget(outerBox);
 tabPane = new QTabWidget();
// tabPane.addChangeListener(new ChangeListener() {
//        /*public*/ void stateChanged(ChangeEvent e) {
//            self.changeTab();
//        }
//    });
 outerBox->layout()->addWidget(tabPane);
 //Box bottomBox = Box.createHorizontalBox();
 QWidget* bottomBox = new QWidget();
 bottomBox->setLayout(new QHBoxLayout);
 //bottomBox->layout()->addWidget(Box.createHorizontalGlue());
 QPushButton* okButton = new QPushButton(tr("OK"));
//    okButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    self.doOK();
//                }
//            }
//        );
 connect(okButton, SIGNAL(clicked()), this, SLOT(doOK()));
 bottomBox->layout()->addWidget(okButton);
 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//        setVisible(false);
//                }
//            }
//        );
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
 bottomBox->layout()->addWidget(cancelButton);
 QPushButton* deleteButton = new QPushButton(tr("Delete"));
//    deleteButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    self.doDelete();
//                }
//            }
//        );
 connect(deleteButton, SIGNAL(clicked()), this, SLOT(doDelete()));
 bottomBox->layout()->addWidget(deleteButton);
 outerBox->layout()->addWidget(bottomBox);
 populateTabs();
//    TurnoutOperationManager.getInstance().addPropertyChangeListener(new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            if (e.getPropertyName().equals("Content")) {
//                populateTabs();
//            }
//        }
//    });
 TurnoutOperationManager* mgr = TurnoutOperationManager::getInstance();
 TurnoutOperationManager::getInstance()->addPropertyChangeListener((PropertyChangeListener*)this);
 //connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if (tabPane->count()>0)
 {
  setVisible(true);
 }
}
void TurnoutOperationFrame::propertyChange(PropertyChangeEvent *e)
{
 if (e->getPropertyName()==("Content"))
 {
  populateTabs();
 }
}

/*private*/ void TurnoutOperationFrame::doOK()
{
 if (currentOperation != NULL)
 {
  currentConfig->endConfigure();
 }
 setVisible(false);
}

/*private*/ void TurnoutOperationFrame::doDelete()
{
 QString query = "";
 if (currentOperation != NULL && !currentOperation->isDefinitive())
 {
  if (currentOperation->isInUse())
  {
   query = "Operation "+currentOperation->getName()+" is in use\n"+
                    "Turnouts using it will revert to the global default\n";
  }
//  if (JOptionPane.showConfirmDialog(this, query+"Delete operation "+currentOperation.getName()+"?",
//                "Confirm delete", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
  if(QMessageBox::question(this, tr("confirm delete"), query+"Delete operation "+currentOperation->getName()+"?",QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
  {
   currentOperation->dispose();
   populateTabs();
  }
 }
}

/*private*/ void TurnoutOperationFrame::populateTabs()
{
 QList<TurnoutOperation*> operations = TurnoutOperationManager::getInstance()->getTurnoutOperations();
 QWidget* firstPane = NULL;
 tabPane->clear();
 QVector<TurnoutOperation*> definitiveOperations =  QVector<TurnoutOperation*>(/*10*/);
 QVector<TurnoutOperation*> namedOperations =  QVector<TurnoutOperation*>(/*50*/);
 for (int i=0; i<operations.length(); ++i)
 {
  if (operations.at(i)->isDefinitive())
  {
   definitiveOperations.append(operations.at(i));
  }
  else if (!operations.at(i)->isNonce())
  {
   namedOperations.append(operations.at(i));
  }
 }
//    java.util.Collections.sort(definitiveOperations);
//    java.util.Collections.sort(namedOperations);
 TurnoutOperationConfig* pane;
 TurnoutOperation* op;
 int iTab;
 for (int j=0; j<definitiveOperations.size(); ++j)
 {
  op = definitiveOperations.at(j);
  pane = TurnoutOperationConfig::getConfigPanel(op);
  if (pane != NULL)
  {
   if (firstPane == NULL)
   {
    firstPane = pane;
   }
   iTab = tabPane->addTab(pane, op->getName());
   if (op->getName()==(previousSelectionName))
   {
    tabPane->setCurrentWidget(pane);
   }
  }
 }
 for (int k=0; k<namedOperations.size(); ++k)
 {
  op = namedOperations.at(k);
  pane = TurnoutOperationConfig::getConfigPanel(op);
  if (pane != NULL)
  {
   iTab = tabPane->addTab(pane, op->getName());
   if (op->getName()==previousSelectionName)
   {
    tabPane->setCurrentWidget(pane);
   }
  }
 }
 if (tabPane->currentWidget()==NULL && firstPane!=NULL)
 {
  tabPane->setCurrentWidget(firstPane);
 }
 changeTab();
}

/*private*/ void TurnoutOperationFrame::changeTab()
{
 currentConfig = (TurnoutOperationConfig*)tabPane->currentWidget();
 if (currentConfig == NULL)
 {
  currentOperation = NULL;
  previousSelectionName = "";
 }
 else
 {
  currentOperation = currentConfig->getOperation();
  previousSelectionName = currentOperation->getName();
 }
}
