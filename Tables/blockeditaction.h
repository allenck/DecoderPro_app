#ifndef BLOCKEDITACTION_H
#define BLOCKEDITACTION_H
#include "beaneditaction.h"

class QRadioButton;
class QComboBox;
class QCheckBox;
class JmriBeanComboBox;
class DecimalFormat;
class BlockEditAction : public BeanEditAction
{
 Q_OBJECT
public:
 explicit BlockEditAction(QObject *parent = 0);
 /*public*/ QString helpTarget();
 /*public*/ QString getBeanType();
 /*public*/ NamedBean* getByUserName(QString name);

signals:

public slots:
 void on_reporterField_currentIndexChanged(QString s);
 void on_setSaveItem();
 void on_setResetItem();

private:
 /*private*/ QString noneText;// = tr("None");
 /*private*/ QString gradualText;// = tr("Gradual");
 /*private*/ QString tightText;// = tr("Tight");
 /*private*/ QString severeText;// = tr("Severe");
 /*public*/ QStringList curveOptions;// = {noneText, gradualText, tightText, severeText};
 static /*final*/ QVector<QString> speedList;// = new QVector<QString>();

 /*private*/ DecimalFormat* twoDigit;// = new DecimalFormat("0.00");
 JTextField* userNameField;// = new JTextField(20);
 JmriBeanComboBox* reporterField;
 QCheckBox* useCurrent;// = new JCheckBox();
 JTextArea* commentField;// = new JTextArea(3, 30);
 QScrollArea* commentFieldScroller;// = new JScrollPane(commentField);
 BeanItemPanel* reporterDetails();
 JTextField* lengthField;// = new JTextField(20);
 QComboBox* curvatureField;// = new QComboBox<String>(curveOptions);
 QCheckBox* permissiveField;// = new QCheckBox();
 QComboBox* speedField;

 QRadioButton* inch;// = new JRadioButton(tr("Inches"));
 QRadioButton* cm;// = new JRadioButton(tr("Centimeters"));

 QString defaultBlockSpeedText;
 BeanItemPanel* physcialDetails();
 JmriBeanComboBox* sensorField;
 BeanItemPanel* sensor();

private slots:
 /*private*/ void updateLength();


protected:
 /*protected*/ void initPanels();

};

#endif // BLOCKEDITACTION_H
