#pragma once

#include <QDialog>
#include <QMap>
#include <QChar>

namespace Ui {
class FullStatsDialog;
}

class FullStatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FullStatsDialog(QWidget *parent = nullptr);
    ~FullStatsDialog();

    void setData(const QMap<QChar, quint64> &counts, quint64 totalChars);

private slots:
    void onOkClicked();

private:
    Ui::FullStatsDialog *ui;
};
