/********************************************************************************
** Form generated from reading UI file 'FullStatsDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FULLSTATSDIALOG_H
#define UI_FULLSTATSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FullStatsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QPushButton *btnOk;

    void setupUi(QDialog *FullStatsDialog)
    {
        if (FullStatsDialog->objectName().isEmpty())
            FullStatsDialog->setObjectName("FullStatsDialog");
        FullStatsDialog->resize(500, 400);
        verticalLayout = new QVBoxLayout(FullStatsDialog);
        verticalLayout->setObjectName("verticalLayout");
        tableWidget = new QTableWidget(FullStatsDialog);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setColumnCount(3);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableWidget);

        btnOk = new QPushButton(FullStatsDialog);
        btnOk->setObjectName("btnOk");

        verticalLayout->addWidget(btnOk);


        retranslateUi(FullStatsDialog);

        QMetaObject::connectSlotsByName(FullStatsDialog);
    } // setupUi

    void retranslateUi(QDialog *FullStatsDialog)
    {
        FullStatsDialog->setWindowTitle(QCoreApplication::translate("FullStatsDialog", "\320\237\320\276\320\273\320\275\320\260\321\217 \321\201\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        tableWidget->setHorizontalHeaderLabels(QStringList{
            QCoreApplication::translate("FullStatsDialog", "\320\241\320\270\320\274\320\262\320\276\320\273", nullptr),
            QCoreApplication::translate("FullStatsDialog", "\320\222\321\205\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr),
            QCoreApplication::translate("FullStatsDialog", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 (%)", nullptr)});
        btnOk->setText(QCoreApplication::translate("FullStatsDialog", "\320\236\320\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FullStatsDialog: public Ui_FullStatsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FULLSTATSDIALOG_H
