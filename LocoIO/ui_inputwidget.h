/********************************************************************************
** Form generated from reading UI file 'inputwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            InputWidget->setObjectName(QLatin1String("InputWidget"));
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
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        rbNotUsed = new QRadioButton(InputWidget);
        rbNotUsed->setObjectName(QLatin1String("rbNotUsed"));

        verticalLayout->addWidget(rbNotUsed);

        edStatus = new QLineEdit(InputWidget);
        edStatus->setObjectName(QLatin1String("edStatus"));
        edStatus->setMaximumSize(QSize(20, 20));
        edStatus->setReadOnly(true);

        verticalLayout->addWidget(edStatus);

        rbBlockDetectionActiveLow = new QRadioButton(InputWidget);
        rbBlockDetectionActiveLow->setObjectName(QLatin1String("rbBlockDetectionActiveLow"));

        verticalLayout->addWidget(rbBlockDetectionActiveLow);

        rbBlockDetectionActiveHigh = new QRadioButton(InputWidget);
        rbBlockDetectionActiveHigh->setObjectName(QLatin1String("rbBlockDetectionActiveHigh"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rbBlockDetectionActiveHigh->sizePolicy().hasHeightForWidth());
        rbBlockDetectionActiveHigh->setSizePolicy(sizePolicy1);
        rbBlockDetectionActiveHigh->setMaximumSize(QSize(16777215, 21));

        verticalLayout->addWidget(rbBlockDetectionActiveHigh);

        chkBlockDetectionDelay = new QCheckBox(InputWidget);
        chkBlockDetectionDelay->setObjectName(QLatin1String("chkBlockDetectionDelay"));

        verticalLayout->addWidget(chkBlockDetectionDelay);

        rbToggleSwitch = new QRadioButton(InputWidget);
        rbToggleSwitch->setObjectName(QLatin1String("rbToggleSwitch"));

        verticalLayout->addWidget(rbToggleSwitch);

        rbPushButtonActiveLow = new QRadioButton(InputWidget);
        rbPushButtonActiveLow->setObjectName(QLatin1String("rbPushButtonActiveLow"));

        verticalLayout->addWidget(rbPushButtonActiveLow);

        rbPushButtonActiveHigh = new QRadioButton(InputWidget);
        rbPushButtonActiveHigh->setObjectName(QLatin1String("rbPushButtonActiveHigh"));

        verticalLayout->addWidget(rbPushButtonActiveHigh);

        chkDirectControl = new QCheckBox(InputWidget);
        chkDirectControl->setObjectName(QLatin1String("chkDirectControl"));

        verticalLayout->addWidget(chkDirectControl);

        rbSwitchPointFeedback = new QRadioButton(InputWidget);
        rbSwitchPointFeedback->setObjectName(QLatin1String("rbSwitchPointFeedback"));

        verticalLayout->addWidget(rbSwitchPointFeedback);

        rbContact1PointFeedback = new QRadioButton(InputWidget);
        rbContact1PointFeedback->setObjectName(QLatin1String("rbContact1PointFeedback"));

        verticalLayout->addWidget(rbContact1PointFeedback);

        rbContact2PointFeedback = new QRadioButton(InputWidget);
        rbContact2PointFeedback->setObjectName(QLatin1String("rbContact2PointFeedback"));

        verticalLayout->addWidget(rbContact2PointFeedback);

        rbDoubleInput = new QRadioButton(InputWidget);
        rbDoubleInput->setObjectName(QLatin1String("rbDoubleInput"));

        verticalLayout->addWidget(rbDoubleInput);

        lblDoubleInputDisabled = new QLabel(InputWidget);
        lblDoubleInputDisabled->setObjectName(QLatin1String("lblDoubleInputDisabled"));

        verticalLayout->addWidget(lblDoubleInputDisabled);


        retranslateUi(InputWidget);

        QMetaObject::connectSlotsByName(InputWidget);
    } // setupUi

    void retranslateUi(QWidget *InputWidget)
    {
        InputWidget->setWindowTitle(QApplication::translate("InputWidget", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        InputWidget->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>&lt;none&gt;</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        rbNotUsed->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Not used.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbNotUsed->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbBlockDetectionActiveLow->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Block detection active high.  Generate an OPC_INPUT_REP (0xB2) message.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbBlockDetectionActiveLow->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbBlockDetectionActiveHigh->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Block detection active low.  Generate an OPC_INPUT_REP (0xB2) message.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbBlockDetectionActiveHigh->setText(QString());
#ifndef QT_NO_TOOLTIP
        chkBlockDetectionDelay->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Delay the block detection message if checked. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        chkBlockDetectionDelay->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbToggleSwitch->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Toggle switch. Generate an OPC_SW_REQ (0xB0) message to set a turnout. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbToggleSwitch->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbPushButtonActiveLow->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Push button, active low. Generate an OPC_SW_REQ (0xB0) message to set a turnout. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbPushButtonActiveLow->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbPushButtonActiveHigh->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Push button, active high. Generate an OPC_SW_REQ (0xB0) message to set a turnout. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbPushButtonActiveHigh->setText(QString());
#ifndef QT_NO_TOOLTIP
        chkDirectControl->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Directly control the turnout if checked.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        chkDirectControl->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbSwitchPointFeedback->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Switch point feedback.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbSwitchPointFeedback->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbContact1PointFeedback->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Contact 1 point feedback.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbContact1PointFeedback->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbContact2PointFeedback->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Contact 2 point feedback.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbContact2PointFeedback->setText(QString());
#ifndef QT_NO_TOOLTIP
        rbDoubleInput->setToolTip(QApplication::translate("InputWidget", "<html><head/><body><p>Double input,  paired with previous port. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rbDoubleInput->setText(QString());
        lblDoubleInputDisabled->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InputWidget: public Ui_InputWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTWIDGET_H
