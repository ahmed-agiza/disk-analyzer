#ifndef CUSTOMPROGRESSBAR_H
#define CUSTOMPROGRESSBAR_H

#include <QProgressBar>
#include <QMouseEvent>

class CustomProgressBar : public QProgressBar
{
    Q_OBJECT
    QString description;
    bool showValue;
public:
    explicit CustomProgressBar(QWidget *parent = 0);

    QString getDescription()const;
    void setDescription(QString);
    bool getShowValue() const;
    void setShowValue(bool value);

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
    QString text() const;

signals:
    void doubleClicked();

public slots:

};

#endif // CUSTOMPROGRESSBAR_H
