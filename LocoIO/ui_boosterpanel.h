/********************************************************************************
** Form generated from reading UI file 'boosterpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOSTERPANEL_H
#define UI_BOOSTERPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoosterPanel
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *BoosterPanel)
    {
        if (BoosterPanel->objectName().isEmpty())
            BoosterPanel->setObjectName(QStringLiteral("BoosterPanel"));
        BoosterPanel->resize(144, 92);
        QFont font;
        font.setPointSize(7);
        BoosterPanel->setFont(font);
        verticalLayout = new QVBoxLayout(BoosterPanel);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(BoosterPanel);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(BoosterPanel);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(BoosterPanel);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);


        retranslateUi(BoosterPanel);

        QMetaObject::connectSlotsByName(BoosterPanel);
    } // setupUi

    void retranslateUi(QWidget *BoosterPanel)
    {
        BoosterPanel->setWindowTitle(QApplication::translate("BoosterPanel", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("BoosterPanel", "5 = Feedback of Booster input", Q_NULLPTR));
        label_2->setText(QApplication::translate("BoosterPanel", "6 = Feedback of Booster output", Q_NULLPTR));
        label_3->setText(QApplication::translate("BoosterPanel", "7 = On-Off Booster output", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BoosterPanel: public Ui_BoosterPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOSTERPANEL_H
