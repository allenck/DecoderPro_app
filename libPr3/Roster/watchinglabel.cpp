#include "watchinglabel.h"
#include <QShowEvent>

//WatchingLabel::WatchingLabel(QWidget *parent) :
//    QLabel(parent)
//{
//}
/**
 * JLabel that watches another component, setting itself
 * invisible if when the other component is
 *
 * @author			Bob Jacobsen   Copyright (C) 2010
 * @version			$Revision: 18543 $
 *
 */
// /*public*/ class WatchingLabel extends javax.swing.JLabel  {
/*public*/ WatchingLabel::WatchingLabel(QString name, QWidget *c, QWidget *parent) : JLabel(name, parent)
{
    //super(name);
    setText(name);
    comp = c;
    self = this;

//    comp.addComponentListener(new java.awt.event.ComponentListener(){
//        /*public*/ void componentHidden(java.awt.event.ComponentEvent e) {
//            self.setVisible(false);
//        }

//        /*public*/ void componentShown(java.awt.event.ComponentEvent e) {
//            self.setVisible(true);
//        }

//        /*public*/ void componentMoved(java.awt.event.ComponentEvent e) {}

//        /*public*/ void componentResized(java.awt.event.ComponentEvent e) {}

//    });

    // set initial status
    //self->setVisible(c->isVisible());
}


