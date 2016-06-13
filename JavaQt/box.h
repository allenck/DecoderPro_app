#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include <QBoxLayout>

class Box : public QWidget
{
 Q_OBJECT
public:
 explicit Box(QWidget *parent = 0);
 /*public*/ Box(QBoxLayout::Direction axis, QWidget *parent = 0);
 /*public*/ static Box* createHorizontalBox();
 /*public*/ static Box* createVerticalBox();
 /*public*/ static QWidget* createGlue();
 /*public*/ static QWidget* createHorizontalGlue();
 /*public*/ static QWidget* createVerticalGlue();
 /*public*/ void setLayout(QLayout* l);
 /*public*/ static QWidget* createRigidArea(QSize d);
 /*public*/ static QWidget* createHorizontalStrut(int width);

signals:

public slots:

};
/*public*/ /*static*/ class Filler : public QWidget // JComponent implements Accessible {
{
public:
    /**
     * Constructor to create shape with the given size ranges.
     *
     * @param min   Minimum size
     * @param pref  Preferred size
     * @param max   Maximum size
     */
    //@ConstructorProperties({"minimumSize", "preferredSize", "maximumSize"})
    /*public*/ Filler(QSize min, QSize pref, QSize max);
    /*public*/ void changeShape(QSize min, QSize pref, QSize max) ;
//    /*protected*/ void paintComponent(Graphics g) ;
//    /*public*/ AccessibleContext getAccessibleContext();
 friend class Box;
};

#endif // BOX_H
