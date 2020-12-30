#include "performfilepanel.h"
#include <QPushButton>
#include <flowlayout.h>
#include "performfilemodel.h"
#include "xmlfile.h"
#include <QLabel>
#include "jfilechooser.h"
#include "file.h"
#include "jframe.h"


//PerformFilePanel::PerformFilePanel(QWidget *parent) :
//    PreferencesPane(parent)
//{
//}
/**
 * Provide a GUI for configuring PerformFileModel objects.
 * <P>
 * A PerformFileModel object loads a file when the program is started.
 * <P>
 *
 * <P>
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 28056 $
 * @see apps.PerformFileModel
 */
// /*public*/ class PerformFilePanel extends QWidget* implements PreferencesPanel {

/**
 *
 */
//private static final long serialVersionUID = 5019870518438422370L;
//QWidget* self;  // used for synchronization
///*protected*/ ResourceBundle rb;

/*public*/ PerformFilePanel::PerformFilePanel(QWidget *parent)
    : QWidget(parent) {
    //self = this;
    dirty = false;
    fc = XmlFile::userFileChooser("XML files", "xml");

    //rb = ResourceBundle.getBundle("apps.AppsConfigBundle");

    // GUi is a series of horizontal entries
    setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

    // add existing items
    QPushButton* addButton = new QPushButton(tr("Add File"));
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
    int n = PerformFileModel::rememberedObjects().size();
    for (int i = 0; i < n; i++) {
        PerformFileModel* m = PerformFileModel::rememberedObjects().at(i);
        thisLayout->addWidget(new PFItem(m, this));
    }
}

/*protected*/ void PerformFilePanel::addItem()
{
 /*synchronized (self) */
 {
  PFItem* i = new PFItem(this);
  if (i->model->getFileName() == "")
  {
   return;  // cancelled
  }
  thisLayout->addWidget(i);
  //validate();
  if (window() != NULL)
  {
   ((JFrame*) window())->pack();
  }
  this->dirty = true;
 }
}


//@Override
/*public*/ QString PerformFilePanel::getPreferencesItem() {
    return "STARTUP"; // NOI18N
}

//@Override
/*public*/ QString PerformFilePanel::getPreferencesItemText() {
    return tr("StartUp"); // NOI18N
}

//@Override
/*public*/ QString PerformFilePanel::getTabbedPreferencesTitle() {
    return tr("Files"); // NOI18N
}

//@Override
/*public*/ QString PerformFilePanel::getLabelKey() {
    return tr("Select any files you'd like loaded when the program starts."); // NOI18N
}

//@Override
/*public*/ QWidget* PerformFilePanel::getPreferencesComponent() {
    return (QWidget*)this;
}

//@Override
/*public*/ bool PerformFilePanel::isPersistant() {
    return true;
}

//@Override
/*public*/ QString PerformFilePanel::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void PerformFilePanel::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/ bool PerformFilePanel::isDirty() {
    return this->dirty;
}

//@Override
/*public*/ bool PerformFilePanel::isRestartRequired() {
    return this->isDirty();
}

// /*public*/ class Item extends QWidget* implements ActionListener {

/**
 *
 */
//private static final long serialVersionUID = 9081562133732338951L;
//QPushButton* removeButton = new QPushButton(tr("ButtonFileRemove"));

PFItem::PFItem(PerformFilePanel* self)
    : QWidget()
{
    this->self = self;
    removeButton = new QPushButton(tr("Remove"));
    model = new PerformFileModel();
    FlowLayout* thisLayout;
    setLayout(thisLayout = new FlowLayout());

    thisLayout->addWidget(removeButton);
    //removeButton.addActionListener(this);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(actionPerformed()));
    // get the filename
    self->fc->showOpenDialog(NULL);

    selected = new QLabel(self->fc->getSelectedFile()->getAbsolutePath());
    model->setFileName(self->fc->getSelectedFile()->getAbsolutePath());
    thisLayout->addWidget(selected);
}

PFItem::PFItem(PerformFileModel* m, PerformFilePanel* self) : QWidget()
{
    this->self = self;
    removeButton = new QPushButton(tr("Remove"));
    model = new PerformFileModel();

    FlowLayout* thisLayout;
    setLayout(thisLayout = new FlowLayout());
    thisLayout->addWidget(removeButton);
    //removeButton.addActionListener(this);
    connect(removeButton, SIGNAL(clicked()), this, SLOT(actionPerformed()));
    model = m;
    selected = new QLabel(m->getFileName());
    thisLayout->addWidget(selected);
}

/*public*/ PerformFileModel* PFItem::getModel() {
    return model;
}

//@Override
/*public*/ void PFItem::actionPerformed(JActionEvent* /*e*/) {
    /*synchronized (self)*/ {
        // remove this item from display
        QWidget* parent = (QWidget*)this->parent();  // have to do this before remove
        QWidget* topParent = self->window();
        parent->layout()->removeWidget(this);
        //parent.validate();
        if (topParent != NULL) {
            ((JFrame*) topParent)->pack();
        }
        //parent.repaint();
        parent->update();
        // unlink to encourage garbage collection
        //removeButton.removeActionListener(this);
        disconnect(removeButton);
        model = NULL;
        self->dirty = true;
    }
}

/*public*/ QString PerformFilePanel::className() {return "PerformFilePanel";}
