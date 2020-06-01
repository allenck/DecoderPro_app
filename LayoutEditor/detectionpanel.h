#ifndef DETECTIONPANEL_H
#define DETECTIONPANEL_H

#include <QWidget>
#include "logger.h"

class JPanel;
class JFrame;
class ItemPanel;
class JTextField;
class QPushButton;
class QCheckBox;
class OBlock;
class DetectionPanel : public QWidget
{
    Q_OBJECT
public:
    //explicit DetectionPanel(QWidget *parent = 0);
    /*public*/ DetectionPanel(ItemPanel* itemPanel, QWidget* parent = 0);
    /*public*/ void dispose();
    /*public*/ bool getShowTrainName();
    /*public*/ void setShowTrainName(bool show);
    /*public*/ QString getOccSensor();
    /*public*/ QString getOccBlock();
    /*public*/ void setOccDetector(QString name);
    /*public*/ QStringList getPaths();
    /*public*/ void setPaths(QStringList iconPath);
signals:

public slots:
    void _openPicklistButton_clicked();
private:
    /*private*/ JTextField*  _occDetectorName;// = new JTextField();   // can be either a Sensor or OBlock name
    /*private*/ JFrame*      _pickFrame;
    /*private*/ QPushButton*  _openPicklistButton;
    /*private*/ QWidget*      _trainIdPanel;
    /*private*/ QCheckBox*   _showTrainName;
    /*private*/ OBlock*      _block;
    /*private*/ QWidget*      _blockPathPanel;
    /*private*/ ItemPanel*   _parent;
    /*private*/ QList<QCheckBox*> _pathBoxes;
    /*private*/ JPanel*      _checkBoxPanel;
    QWidget* makeSensorPanel(JTextField* field, QString text, QString toolTip);
    Logger * log;
    void openPickList();
    void closePickList();
    /*private*/ QWidget* makeTrainIdPanel();
    /*private*/ void makePathList(OBlock* block);

private slots:
    /*private*/ void checkDetection();
    void OnTextChanged(QString text);

};

#endif // DETECTIONPANEL_H
