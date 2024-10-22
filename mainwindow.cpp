#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "word.h"
#include "compositeword.h"
#include "wordhandler.h"


// Checks the kanji according to the values on thisthis site
// http://www.rikai.com/library/kanjitables/kanji_codes.unicode.shtml
// hex value range [4e00, 9faf]
bool isKanji(QChar character) {
    if (19968 < character.unicode() && character.unicode() < 40879) {
        return true;
    }
    return false;
}

static QPoint Nextpos(QPoint currentPoint, int random_degree) {
    //const quint32 rand_value = QRandomGenerator::global()->generateDouble();
    //const quint32 random_degree = rand_value % 360;
    const double y = qSin(random_degree);
    const double x = qCos(random_degree);

    QPoint newpos(currentPoint.x() + x, currentPoint.y() + y);

    return newpos;
}

QPoint MainWindow::DrawNext(QHash<Word*, bool>& is_drawn_already, Word* word, size_t number_to_draw, QPoint currentpos) {
    if (is_drawn_already.size() == number_to_draw) {
        return currentpos;
    }

    if (!is_drawn_already.value(word)) {
        is_drawn_already.insert(word, true);
    }

    //if (composite_list.length() == 0) {
    //    return; // when all comp words are exhausted
    //}

    //if (word)

    // if (pointer == composite && isinlist) // dealing with the word list
    //    pointer.setpos(currentpoin)
    //    words.remove(pointer)

    //    for (Kanji in comps)
    //        next_pos = calcunextpos(nextpoint)
    //        drawLine(currentpoint, nextpoint)
    //        DrawNext(kanji, next_pos)
    // if (pointer == kanji && isinlist) // dealing with Kanji
    //        pointer.setpos(currentpoint)
    //    for (Composite in kanji)
    //        next_pos = calcunextpos(nextpoint)
    //        drawLine(currentpoint,nextpoint)
    //        DrawNext(composite, next_pos)

}


void MainWindow::DrawMaster(size_t item_amount) {
    QList<Word*> unified_list(word_handler.getAllWords());

    QHash<Word*, bool> is_drawn_already;

    Word* first_item = unified_list.first();

    QListIterator iter(unified_list);
    //QPoint curr_point =
    while (iter.hasNext()) {
        //curr_point = DrawNext(is_drawn_already, first_item, item_amount);
    }
}


//void MainWindow::CreateGraphicsItems() {
//    for (Kanji* kanji : word_handler.getKanjiPointers()) {
//        graphics_items.append(QSharedPointer<GraphicsItemWord>::create(kanji));
//    }
//
//    for (CompositeWord* comp : word_handler.getCompositePointers()) {
//        graphics_items.append(QSharedPointer<GraphicsItemWord>::create(comp));
//    }
//}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphics_scene = new QGraphicsScene();
    ui->graphicsView->setScene(graphics_scene);

    size_t item_amount = word_handler.getCompositeStorageSize() + word_handler.getKanjiStorageSize();
    word_handler =  WordHandler();
    graphics_items = QList<QSharedPointer<GraphicsItemWord>>();
    graphics_items.reserve(item_amount);

    word_handler.ReadParse(QString("/home/momo/Desktop/core2k.txt"));
    word_handler.LinkWords();
    //CreateGraphicsItems();
    //DrawMaster(item_amount);
    GraphicsItemWord* abc = new GraphicsItemWord(word_handler.getKanjiPointers().at(1));
    abc->setPos(0,0);
    graphics_scene->addItem(abc);

    for (int i = 0; i < 360; i++) {
        qDebug() << Nextpos(QPoint(0,0), i) << "\n";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
