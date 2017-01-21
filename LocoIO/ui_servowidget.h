/********************************************************************************
** Form generated from reading UI file 'servowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVOWIDGET_H
#define UI_SERVOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServoWidget
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbNotUsed1;
    QRadioButton *rbNotUsed2;
    QRadioButton *rbNotUsed3;
    QRadioButton *rbNotUsed4;
    QRadioButton *rbNotUsed5;
    QRadioButton *rbNotUsed6;
    QRadioButton *rbNotUsed7;
    QRadioButton *rbNotUsed8;
    QGroupBox *gbServo;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnTest1;
    QToolButton *btnCenter1;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btnTest2;
    QToolButton *btnCenter2;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *btnTest3;
    QToolButton *btnCenter3;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *btnTest4;
    QToolButton *btnCenter4;
    QHBoxLayout *horizontalLayout_7;
    QToolButton *btnTest5;
    QToolButton *btnCenter5;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *btnTest6;
    QToolButton *btnCenter6;
    QHBoxLayout *horizontalLayout_9;
    QToolButton *btnTest7;
    QToolButton *btnCenter7;
    QHBoxLayout *horizontalLayout_10;
    QToolButton *btnTest8;
    QToolButton *btnCenter8;
    QLabel *lblServo1;
    QLabel *lbl11;
    QLabel *lbl12;
    QLabel *lbl13;
    QLabel *lbl14;
    QLabel *lbl15;
    QLabel *lbl16;
    QLabel *lbl17;
    QLabel *lbl18;
    QSpinBox *sbP11;
    QSpinBox *sbP12;
    QSpinBox *sbP13;
    QSpinBox *sbP14;
    QSpinBox *sbP15;
    QSpinBox *sbP16;
    QSpinBox *sbP17;
    QSpinBox *sbP18;
    QLabel *lblServo2;
    QLabel *lbl21;
    QLabel *lbl22;
    QLabel *lbl23;
    QLabel *lbl24;
    QLabel *lbl25;
    QLabel *lbl26;
    QLabel *lbl27;
    QLabel *lbl28;
    QSpinBox *sbP21;
    QSpinBox *sbP22;
    QSpinBox *sbP23;
    QSpinBox *sbP24;
    QSpinBox *sbP25;
    QSpinBox *sbP26;
    QSpinBox *sbP27;
    QSpinBox *sbP28;
    QLabel *lblServoSpeed;
    QSpinBox *sbS1;
    QSpinBox *sbS2;
    QSpinBox *sbS3;
    QSpinBox *sbS4;
    QSpinBox *sbS5;
    QSpinBox *sbS6;
    QSpinBox *sbS7;
    QSpinBox *sbS8;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rbS1;
    QRadioButton *rbS2;
    QRadioButton *rbS3;
    QRadioButton *rbS4;
    QRadioButton *rbS5;
    QRadioButton *rbS6;
    QRadioButton *rbS7;
    QRadioButton *rbS8;

    void setupUi(QWidget *ServoWidget)
    {
        if (ServoWidget->objectName().isEmpty())
            ServoWidget->setObjectName(QStringLiteral("ServoWidget"));
        ServoWidget->resize(523, 368);
        QFont font;
        font.setPointSize(7);
        ServoWidget->setFont(font);
        gridLayout_2 = new QGridLayout(ServoWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rbNotUsed1 = new QRadioButton(ServoWidget);
        rbNotUsed1->setObjectName(QStringLiteral("rbNotUsed1"));
        rbNotUsed1->setMaximumSize(QSize(35, 16777215));
        rbNotUsed1->setChecked(false);
        rbNotUsed1->setAutoExclusive(false);

        horizontalLayout->addWidget(rbNotUsed1);

        rbNotUsed2 = new QRadioButton(ServoWidget);
        rbNotUsed2->setObjectName(QStringLiteral("rbNotUsed2"));
        rbNotUsed2->setMaximumSize(QSize(35, 16777215));
        rbNotUsed2->setChecked(true);
        rbNotUsed2->setAutoExclusive(false);

        horizontalLayout->addWidget(rbNotUsed2);

        rbNotUsed3 = new QRadioButton(ServoWidget);
        rbNotUsed3->setObjectName(QStringLiteral("rbNotUsed3"));
        rbNotUsed3->setMaximumSize(QSize(35, 16777215));
        rbNotUsed3->setChecked(false);

        horizontalLayout->addWidget(rbNotUsed3);

        rbNotUsed4 = new QRadioButton(ServoWidget);
        rbNotUsed4->setObjectName(QStringLiteral("rbNotUsed4"));
        rbNotUsed4->setMaximumSize(QSize(35, 16777215));

        horizontalLayout->addWidget(rbNotUsed4);

        rbNotUsed5 = new QRadioButton(ServoWidget);
        rbNotUsed5->setObjectName(QStringLiteral("rbNotUsed5"));
        rbNotUsed5->setMaximumSize(QSize(35, 16777215));

        horizontalLayout->addWidget(rbNotUsed5);

        rbNotUsed6 = new QRadioButton(ServoWidget);
        rbNotUsed6->setObjectName(QStringLiteral("rbNotUsed6"));
        rbNotUsed6->setMaximumSize(QSize(35, 16777215));

        horizontalLayout->addWidget(rbNotUsed6);

        rbNotUsed7 = new QRadioButton(ServoWidget);
        rbNotUsed7->setObjectName(QStringLiteral("rbNotUsed7"));
        rbNotUsed7->setMaximumSize(QSize(35, 16777215));

        horizontalLayout->addWidget(rbNotUsed7);

        rbNotUsed8 = new QRadioButton(ServoWidget);
        rbNotUsed8->setObjectName(QStringLiteral("rbNotUsed8"));
        rbNotUsed8->setMaximumSize(QSize(35, 16777215));

        horizontalLayout->addWidget(rbNotUsed8);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        gbServo = new QGroupBox(ServoWidget);
        gbServo->setObjectName(QStringLiteral("gbServo"));
        gbServo->setFlat(true);
        gridLayout = new QGridLayout(gbServo);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(gbServo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnTest1 = new QToolButton(gbServo);
        btnTest1->setObjectName(QStringLiteral("btnTest1"));

        horizontalLayout_3->addWidget(btnTest1);

        btnCenter1 = new QToolButton(gbServo);
        btnCenter1->setObjectName(QStringLiteral("btnCenter1"));

        horizontalLayout_3->addWidget(btnCenter1);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnTest2 = new QToolButton(gbServo);
        btnTest2->setObjectName(QStringLiteral("btnTest2"));

        horizontalLayout_4->addWidget(btnTest2);

        btnCenter2 = new QToolButton(gbServo);
        btnCenter2->setObjectName(QStringLiteral("btnCenter2"));

        horizontalLayout_4->addWidget(btnCenter2);


        gridLayout->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnTest3 = new QToolButton(gbServo);
        btnTest3->setObjectName(QStringLiteral("btnTest3"));

        horizontalLayout_5->addWidget(btnTest3);

        btnCenter3 = new QToolButton(gbServo);
        btnCenter3->setObjectName(QStringLiteral("btnCenter3"));

        horizontalLayout_5->addWidget(btnCenter3);


        gridLayout->addLayout(horizontalLayout_5, 1, 2, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        btnTest4 = new QToolButton(gbServo);
        btnTest4->setObjectName(QStringLiteral("btnTest4"));

        horizontalLayout_6->addWidget(btnTest4);

        btnCenter4 = new QToolButton(gbServo);
        btnCenter4->setObjectName(QStringLiteral("btnCenter4"));

        horizontalLayout_6->addWidget(btnCenter4);


        gridLayout->addLayout(horizontalLayout_6, 1, 3, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        btnTest5 = new QToolButton(gbServo);
        btnTest5->setObjectName(QStringLiteral("btnTest5"));

        horizontalLayout_7->addWidget(btnTest5);

        btnCenter5 = new QToolButton(gbServo);
        btnCenter5->setObjectName(QStringLiteral("btnCenter5"));

        horizontalLayout_7->addWidget(btnCenter5);


        gridLayout->addLayout(horizontalLayout_7, 1, 4, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        btnTest6 = new QToolButton(gbServo);
        btnTest6->setObjectName(QStringLiteral("btnTest6"));

        horizontalLayout_8->addWidget(btnTest6);

        btnCenter6 = new QToolButton(gbServo);
        btnCenter6->setObjectName(QStringLiteral("btnCenter6"));

        horizontalLayout_8->addWidget(btnCenter6);


        gridLayout->addLayout(horizontalLayout_8, 1, 5, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        btnTest7 = new QToolButton(gbServo);
        btnTest7->setObjectName(QStringLiteral("btnTest7"));

        horizontalLayout_9->addWidget(btnTest7);

        btnCenter7 = new QToolButton(gbServo);
        btnCenter7->setObjectName(QStringLiteral("btnCenter7"));

        horizontalLayout_9->addWidget(btnCenter7);


        gridLayout->addLayout(horizontalLayout_9, 1, 6, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        btnTest8 = new QToolButton(gbServo);
        btnTest8->setObjectName(QStringLiteral("btnTest8"));

        horizontalLayout_10->addWidget(btnTest8);

        btnCenter8 = new QToolButton(gbServo);
        btnCenter8->setObjectName(QStringLiteral("btnCenter8"));

        horizontalLayout_10->addWidget(btnCenter8);


        gridLayout->addLayout(horizontalLayout_10, 1, 7, 1, 1);

        lblServo1 = new QLabel(gbServo);
        lblServo1->setObjectName(QStringLiteral("lblServo1"));
        lblServo1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblServo1, 2, 0, 1, 1);

        lbl11 = new QLabel(gbServo);
        lbl11->setObjectName(QStringLiteral("lbl11"));
        lbl11->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl11, 3, 0, 1, 1);

        lbl12 = new QLabel(gbServo);
        lbl12->setObjectName(QStringLiteral("lbl12"));
        lbl12->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl12, 3, 1, 1, 1);

        lbl13 = new QLabel(gbServo);
        lbl13->setObjectName(QStringLiteral("lbl13"));
        lbl13->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl13, 3, 2, 1, 1);

        lbl14 = new QLabel(gbServo);
        lbl14->setObjectName(QStringLiteral("lbl14"));
        lbl14->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl14, 3, 3, 1, 1);

        lbl15 = new QLabel(gbServo);
        lbl15->setObjectName(QStringLiteral("lbl15"));
        lbl15->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl15, 3, 4, 1, 1);

        lbl16 = new QLabel(gbServo);
        lbl16->setObjectName(QStringLiteral("lbl16"));
        lbl16->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl16, 3, 5, 1, 1);

        lbl17 = new QLabel(gbServo);
        lbl17->setObjectName(QStringLiteral("lbl17"));
        lbl17->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl17, 3, 6, 1, 1);

        lbl18 = new QLabel(gbServo);
        lbl18->setObjectName(QStringLiteral("lbl18"));
        lbl18->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl18, 3, 7, 1, 1);

        sbP11 = new QSpinBox(gbServo);
        sbP11->setObjectName(QStringLiteral("sbP11"));
        sbP11->setFont(font);
        sbP11->setAutoFillBackground(true);
        sbP11->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP11->setMinimum(1);
        sbP11->setMaximum(127);
        sbP11->setValue(127);

        gridLayout->addWidget(sbP11, 4, 0, 1, 1);

        sbP12 = new QSpinBox(gbServo);
        sbP12->setObjectName(QStringLiteral("sbP12"));
        sbP12->setFont(font);
        sbP12->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP12->setMinimum(1);
        sbP12->setMaximum(127);
        sbP12->setValue(127);

        gridLayout->addWidget(sbP12, 4, 1, 1, 1);

        sbP13 = new QSpinBox(gbServo);
        sbP13->setObjectName(QStringLiteral("sbP13"));
        sbP13->setFont(font);
        sbP13->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP13->setMinimum(1);
        sbP13->setMaximum(127);
        sbP13->setValue(127);

        gridLayout->addWidget(sbP13, 4, 2, 1, 1);

        sbP14 = new QSpinBox(gbServo);
        sbP14->setObjectName(QStringLiteral("sbP14"));
        sbP14->setFont(font);
        sbP14->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP14->setMinimum(1);
        sbP14->setMaximum(127);
        sbP14->setValue(127);

        gridLayout->addWidget(sbP14, 4, 3, 1, 1);

        sbP15 = new QSpinBox(gbServo);
        sbP15->setObjectName(QStringLiteral("sbP15"));
        sbP15->setFont(font);
        sbP15->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP15->setMinimum(1);
        sbP15->setMaximum(127);
        sbP15->setValue(127);

        gridLayout->addWidget(sbP15, 4, 4, 1, 1);

        sbP16 = new QSpinBox(gbServo);
        sbP16->setObjectName(QStringLiteral("sbP16"));
        sbP16->setFont(font);
        sbP16->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP16->setMinimum(1);
        sbP16->setMaximum(127);
        sbP16->setValue(127);

        gridLayout->addWidget(sbP16, 4, 5, 1, 1);

        sbP17 = new QSpinBox(gbServo);
        sbP17->setObjectName(QStringLiteral("sbP17"));
        sbP17->setFont(font);
        sbP17->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP17->setMinimum(1);
        sbP17->setMaximum(127);
        sbP17->setValue(127);

        gridLayout->addWidget(sbP17, 4, 6, 1, 1);

        sbP18 = new QSpinBox(gbServo);
        sbP18->setObjectName(QStringLiteral("sbP18"));
        sbP18->setFont(font);
        sbP18->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP18->setMinimum(1);
        sbP18->setMaximum(127);
        sbP18->setValue(127);

        gridLayout->addWidget(sbP18, 4, 7, 1, 1);

        lblServo2 = new QLabel(gbServo);
        lblServo2->setObjectName(QStringLiteral("lblServo2"));
        lblServo2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblServo2, 5, 0, 1, 1);

        lbl21 = new QLabel(gbServo);
        lbl21->setObjectName(QStringLiteral("lbl21"));
        lbl21->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl21, 6, 0, 1, 1);

        lbl22 = new QLabel(gbServo);
        lbl22->setObjectName(QStringLiteral("lbl22"));
        lbl22->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl22, 6, 1, 1, 1);

        lbl23 = new QLabel(gbServo);
        lbl23->setObjectName(QStringLiteral("lbl23"));
        lbl23->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl23, 6, 2, 1, 1);

        lbl24 = new QLabel(gbServo);
        lbl24->setObjectName(QStringLiteral("lbl24"));
        lbl24->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl24, 6, 3, 1, 1);

        lbl25 = new QLabel(gbServo);
        lbl25->setObjectName(QStringLiteral("lbl25"));
        lbl25->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl25, 6, 4, 1, 1);

        lbl26 = new QLabel(gbServo);
        lbl26->setObjectName(QStringLiteral("lbl26"));
        lbl26->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl26, 6, 5, 1, 1);

        lbl27 = new QLabel(gbServo);
        lbl27->setObjectName(QStringLiteral("lbl27"));
        lbl27->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl27, 6, 6, 1, 1);

        lbl28 = new QLabel(gbServo);
        lbl28->setObjectName(QStringLiteral("lbl28"));
        lbl28->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl28, 6, 7, 1, 1);

        sbP21 = new QSpinBox(gbServo);
        sbP21->setObjectName(QStringLiteral("sbP21"));
        sbP21->setFont(font);
        sbP21->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP21->setMinimum(1);
        sbP21->setMaximum(127);
        sbP21->setValue(126);

        gridLayout->addWidget(sbP21, 7, 0, 1, 1);

        sbP22 = new QSpinBox(gbServo);
        sbP22->setObjectName(QStringLiteral("sbP22"));
        sbP22->setFont(font);
        sbP22->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP22->setMinimum(1);
        sbP22->setMaximum(127);
        sbP22->setValue(126);

        gridLayout->addWidget(sbP22, 7, 1, 1, 1);

        sbP23 = new QSpinBox(gbServo);
        sbP23->setObjectName(QStringLiteral("sbP23"));
        sbP23->setFont(font);
        sbP23->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP23->setMinimum(1);
        sbP23->setMaximum(128);
        sbP23->setValue(126);

        gridLayout->addWidget(sbP23, 7, 2, 1, 1);

        sbP24 = new QSpinBox(gbServo);
        sbP24->setObjectName(QStringLiteral("sbP24"));
        sbP24->setFont(font);
        sbP24->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP24->setMinimum(1);
        sbP24->setMaximum(128);
        sbP24->setValue(127);

        gridLayout->addWidget(sbP24, 7, 3, 1, 1);

        sbP25 = new QSpinBox(gbServo);
        sbP25->setObjectName(QStringLiteral("sbP25"));
        sbP25->setFont(font);
        sbP25->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP25->setMinimum(1);
        sbP25->setMaximum(127);
        sbP25->setValue(127);

        gridLayout->addWidget(sbP25, 7, 4, 1, 1);

        sbP26 = new QSpinBox(gbServo);
        sbP26->setObjectName(QStringLiteral("sbP26"));
        sbP26->setFont(font);
        sbP26->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP26->setMinimum(1);
        sbP26->setMaximum(127);
        sbP26->setValue(127);

        gridLayout->addWidget(sbP26, 7, 5, 1, 1);

        sbP27 = new QSpinBox(gbServo);
        sbP27->setObjectName(QStringLiteral("sbP27"));
        sbP27->setFont(font);
        sbP27->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP27->setMinimum(1);
        sbP27->setMaximum(127);
        sbP27->setValue(127);

        gridLayout->addWidget(sbP27, 7, 6, 1, 1);

        sbP28 = new QSpinBox(gbServo);
        sbP28->setObjectName(QStringLiteral("sbP28"));
        sbP28->setFont(font);
        sbP28->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbP28->setMinimum(1);
        sbP28->setMaximum(127);
        sbP28->setValue(127);

        gridLayout->addWidget(sbP28, 7, 7, 1, 1);

        lblServoSpeed = new QLabel(gbServo);
        lblServoSpeed->setObjectName(QStringLiteral("lblServoSpeed"));
        lblServoSpeed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblServoSpeed, 8, 0, 1, 1);

        sbS1 = new QSpinBox(gbServo);
        sbS1->setObjectName(QStringLiteral("sbS1"));
        sbS1->setFont(font);
        sbS1->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS1->setMinimum(0);
        sbS1->setMaximum(5);
        sbS1->setValue(5);

        gridLayout->addWidget(sbS1, 9, 0, 1, 1);

        sbS2 = new QSpinBox(gbServo);
        sbS2->setObjectName(QStringLiteral("sbS2"));
        sbS2->setFont(font);
        sbS2->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS2->setMinimum(0);
        sbS2->setMaximum(5);
        sbS2->setValue(5);

        gridLayout->addWidget(sbS2, 9, 1, 1, 1);

        sbS3 = new QSpinBox(gbServo);
        sbS3->setObjectName(QStringLiteral("sbS3"));
        sbS3->setFont(font);
        sbS3->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS3->setMinimum(0);
        sbS3->setMaximum(5);
        sbS3->setValue(5);

        gridLayout->addWidget(sbS3, 9, 2, 1, 1);

        sbS4 = new QSpinBox(gbServo);
        sbS4->setObjectName(QStringLiteral("sbS4"));
        sbS4->setFont(font);
        sbS4->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS4->setMinimum(0);
        sbS4->setMaximum(5);
        sbS4->setValue(5);

        gridLayout->addWidget(sbS4, 9, 3, 1, 1);

        sbS5 = new QSpinBox(gbServo);
        sbS5->setObjectName(QStringLiteral("sbS5"));
        sbS5->setFont(font);
        sbS5->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS5->setMinimum(0);
        sbS5->setMaximum(5);
        sbS5->setValue(5);

        gridLayout->addWidget(sbS5, 9, 4, 1, 1);

        sbS6 = new QSpinBox(gbServo);
        sbS6->setObjectName(QStringLiteral("sbS6"));
        sbS6->setFont(font);
        sbS6->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS6->setMinimum(0);
        sbS6->setMaximum(5);
        sbS6->setValue(5);

        gridLayout->addWidget(sbS6, 9, 5, 1, 1);

        sbS7 = new QSpinBox(gbServo);
        sbS7->setObjectName(QStringLiteral("sbS7"));
        sbS7->setFont(font);
        sbS7->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS7->setMinimum(0);
        sbS7->setMaximum(5);
        sbS7->setValue(5);

        gridLayout->addWidget(sbS7, 9, 6, 1, 1);

        sbS8 = new QSpinBox(gbServo);
        sbS8->setObjectName(QStringLiteral("sbS8"));
        sbS8->setFont(font);
        sbS8->setStyleSheet(QStringLiteral("QSpinBox { background-color : rgb(170, 170, 255);}"));
        sbS8->setMinimum(0);
        sbS8->setMaximum(5);
        sbS8->setValue(5);

        gridLayout->addWidget(sbS8, 9, 7, 1, 1);


        gridLayout_2->addWidget(gbServo, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rbS1 = new QRadioButton(ServoWidget);
        rbS1->setObjectName(QStringLiteral("rbS1"));
        rbS1->setMaximumSize(QSize(40, 16777215));
        rbS1->setAutoExclusive(false);

        horizontalLayout_2->addWidget(rbS1);

        rbS2 = new QRadioButton(ServoWidget);
        rbS2->setObjectName(QStringLiteral("rbS2"));
        rbS2->setMaximumSize(QSize(40, 16777215));
        rbS2->setAutoExclusive(false);

        horizontalLayout_2->addWidget(rbS2);

        rbS3 = new QRadioButton(ServoWidget);
        rbS3->setObjectName(QStringLiteral("rbS3"));
        rbS3->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(rbS3);

        rbS4 = new QRadioButton(ServoWidget);
        rbS4->setObjectName(QStringLiteral("rbS4"));
        rbS4->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(rbS4);

        rbS5 = new QRadioButton(ServoWidget);
        rbS5->setObjectName(QStringLiteral("rbS5"));
        rbS5->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(rbS5);

        rbS6 = new QRadioButton(ServoWidget);
        rbS6->setObjectName(QStringLiteral("rbS6"));
        rbS6->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(rbS6);

        rbS7 = new QRadioButton(ServoWidget);
        rbS7->setObjectName(QStringLiteral("rbS7"));
        rbS7->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(rbS7);

        rbS8 = new QRadioButton(ServoWidget);
        rbS8->setObjectName(QStringLiteral("rbS8"));
        rbS8->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(rbS8);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);


        retranslateUi(ServoWidget);

        QMetaObject::connectSlotsByName(ServoWidget);
    } // setupUi

    void retranslateUi(QWidget *ServoWidget)
    {
        ServoWidget->setWindowTitle(QApplication::translate("ServoWidget", "Form", 0));
        rbNotUsed1->setText(QApplication::translate("ServoWidget", "1", 0));
        rbNotUsed2->setText(QApplication::translate("ServoWidget", "2", 0));
        rbNotUsed3->setText(QApplication::translate("ServoWidget", "3", 0));
        rbNotUsed4->setText(QApplication::translate("ServoWidget", "4", 0));
        rbNotUsed5->setText(QApplication::translate("ServoWidget", "5", 0));
        rbNotUsed6->setText(QApplication::translate("ServoWidget", "6", 0));
        rbNotUsed7->setText(QApplication::translate("ServoWidget", "7", 0));
        rbNotUsed8->setText(QApplication::translate("ServoWidget", "8", 0));
        gbServo->setTitle(QApplication::translate("ServoWidget", "Servo", 0));
        label_2->setText(QApplication::translate("ServoWidget", "Test", 0));
        btnTest1->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter1->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter1->setText(QApplication::translate("ServoWidget", "C", 0));
        btnTest2->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter2->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter2->setText(QApplication::translate("ServoWidget", "C", 0));
        btnTest3->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter3->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter3->setText(QApplication::translate("ServoWidget", "C", 0));
        btnTest4->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter4->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter4->setText(QApplication::translate("ServoWidget", "C", 0));
        btnTest5->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter5->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter5->setText(QApplication::translate("ServoWidget", "C", 0));
        btnTest6->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter6->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter6->setText(QApplication::translate("ServoWidget", "C", 0));
        btnTest7->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter7->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter7->setText(QApplication::translate("ServoWidget", "C", 0));
        btnTest8->setText(QApplication::translate("ServoWidget", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnCenter8->setToolTip(QApplication::translate("ServoWidget", "Click to Center Servo", 0));
#endif // QT_NO_TOOLTIP
        btnCenter8->setText(QApplication::translate("ServoWidget", "C", 0));
        lblServo1->setText(QApplication::translate("ServoWidget", "Position 1", 0));
        lbl11->setText(QApplication::translate("ServoWidget", "Pos1", 0));
        lbl12->setText(QApplication::translate("ServoWidget", "Pos3", 0));
        lbl13->setText(QApplication::translate("ServoWidget", "Pos1", 0));
        lbl14->setText(QApplication::translate("ServoWidget", "Pos3", 0));
        lbl15->setText(QApplication::translate("ServoWidget", "Pos1", 0));
        lbl16->setText(QApplication::translate("ServoWidget", "Pos3", 0));
        lbl17->setText(QApplication::translate("ServoWidget", "Pos1", 0));
        lbl18->setText(QApplication::translate("ServoWidget", "Pos3", 0));
        lblServo2->setText(QApplication::translate("ServoWidget", "Position 2", 0));
        lbl21->setText(QApplication::translate("ServoWidget", "Pos2", 0));
        lbl22->setText(QApplication::translate("ServoWidget", "Pos4", 0));
        lbl23->setText(QApplication::translate("ServoWidget", "Pos2", 0));
        lbl24->setText(QApplication::translate("ServoWidget", "Pos4", 0));
        lbl25->setText(QApplication::translate("ServoWidget", "Pos2", 0));
        lbl26->setText(QApplication::translate("ServoWidget", "Pos4", 0));
        lbl27->setText(QApplication::translate("ServoWidget", "Pos2", 0));
        lbl28->setText(QApplication::translate("ServoWidget", "Pos4", 0));
        lblServoSpeed->setText(QApplication::translate("ServoWidget", "Speed", 0));
        rbS1->setText(QString());
        rbS2->setText(QString());
        rbS3->setText(QString());
        rbS4->setText(QString());
        rbS5->setText(QString());
        rbS6->setText(QString());
        rbS7->setText(QString());
        rbS8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ServoWidget: public Ui_ServoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVOWIDGET_H
