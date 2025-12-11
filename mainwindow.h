#pragma once

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QSharedPointer>
#include <QFutureWatcher>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct FileAnalysis {
    QString filePath;
    quint64 totalBytes = 0;
    quint64 totalChars = 0;
    QMap<QChar, quint64> counts;
    QChar mostChar;
    quint64 mostCount = 0;
    double mostFreq = 0.0;

    QString fullText;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectFile();
    void onStartAnalysis();
    void onSearchString();
    void onClear();
    void onAnalysisFinished();
    void onShowFullStats();

private:
    Ui::MainWindow *ui;
    QString m_filePath;
    QSharedPointer<FileAnalysis> m_analysis;
    QFutureWatcher<void> *m_watcher = nullptr;
    QPushButton *btnFullStats = nullptr;

    void analyzeFile();
};
