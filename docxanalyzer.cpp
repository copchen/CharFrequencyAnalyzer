#include "docxanalyzer.h"
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QRegularExpression>
#include <QDebug>

QString DocxAnalyzer::extractFullText(const QString &path)
{
    QString tempDir = QDir::temp().absoluteFilePath("docx_extract");
    QDir().mkpath(tempDir);


    QString psCommand = QString(
                            "powershell -Command \"Add-Type -AssemblyName System.IO.Compression.FileSystem;"
                            "[System.IO.Compression.ZipFile]::ExtractToDirectory('%1','%2')\"")
                            .arg(path).arg(tempDir);

    QProcess proc;
    proc.start(psCommand);
    proc.waitForFinished();

    QFile xmlFile(tempDir + "/word/document.xml");
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};

    QString content = xmlFile.readAll();
    xmlFile.close();

    QString plain;
    QRegularExpression re("<w:t[^>]*>([^<]*)</w:t>");
    auto it = re.globalMatch(content);
    while (it.hasNext()) {
        auto match = it.next();
        plain += match.captured(1);
    }

    return plain;
}

QMap<QChar, quint64> DocxAnalyzer::analyzeDocx(const QString &path)
{
    QMap<QChar, quint64> freq;
    QString text = extractFullText(path);

    for (QChar ch : text) {
        if (ch.isPrint() && !ch.isSpace()) {
            freq[ch]++;
        }
    }

    return freq;
}
