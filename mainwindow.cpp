#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "word.h"
#include "wordhandler.h"
#include <QMessageBox>
#include <QDebug>


// Checks the kanji according to the values on thisthis site
// http://www.rikai.com/library/kanjitables/kanji_codes.unicode.shtml
// hex value range [4e00, 9faf]
bool isKanji(QChar character)
{
    if (19968 < character.unicode() && character.unicode() < 40879) {
        return true;
    }
    return false;
}

static QPoint Nextpos(QPoint currentPoint)
{
    const quint32 length_from_last_point = 10;
    const quint32 rand_value = QRandomGenerator::global()->generate();
    const quint32 degrees = rand_value % 360;

    const double in_radians = qDegreesToRadians(degrees);
    const double y = qSin(in_radians) * length_from_last_point;
    const double x = qCos(in_radians) * length_from_last_point;

    return QPoint(currentPoint.x() + x, currentPoint.y() + y);
}


QPoint MainWindow::DrawNext(QHash<Word *, bool> &is_drawn_already,
                            Word *word,
                            qsizetype number_to_draw,
                            QPoint &currentpos)
{
    qDebug() << "We here";
    if (is_drawn_already.size() == number_to_draw) {
        return currentpos;
    }

    if (!is_drawn_already.value(word)) {
        is_drawn_already.insert(word, true);
        GraphicsItemWord *graphics_item = new GraphicsItemWord(word);
        graphics_item->setPos(currentpos);
        graphics_scene->addItem(graphics_item);

        QListIterator iter(word->getRelatedWords());
        while (iter.hasNext()) {
            QPoint nextpos = Nextpos(currentpos);
            DrawNext(is_drawn_already, iter.next(), number_to_draw, nextpos) ;
        }
    }
    return currentpos;
}


void MainWindow::DrawMaster(qsizetype item_amount)
{
    QList<Word *> unified_list(word_handler.getAllWords());

    QHash<Word *, bool> is_drawn_already;

    Word *first_item = unified_list.first();

    QListIterator iter(unified_list);
    QPoint curr_point(0,0);
    while (iter.hasNext()) {
        curr_point = DrawNext(is_drawn_already, first_item, item_amount, curr_point);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() <<  "can we get here";
    ui->setupUi(this);

    word_handler = WordHandler();
    graphics_scene = new QGraphicsScene();
    qDebug() << "Hello";
    ui->graphicsView->setScene(graphics_scene);
    qDebug() << "Over";
    bool success = word_handler.ReadParse(QString("/home/momo/Desktop/core2k.txt"));
    word_handler.LinkWords();
    //DrawMaster(word_handler.getCompositeStorageSize() + word_handler.getKanjiStorageSize());
}

MainWindow::~MainWindow()
{
    delete ui;
}
