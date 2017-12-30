/********************************************************************************
** Form generated from reading UI file 'itempalettewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMPALETTEWIDGET_H
#define UI_ITEMPALETTEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemPaletteWidget
{
public:
    QHBoxLayout *horizontalLayout_ItemPalette;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_scrollArea;
    QTabWidget *_tabPane;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_6;
    QWidget *topPanel_Tab1;
    QVBoxLayout *verticalLayout_topPanelMemory;
    QLabel *label_2;
    QTableWidget *tableWidget_2;
    QHBoxLayout *horizontalLayout_topPanelTab1;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *MemoryTab;
    QVBoxLayout *verticalLayout_Memory;
    QWidget *topPanel;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *instructions;
    QVBoxLayout *verticalLayout_instructions;
    QLabel *blurb1;
    QLabel *blurb2;
    QHBoxLayout *blurb3Layout;
    QLabel *blurb3Icon;
    QLabel *blurb3Text;
    QLabel *blurb4;
    QLabel *blurb5;
    QSpacerItem *horizontalSpacer_instructions;
    QLabel *blurb6;
    QLabel *blurb7;
    QWidget *_DnDIconPanel;
    QGridLayout *gridLayout_DND;
    QWidget *_writeMem;
    QVBoxLayout *verticalLayout_InputBoxMemory_2;
    QGroupBox *gbInputBox;
    QVBoxLayout *verticalLayout_gbInputBoxMemory;
    QLineEdit *_textBox;
    QWidget *displayMemory;
    QVBoxLayout *verticalLayout_DisplayMemory;
    QGroupBox *gbDisplayMemory;
    QVBoxLayout *verticalLayout_gbDisplayMemory;
    QLabel *label_20;
    QWidget *spinnerMemory;
    QVBoxLayout *verticalLayout_SpinnerMemory;
    QGroupBox *gbSpinnerMemory;
    QVBoxLayout *verticalLayout_gbSpinnerMemory;
    QSpinBox *_spinnerMemory;
    QHBoxLayout *horizontalLayout_colWidth;
    QLabel *lbColWidth;
    QSpinBox *_spinner;
    QSpacerItem *horizontalSpacer_2;
    QWidget *comboBoxMemory;
    QVBoxLayout *verticalLayout_InputBoxMemory;
    QLabel *lbComboBoxMemory;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lbInputBoxMemory;
    QLabel *lbSpinnerMemory;
    QLabel *lbDisplayMemory;
    QGroupBox *gbComboBoxMemory;
    QVBoxLayout *verticalLayout_gbComboBoxMemory;
    QComboBox *_comboBox;

    void setupUi(QWidget *ItemPaletteWidget)
    {
        if (ItemPaletteWidget->objectName().isEmpty())
            ItemPaletteWidget->setObjectName(QStringLiteral("ItemPaletteWidget"));
        ItemPaletteWidget->resize(494, 846);
        horizontalLayout_ItemPalette = new QHBoxLayout(ItemPaletteWidget);
        horizontalLayout_ItemPalette->setObjectName(QStringLiteral("horizontalLayout_ItemPalette"));
        scrollArea = new QScrollArea(ItemPaletteWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 493, 810));
        verticalLayout_scrollArea = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_scrollArea->setObjectName(QStringLiteral("verticalLayout_scrollArea"));
        _tabPane = new QTabWidget(scrollAreaWidgetContents);
        _tabPane->setObjectName(QStringLiteral("_tabPane"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_6 = new QHBoxLayout(tab);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        topPanel_Tab1 = new QWidget(tab);
        topPanel_Tab1->setObjectName(QStringLiteral("topPanel_Tab1"));
        verticalLayout_topPanelMemory = new QVBoxLayout(topPanel_Tab1);
        verticalLayout_topPanelMemory->setObjectName(QStringLiteral("verticalLayout_topPanelMemory"));
        label_2 = new QLabel(topPanel_Tab1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_topPanelMemory->addWidget(label_2);

        tableWidget_2 = new QTableWidget(topPanel_Tab1);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));

        verticalLayout_topPanelMemory->addWidget(tableWidget_2);

        horizontalLayout_topPanelTab1 = new QHBoxLayout();
        horizontalLayout_topPanelTab1->setObjectName(QStringLiteral("horizontalLayout_topPanelTab1"));
        pushButton_3 = new QPushButton(topPanel_Tab1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        horizontalLayout_topPanelTab1->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(topPanel_Tab1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);

        horizontalLayout_topPanelTab1->addWidget(pushButton_4);


        verticalLayout_topPanelMemory->addLayout(horizontalLayout_topPanelTab1);


        horizontalLayout_6->addWidget(topPanel_Tab1);

        _tabPane->addTab(tab, QString());
        MemoryTab = new QWidget();
        MemoryTab->setObjectName(QStringLiteral("MemoryTab"));
        verticalLayout_Memory = new QVBoxLayout(MemoryTab);
        verticalLayout_Memory->setObjectName(QStringLiteral("verticalLayout_Memory"));
        topPanel = new QWidget(MemoryTab);
        topPanel->setObjectName(QStringLiteral("topPanel"));
        verticalLayout_2 = new QVBoxLayout(topPanel);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(topPanel);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        tableWidget = new QTableWidget(topPanel);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(topPanel);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(topPanel);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_Memory->addWidget(topPanel);

        instructions = new QWidget(MemoryTab);
        instructions->setObjectName(QStringLiteral("instructions"));
        QFont font;
        font.setPointSize(8);
        instructions->setFont(font);
        verticalLayout_instructions = new QVBoxLayout(instructions);
        verticalLayout_instructions->setObjectName(QStringLiteral("verticalLayout_instructions"));
        blurb1 = new QLabel(instructions);
        blurb1->setObjectName(QStringLiteral("blurb1"));

        verticalLayout_instructions->addWidget(blurb1);

        blurb2 = new QLabel(instructions);
        blurb2->setObjectName(QStringLiteral("blurb2"));

        verticalLayout_instructions->addWidget(blurb2);

        blurb3Layout = new QHBoxLayout();
        blurb3Layout->setObjectName(QStringLiteral("blurb3Layout"));
        blurb3Icon = new QLabel(instructions);
        blurb3Icon->setObjectName(QStringLiteral("blurb3Icon"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(blurb3Icon->sizePolicy().hasHeightForWidth());
        blurb3Icon->setSizePolicy(sizePolicy1);
        blurb3Icon->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/misc/X-red.gif")));

        blurb3Layout->addWidget(blurb3Icon);

        blurb3Text = new QLabel(instructions);
        blurb3Text->setObjectName(QStringLiteral("blurb3Text"));

        blurb3Layout->addWidget(blurb3Text);


        verticalLayout_instructions->addLayout(blurb3Layout);

        blurb4 = new QLabel(instructions);
        blurb4->setObjectName(QStringLiteral("blurb4"));

        verticalLayout_instructions->addWidget(blurb4);

        blurb5 = new QLabel(instructions);
        blurb5->setObjectName(QStringLiteral("blurb5"));

        verticalLayout_instructions->addWidget(blurb5);

        horizontalSpacer_instructions = new QSpacerItem(432, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_instructions->addItem(horizontalSpacer_instructions);

        blurb6 = new QLabel(instructions);
        blurb6->setObjectName(QStringLiteral("blurb6"));

        verticalLayout_instructions->addWidget(blurb6);

        blurb7 = new QLabel(instructions);
        blurb7->setObjectName(QStringLiteral("blurb7"));

        verticalLayout_instructions->addWidget(blurb7);


        verticalLayout_Memory->addWidget(instructions);

        _DnDIconPanel = new QWidget(MemoryTab);
        _DnDIconPanel->setObjectName(QStringLiteral("_DnDIconPanel"));
        gridLayout_DND = new QGridLayout(_DnDIconPanel);
        gridLayout_DND->setObjectName(QStringLiteral("gridLayout_DND"));
        gridLayout_DND->setSizeConstraint(QLayout::SetFixedSize);
        _writeMem = new QWidget(_DnDIconPanel);
        _writeMem->setObjectName(QStringLiteral("_writeMem"));
        verticalLayout_InputBoxMemory_2 = new QVBoxLayout(_writeMem);
        verticalLayout_InputBoxMemory_2->setObjectName(QStringLiteral("verticalLayout_InputBoxMemory_2"));
        gbInputBox = new QGroupBox(_writeMem);
        gbInputBox->setObjectName(QStringLiteral("gbInputBox"));
        verticalLayout_gbInputBoxMemory = new QVBoxLayout(gbInputBox);
        verticalLayout_gbInputBoxMemory->setObjectName(QStringLiteral("verticalLayout_gbInputBoxMemory"));
        _textBox = new QLineEdit(gbInputBox);
        _textBox->setObjectName(QStringLiteral("_textBox"));

        verticalLayout_gbInputBoxMemory->addWidget(_textBox);


        verticalLayout_InputBoxMemory_2->addWidget(gbInputBox);


        gridLayout_DND->addWidget(_writeMem, 1, 0, 1, 1);

        displayMemory = new QWidget(_DnDIconPanel);
        displayMemory->setObjectName(QStringLiteral("displayMemory"));
        verticalLayout_DisplayMemory = new QVBoxLayout(displayMemory);
        verticalLayout_DisplayMemory->setObjectName(QStringLiteral("verticalLayout_DisplayMemory"));
        gbDisplayMemory = new QGroupBox(displayMemory);
        gbDisplayMemory->setObjectName(QStringLiteral("gbDisplayMemory"));
        verticalLayout_gbDisplayMemory = new QVBoxLayout(gbDisplayMemory);
        verticalLayout_gbDisplayMemory->setObjectName(QStringLiteral("verticalLayout_gbDisplayMemory"));
        label_20 = new QLabel(gbDisplayMemory);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setPixmap(QPixmap(QString::fromUtf8(":/resources/icons/misc/X-red.gif")));
        label_20->setAlignment(Qt::AlignCenter);

        verticalLayout_gbDisplayMemory->addWidget(label_20);


        verticalLayout_DisplayMemory->addWidget(gbDisplayMemory);


        gridLayout_DND->addWidget(displayMemory, 1, 1, 1, 1);

        spinnerMemory = new QWidget(_DnDIconPanel);
        spinnerMemory->setObjectName(QStringLiteral("spinnerMemory"));
        verticalLayout_SpinnerMemory = new QVBoxLayout(spinnerMemory);
        verticalLayout_SpinnerMemory->setObjectName(QStringLiteral("verticalLayout_SpinnerMemory"));
        gbSpinnerMemory = new QGroupBox(spinnerMemory);
        gbSpinnerMemory->setObjectName(QStringLiteral("gbSpinnerMemory"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gbSpinnerMemory->sizePolicy().hasHeightForWidth());
        gbSpinnerMemory->setSizePolicy(sizePolicy2);
        verticalLayout_gbSpinnerMemory = new QVBoxLayout(gbSpinnerMemory);
        verticalLayout_gbSpinnerMemory->setObjectName(QStringLiteral("verticalLayout_gbSpinnerMemory"));
        _spinnerMemory = new QSpinBox(gbSpinnerMemory);
        _spinnerMemory->setObjectName(QStringLiteral("_spinnerMemory"));

        verticalLayout_gbSpinnerMemory->addWidget(_spinnerMemory);


        verticalLayout_SpinnerMemory->addWidget(gbSpinnerMemory);


        gridLayout_DND->addWidget(spinnerMemory, 1, 2, 1, 2);

        horizontalLayout_colWidth = new QHBoxLayout();
        horizontalLayout_colWidth->setObjectName(QStringLiteral("horizontalLayout_colWidth"));
        lbColWidth = new QLabel(_DnDIconPanel);
        lbColWidth->setObjectName(QStringLiteral("lbColWidth"));

        horizontalLayout_colWidth->addWidget(lbColWidth);

        _spinner = new QSpinBox(_DnDIconPanel);
        _spinner->setObjectName(QStringLiteral("_spinner"));

        horizontalLayout_colWidth->addWidget(_spinner);


        gridLayout_DND->addLayout(horizontalLayout_colWidth, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_DND->addItem(horizontalSpacer_2, 3, 0, 1, 1);

        comboBoxMemory = new QWidget(_DnDIconPanel);
        comboBoxMemory->setObjectName(QStringLiteral("comboBoxMemory"));
        verticalLayout_InputBoxMemory = new QVBoxLayout(comboBoxMemory);
        verticalLayout_InputBoxMemory->setObjectName(QStringLiteral("verticalLayout_InputBoxMemory"));
        lbComboBoxMemory = new QLabel(comboBoxMemory);
        lbComboBoxMemory->setObjectName(QStringLiteral("lbComboBoxMemory"));

        verticalLayout_InputBoxMemory->addWidget(lbComboBoxMemory);


        gridLayout_DND->addWidget(comboBoxMemory, 3, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_DND->addItem(horizontalSpacer_3, 3, 3, 1, 1);

        lbInputBoxMemory = new QLabel(_DnDIconPanel);
        lbInputBoxMemory->setObjectName(QStringLiteral("lbInputBoxMemory"));

        gridLayout_DND->addWidget(lbInputBoxMemory, 0, 0, 1, 1);

        lbSpinnerMemory = new QLabel(_DnDIconPanel);
        lbSpinnerMemory->setObjectName(QStringLiteral("lbSpinnerMemory"));

        gridLayout_DND->addWidget(lbSpinnerMemory, 0, 3, 1, 1);

        lbDisplayMemory = new QLabel(_DnDIconPanel);
        lbDisplayMemory->setObjectName(QStringLiteral("lbDisplayMemory"));

        gridLayout_DND->addWidget(lbDisplayMemory, 0, 1, 1, 1);

        gbComboBoxMemory = new QGroupBox(_DnDIconPanel);
        gbComboBoxMemory->setObjectName(QStringLiteral("gbComboBoxMemory"));
        verticalLayout_gbComboBoxMemory = new QVBoxLayout(gbComboBoxMemory);
        verticalLayout_gbComboBoxMemory->setObjectName(QStringLiteral("verticalLayout_gbComboBoxMemory"));
        _comboBox = new QComboBox(gbComboBoxMemory);
        _comboBox->setObjectName(QStringLiteral("_comboBox"));

        verticalLayout_gbComboBoxMemory->addWidget(_comboBox);


        gridLayout_DND->addWidget(gbComboBoxMemory, 4, 1, 1, 1);


        verticalLayout_Memory->addWidget(_DnDIconPanel);

        _tabPane->addTab(MemoryTab, QString());

        verticalLayout_scrollArea->addWidget(_tabPane);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_ItemPalette->addWidget(scrollArea);


        retranslateUi(ItemPaletteWidget);

        _tabPane->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ItemPaletteWidget);
    } // setupUi

    void retranslateUi(QWidget *ItemPaletteWidget)
    {
        ItemPaletteWidget->setWindowTitle(QApplication::translate("ItemPaletteWidget", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("ItemPaletteWidget", "Memory Table", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ItemPaletteWidget", "Add New Table Item ", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ItemPaletteWidget", "Clear Table Selections", Q_NULLPTR));
        _tabPane->setTabText(_tabPane->indexOf(tab), QApplication::translate("ItemPaletteWidget", "Turnout 1", Q_NULLPTR));
        label->setText(QApplication::translate("ItemPaletteWidget", "Memory Table", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ItemPaletteWidget", "Add New Table Item ", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ItemPaletteWidget", "Clear Table Selections", Q_NULLPTR));
        blurb1->setText(QApplication::translate("ItemPaletteWidget", "To Add an Icon to your control panel:", Q_NULLPTR));
        blurb2->setText(QApplication::translate("ItemPaletteWidget", "--drag and icon from the display panel below to your control panel", Q_NULLPTR));
        blurb3Icon->setText(QString());
        blurb3Text->setText(QApplication::translate("ItemPaletteWidget", "is displayed for the Display Memory Icon when Memory is null.", Q_NULLPTR));
        blurb4->setText(QApplication::translate("ItemPaletteWidget", "When memory is and empty string i.e. \"\", the display memory icon is blank.", Q_NULLPTR));
        blurb5->setText(QApplication::translate("ItemPaletteWidget", "When blank, enter a value in the other memory icons to view and drag it. ", Q_NULLPTR));
        blurb6->setText(QApplication::translate("ItemPaletteWidget", "The ComboBox Memory Icon sets a memory by selecting and item from the ComboBox.", Q_NULLPTR));
        blurb7->setText(QApplication::translate("ItemPaletteWidget", "Use the \"Edit Memory Icon\" popup to add or delete items.", Q_NULLPTR));
        gbInputBox->setTitle(QApplication::translate("ItemPaletteWidget", "Drag to Panel", Q_NULLPTR));
        gbDisplayMemory->setTitle(QApplication::translate("ItemPaletteWidget", "Drag to Panel", Q_NULLPTR));
        label_20->setText(QString());
        gbSpinnerMemory->setTitle(QApplication::translate("ItemPaletteWidget", "Drag to Panel", Q_NULLPTR));
        lbColWidth->setText(QApplication::translate("ItemPaletteWidget", "Col Width", Q_NULLPTR));
        lbComboBoxMemory->setText(QApplication::translate("ItemPaletteWidget", "ComboBox Memory", Q_NULLPTR));
        lbInputBoxMemory->setText(QApplication::translate("ItemPaletteWidget", "Input Box Memory", Q_NULLPTR));
        lbSpinnerMemory->setText(QApplication::translate("ItemPaletteWidget", "Spinner Memory", Q_NULLPTR));
        lbDisplayMemory->setText(QApplication::translate("ItemPaletteWidget", "Display Memory", Q_NULLPTR));
        gbComboBoxMemory->setTitle(QApplication::translate("ItemPaletteWidget", "Drag to Panel", Q_NULLPTR));
        _tabPane->setTabText(_tabPane->indexOf(MemoryTab), QApplication::translate("ItemPaletteWidget", "Memory", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ItemPaletteWidget: public Ui_ItemPaletteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMPALETTEWIDGET_H
