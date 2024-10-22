#include "wordhandler.h"
#include <QDebug>


// Checks the kanji according to the values on this site
// http://www.rikai.com/library/kanjitables/kanji_codes.unicode.shtml
// hex value range [4e00, 9faf]
static bool isKanji(QChar character) {
    if (19968 < character.unicode() && character.unicode() < 40879) {
        return true;
    }
    return false;
}

WordHandler::WordHandler() {}

WordHandler::~WordHandler() {
    QListIterator iter_comp(this->composite_storage);
    while (iter_comp.hasNext()) {
        delete iter_comp.next();
    }

    QListIterator iter_kanji(this->kanji_storage);
    while (iter_kanji.hasNext()) {
        delete iter_kanji.next();
    }
}

QList<Kanji*> WordHandler::getKanjiPointers(){
    QList<Kanji*>  kanji_storage_copy;
    for (Kanji* kanji : this->kanji_storage) {
        kanji_storage_copy.append(kanji);
    }
    return kanji_storage_copy;
}


QList<CompositeWord*>  WordHandler::getCompositePointers() {
    QList<CompositeWord*>  composite_storage_copy;
    for (CompositeWord* composite : this->composite_storage) {
        composite_storage_copy.append(composite);
    }
    return composite_storage_copy;
}


// Just hack the line into three parts based on tabs
QList<QString> WordHandler::ProcessLine(QString line) {
    QList<QString> word_data;

    if (line.isEmpty() | line.at(0) == QChar('#')) {
        return word_data;
    }

    static QRegularExpression e("\\t+|\\s\\s+");
    QList<QString> tokens = line.split(e);
    for (auto const &t : tokens) {
        word_data.append(t);
    }

    if (word_data.length() != 4) {
        qDebug() << "[NOTICE: line was broken into not four parts]" << "\n" << line << "\n";
    }

    return word_data;
}


void WordHandler::ReadParse(QString ankideck_url) {
    QFile file(ankideck_url);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QString line = file.readLine();
        QList<QString> data_per_word = ProcessLine(line);

        if (!data_per_word.isEmpty() & data_per_word.length() == 4) {
            QString the_word_itself(data_per_word.at(0));
            if (the_word_itself.length() > 1) {
                this->AddComposite(
                    data_per_word.at(0),
                    data_per_word.at(1),
                    data_per_word.at(2),
                    data_per_word.at(3));
            }
            else {
                this->AddKanji(
                    data_per_word.at(0),
                    data_per_word.at(1),
                    data_per_word.at(2),
                    data_per_word.at(3));
            }
        }
    }
}


void WordHandler::AddKanji(const QString &chars, const QString &reading, const QString &explanation, const QString &englishEquivalent) {
    Kanji* kanji = new Kanji(chars, reading, explanation, englishEquivalent);

    this->kanji_storage.append(kanji);
    this->kanji_map.insert(chars, kanji);
}


void WordHandler::AddComposite(const QString &chars, const QString &reading, const QString &explanation, const QString &englishEquivalent) {
    CompositeWord* composite = new CompositeWord(chars, reading, explanation, englishEquivalent);
    this->composite_storage.append(composite);
}


// Links the compositeword to know the pointers of its constituent kanji and kanji to know where it appears
void WordHandler::LinkWords() {
    for (CompositeWord* c_word : this->composite_storage) {
        const QString &c_word_const = c_word->getCharacters(); // apparently needed to not detach QString when iterating below
        for (auto const &current_char : c_word_const) {
            Kanji* corresponding_kanji = this->kanji_map.value(current_char);
            if (isKanji(current_char) & corresponding_kanji != NULL) {
                corresponding_kanji->setAppearsIn(c_word);
                c_word->setKanji(corresponding_kanji);
            }
        }
    }
}

size_t WordHandler::getKanjiStorageSize() {
    return this->kanji_storage.size();
}
size_t WordHandler::getCompositeStorageSize() {
    return this->composite_storage.size();
}


QList<Word*> WordHandler::getAllWords() const{
    QList<Word*> list;
    for (Kanji* kanji : this->kanji_storage) {
        Word* word = static_cast<Word*>(kanji);
        list.append(word);
    }
    return list;
}
