#pragma once

#include <QString>
#include <QMap>
#include <QChar>
#include <QtGlobal>

class DocxAnalyzer
{
public:
    // Анализирует DOCX и возвращает частоту каждого символа (без пробелов)
    static QMap<QChar, quint64> analyzeDocx(const QString &filePath);

    // Возвращает полный текст DOCX (для поиска подстрок)
    static QString extractFullText(const QString &filePath);
};
