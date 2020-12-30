#include "performscriptpanel.h"
#include <QBoxLayout>
#include <QPushButton>
#include <flowlayout.h>
#include "xmlfile.h"
#include "jfilechooser.h"
#include "file.h"
#include "performscriptmodel.h"
#include <QLabel>
#include "jframe.h"

//PerformScriptPanel::PerformScriptPanel(QWidget *parent) :
//  PreferencesPanel(parent)
//{
//}
#if 1
/**
 * Provide a GUI for configuring PerformScriptModel objects.
 * <P>
 * A PerformScriptModel object runs a script when the program is started.
 * <P>
 *
 * <P>
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 29245 $
 * @see apps.PerformScriptModel
 */
///*public*/ class PerformScriptPanel extends JPanel implements PreferencesPanel {

/**
 *
 */
//private static final long serialVersionUID = -5977442451170083348L;
//protected ResourceBundle rb;

/*public*/ PerformScriptPanel::PerformScriptPanel(QWidget *parent) :
  QWidget(parent)
{
 _self = this;
 dirty = false;

 fc = XmlFile::userFileChooser("Python script files (*.py *.pyq);; All files (*.*)", "py");


// rb = ResourceBundle.getBundle("apps.AppsConfigBundle");

 // GUi is a series of horizontal entries
 //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 thisLayout = new QVBoxLayout(this);

 // add existing items
 QPushButton* addButton = new QPushButton(tr("Python script files"));
 QWidget* pane1 = new QWidget();  // button is a horizontal item too; expands to fill BoxLayout
 //panel.setLayout(new FlowLayout());
 FlowLayout* pane1Layout = new FlowLayout(pane1);
 pane1Layout->addWidget(addButton);
 thisLayout->addWidget(pane1);
// addButton.addActionListener((ActionEvent e) -> {
//     addItem();
// });
 connect(addButton, SIGNAL(clicked()), this, SLOT(addItem()));

 // are there any existing objects from reading existing config?
 int n = PerformScriptModel::rememberedObjects().size();
 for (int i = 0; i < n; i++) {
     PerformScriptModel* m = PerformScriptModel::rememberedObjects().at(i);
     thisLayout->addWidget(new PSPItem(m, this));
 }
}

/*protected*/ void PerformScriptPanel::addItem()
{
    /*synchronized (self)*/
 {
  PSPItem* i = new PSPItem(this);
  if (i->model->getFileName() == NULL)
  {
   return;  // cancelled
  }
  thisLayout->addWidget(i);
  //revalidate();
  update();
  this->dirty = true;
 }
}

//@Override
/*public*/ QString PerformScriptPanel::getPreferencesItem() {
    return "STARTUP"; // NOI18N
}

//@Override
/*public*/ QString PerformScriptPanel::getPreferencesItemText() {
    return tr("Start Up"); // NOI18N
}

//@Override
/*public*/ QString PerformScriptPanel::getTabbedPreferencesTitle() {
    return tr("Scripts"); // NOI18N
}

//@Override
/*public*/ QString PerformScriptPanel::getLabelKey() {
    return tr("Select any scripts you'd like run when the program starts."); // NOI18N
}

//@Override
/*public*/ QWidget* PerformScriptPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool PerformScriptPanel::isPersistant() {
    return true;
}

//@Override
/*public*/ QString PerformScriptPanel::getPreferencesTooltip() {
    return NULL;
}

//@Override
/*public*/ void PerformScriptPanel::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/ bool PerformScriptPanel::isDirty() {
    return this->dirty;
}

//@Override
/*public*/ bool PerformScriptPanel::isRestartRequired() {
    return this->isDirty();
}

//@Override
/*public*/ bool PerformScriptPanel::isPreferencesValid() {
    return true; // no validity checking performed
}

///*public*/ class Item extends JPanel implements ActionListener {

//    /**
//     *
//     */
//    private static final long serialVersionUID = 773446142833490795L;
//    JButton removeButton = new JButton(rb.getString("ButtonScriptRemove"));

PSPItem::PSPItem(QWidget* parent) : QWidget(parent)
{
 removeButton = new QPushButton(tr("Remove"));

 model = new PerformScriptModel();
 //setLayout(new FlowLayout());
 FlowLayout* thisLayout = new FlowLayout(this);
 thisLayout->addWidget(removeButton);
 //removeButton.addActionListener(this);
 connect(removeButton, SIGNAL(clicked()), this, SLOT(actionPerformed()));
 // get the filename
 ((PerformScriptPanel*)parent)->fc->showOpenDialog(NULL);
 if (((PerformScriptPanel*)parent)->fc->getSelectedFile() == NULL)
 {
  return; // cancelled
 }
 selected = new QLabel(((PerformScriptPanel*)parent)->fc->getSelectedFile()->getAbsolutePath());
 model->setFileName(((PerformScriptPanel*)parent)->fc->getSelectedFile()->getAbsolutePath());
 thisLayout->addWidget(selected);
}

PSPItem::PSPItem(PerformScriptModel* m, QWidget* parent) : QWidget(parent)
{
 removeButton = new QPushButton(tr("Remove"));

 model = new PerformScriptModel();
 //setLayout(new FlowLayout());
 FlowLayout* thisLayout = new FlowLayout(this);
 thisLayout->addWidget(removeButton);
 //removeButton.addActionListener(this);
 connect(removeButton, SIGNAL(clicked()), this, SLOT(actionPerformed()));
 model = m;
 selected = new QLabel(m->getFileName());
 thisLayout->addWidget(selected);
}

/*public*/ PerformScriptModel* PSPItem::getModel()
{
 return model;
}

//@Override
/*public*/ void PSPItem::actionPerformed(JActionEvent* /*e*/)
{
 /*synchronized (self)*/
 {
  // remove this item from display
  QWidget* parent = (QWidget*)this->parent();  // have to do this before remove
  QWidget* topParent = /*this->getTopLevelAncestor*/window();
  parent->layout()->removeWidget(this);
  //parent->revalidate();
  if (topParent != NULL) {
      ((JFrame*) topParent)->adjustSize();
  }
  parent->repaint();
  // unlink to encourage garbage collection
  //removeButton->removeActionListener(this);
  disconnect(removeButton, SIGNAL(clicked()), this, SLOT(actionPerformed()));
  model = NULL;
  ((PerformScriptPanel*)parent)->dirty = true;
 }
}

/*public*/ QString PerformScriptPanel::className() {return "PerformScriptPanel";}

//};
#endif
