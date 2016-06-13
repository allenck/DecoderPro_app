#include "reporteritempanel.h"
#include "QBoxLayout"
#include "itempalette.h"
#include "editor.h"
#include "flowlayout.h"
#include "reportericon.h"
#include "dataflavor.h"
#include <QTableView>
#include <QGroupBox>

//ReporterItemPanel::ReporterItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
///*public*/ class ReporterItemPanel extends TableItemPanel {

/*public*/ ReporterItemPanel::ReporterItemPanel(JmriJFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor* editor, QWidget *parent) : TableItemPanel(parentFrame, type, family, model, editor,parent){
        //super(parentFrame, type, family, model, editor);
    log = new Logger("ReporterItemPanel");
    }

/*public*/ void ReporterItemPanel::init()
{
 if (!_initialized)
 {
  layout()->addWidget(initTablePanel(_model, _editor));        // NORTH Panel
  initIconFamiliesPanel();
  layout()->addWidget(_iconFamilyPanel);
 }
}

/*protected*/ QWidget* ReporterItemPanel::instructions() {
    QWidget* blurb = new QWidget();
    QVBoxLayout* layout;
    blurb->setLayout(layout = new QVBoxLayout(blurb/*, BoxLayout.Y_AXIS*/));
    //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
    layout->addStrut(ItemPalette::STRUT_SIZE);
    blurb->layout()->addWidget(new JLabel(tr("To Add an Icon to your control panel:")));
    blurb->layout()->addWidget(new JLabel(tr("--drag an icon from the display panel below to your control panel")));
    //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
    layout->addStrut(ItemPalette::STRUT_SIZE);
    QWidget*  panel = new QWidget();
    panel->setLayout(new FlowLayout);
    panel->layout()->addWidget(blurb);
    return panel;
}

/*protected*/ void ReporterItemPanel::initIconFamiliesPanel() {
    _iconFamilyPanel = new QWidget();
    _iconFamilyPanel->setLayout(new QVBoxLayout(_iconFamilyPanel/*, QVBoxLayout.Y_AXIS*/));
    if (!_update) {
        _iconFamilyPanel->layout()->addWidget(instructions());
    }
    makeDndIconPanel(NULL, NULL);

    _iconFamilyPanel->layout()->addWidget(_dragIconPanel);
}

/*protected*/ void ReporterItemPanel::makeDndIconPanel(QHash<QString, NamedIcon*>* iconMap, QString displayKey)
{
 if (_update)
 {
  return;
 }
 _reporter = new ReporterIcon(_editor);
 QGroupBox*  panel = new QGroupBox();
 QString borderName = tr("Drag to Panel");
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 panel->setLayout(new QHBoxLayout);
 panel->setTitle(borderName);
 panel->setStyleSheet(gbStyleSheet);
 QWidget*  comp;
 DataFlavor* flavor;
 try {
     //comp = getDragger(flavor = new DataFlavor(Editor::POSITIONABLE_FLAVOR));
     comp = getDragger(flavor = new DataFlavor(_reporter,"ReporterIcon"));
     flavor->setMimeTypeParameter("reporter", _reporter->getName());
     comp->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 } catch (ClassNotFoundException cnfe) {
     //cnfe.printStackTrace();
     comp = new QWidget();
 }
 comp->setLayout(new FlowLayout);
 comp->layout()->addWidget(_reporter);
 panel->layout()->addWidget(comp);
 //panel.validate();
 int width = qMax(100, panel->sizeHint().width());
 panel->setMinimumSize( QSize(width, panel->minimumSize().height()));
 panel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 _dragIconPanel = panel;
 _dragIconPanel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
}

/**
*  ListSelectionListener action from table
*/
/*public*/ void ReporterItemPanel::valueChanged(ListSelectionEvent* /*e*/)
{
 if (_table == NULL)
 {
  return;
 }
 int row = _table->currentIndex().row();
 if (log->isDebugEnabled()) log->debug("Table valueChanged: row= "+QString::number(row));
 if (row >= 0)
 {
  if (_updateButton!=NULL)
  {
   _updateButton->setEnabled(true);
   _updateButton->setToolTip("");
  }
  NamedBean* bean = getNamedBean();
  _reporter->setReporter(bean->getDisplayName());
 }
 else
 {
  if (_updateButton!=NULL)
  {
   _updateButton->setEnabled(false);
   _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the panel"));
  }
 }
 //validate();
}

/*protected*/ RIconDragJComponent* ReporterItemPanel::getDragger(DataFlavor* flavor)
{
 return new RIconDragJComponent(flavor, _reporter->getPreferredSize(), this);
}

///*protected*/ class RIconDragJComponent extends DragJComponent {

/*public*/ RIconDragJComponent::RIconDragJComponent(DataFlavor* flavor, QSize dim, ReporterItemPanel* self) :DragJComponent(flavor, dim,self){
        //super(flavor, dim);
    this->self = self;
    }
/*public*/ QObject* RIconDragJComponent::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
 if (!isDataFlavorSupported(flavor))
 {
  return NULL;
 }
 NamedBean* bean = self->getNamedBean();
 if (bean==NULL)
 {
  self->log->error("IconDragJLabel.getTransferData: NamedBean is NULL!");
  return NULL;
 }

 ReporterIcon* r = new ReporterIcon(self->_editor);
 r->setReporter(bean->getDisplayName());
 r->setLevel(Editor::REPORTERS);
 return r;
}

/*public*/ QString RIconDragJComponent::mimeData()
{
 if(self->_table->currentIndex().isValid())
 {
  QModelIndex index = self->_table->model()->index( self->_table->currentIndex().row(), 0);
  QString name = index.data(Qt::DisplayRole).toString();
  _dataFlavor->setMimeTypeParameter("reporter", name);
  return _dataFlavor->toString();
 }
 return "";
}

//};
