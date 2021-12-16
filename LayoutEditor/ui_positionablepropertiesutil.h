/********************************************************************************
** Form generated from reading UI file 'positionablepropertiesutil.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITIONABLEPROPERTIESUTIL_H
#define UI_POSITIONABLEPROPERTIESUTIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PositionablePropertiesUtil
{
public:
    QFormLayout *formLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *cancel;
    QPushButton *applyButton;
    QPushButton *okButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QComboBox *fontSizeField;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QComboBox *_justificationCombo;
    QCheckBox *bold;
    QFontComboBox *fontComboBox;
    QCheckBox *italic;
    QLabel *label_10;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lbFontColor;
    QComboBox *fontColor;
    QLabel *lbBackgroundColor;
    QComboBox *backgroundColor;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *textField;
    QWidget *tab_3;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *borderColorCombo;
    QSplitter *splitter;
    QLabel *label_2;
    QSpinBox *borderSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *marginSize;
    QWidget *tab_4;
    QGridLayout *gridLayout;
    QSpinBox *height;
    QSpinBox *width;
    QLabel *label_7;
    QLabel *label_5;
    QSpinBox *xPosition;
    QLabel *label_6;
    QSpinBox *yPosition;
    QLabel *label_8;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *tmp;

    void setupUi(QDialog *PositionablePropertiesUtil)
    {
        if (PositionablePropertiesUtil->objectName().isEmpty())
            PositionablePropertiesUtil->setObjectName(QLatin1String("PositionablePropertiesUtil"));
        PositionablePropertiesUtil->resize(484, 409);
        formLayout_2 = new QFormLayout(PositionablePropertiesUtil);
        formLayout_2->setObjectName(QLatin1String("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QLatin1String("horizontalLayout_4"));
        cancel = new QPushButton(PositionablePropertiesUtil);
        cancel->setObjectName(QLatin1String("cancel"));

        horizontalLayout_4->addWidget(cancel);

        applyButton = new QPushButton(PositionablePropertiesUtil);
        applyButton->setObjectName(QLatin1String("applyButton"));

        horizontalLayout_4->addWidget(applyButton);

        okButton = new QPushButton(PositionablePropertiesUtil);
        okButton->setObjectName(QLatin1String("okButton"));

        horizontalLayout_4->addWidget(okButton);


        formLayout_2->setLayout(2, QFormLayout::SpanningRole, horizontalLayout_4);

        tabWidget = new QTabWidget(PositionablePropertiesUtil);
        tabWidget->setObjectName(QLatin1String("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QLatin1String("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QLatin1String("gridLayout_2"));
        fontSizeField = new QComboBox(tab);
        fontSizeField->setObjectName(QLatin1String("fontSizeField"));

        gridLayout_2->addWidget(fontSizeField, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QLatin1String("horizontalLayout_5"));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QLatin1String("label_9"));

        horizontalLayout_5->addWidget(label_9);

        _justificationCombo = new QComboBox(tab);
        _justificationCombo->addItem(QString());
        _justificationCombo->addItem(QString());
        _justificationCombo->addItem(QString());
        _justificationCombo->setObjectName(QLatin1String("_justificationCombo"));

        horizontalLayout_5->addWidget(_justificationCombo);


        gridLayout_2->addLayout(horizontalLayout_5, 5, 1, 1, 1);

        bold = new QCheckBox(tab);
        bold->setObjectName(QLatin1String("bold"));

        gridLayout_2->addWidget(bold, 3, 2, 1, 1);

        fontComboBox = new QFontComboBox(tab);
        fontComboBox->setObjectName(QLatin1String("fontComboBox"));

        gridLayout_2->addWidget(fontComboBox, 0, 0, 1, 3);

        italic = new QCheckBox(tab);
        italic->setObjectName(QLatin1String("italic"));

        gridLayout_2->addWidget(italic, 4, 2, 1, 1);

        label_10 = new QLabel(tab);
        label_10->setObjectName(QLatin1String("label_10"));

        gridLayout_2->addWidget(label_10, 2, 1, 1, 1);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QLatin1String("groupBox_2"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_2);
        horizontalLayout_7->setObjectName(QLatin1String("horizontalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QLatin1String("horizontalLayout_6"));
        lbFontColor = new QLabel(groupBox_2);
        lbFontColor->setObjectName(QLatin1String("lbFontColor"));

        horizontalLayout_6->addWidget(lbFontColor);

        fontColor = new QComboBox(groupBox_2);
        fontColor->setObjectName(QLatin1String("fontColor"));

        horizontalLayout_6->addWidget(fontColor);

        lbBackgroundColor = new QLabel(groupBox_2);
        lbBackgroundColor->setObjectName(QLatin1String("lbBackgroundColor"));

        horizontalLayout_6->addWidget(lbBackgroundColor);

        backgroundColor = new QComboBox(groupBox_2);
        backgroundColor->setObjectName(QLatin1String("backgroundColor"));

        horizontalLayout_6->addWidget(backgroundColor);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        gridLayout_2->addWidget(groupBox_2, 6, 0, 1, 3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QLatin1String("tab_2"));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QLatin1String("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 227, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QLatin1String("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QLatin1String("label_4"));

        horizontalLayout_3->addWidget(label_4);

        textField = new QLineEdit(layoutWidget);
        textField->setObjectName(QLatin1String("textField"));

        horizontalLayout_3->addWidget(textField);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QLatin1String("tab_3"));
        formLayout = new QFormLayout(tab_3);
        formLayout->setObjectName(QLatin1String("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        label = new QLabel(tab_3);
        label->setObjectName(QLatin1String("label"));

        horizontalLayout->addWidget(label);

        borderColorCombo = new QComboBox(tab_3);
        borderColorCombo->setObjectName(QLatin1String("borderColorCombo"));

        horizontalLayout->addWidget(borderColorCombo);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        splitter = new QSplitter(tab_3);
        splitter->setObjectName(QLatin1String("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QLatin1String("label_2"));
        splitter->addWidget(label_2);
        borderSize = new QSpinBox(splitter);
        borderSize->setObjectName(QLatin1String("borderSize"));
        splitter->addWidget(borderSize);

        formLayout->setWidget(1, QFormLayout::LabelRole, splitter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QLatin1String("label_3"));

        horizontalLayout_2->addWidget(label_3);

        marginSize = new QSpinBox(tab_3);
        marginSize->setObjectName(QLatin1String("marginSize"));

        horizontalLayout_2->addWidget(marginSize);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_2);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QLatin1String("tab_4"));
        gridLayout = new QGridLayout(tab_4);
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        height = new QSpinBox(tab_4);
        height->setObjectName(QLatin1String("height"));
        height->setMinimum(0);

        gridLayout->addWidget(height, 3, 1, 1, 1);

        width = new QSpinBox(tab_4);
        width->setObjectName(QLatin1String("width"));
        width->setMinimum(0);

        gridLayout->addWidget(width, 2, 1, 1, 1);

        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QLatin1String("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QLatin1String("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        xPosition = new QSpinBox(tab_4);
        xPosition->setObjectName(QLatin1String("xPosition"));
        xPosition->setMaximum(1000);

        gridLayout->addWidget(xPosition, 0, 1, 1, 1);

        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QLatin1String("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        yPosition = new QSpinBox(tab_4);
        yPosition->setObjectName(QLatin1String("yPosition"));
        yPosition->setMaximum(1000);

        gridLayout->addWidget(yPosition, 1, 1, 1, 1);

        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QLatin1String("label_8"));

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        formLayout_2->setWidget(0, QFormLayout::SpanningRole, tabWidget);

        groupBox = new QGroupBox(PositionablePropertiesUtil);
        groupBox->setObjectName(QLatin1String("groupBox"));
        groupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setObjectName(QLatin1String("horizontalLayout_8"));
        tmp = new QLabel(groupBox);
        tmp->setObjectName(QLatin1String("tmp"));
        tmp->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(tmp);


        formLayout_2->setWidget(1, QFormLayout::FieldRole, groupBox);


        retranslateUi(PositionablePropertiesUtil);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PositionablePropertiesUtil);
    } // setupUi

    void retranslateUi(QDialog *PositionablePropertiesUtil)
    {
        PositionablePropertiesUtil->setWindowTitle(QApplication::translate("PositionablePropertiesUtil", "Dialog", nullptr));
        cancel->setText(QApplication::translate("PositionablePropertiesUtil", "Cancel", nullptr));
        applyButton->setText(QApplication::translate("PositionablePropertiesUtil", "Apply", nullptr));
        okButton->setText(QApplication::translate("PositionablePropertiesUtil", "OK", nullptr));
        label_9->setText(QApplication::translate("PositionablePropertiesUtil", "Justification", nullptr));
        _justificationCombo->setItemText(0, QApplication::translate("PositionablePropertiesUtil", "Left", nullptr));
        _justificationCombo->setItemText(1, QApplication::translate("PositionablePropertiesUtil", "Right", nullptr));
        _justificationCombo->setItemText(2, QApplication::translate("PositionablePropertiesUtil", "Center", nullptr));

        bold->setText(QApplication::translate("PositionablePropertiesUtil", "Bold", nullptr));
        italic->setText(QApplication::translate("PositionablePropertiesUtil", "Italic", nullptr));
        label_10->setText(QString());
        groupBox_2->setTitle(QApplication::translate("PositionablePropertiesUtil", "GroupBox", nullptr));
        lbFontColor->setText(QApplication::translate("PositionablePropertiesUtil", "Font Color", nullptr));
        lbBackgroundColor->setText(QApplication::translate("PositionablePropertiesUtil", "Background Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PositionablePropertiesUtil", "Font", nullptr));
        label_4->setText(QApplication::translate("PositionablePropertiesUtil", "Text Value", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("PositionablePropertiesUtil", "Edit Text", nullptr));
        label->setText(QApplication::translate("PositionablePropertiesUtil", "Border Color", nullptr));
        label_2->setText(QApplication::translate("PositionablePropertiesUtil", "Border Size", nullptr));
        label_3->setText(QApplication::translate("PositionablePropertiesUtil", "Margin Size", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("PositionablePropertiesUtil", "Border", nullptr));
        label_7->setText(QApplication::translate("PositionablePropertiesUtil", "Width = ", nullptr));
        label_5->setText(QApplication::translate("PositionablePropertiesUtil", "x = ", nullptr));
        label_6->setText(QApplication::translate("PositionablePropertiesUtil", "y= ", nullptr));
        label_8->setText(QApplication::translate("PositionablePropertiesUtil", "Height = ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("PositionablePropertiesUtil", "Size and Position", nullptr));
        groupBox->setTitle(QApplication::translate("PositionablePropertiesUtil", "Preview", nullptr));
        tmp->setText(QApplication::translate("PositionablePropertiesUtil", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PositionablePropertiesUtil: public Ui_PositionablePropertiesUtil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITIONABLEPROPERTIESUTIL_H
