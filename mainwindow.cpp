#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btnStart->setEnabled(false);
    ui->progressBar->setValue(0);

    connect(ui->btnChoose, &QPushButton::clicked,
            this, &MainWindow::onChooseFiles);

    connect(ui->btnStart, &QPushButton::clicked,
            this, &MainWindow::onStartAnalysis);


    ui->tableResults->setColumnCount(4);
    ui->tableResults->setHorizontalHeaderLabels({
        "Файл", "Всего байт", "Чаще байт", "Частота %"
    });
}

MainWindow::~MainWindow()
{
    for (auto *w : m_watchers) {
        w->waitForFinished();
        delete w;
    }
    delete ui;
}

void MainWindow::onChooseFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Выберите файлы");

    if (files.isEmpty())
        return;

    m_files = files;
    ui->listFiles->clear();

    for (auto &f : m_files)
        ui->listFiles->addItem(f);

    ui->btnStart->setEnabled(true);
    ui->lblStatus->setText("Файлы выбраны");
    ui->tableResults->setRowCount(0);
}

FileResult MainWindow::analyzeFile(const QString &path)
{
    FileResult result;
    result.filePath = path;
    result.counts = QVector<quint64>(256, 0);

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return result;

    const qint64 bufSize = 64 * 1024;

    while (!file.atEnd()) {
        QByteArray data = file.read(bufSize);
        result.totalBytes += data.size();

        const uchar *p = reinterpret_cast<const uchar*>(data.constData());
        for (int i = 0; i < data.size(); i++)
            result.counts[p[i]]++;
    }

    return result;
}

void MainWindow::onStartAnalysis()
{
    if (m_files.isEmpty())
        return;

    ui->btnChoose->setEnabled(false);
    ui->btnStart->setEnabled(false);

    ui->progressBar->setRange(0, m_files.size());
    ui->progressBar->setValue(0);
    ui->lblStatus->setText("Анализ...");

    ui->tableResults->setRowCount(0);

    m_results.clear();

    // Удаляем старые watcher
    for (auto *w : m_watchers) {
        w->waitForFinished();
        delete w;
    }
    m_watchers.clear();

    m_doneCount = 0;

    for (const QString &file : m_files) {

        // Хранилище результата
        auto resultPtr = QSharedPointer<FileResult>::create();
        m_results.append(resultPtr);

        // Задача для потока
        auto task = [=]() {
            *resultPtr = analyzeFile(file);
        };

        // Watcher (шаблонный)
        auto *watcher = new QFutureWatcher<void>(this);
        m_watchers.append(watcher);

        connect(watcher, &QFutureWatcher<void>::finished,
                this, &MainWindow::onSingleFileDone);

        watcher->setFuture(QtConcurrent::run(task));
    }
}

void MainWindow::onSingleFileDone()
{
    QObject *obj = sender();
    int index = -1;
    for (int i = 0; i < m_watchers.size(); ++i) {
        if (m_watchers[i] == obj) {
            index = i;
            break;
        }
    }

    if (index < 0)
        return;

    auto res = m_results[index];

    int row = ui->tableResults->rowCount();
    ui->tableResults->insertRow(row);

    ui->tableResults->setItem(row, 0, new QTableWidgetItem(res->filePath));
    ui->tableResults->setItem(row, 1,
                              new QTableWidgetItem(QString::number(res->totalBytes)));

    quint64 maxCount = 0;
    int maxByte = -1;

    for (int b = 0; b < 256; ++b) {
        if (res->counts[b] > maxCount) {
            maxCount = res->counts[b];
            maxByte = b;
        }
    }

    if (maxByte >= 0) {
        double pct = res->totalBytes ? (100.0 * maxCount / res->totalBytes) : 0;

        ui->tableResults->setItem(row, 2,
                                  new QTableWidgetItem(QString("0x%1")
                                                           .arg(maxByte, 2, 16, QChar('0'))));

        ui->tableResults->setItem(row, 3,
                                  new QTableWidgetItem(QString::number(pct, 'f', 3)));
    }

    m_doneCount++;
    ui->progressBar->setValue(m_doneCount);

    if (m_doneCount == m_files.size())
        onAllDone();
}

void MainWindow::onAllDone()
{
    ui->btnChoose->setEnabled(true);
    ui->btnStart->setEnabled(true);

    ui->lblStatus->setText("Готово!");

    QMessageBox::information(this,
                             "Анализ завершён", "Все файлы обработаны.");
}
