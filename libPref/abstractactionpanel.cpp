#include "abstractactionpanel.h"
#include <QBoxLayout>
#include <QPushButton>
#include "flowlayout.h"
#include "instancemanager.h"
#include <QComboBox>
#include "createbuttonmodel.h"
#include "abstractactionmodel.h"
#include "jframe.h"
#include "createbuttonmodel.h"


//AbstractActionPanel::AbstractActionPanel(QWidget *parent) :
//    PreferencesPanel(parent)
//{
//}
/**
 * Provide an abstract GUI for configuring use of Actions.
 * <P>
 * A {@link PerformActionPanel}/{@link PerformActionModel} object pair invokes a
 * Swing Action when the program is started.
 * <P>
 * A {@link CreateButtonPanel}/{@link CreateButtonModel} object pair creates a
 * new GUI button when the program is started.
 * <P>
 *
 * <P>
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 28432 $
 */
// abstract /*public*/ class AbstractActionPanel extends QWidget* implements PreferencesPanel {


/*public*/ AbstractActionPanel::AbstractActionPanel(QString addButtonKey, QString removeButtonKey,QWidget *parent)
    : PreferencesPanel(parent)
{
 self = this;
 dirty = false;
 log = new Logger("AbstractActionPanel");
 this->removeButtonKey = removeButtonKey;

 //rb = ResourceBundle.getBundle("apps.AppsConfigBundle");

 // GUi is a series of horizontal entries
 //QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 // add existing items
 QPushButton* addButton = new QPushButton(/*tr*/(addButtonKey));
 QWidget* panel = new QWidget();  // button is a horizontal item too; expands to fill BoxLayout
 FlowLayout* panelLayout;
 panel->setLayout(panelLayout = new FlowLayout());
 panelLayout->addWidget(addButton);
 thisLayout->addWidget(panel);
//    addButton.addActionListener((ActionEvent e) -> {
//        addItem();
//    });
 connect(addButton, SIGNAL(clicked()), this, SLOT(addItem()));

 // are there any existing objects from reading existing config?
 int n = rememberedObjects().size();
 for (int i = 0; i < n; i++)
 {
  AbstractActionModel* m = (AbstractActionModel*) rememberedObjects().at(i);
  thisLayout->addWidget(new Item(m,this));
  this->dirty = false; // reset to false - setting the model in the Item ctor sets this true
 }
// ((CreateButtonModel*)InstanceManager::getDefault("CreateButtonModel"))->addPropertyChangeListener(PropertyChangeEvent* e);
//            -> {
//        if (e.getPropertyName().equals("length")) {
//            Component[] l = getComponents();
//            for (Component m : l) {
//                if ((m != null) && (m instanceof AbstractActionPanel.Item)) {
//                    ((Item) m).updateCombo();
//                }
//            }
//        }
//    });

 CreateButtonModel* createButtonModel = (CreateButtonModel*)InstanceManager::getDefault("CreateButtonModel");
 connect(createButtonModel->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}
// /*abstract*/ List<?> rememberedObjects();

/*protected*/ void AbstractActionPanel::addItem()
{
 /*synchronized (self) */
 {
  thisLayout->addWidget(new Item(removeButtonKey, this));
  //validate();
  update();
  if (getTopLevelAncestor() != NULL)
  {
   ((JFrame*) getTopLevelAncestor())->pack();
  }
  this->dirty = true;
 }
}
void AbstractActionPanel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length"))
 {
  QObjectList l = children();
  foreach (QObject* m, l)
  {
   //if ((m != null) && (m instanceof AbstractActionPanel::Item)) {
   if(m != NULL && qobject_cast<Item*>(m)!=NULL)
   {
    ((Item*) m)->updateCombo();
   }
  }
 }
}

/*abstract*/ AbstractActionModel* AbstractActionPanel::getNewModel() { return NULL;}

//@Override
/*public*/ QString AbstractActionPanel::getPreferencesItem() {
    return "STARTUP"; // NOI18N
}

//@Override
/*public*/ QString AbstractActionPanel::getPreferencesItemText() {
    return tr("Start Up"); // NOI18N
}

