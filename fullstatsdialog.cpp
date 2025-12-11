#include "FullStatsDialog.h"
#include "ui_FullStatsDialog.h"

#include <QTableWidgetItem>
#include <algorithm>

FullStatsDialog::FullStatsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FullStatsDialog)
{
    ui->setupUi(this);


    connect(ui->btnOk, &QPushButton::clicked, this, &FullStatsDialog::onOkClicked);
}

FullStatsDialog::~FullStatsDialog()
{
    delete ui;
}

void FullStatsDialog::onOkClicked()
{
    accept();
}

void FullStatsDialog::setData(const QMap<QChar, quint64> &counts, quint64 totalChars)
{

    QVector<QPair<QChar, quint64>> vec;
    for (auto it = counts.begin(); it != counts.end(); ++it)
        vec.append({it.key(), it.value()});

    std::sort(vec.begin(), vec.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    ui->tableWidget->setRowCount(vec.size());
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Символ", "Количество", "Частота (%)"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < vec.size(); ++i) {
        const auto &p = vec[i];
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(p.first)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(p.second)));
        double freq = totalChars ? (100.0 * p.second / totalChars) : 0.0;
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(freq, 'f', 2)));
    }
}
