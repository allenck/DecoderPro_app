#ifndef MULTIICONEDITOR_H
#define MULTIICONEDITOR_H

#include <QObject>
#include"namedicon.h"
#include <QWidget>
#include "catalogpane.h"
#include <QPushButton>

class QSignalMapper;
class QGridLayout;
class CatalogPane;
class MultiIconEditor : public QWidget
{
    Q_OBJECT
public:
    //explicit MultiIconEditor(QObject *parent = 0);
    /*public*/ MultiIconEditor(int nIcons, QWidget* parent = 0);
    /*public*/ void setIcon(int iconNum, QString label, QString name);
    /**
     * Returns a new NamedIcon object for your own use.
     * @param iconNum 0 to n-1
     * @return Unique object
     */
    /*public*/ NamedIcon* getIcon(int iconNum) ;
    QString getIconName(int iconNum);
    /*public*/ void complete();
    /**
     * Clean up when its time to make it all go away
     */
    /*public*/ void dispose();
    CatalogPane* catalog();
signals:
    
public slots:
    void iconButton_clicked(int iconNum);
private:
    QVector<NamedIcon*>* iconList;// = new QList<NamedIcon*>();
    QVector<QString>* iconNameList;
    CatalogPane* _catalog;
    QVector<QPushButton*>* buttonList;
    QGridLayout* g;
    QSignalMapper* mapper;

    friend class IconButton;
};

/*private*/ class IconButton : public QPushButton
{
 Q_OBJECT
public:
 IconButton(int index, QIcon init, MultiIconEditor* parent) : QPushButton(init, "")
 {  // init icon passed to avoid ref before ctor complete
   //super(init);
  savedIndex = index;
  this->parent = parent;
  setIcon(init);
//                addActionListener( new ActionListener() {
//                        public void actionPerformed(ActionEvent a) {
//                            pickIcon();
//                        }
//                    }
//                                            );
 connect(this, SIGNAL(clicked()), this, SLOT(pickIcon()));
 }
 int savedIndex;
 MultiIconEditor* parent;
public slots:
void pickIcon() {
    NamedIcon* newIcon = parent->_catalog->getSelectedIcon();
    if(newIcon == NULL)
     return;
    parent->iconList->replace(savedIndex, newIcon);
    parent->buttonList->at(savedIndex)->setIcon(QIcon(newIcon->getURL()));
 }
};

#endif // MULTIICONEDITOR_H
