#include "docxanalyzer.h"

#include <QTemporaryDir>
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

QMap<QChar, quint64> DocxAnalyzer::analyzeDocx(const QString &filePath)
{
    QMap<QChar, quint64> counts;
    QString text = extractFullText(filePath);

    for (QChar ch : text) {
        if (ch.isPrint() && !ch.isSpace()) {
            counts[ch]++;
        }
    }

    return counts;
}

QString DocxAnalyzer::extractFullText(const QString &filePath)
{
    QTemporaryDir tempDir;
    if (!tempDir.isValid()) {
        qDebug() << "Не удалось создать временную папку";
        return "";
    }

    QString tempPath = tempDir.path();

    // Экранируем апострофы для PowerShell
    QString escapedFilePath = filePath;
    escapedFilePath.replace("'", "''");

    QString psCommand = QString(
                            "powershell -NoProfile -Command \"try { Expand-Archive -Path '%1' -DestinationPath '%2' -Force } catch { Write-Error $_; exit 1 }\""
                            ).arg(escapedFilePath, tempPath);

    QProcess process;
    process.start(psCommand);
    if (!process.waitForFinished(15000)) { // 15 секунд на распаковку
        qDebug() << "PowerShell не завершился вовремя";
        return "";
    }

    if (process.exitCode() != 0) {
        qDebug() << "Ошибка распаковки DOCX:" << process.readAllStandardError();
        return "";
    }

    QString xmlPath = tempPath + "/word/document.xml";
    QFile xmlFile(xmlPath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть document.xml";
        return "";
    }

    QString xmlContent = xmlFile.readAll();
    xmlFile.close();

    QString plainText;
    QRegularExpression re("<w:t[^>]*>([^<]*)</w:t>");
    auto it = re.globalMatch(xmlContent);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        plainText += match.captured(1);
    }

    return plainText;
}
