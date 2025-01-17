#ifndef WORDHANDLER_H
#define WORDHANDLER_H

#include <kanji.h>
#include <word.h>

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QIODevice>
#include <QList>
#include <QRegularExpression>
#include <QScopedPointer>
#include <QUrl>
#include <QWeakPointer>
#include <compositeword.h>

class WordHandler
{
public:
    WordHandler();
    ~WordHandler();

    void AddKanji(const QString &id,
                    const QString &chars,
                    const QString &reading,
                    const QString &english_eq,
                    const QString &explanation,
                    const QString &explanation_eng);
    void AddComposite(const QString &id,
                    const QString &chars,
                    const QString &reading,
                    const QString &english_eq,
                    const QString &explanation,
                      const QString &explanation_eng);
    void LinkWords();
    bool ReadParse(QString ankideck_url);

    QList<Kanji *> getKanjiPointers();
    QList<CompositeWord *> getCompositePointers();
    qsizetype getKanjiStorageSize();
    qsizetype getCompositeStorageSize();
    QList<Word *> getAllWords() const;
    QList<Word *> GetFirstOrderRelated(QString search_key);

private:
    QList<QString> ProcessLine(QString line);

    QList<Kanji *> kanji_storage;
    QList<CompositeWord *> composite_storage;
    QHash<QString, Kanji *> kanji_map;
    QHash<QString, Kanji *> remnant_map;

    QList<Word *> GetRelated(Word *kanji);
};

#endif // WORDHANDLER_H