//@Override
/*public*/ QWidget* AbstractActionPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool AbstractActionPanel::isPersistant() {
    return true;
}

//@Override
/*public*/ QString AbstractActionPanel::getPreferencesTooltip() {
        return "";
}

//@Override
/*public*/ void AbstractActionPanel::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/ bool AbstractActionPanel::isDirty() {
    return this->dirty;
}

//@Override
/*public*/ bool AbstractActionPanel::isRestartRequired() {
    return this->isDirty();
}

///*public*/ class Item extends QWidget* implements ActionListener {

//    private static final long serialVersionUID = -2499516926618516181L;
//    JButton removeButton = new JButton(tr(removeButtonKey));

Item::Item(QString removeButtonKey, AbstractActionPanel* panel)
    : QWidget(NULL)
{
 this->removeButtonKey = removeButtonKey;
 common(panel);
}
void Item::common(AbstractActionPanel* panel)
{
 this->panel = panel;
 model = NULL;
 log = new Logger("Item");
 //this->removeButtonKey = removeButtonKey;
 removeButton = new QPushButton((removeButtonKey));
 FlowLayout* thisLayout;
 setLayout(thisLayout = new FlowLayout());
 thisLayout->addWidget(removeButton);
 //removeButton->addActionListener(this);
 connect(removeButton, SIGNAL(clicked()), this, SLOT(actionPerformed()));
 // create the list of possibilities
 selections = new QComboBox();
 selections->addItems(AbstractActionModel::nameList());
 thisLayout->addWidget(selections);
//    selections.addItemListener((ItemEvent e) -> {
//        if (e.getStateChange() == ItemEvent.SELECTED) {
//            dirty = true;
//        }
//    });
 connect(selections, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_selections_currentIndexChanged(QString)));
}
void Item::On_selections_currentIndexChanged(QString)
{
 //if (egetStateChange() == ItemEvent.SELECTED) {
 panel->dirty = true;
}

Item::Item(AbstractActionModel* m, AbstractActionPanel* panel)
    : QWidget(NULL)
{
 common(panel);
 model = m;
 selections->setCurrentIndex(selections->findText(m->getName()));
}


void Item::updateCombo()
{
 QString current = selections->currentText();
 selections->clear();
 QStringList items = AbstractActionModel::nameList();
 foreach (QString item, items)
 {
  selections->addItem(item);
 }
 //if (Arrays.asList(items).contains(current))
 if(items.contains(current))
 {
  selections->setCurrentIndex(selections->findText(current));
 }
 else
 {
  log->info("Item " + current + " has been removed as it is no longer a valid option");
  actionPerformed(NULL);
 }
}

/*public*/ AbstractActionModel* Item::updatedModel()
{
 if (model == NULL)
 {
  model = panel->getNewModel();
 }
 model->setName( selections->currentText());
    return model;
}

//@Override
/*public*/ void Item::actionPerformed(ActionEvent* /*e*/)
{
    /*synchronized (self) */
 {
  // remove this item from display
  QWidget* parent = (QWidget*)this->parent();  // have to do this before remove
  QWidget* topParent = panel->getTopLevelAncestor();
  parent->layout()->removeWidget(this);
//  parent.validate();
  if (topParent != NULL)
  {
   ((JFrame*) topParent)->pack();
  }
  parent->update();
  // unlink to encourage garbage collection
  //removeButton->removeActionListener(this);
  disconnect(removeButton);
  model = NULL;
  panel->dirty = true;
 }
}
/**
 * Returns the top-level ancestor of this component (either the
 * containing <code>Window</code> or <code>Applet</code>),
 * or <code>null</code> if this component has not
 * been added to any container.
 *
 * @return the top-level <code>Container</code> that this component is in,
 *          or <code>null</code> if not in any container
 */
/*public*/ QWidget* AbstractActionPanel::getTopLevelAncestor()
{
 for(QObject* p = this; p != NULL; p = p->parent())
 {
  //if(p instanceof Window || p instanceof Applet)
     if(qobject_cast<JFrame*>(p)!=NULL)
  {
   return (QWidget*)p;
  }
 }
 return NULL;
}
