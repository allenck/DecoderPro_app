/********************************************************************************
** Form generated from reading UI file 'inputwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTWIDGET_H
#define UI_INPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputWidget
{
public:
    QVBoxLayout *verticalLayout;
    QRadioButton *rbNotUsed;
    QLineEdit *edStatus;
    QRadioButton *rbBlockDetectionActiveLow;
    QRadioButton *rbBlockDetectionActiveHigh;
    QCheckBox *chkBlockDetectionDelay;
    QRadioButton *rbToggleSwitch;
    QRadioButton *rbPushButtonActiveLow;
    QRadioButton *rbPushButtonActiveHigh;
    QCheckBox *chkDirectControl;
    QRadioButton *rbSwitchPointFeedback;
    QRadioButton *rbContact1PointFeedback;
    QRadioButton *rbContact2PointFeedback;
    QRadioButton *rbDoubleInput;
    QLabel *lblDoubleInputDisabled;

    void setupUi(QWidget *InputWidget)
    {
        if (InputWidget->objectName().isEmpty())
            InputWidget->setObjectName(QString::fromUtf8("InputWidget"));
        InputWidget->resize(23, 326);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InputWidget->sizePolicy().hasHeightForWidth());
        InputWidget->setSizePolicy(sizePolicy);
        InputWidget->setMaximumSize(QSize(64, 16777215));
        QFont font;
        font.setPointSize(7);
        InputWidget->setFont(font);
        verticalLayout = new QVBoxLayout(InputWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbNotUsed = new QRadioButton(InputWidget);
        rbNotUsed->setObjectName(QString::fromUtf8("rbNotUsed"));

        verticalLayout->addWidget(rbNotUsed);

        edStatus = new QLineEdit(InputWidget);
        edStatus->setObjectName(QString::fromUtf8("edStatus"));
        edStatus->setMaximumSize(QSize(20, 20));
        edStatus->setReadOnly(true);

        verticalLayout->addWidget(edStatus);

        rbBlockDetectionActiveLow = new QRadioButton(InputWidget);
        rbBlockDetectionActiveLow->setObjectName(QString::fromUtf8("rbBlockDetectionActiveLow"));

        verticalLayout->addWidget(rbBlockDetectionActiveLow);

        rbBlockDetectionActiveHigh = new QRadioButton(InputWidget);
        rbBlockDetectionActiveHigh->setObjectName(QString::fromUtf8("rbBlockDetectionActiveHigh"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rbBlockDetectionActiveHigh->sizePolicy().hasHeightForWidth());
        rbBlockDetectionActiveHigh->setSizePolicy(sizePolicy1);
        rbBlockDetectionActiveHigh->setMaximumSize(QSize(16777215, 21));

        verticalLayout->addWidget(rbBlockDetectionActiveHigh);

        chkBlockDetectionDelay = new QCheckBox(InputWidget);
        chkBlockDetectionDelay->setObjectName(QString::fromUtf8("chkBlockDetectionDelay"));

        verticalLayout->addWidget(chkBlockDetectionDelay);

        rbToggleSwitch = new QRadioButton(InputWidget);
        rbToggleSwitch->setObjectName(QString::fromUtf8("rbToggleSwitch"));

        verticalLayout->addWidget(rbToggleSwitch);

        rbPushButtonActiveLow = new QRadioButton(InputWidget);
        rbPushButtonActiveLow->setObjectName(QString::fromUtf8("rbPushButtonActiveLow"));

        verticalLayout->addWidget(rbPushButtonActiveLow);

        rbPushButtonActiveHigh = new QRadioButton(InputWidget);
        rbPushButtonActiveHigh->setObjectName(QString::fromUtf8("rbPushButtonActiveHigh"));

        verticalLayout->addWidget(rbPushButtonActiveHigh);

        chkDirectControl = new QCheckBox(InputWidget);
        chkDirectControl->setObjectName(QString::fromUtf8("chkDirectControl"));

        verticalLayout->addWidget(chkDirectControl);

        rbSwitchPointFeedback = new QRadioButton(InputWidget);
        rbSwitchPointFeedback->setObjectName(QString::fromUtf8("rbSwitchPointFeedback"));

        verticalLayout->addWidget(rbSwitchPointFeedback);

        rbContact1PointFeedback = new QRadioButton(InputWidget);
        rbContact1PointFeedback->setObjectName(QString::fromUtf8("rbContact1PointFeedback"));

        verticalLayout->addWidget(rbContact1PointFeedback);

        rbContact2PointFeedback = new QRadioButton(InputWidget);
        rbContact2PointFeedback->setObjectName(QString::fromUtf8("rbContact2PointFeedback"));

        verticalLayout->addWidget(rbContact2PointFeedback);

        rbDoubleInput = new QRadioButton(InputWidget);
        rbDoubleInput->setObjectName(QString::fromUtf8("rbDoubleInput"));

        verticalLayout->addWidget(rbDoubleInput);

        lblDoubleInputDisabled = new QLabel(InputWidget);
        lblDoubleInputDisabled->setObjectName(QString::fromUtf8("lblDoubleInputDisabled"));

        verticalLayout->addWidget(lblDoubleInputDisabled);


        retranslateUi(InputWidget);

        QMetaObject::connectSlotsByName(InputWidget);
    } // setupUi

    void retranslateUi(QWidget *InputWidget)
    {
        InputWidget->setWindowTitle(QCoreApplication::translate("InputWidget", "Form", nullptr));
#if QT_CONFIG(tooltip)
        InputWidget->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>&lt;none&gt;</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        rbNotUsed->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Not used.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbNotUsed->setText(QString());
#if QT_CONFIG(tooltip)
        rbBlockDetectionActiveLow->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Block detection active high.  Generate an OPC_INPUT_REP (0xB2) message.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbBlockDetectionActiveLow->setText(QString());
#if QT_CONFIG(tooltip)
        rbBlockDetectionActiveHigh->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Block detection active low.  Generate an OPC_INPUT_REP (0xB2) message.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbBlockDetectionActiveHigh->setText(QString());
#if QT_CONFIG(tooltip)
        chkBlockDetectionDelay->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Delay the block detection message if checked. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        chkBlockDetectionDelay->setText(QString());
#if QT_CONFIG(tooltip)
        rbToggleSwitch->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Toggle switch. Generate an OPC_SW_REQ (0xB0) message to set a turnout. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbToggleSwitch->setText(QString());
#if QT_CONFIG(tooltip)
        rbPushButtonActiveLow->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Push button, active low. Generate an OPC_SW_REQ (0xB0) message to set a turnout. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbPushButtonActiveLow->setText(QString());
#if QT_CONFIG(tooltip)
        rbPushButtonActiveHigh->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Push button, active high. Generate an OPC_SW_REQ (0xB0) message to set a turnout. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbPushButtonActiveHigh->setText(QString());
#if QT_CONFIG(tooltip)
        chkDirectControl->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Directly control the turnout if checked.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        chkDirectControl->setText(QString());
#if QT_CONFIG(tooltip)
        rbSwitchPointFeedback->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Switch point feedback.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbSwitchPointFeedback->setText(QString());
#if QT_CONFIG(tooltip)
        rbContact1PointFeedback->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Contact 1 point feedback.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbContact1PointFeedback->setText(QString());
#if QT_CONFIG(tooltip)
        rbContact2PointFeedback->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Contact 2 point feedback.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbContact2PointFeedback->setText(QString());
#if QT_CONFIG(tooltip)
        rbDoubleInput->setToolTip(QCoreApplication::translate("InputWidget", "<html><head/><body><p>Double input,  paired with previous port. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        rbDoubleInput->setText(QString());
        lblDoubleInputDisabled->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InputWidget: public Ui_InputWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTWIDGET_H
