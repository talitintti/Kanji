#ifndef NEXTPOS_H
#define NEXTPOS_H
#include <QPoint>
#include <QtNumeric>

class NextPos
{
public:
    NextPos()
        : radius(50)
        , starting_amount(4)
        , radius_mult(1)
        , item_amount(starting_amount)
        , current_radius(radius)
        , step_length_on_circle(DivisionLength(starting_amount, radius))
        , current_angle(0)
        , item_counter_per_circle(0)
        , center(QPoint(0, 0))
        , iterations(0)
    {}
    QPoint Get();
    QPoint GetWithoutRotation();
    quint32 GetIterations();

private:
    const double radius;
    const quint32 starting_amount;
    const double step_length_on_circle;

    quint32 iterations;

    double radius_mult;
    quint32 item_amount;
    double current_radius;
    double current_angle;
    quint32 item_counter_per_circle;

    QPoint center;

    double DivisionLength(quint32 number_of_divisions, double radius);
    QPoint CalcNext(QPoint center, double radius, double degrees);
    void  PrintState();
};

#endif // NEXTPOS_H
