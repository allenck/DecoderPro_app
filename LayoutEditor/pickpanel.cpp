#include "pickpanel.h"
#include "jtextfield.h"
#include <QTableView>
#include "picklistmodel.h"
#include <QVBoxLayout>
#include <QLabel>
#include "changeevent.h"
#include "addnewdevicepanel.h"
#include "actionlistener.h"
#include <QDrag>
#include <QMimeData>
#include <QDragMoveEvent>

//PickPanel::PickPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Tabbed Container for holding pick list tables
 *
 * @author Pete Cressman  Copyright (c) 2010
 */

//public class PickPanel extends JPanel implements ListSelectionListener, ChangeListener {

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2")
/*public*/ PickPanel::PickPanel(QList<PickListModel*> models, QWidget *parent) : QWidget(parent)
{
 _tabPane = new QTabWidget();
 _models =  QList<PickListModel*>();
    //System.arraycopy(models, 0, _models, 0, models.length);
 for (int i=0; i<models.length(); i++)
 {
  _models.append(models.at(i));
  QTableView* table = models.at(i)->makePickTable();
  QWidget* p = new QWidget();
  p->setLayout(/*new BorderLayout(5,5)*/new QVBoxLayout());
  //p->layout()->addWidget(new QLabel(models.at(i)->getName()/*, SwingConstants.CENTER), BorderLayout.NORTH*/));
  //p->layout()->addWidget(new JScrollPane(table), BorderLayout.CENTER);
  p->layout()->addWidget(table);
  _tabPane->addTab(p, models.at(i)->getName());
   ROW_HEIGHT = table->rowHeight(0);
   connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(onRowClicked(QModelIndex)));
 }
 setLayout(/*new BorderLayout(5,5)*/new QVBoxLayout());
 layout()->addWidget(_tabPane/*, BorderLayout.CENTER*/);
 layout()->addWidget(makeAddToTablePanel()/*, BorderLayout.SOUTH*/);
// _tabPane->addChangeListener((ChangeListener*)this);
}
void PickPanel::onRowClicked(QModelIndex index)
{
 int row =index.row();
 if(index.column() > 1) return;
 QString name = index.data().toString();
 if(name == "") return;
 QDrag* dr = new QDrag(this);
 QMimeData* data = new QMimeData;
 data->setText(name);
 dr->setMimeData(data);
 dr->start();
}
/*private*/ QWidget* PickPanel::makeAddToTablePanel()
{
 _sysNametext = new JTextField();
 _userNametext = new JTextField();
    ItActionListener* listener = new ItActionListener(this);
//    {
//            public void actionPerformed(ActionEvent a) {
//                addToTable();
//            }
//        };
    PPCancelListener* cancelListener = new PPCancelListener(this);
 _addPanel = new AddNewDevicePanel(
                 _sysNametext, _userNametext, "Add To Table", listener, cancelListener);
 _cantAddPanel = new QWidget();
    _cantAddPanel->setLayout(/*new BorderLayout(5,5)*/new QVBoxLayout);
 _cantAddPanel->layout()->addWidget(new QLabel("Cannot add new items to this pick panel"/*, SwingConstants.CENTER), BorderLayout.NORTH*/));
 _cantAddPanel->layout()->addWidget(new QLabel("Open another tool to add an item."/*, SwingConstants.CENTER), BorderLayout.SOUTH*/));
    QWidget* p = new QWidget();
    p->setLayout(new QVBoxLayout());
    p->layout()->addWidget(_addPanel);
    p->layout()->addWidget(_cantAddPanel);
    stateChanged(NULL);
    int width = qMax(100, this->size().width());
    _sysNametext->setMinimumSize( QSize(width, _sysNametext->getPreferredSize().height()));
    return p;
}
ItActionListener::ItActionListener(PickPanel* self)
{
 this->self = self;
}
void ItActionListener::actionPerformed(JActionEvent* a)
{
  self->addToTable();
}
PPCancelListener::PPCancelListener(PickPanel *self)
{
 this->self = self;
}
void PPCancelListener::actionPerformed()
{
 self->close();
}

void PickPanel::addToTable() {
    QString sysname = _sysNametext->text();
    if (sysname != "" && sysname.length() > 1) {
        PickListModel* model = _models.at(_tabPane->currentIndex());
        QString uname = _userNametext->text();
        if (uname!="" && uname.trimmed().length()==0) {
            uname = "";
        }
        NamedBean* bean = model->addBean(sysname, uname);
        if (bean!=NULL) {
            int setRow = model->getIndexOf(bean);
//            model->getTable()->setRowSelectionInterval(setRow, setRow);
            QWidget* p = (QWidget*)_tabPane->/*getSelectedComponent();*/currentWidget();
//            ((JScrollPane)p.getComponent(1)).getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
            _sysNametext->setText("");
        }
    }
}

/*public*/ void PickPanel::stateChanged(ChangeEvent* e) {
    PickListModel* model = _models.at(_tabPane->currentIndex());
    if (model->canAddBean()) {
        _cantAddPanel->setVisible(false);
        _addPanel->setVisible(true);
    }
    else {
        _addPanel->setVisible(false);
        _cantAddPanel->setVisible(true);
    }
}
//void PickPanel::dragEnterEvent(QDragEnterEvent *event)
//{
// // Set the drop action to be the proposed action.
// event->acceptProposedAction();
//}

//void PickPanel::dragMoveEvent(QDragMoveEvent *de )
//{
//    // The event needs to be accepted here
//    de->accept();

//}

#if 0
/*public*/ void valueChanged(ListSelectionEvent* e) {
    if (log.isDebugEnabled()) log.debug("ListSelectionEvent from "+e.getSource().getClass().getName()
                                        +" idx= "+e.getFirstIndex());
}
#endif
