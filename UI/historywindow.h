#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QDialog>

#include "imagehistorymanager.h"


namespace Ui {
class HistoryWindow;
}

class HistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryWindow(QWidget *parent = nullptr);
    void setHistoryManager(const ImageHistoryManager *historyManager);
    ~HistoryWindow();

private:
    Ui::HistoryWindow *ui;
    const ImageHistoryManager * historyManager = nullptr;
public slots:
    void callShow();
    void callClose();
    void loadFilters();
signals:
    void showRequest(const QString& path);
};

#endif // HISTORYWINDOW_H
