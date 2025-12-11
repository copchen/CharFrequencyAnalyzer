#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QtConcurrent>
#include <QMessageBox>
#include <QStringConverter>

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
    QString file = QFileDialog::getOpenFileName(
        this,
        "Выберите файл",
        QString(),
        "Text Files (*.txt *.log *.cpp *.cs *.py)"
        );
    if (file.isEmpty())
        return;

    m_filePath = file;
    ui->labelSelectedFile->setText(file);
    ui->valueFilePath->setText(file);
    ui->btnStartAnalysis->setEnabled(true);

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

    m_watcher = new QFutureWatcher<void>(this);
    connect(m_watcher, &QFutureWatcher<void>::finished, this, &MainWindow::onAnalysisFinished);

    m_watcher->setFuture(QtConcurrent::run([this]() { analyzeFile(); }));
}

void MainWindow::analyzeFile()
{
    if (m_filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите файл!");
        return;
    }

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    QMap<QChar, quint64> counts;
    quint64 totalChars = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        for (QChar ch : line) {
            if (ch.isPrint() && !ch.isSpace()) {
                counts[ch]++;
                totalChars++;
            }
        }
    }

    file.close();

    m_analysis->counts = counts;
    m_analysis->totalChars = totalChars;
    m_analysis->totalBytes = QFileInfo(m_filePath).size();

    QChar mostChar;
    quint64 mostCount = 0;
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        if (it.value() > mostCount) {
            mostChar = it.key();
            mostCount = it.value();
        }
    }

    m_analysis->mostChar = mostChar;
    m_analysis->mostCount = mostCount;
    m_analysis->mostFreq = totalChars ? (100.0 * mostCount / totalChars) : 0.0;
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

    QString searchStr = ui->editSearchString->text().trimmed();
    if (searchStr.length() != 1) {
        QMessageBox::warning(this, "Ошибка", "Можно вводить только один символ для поиска");
        return;
    }

    QChar search = searchStr[0];
    quint64 count = m_analysis->counts.value(search, 0);
    double freq = m_analysis->totalChars ? (100.0 * count / m_analysis->totalChars) : 0.0;

    ui->valueSearchResult->setText(QString("%1 (частота: %2%)")
                                       .arg(count)
                                       .arg(freq, 0, 'f', 2));
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
