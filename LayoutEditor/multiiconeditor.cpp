#include "multiiconeditor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSignalMapper>

//MultiIconEditor::MultiIconEditor(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Provides a simple editor for selecting N NamedIcons, perhaps
 * for use in creating a panel icon.
 * <P>See {@link SensorIcon} for an item
 * that might want to have that type of information, and
 * {@link jmri.jmrit.display.panelEditor.PanelEditor}
 * for an example of how to use this.
 *
 * @author Bob Jacobsen  Copyright (c) 2003
 * @version $Revision: 17977 $
 * @see jmri.jmrit.display.SensorIcon
 * @see jmri.jmrit.display.panelEditor.PanelEditor
 * @see jmri.jmrit.catalog
 */

///*public*/ class MultiIconEditor extends JPanel {

//    JButton[] buttonList;

//    /*public*/ CatalogPane catalog = new CatalogPane();

/*public*/ MultiIconEditor::MultiIconEditor(int nIcons, QWidget* parent) : QWidget(parent)
{
 iconList = new QVector<NamedIcon*>(nIcons);
 iconNameList = new QVector<QString>(nIcons);

 this->setLayout(g = new QGridLayout());//, BoxLayout.Y_AXIS)));
 _catalog = new CatalogPane(true);
 buttonList = new QVector<QPushButton*>(nIcons);
 mapper = new QSignalMapper();
 connect(mapper, SIGNAL(mapped(int)), this, SLOT(iconButton_clicked(int)));
}

/*public*/ void MultiIconEditor::setIcon(int iconNum, QString label, QString name)
{
//    iconList[iconNum] = new NamedIcon(name, name);
 iconList->replace(iconNum, new NamedIcon(name, name) );
 iconNameList->replace(iconNum, label);
 // make a button to change that icon
 QPushButton* j = new IconButton(iconNum, QIcon(iconList->at(iconNum)->getURL()), this);
 j->setToolTip(iconList->at(iconNum)->getName());
 buttonList->replace(iconNum, j);
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(j->sizePolicy().hasHeightForWidth());
 j->setSizePolicy(sizePolicy);
 mapper->setMapping(j,iconNum);
 connect(j, SIGNAL(clicked()), mapper, SLOT(map()));

 // and add it to this panel
 QWidget* p = new QWidget();
 p->setLayout(new  QHBoxLayout());
 p->layout()->addWidget(new QLabel(label));
 p->layout()->addWidget(j);
 g->addWidget(p, iconNum/2, iconNum%2);
}
void MultiIconEditor::iconButton_clicked(int iconNum)
{
 NamedIcon* icon = catalog()->getSelectedIcon();
 if(icon != NULL)
 {
  buttonList->at(iconNum)->setIcon(QIcon(QPixmap::fromImage(icon->getImage())));
  iconList->replace(iconNum, icon);
  iconNameList->replace(iconNum, icon->getName());
 }
}

/**
 * Returns a new NamedIcon object for your own use.
 * @param iconNum 0 to n-1
 * @return Unique object
 */
/*public*/ NamedIcon* MultiIconEditor::getIcon(int iconNum) {
   return new NamedIcon(iconList->at(iconNum));
  //return iconList->at(iconNum);
}
QString MultiIconEditor::getIconName(int iconNum)
{
    return iconNameList->at(iconNum);
}

/*public*/ void MultiIconEditor::complete()
{
    // add the catalog, so icons can be selected
 g->addWidget(_catalog, iconList->count()+1,0,1,2);
}

CatalogPane* MultiIconEditor::catalog()
{
 return _catalog;
}

#if 0

    private class IconButton extends JButton {
        IconButton(int index, Icon init) {  // init icon passed to avoid ref before ctor complete
            super(init);
            savedIndex = index;
            addActionListener( new ActionListener() {
                    /*public*/ void actionPerformed(ActionEvent a) {
                        pickIcon();
                    }
                }
                                        );
        }

        int savedIndex;

        void pickIcon() {
            NamedIcon newIcon = catalog.getSelectedIcon();
            iconList[savedIndex] = newIcon;
            buttonList[savedIndex].setIcon(newIcon);
        }
    }
#endif
/**
 * Clean up when its time to make it all go away
 */
/*public*/ void MultiIconEditor::dispose() {
    // clean up GUI aspects
//        this.removeAll();
    iconList = NULL;
//        buttonList = null;
//        catalog = null;
}

