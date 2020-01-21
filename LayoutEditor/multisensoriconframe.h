#ifndef MULTISENSORICONFRAME_H
#define MULTISENSORICONFRAME_H
#include "jmrijframe.h"

class JTextField;
class Entry;
class QButtonGroup;
class QRadioButton;
class MultiIconEditor;
class LayoutEditor;
class MultiSensorIconFrame : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit MultiSensorIconFrame(QWidget *parent = 0);
    MultiSensorIconFrame(LayoutEditor* p, QWidget *parent = 0);
    /*public*/ void initComponents();
    /*public*/ QString getClassName();

signals:

public slots:
    void on_addSensor();
    void on_createAndAdd();
    void on_setIcons();

private:
    QWidget* content;// = new JPanel();
    JmriJFrame* defaultsFrame;
    MultiIconEditor* defaultIcons;
    LayoutEditor* layoutEditor;// = null;
    QRadioButton* updown;// = new JRadioButton("Up - Down");
    QRadioButton* rightleft;// = new JRadioButton("Right - Left");
    QButtonGroup* group;// = new ButtonGroup();
    void remove(Entry* e);
    void make();
    void removeWindows();
};
class Entry : public QWidget
{
    Q_OBJECT
    JTextField* sensor;// = new JTextField(5);
    QWidget* self;
    MultiIconEditor* ed;// = new MultiIconEditor(1);
    JmriJFrame* edf;// = new JmriJFrame("", false, true);
public:
    /*public*/ QString toString();
    Entry(QWidget* self, JmriJFrame* frame, QString name);
    ~Entry();
    /*public*/ void dispose();
public slots:
    void on_setIcon();

 friend class MultiSensorIconFrame;
};
class AddSensorActionListener : public QObject
{
 Q_OBJECT
 QWidget* self;
 JmriJFrame* frame;
public:
 AddSensorActionListener() {}
 AddSensorActionListener* init(QWidget* self, JmriJFrame* frame);
public slots:
 /*public*/ void actionPerformed(/*ActionEvent a*/);

};

class DeleteActionListener : public QObject
{
 Q_OBJECT
 Entry* entry;
 QWidget* self;
 JmriJFrame* frame;
public:
 DeleteActionListener(){}
 DeleteActionListener* init(Entry* entry, QWidget* self, JmriJFrame* frame);
public slots:
 /*public*/ void actionPerformed(/*ActionEvent a*/);

};

#endif // MULTISENSORICONFRAME_H
