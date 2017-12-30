/********************************************************************************
** Form generated from reading UI file 'audiowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOWIDGET_H
#define UI_AUDIOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *addSource;
    QPushButton *addBuffer;

    void setupUi(QWidget *AudioWidget)
    {
        if (AudioWidget->objectName().isEmpty())
            AudioWidget->setObjectName(QStringLiteral("AudioWidget"));
        AudioWidget->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(AudioWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addSource = new QPushButton(AudioWidget);
        addSource->setObjectName(QStringLiteral("addSource"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addSource->sizePolicy().hasHeightForWidth());
        addSource->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(addSource);

        addBuffer = new QPushButton(AudioWidget);
        addBuffer->setObjectName(QStringLiteral("addBuffer"));
        sizePolicy.setHeightForWidth(addBuffer->sizePolicy().hasHeightForWidth());
        addBuffer->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(addBuffer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(AudioWidget);

        QMetaObject::connectSlotsByName(AudioWidget);
    } // setupUi

    void retranslateUi(QWidget *AudioWidget)
    {
        AudioWidget->setWindowTitle(QApplication::translate("AudioWidget", "Form", Q_NULLPTR));
        addSource->setText(QApplication::translate("AudioWidget", "Add Source...", Q_NULLPTR));
        addBuffer->setText(QApplication::translate("AudioWidget", "Add Buffer...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AudioWidget: public Ui_AudioWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOWIDGET_H
