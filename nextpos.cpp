#include "nextpos.h"
#include <QPoint>
#include <QtMath>
#include <QtNumeric>
#include <QDebug>

void NextPos::PrintState() {
    qDebug() << "angle " << current_angle;
    qDebug() << "radius " << current_radius;
    qDebug() << "item counter " << item_counter_per_circle;
    qDebug() << "item amount " << item_amount;
    qDebug() << "\n";
}

double NextPos::DivisionLength(quint32 number_of_divisions, double radius)
{
    return ((2 * M_PI) * radius) / number_of_divisions;
}

QPoint NextPos::CalcNext(QPoint center, double radius, double degrees)
{
    const double radians = qDegreesToRadians(degrees);
    const double y = qSin(radians) * radius;
    const double x = qCos(radians) * radius;

    return QPoint(center.x() + x, center.y() + y);
}

QPoint NextPos::Get()
{
    if ((item_counter_per_circle % item_amount) == 0) {
        current_angle = 0;
        item_counter_per_circle = 0;
        current_radius = radius * radius_mult;
        item_amount = qFloor((2 * M_PI * current_radius) / step_length_on_circle);
        radius_mult++;
    } else {
        current_angle += 360 / (double)item_amount;
    }
    item_counter_per_circle++;
    iterations++;

    return CalcNext(center, current_radius, current_angle);
}

quint32 NextPos::GetIterations() {
    return iterations;
}
