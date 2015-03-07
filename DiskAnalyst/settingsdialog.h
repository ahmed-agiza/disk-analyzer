#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QAbstractButton>
#include <QDir>

namespace Ui {
class SettingsDialog;
}


class SettingsDialog : public QDialog
{
    Q_OBJECT
    void loadValues();
    bool saveValues();
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

protected:
    void showEvent(QShowEvent * event);

private slots:
    void on_bbxOkCancel_clicked(QAbstractButton *button);
    void refreshDisplayReableButton();
    void on_btnStartupDirectory_clicked();
    void loadDefaultValues();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
