#include "customprogressbar.h"
#include <QDebug>


bool CustomProgressBar::getShowValue() const
{
    return showValue;
}

void CustomProgressBar::setShowValue(bool value)
{
    showValue = value;
}
CustomProgressBar::CustomProgressBar(QWidget *parent) :
    QProgressBar(parent), showValue(true){
}

QString CustomProgressBar::getDescription() const{
    return description;
}

void CustomProgressBar::setDescription(QString value){
    description = value;
}

void CustomProgressBar::mouseDoubleClickEvent(QMouseEvent *e){
    emit doubleClicked();
    QProgressBar::mousePressEvent(e);
}

QString CustomProgressBar::text() const{
    QString result;
    if(getShowValue())
        result.append(QString::number(value()) + "% ");
    result.append(getDescription());
    return result;
}
