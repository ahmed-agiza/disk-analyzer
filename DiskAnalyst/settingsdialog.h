#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QAbstractButton>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void on_btnStartuoDirectory_clicked();


    void on_bbxOkCancel_clicked(QAbstractButton *button);

private:
    QSettings settings;
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
