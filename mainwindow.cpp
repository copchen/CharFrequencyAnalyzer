#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QtConcurrent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btnStartAnalysis->setEnabled(false);
    ui->btnSearchString->setEnabled(false);

    connect(ui->btnSelectFile, &QPushButton::clicked, this, &MainWindow::onSelectFile);
    connect(ui->btnStartAnalysis, &QPushButton::clicked, this, &MainWindow::onStartAnalysis);
    connect(ui->btnSearchString, &QPushButton::clicked, this, &MainWindow::onSearchString);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSelectFile()
{
    QString file = QFileDialog::getOpenFileName(this, "Выберите UTF-8 файл", QString(),
                                                "Text Files (*.txt);;All Files (*)");
    if (file.isEmpty())
        return;

    m_filePath = file;
    ui->labelSelectedFile->setText(file);
    ui->valueFilePath->setText(file);
    ui->btnStartAnalysis->setEnabled(true);

    // Очистка предыдущих результатов
    ui->valueFileSize->clear();
    ui->valueCharCount->clear();
    ui->valueMostChar->clear();
    ui->valueMostCount->clear();
    ui->valueFrequency->clear();
    ui->editSearchString->clear();
    ui->valueSearchResult->clear();
    ui->btnSearchString->setEnabled(false);
}

void MainWindow::onStartAnalysis()
{
    if (m_filePath.isEmpty())
        return;

    ui->btnStartAnalysis->setEnabled(false);
    ui->statusbar->showMessage("Анализ файла...");

    m_analysis = QSharedPointer<FileAnalysis>::create();
    m_analysis->filePath = m_filePath;

    // Запуск анализа в отдельном потоке
    m_watcher = new QFutureWatcher<void>(this);
    connect(m_watcher, &QFutureWatcher<void>::finished, this, &MainWindow::onAnalysisFinished);

    m_watcher->setFuture(QtConcurrent::run([this]() { analyzeFile(); }));
}

void MainWindow::analyzeFile()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);


    QMap<QChar, quint64> counts;
    quint64 totalChars = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        for (QChar ch : line) {
            counts[ch]++;
            totalChars++;
        }
    }

    m_analysis->totalChars = totalChars;
    m_analysis->totalBytes = file.size();
    m_analysis->counts = counts;


    QChar most;
    quint64 maxCount = 0;
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        if (it.value() > maxCount) {
            most = it.key();
            maxCount = it.value();
        }
    }
    m_analysis->mostChar = most;
    m_analysis->mostCount = maxCount;
    m_analysis->mostFreq = totalChars ? (100.0 * maxCount / totalChars) : 0.0;
}


void MainWindow::onAnalysisFinished()
{
    ui->valueFileSize->setText(QString::number(m_analysis->totalBytes));
    ui->valueCharCount->setText(QString::number(m_analysis->totalChars));
    ui->valueMostChar->setText(m_analysis->mostChar);
    ui->valueMostCount->setText(QString::number(m_analysis->mostCount));
    ui->valueFrequency->setText(QString::number(m_analysis->mostFreq, 'f', 2) + "%");

    ui->btnSearchString->setEnabled(true);
    ui->btnStartAnalysis->setEnabled(true);
    ui->statusbar->showMessage("Анализ завершен", 5000);
}

void MainWindow::onSearchString()
{
    if (!m_analysis || ui->editSearchString->text().isEmpty())
        return;

    QString search = ui->editSearchString->text();
    quint64 count = 0;
    for (auto it = m_analysis->counts.begin(); it != m_analysis->counts.end(); ++it) {
        if (QString(it.key()) == search)
            count = it.value();
    }
    ui->valueSearchResult->setText(QString::number(count));
}

void MainWindow::onClear()
{
    ui->labelSelectedFile->setText("Файл: (не выбран)");
    ui->valueFilePath->clear();
    ui->valueFileSize->clear();
    ui->valueCharCount->clear();
    ui->valueMostChar->clear();
    ui->valueMostCount->clear();
    ui->valueFrequency->clear();
    ui->editSearchString->clear();
    ui->valueSearchResult->clear();
    ui->btnStartAnalysis->setEnabled(false);
    ui->btnSearchString->setEnabled(false);
    m_filePath.clear();
    m_analysis.clear();
    ui->statusbar->clearMessage();
}
