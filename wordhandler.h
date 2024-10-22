#ifndef WORDHANDLER_H
#define WORDHANDLER_H

#include <word.h>
#include <kanji.h>

#include <compositeword.h>
#include <QScopedPointer>
#include <QList>
#include <QHash>
#include <QWeakPointer>
#include <QDebug>
#include <QUrl>
#include <QIODevice>
#include <QFile>
#include <QRegularExpression>

class WordHandler
{
public:
    WordHandler();
    ~WordHandler();

    void AddKanji(const QString &chars, const QString &reading, const QString &explanation, const QString &englishEquivalent);
    void AddComposite(const QString &chars, const QString &reading, const QString &explanation, const QString &englishEquivalent);
    void LinkWords();
    void ReadParse(QString ankideck_url);

    QList<Kanji*> getKanjiPointers();
    QList<CompositeWord*> getCompositePointers();
    size_t getKanjiStorageSize();
    size_t getCompositeStorageSize();
    QList<Word*> getAllWords() const;

private:
    QList<QString> ProcessLine(QString line);

    QList<Kanji*> kanji_storage;
    QList<CompositeWord*> composite_storage;
    QHash<QString, Kanji*> kanji_map;
};

#endif // WORDHANDLER_H
