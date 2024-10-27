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

    void AddKanji(const QString &chars,
                  const QString &reading,
                  const QString &explanation,
                  const QString &englishEquivalent);
    void AddComposite(const QString &chars,
                      const QString &reading,
                      const QString &explanation,
                      const QString &englishEquivalent);
    void LinkWords();
    bool ReadParse(QString ankideck_url);

    QList<Kanji *> getKanjiPointers();
    QList<CompositeWord *> getCompositePointers();
    qsizetype getKanjiStorageSize();
    qsizetype getCompositeStorageSize();
    QList<Word *> getAllWords() const;

private:
    QList<QString> ProcessLine(QString line);

    QList<Kanji *> kanji_storage;
    QList<CompositeWord *> composite_storage;
    QHash<QString, Kanji *> kanji_map;
};

#endif // WORDHANDLER_H
