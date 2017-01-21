/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit;
    QLabel *label;
    QWidget *previewPanel;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *js;
    QWidget *_preview;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(326, 176);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form->sizePolicy().hasHeightForWidth());
        Form->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(Form);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(lineEdit);

        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        previewPanel = new QWidget(Form);
        previewPanel->setObjectName(QStringLiteral("previewPanel"));
        sizePolicy.setHeightForWidth(previewPanel->sizePolicy().hasHeightForWidth());
        previewPanel->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(previewPanel);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        js = new QScrollArea(previewPanel);
        js->setObjectName(QStringLiteral("js"));
        js->setWidgetResizable(true);
        _preview = new QWidget();
        _preview->setObjectName(QStringLiteral("_preview"));
        _preview->setGeometry(QRect(0, 0, 272, 104));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(_preview->sizePolicy().hasHeightForWidth());
        _preview->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(_preview);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        frame = new QFrame(_preview);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../../../../test.png")));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);


        verticalLayout_4->addWidget(frame);

        js->setWidget(_preview);

        verticalLayout_2->addWidget(js);


        verticalLayout_3->addWidget(previewPanel);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label->setText(QApplication::translate("Form", "TextLabel", 0));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("Form", "TextLabel", 0));
        label_4->setText(QApplication::translate("Form", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
