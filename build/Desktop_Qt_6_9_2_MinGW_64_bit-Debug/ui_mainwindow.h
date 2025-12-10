/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *layoutSelectFile;
    QLabel *labelSelectedFile;
    QPushButton *btnSelectFile;
    QGroupBox *groupFileInfo;
    QFormLayout *formFileInfo;
    QLabel *labelFilePath;
    QLabel *valueFilePath;
    QLabel *labelFileSize;
    QLabel *valueFileSize;
    QLabel *labelCharCount;
    QLabel *valueCharCount;
    QGroupBox *groupAnalysis;
    QFormLayout *formAnalysis;
    QLabel *labelMostChar;
    QLabel *valueMostChar;
    QLabel *labelMostCount;
    QLabel *valueMostCount;
    QLabel *labelFrequency;
    QLabel *valueFrequency;
    QGroupBox *groupSearch;
    QFormLayout *formSearch;
    QLabel *labelSearch;
    QLineEdit *editSearchString;
    QLabel *labelSearchResult;
    QLabel *valueSearchResult;
    QPushButton *btnSearchString;
    QHBoxLayout *layoutBottomButtons;
    QPushButton *btnStartAnalysis;
    QPushButton *btnClear;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(640, 554);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        layoutSelectFile = new QHBoxLayout();
        layoutSelectFile->setObjectName("layoutSelectFile");
        labelSelectedFile = new QLabel(centralwidget);
        labelSelectedFile->setObjectName("labelSelectedFile");

        layoutSelectFile->addWidget(labelSelectedFile);

        btnSelectFile = new QPushButton(centralwidget);
        btnSelectFile->setObjectName("btnSelectFile");

        layoutSelectFile->addWidget(btnSelectFile);


        verticalLayout->addLayout(layoutSelectFile);

        groupFileInfo = new QGroupBox(centralwidget);
        groupFileInfo->setObjectName("groupFileInfo");
        formFileInfo = new QFormLayout(groupFileInfo);
        formFileInfo->setObjectName("formFileInfo");
        labelFilePath = new QLabel(groupFileInfo);
        labelFilePath->setObjectName("labelFilePath");

        formFileInfo->setWidget(0, QFormLayout::ItemRole::LabelRole, labelFilePath);

        valueFilePath = new QLabel(groupFileInfo);
        valueFilePath->setObjectName("valueFilePath");

        formFileInfo->setWidget(0, QFormLayout::ItemRole::FieldRole, valueFilePath);

        labelFileSize = new QLabel(groupFileInfo);
        labelFileSize->setObjectName("labelFileSize");

        formFileInfo->setWidget(1, QFormLayout::ItemRole::LabelRole, labelFileSize);

        valueFileSize = new QLabel(groupFileInfo);
        valueFileSize->setObjectName("valueFileSize");

        formFileInfo->setWidget(1, QFormLayout::ItemRole::FieldRole, valueFileSize);

        labelCharCount = new QLabel(groupFileInfo);
        labelCharCount->setObjectName("labelCharCount");

        formFileInfo->setWidget(2, QFormLayout::ItemRole::LabelRole, labelCharCount);

        valueCharCount = new QLabel(groupFileInfo);
        valueCharCount->setObjectName("valueCharCount");

        formFileInfo->setWidget(2, QFormLayout::ItemRole::FieldRole, valueCharCount);


        verticalLayout->addWidget(groupFileInfo);

        groupAnalysis = new QGroupBox(centralwidget);
        groupAnalysis->setObjectName("groupAnalysis");
        formAnalysis = new QFormLayout(groupAnalysis);
        formAnalysis->setObjectName("formAnalysis");
        labelMostChar = new QLabel(groupAnalysis);
        labelMostChar->setObjectName("labelMostChar");

        formAnalysis->setWidget(0, QFormLayout::ItemRole::LabelRole, labelMostChar);

        valueMostChar = new QLabel(groupAnalysis);
        valueMostChar->setObjectName("valueMostChar");

        formAnalysis->setWidget(0, QFormLayout::ItemRole::FieldRole, valueMostChar);

        labelMostCount = new QLabel(groupAnalysis);
        labelMostCount->setObjectName("labelMostCount");

        formAnalysis->setWidget(1, QFormLayout::ItemRole::LabelRole, labelMostCount);

        valueMostCount = new QLabel(groupAnalysis);
        valueMostCount->setObjectName("valueMostCount");

        formAnalysis->setWidget(1, QFormLayout::ItemRole::FieldRole, valueMostCount);

        labelFrequency = new QLabel(groupAnalysis);
        labelFrequency->setObjectName("labelFrequency");

        formAnalysis->setWidget(2, QFormLayout::ItemRole::LabelRole, labelFrequency);

        valueFrequency = new QLabel(groupAnalysis);
        valueFrequency->setObjectName("valueFrequency");

        formAnalysis->setWidget(2, QFormLayout::ItemRole::FieldRole, valueFrequency);


        verticalLayout->addWidget(groupAnalysis);

        groupSearch = new QGroupBox(centralwidget);
        groupSearch->setObjectName("groupSearch");
        formSearch = new QFormLayout(groupSearch);
        formSearch->setObjectName("formSearch");
        labelSearch = new QLabel(groupSearch);
        labelSearch->setObjectName("labelSearch");

        formSearch->setWidget(0, QFormLayout::ItemRole::LabelRole, labelSearch);

        editSearchString = new QLineEdit(groupSearch);
        editSearchString->setObjectName("editSearchString");

        formSearch->setWidget(0, QFormLayout::ItemRole::FieldRole, editSearchString);

        labelSearchResult = new QLabel(groupSearch);
        labelSearchResult->setObjectName("labelSearchResult");

        formSearch->setWidget(1, QFormLayout::ItemRole::LabelRole, labelSearchResult);

        valueSearchResult = new QLabel(groupSearch);
        valueSearchResult->setObjectName("valueSearchResult");

        formSearch->setWidget(1, QFormLayout::ItemRole::FieldRole, valueSearchResult);

        btnSearchString = new QPushButton(groupSearch);
        btnSearchString->setObjectName("btnSearchString");

        formSearch->setWidget(2, QFormLayout::ItemRole::FieldRole, btnSearchString);


        verticalLayout->addWidget(groupSearch);

        layoutBottomButtons = new QHBoxLayout();
        layoutBottomButtons->setObjectName("layoutBottomButtons");
        btnStartAnalysis = new QPushButton(centralwidget);
        btnStartAnalysis->setObjectName("btnStartAnalysis");

        layoutBottomButtons->addWidget(btnStartAnalysis);

        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");

        layoutBottomButtons->addWidget(btnClear);


        verticalLayout->addLayout(layoutBottomButtons);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Char Frequency Analyzer", nullptr));
        labelSelectedFile->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273: (\320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275)", nullptr));
        btnSelectFile->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        groupFileInfo->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 \321\204\320\260\320\271\320\273\320\265", nullptr));
        labelFilePath->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214:", nullptr));
        labelFileSize->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 (\320\261\320\260\320\271\321\202):", nullptr));
        labelCharCount->setText(QCoreApplication::translate("MainWindow", "\320\247\320\270\321\201\320\273\320\276 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262 (UTF-8):", nullptr));
        groupAnalysis->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\260\320\275\320\260\320\273\320\270\320\267\320\260", nullptr));
        labelMostChar->setText(QCoreApplication::translate("MainWindow", "\320\241\320\260\320\274\321\213\320\271 \321\207\320\260\321\201\321\202\321\213\320\271 \321\201\320\270\320\274\320\262\320\276\320\273:", nullptr));
        labelMostCount->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        labelFrequency->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 (%):", nullptr));
        groupSearch->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276\320\264\321\201\321\202\321\200\320\276\320\272\320\270", nullptr));
        labelSearch->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\276\320\264\321\201\321\202\321\200\320\276\320\272\321\203:", nullptr));
        labelSearchResult->setText(QCoreApplication::translate("MainWindow", "\320\222\321\205\320\276\320\266\320\264\320\265\320\275\320\270\320\271:", nullptr));
        btnSearchString->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214", nullptr));
        btnStartAnalysis->setText(QCoreApplication::translate("MainWindow", "\320\220\320\275\320\260\320\273\320\270\320\267\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
