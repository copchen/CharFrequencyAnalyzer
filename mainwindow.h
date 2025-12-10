#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QSharedPointer>
#include <QFutureWatcher>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct FileResult {
    QString filePath;
    QVector<quint64> counts;
    quint64 totalBytes = 0;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onChooseFiles();
    void onStartAnalysis();
    void onSingleFileDone();
    void onAllDone();

private:
    FileResult analyzeFile(const QString &path);

private:
    Ui::MainWindow *ui;

    QStringList m_files;
    QList<QSharedPointer<FileResult>> m_results;


    QList<QFutureWatcher<void>*> m_watchers;

    int m_doneCount = 0;
};

#endif // MAINWINDOW_H
