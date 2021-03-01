#ifndef TREEPANEL_H
#define TREEPANEL_H

#include <QWidget>
#include "logger.h"
#include "controller.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class JTextField;
class QCheckBox;
class QLabel;
class UsbNode;
class JTree;
namespace Usb
{
class TreePanel : public QWidget, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 explicit TreePanel(QWidget *parent = 0);
  QObject* self() override {return (QObject*)this;}

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
 JTree* dTree;
 UsbNode* currentNode;// = null;
 QLabel* controllerName;// = new JLabel();
 QLabel* controllerType;// = new JLabel();
 QLabel* componentName;// = new JLabel();
 QLabel* componentId;// = new JLabel();
 QLabel* componentAnalog;// = new JLabel();
 QLabel* componentRelative;// = new JLabel();
 QLabel* componentValue;// = new JLabel();
 QCheckBox* sensorBox;// = new JCheckBox("Copy to JMRI Sensor  ");
 JTextField* sensorName;// = new JTextField(25);
 QCheckBox* memoryBox;// = new JCheckBox("Copy to JMRI Memory  ");
 JTextField* memoryName;// = new JTextField(25);
 void update();
 /*public*/ UsbNode* getSelectedElement();
 Logger* log;
private slots:
 void checkSensorBox();
 void checkMemoryBox();
};
}
#endif // TREEPANEL_H
