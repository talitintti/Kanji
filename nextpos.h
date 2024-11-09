#ifndef NEXTPOS_H
#define NEXTPOS_H
#include <QtNumeric>
#include <QPoint>

class NextPos
{
public:
    NextPos() :
        radius(20),
        starting_amount(4),
        original_radian_step(GetRadiansPerDivision(1, starting_amount)),
        radius_mult(1),
        item_amount(4),
        current_radius(radius),
        current_radians(0),
        item_counter_per_circle(0),
        center(QPoint(0,0))
    {}
    QPoint Get();
private:
    const double radius;
    const quint32 starting_amount;
    const double original_radian_step;

    double radius_mult;
    quint32 item_amount;
    double current_radius;
    double current_radians;
    quint32 item_counter_per_circle;

    QPoint center;

    double GetRadiansPerDivision(quint32 multiplier, quint32 number_of_divisions);
    QPoint CalcNext(QPoint center, double radius, double radians);
};

#endif // NEXTPOS_H
