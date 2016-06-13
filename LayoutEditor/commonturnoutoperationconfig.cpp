#include "commonturnoutoperationconfig.h"
#include <QSpinBox>
#include "commonturnoutoperation.h"
#include <QBoxLayout>
#include <QLabel>

//CommonTurnoutOperationConfig::CommonTurnoutOperationConfig(QObject *parent) :
//    TurnoutOperationConfig(parent)
//{
//}
/**
 * Extension of TurnoutOperationConfig to handle config for common aspects of some
 * subclasses
 * @author John Harper	Copyright 2005
 *
 */
///*public*/ class CommonTurnoutOperationConfig extends TurnoutOperationConfig {


/**
 * Create the config JPanel, if there is one, to configure this operation type
 */
/*public*/ CommonTurnoutOperationConfig::CommonTurnoutOperationConfig(TurnoutOperation* op, QWidget* parent) : TurnoutOperationConfig(op, parent)
{
 //super(op);
 setLayout(new QVBoxLayout);
 myOp = (CommonTurnoutOperation*)op;

 maxTriesSpinner = new QSpinBox();
 intervalSpinner = new QSpinBox();
 //Box vbox = Box.createVerticalBox();
 QWidget* vbox = new QWidget();
 vbox->setLayout(new QVBoxLayout);
 //Box hbox1 = Box.createHorizontalBox();
 QWidget* hbox1 = new QWidget();
 hbox1->setLayout(new QHBoxLayout);

 //Box hbox2 = Box.createHorizontalBox();
 QWidget* hbox2 = new QWidget();
 hbox2->setLayout(new QHBoxLayout);
 vbox->layout()->addWidget(hbox1);
 vbox->layout()->addWidget(hbox2);
 //vbox->layout()->addWidget(Box.createVerticalGlue());
 hbox1->layout()->addWidget(new QLabel(tr("Interval")+":     "));
 //hbox1.add(Box.createHorizontalGlue());
 intervalSpinner->setMinimumSize(QSize(100,20));

// intervalSpinner.setModel(
//                    new SpinnerNumberModel(myOp.getInterval(),
//                                    CommonTurnoutOperation.minInterval, CommonTurnoutOperation.maxInterval,
//                                    CommonTurnoutOperation.intervalStepSize)); // val, min, max, step
 intervalSpinner->setValue(myOp->getInterval());
 intervalSpinner->setMinimum(CommonTurnoutOperation::minInterval);
 intervalSpinner->setMaximum(CommonTurnoutOperation::maxInterval);
 intervalSpinner->setSingleStep(CommonTurnoutOperation::intervalStepSize);

 hbox1->layout()->addWidget(intervalSpinner);
 hbox2->layout()->addWidget(new QLabel(tr("Times to try")+":   "));
 //hbox2.add(Box.createHorizontalGlue());
 maxTriesSpinner->setMinimumSize( QSize(100,20));

// maxTriesSpinner.setModel(
//                    new SpinnerNumberModel(myOp.getMaxTries(),
//                                    CommonTurnoutOperation.minMaxTries, CommonTurnoutOperation.maxMaxTries, 1)); // val, min, max, step
 maxTriesSpinner->setValue(myOp->getMaxTries());
 maxTriesSpinner->setMinimum(CommonTurnoutOperation::minInterval);
 maxTriesSpinner->setMaximum(CommonTurnoutOperation::maxInterval);
 maxTriesSpinner->setSingleStep(CommonTurnoutOperation::intervalStepSize);

 hbox2->layout()->addWidget(maxTriesSpinner);

 //Box hbox3 = Box.createHorizontalBox();
 QWidget* hbox3 = new QWidget();
 hbox3->setLayout(new QHBoxLayout);
 //hbox3->layout()->addWidget(Box.createHorizontalStrut(150));
 ((QBoxLayout*)hbox3->layout())->addStrut(150);
 vbox->layout()->addWidget(hbox3);
 layout()->addWidget(vbox);
}

/**
 * called when OK button pressed in config panel, to retrieve and set new values
 */
/*public*/ void CommonTurnoutOperationConfig::endConfigure()
{
 int newInterval = intervalSpinner->value();
 myOp->setInterval(newInterval);
 int newMaxTries = (maxTriesSpinner->value());
 myOp->setMaxTries(newMaxTries);
}
