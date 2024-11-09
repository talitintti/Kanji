#include "nextpos.h"
#include <QtMath>
#include <QtNumeric>
#include <QPoint>

double NextPos::GetRadiansPerDivision(quint32 multiplier, quint32 number_of_divisions) {
    return ((2*M_PI)*multiplier) / number_of_divisions;
}



QPoint NextPos::CalcNext(QPoint center, double radius, double radians)
{
    const double y = qSin(radians) * radius;
    const double x = qCos(radians) * radius;

    return QPoint(center.x() + x, center.y() + y);
}


QPoint NextPos::Get() {
        if ((item_counter_per_circle % item_amount) == 0) {
            item_counter_per_circle = 0;
            item_amount = qFloor( ((2*M_PI)*current_radius) / (original_radian_step*radius) ) ;
            current_radians = 0;
            current_radius = radius * radius_mult;
            radius_mult++;
        }
        else {
            current_radians += GetRadiansPerDivision(radius_mult, item_amount);
        }
        item_counter_per_circle++;

        return CalcNext(center, current_radius, current_radians);
}
