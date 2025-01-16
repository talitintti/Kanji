#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QStackedWidget>
#include <QGraphicsView>
#include "ui_mainwindow.h"
#include "word.h"
#include "wordhandler.h"

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


void MainWindow::DrawWord(QPoint pos, Word* word, QGraphicsScene *scene) {
    GraphicsItemWord *graphics_item = new GraphicsItemWord(word);
    graphics_item->setPos(pos);

    scene->addItem(graphics_item);
}

void MainWindow::DrawLine(QPoint pos1, QPoint pos2, QGraphicsScene *scene) {
    QGraphicsLineItem *lineItem = new QGraphicsLineItem(pos1.x(),
                                                        pos1.y(),
                                                        pos2.x(),
                                                        pos2.y());

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    lineItem->setPen(pen);

    scene->addItem(lineItem);
}

// Returns true if there are stil items to draw.
// Returns false if we have drawn the given amount already
bool MainWindow::DrawNext(QHash<Word *, bool> &is_drawn_already,
                            Word *word,
                            qsizetype number_to_draw,
                            QPoint last_point,
                            bool no_relation
                            )
{
    if ((is_drawn_already.size() == number_to_draw) ) {
        return false;
    }

    if (is_drawn_already.contains(word)) {
        return true;
    }

    QPoint current_point = nextpos.Get();

    DrawWord(current_point, word, graphics_scene_all);
    is_drawn_already.insert(word, true);

    if (!no_relation) {
        DrawLine(last_point, current_point, graphics_scene_all);
    }

    QListIterator iter(word->getRelatedWords());
    while (iter.hasNext()) {
        DrawNext(is_drawn_already, iter.next(), number_to_draw, current_point, false);
    }

    return true;
}

void MainWindow::DrawAll(QList<Word*> & unified_list)
{
    qsizetype list_size = unified_list.size() ;
    QHash<Word *, bool> is_drawn_already;
    QListIterator iter(unified_list);

    while (iter.hasNext()) {
        Word *next_word = iter.next();
        if (!DrawNext(is_drawn_already, next_word, list_size, nextpos.GetWithoutRotation(), true)) {
            break;
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphics_scene_all = new QGraphicsScene();
    graphics_scene_search = new QGraphicsScene();
    QGraphicsView *view_all = new QGraphicsView();
    QGraphicsView *view_search = new QGraphicsView();

    ui->stackedWidget->addWidget(view_all);
    ui->stackedWidget->addWidget(view_search);

    view_all->setScene(graphics_scene_all);
    view_search->setScene(graphics_scene_search);

    word_handler = WordHandler();
    bool success = word_handler.ReadParse(QString("/home/momo/Desktop/core2k.txt"));
    word_handler.LinkWords();

    QList<Word *> unified_list(word_handler.getAllWords());
    DrawAll(unified_list);

    SetStyles();
}

void MainWindow::SetStyles() {
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawSearched(QList<Word*> drawables) {
    nextpos.Reset();
    for (int i = 0; i < drawables.count(); i++) {
        Word *word = drawables.at(i);
        QPoint point = nextpos.Get();
        DrawWord(point, word, graphics_scene_search);
    }
}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    QString arg = arg1.trimmed();
    if (arg == "") {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        graphics_scene_search->clear();
        ui->stackedWidget->setCurrentIndex(1);

        QList<Word*> found = word_handler.GetFirstOrderRelated(arg);
        qDebug() << found.count() << "\n";
        DrawSearched(found);

    }
}

