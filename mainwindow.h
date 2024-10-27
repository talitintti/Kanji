#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QRandomGenerator>
#include <graphicsitemword.h>
#include <wordhandler.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WordHandler word_handler;
    QGraphicsScene *graphics_scene;
    //QList<QSharedPointer<GraphicsItemWord>> graphics_items;

    void CreateGraphicsItems();
    void DrawMaster(qsizetype item_amount);
    QPoint DrawNext(QHash<Word *, bool> &is_drawn_already,
                    Word *word,
                    qsizetype number_to_draw,
                    QPoint &currentpos);
};
#endif // MAINWINDOW_H
