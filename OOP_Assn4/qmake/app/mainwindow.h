#ifndef __APP_WIDGETS_MAINWINDOW_H
#define __APP_WIDGETS_MAINWINDOW_H

#include <QWidget>
#include "ui_mainwindowwidget.h"

namespace app::widgets
{
    /**
     * A root widget for this application
     *
     * Note)
     * All the other widgets are spawned and manages inside this class
     */
    class MainWindowWidget : public QWidget
    {
        Q_OBJECT
    public:
        MainWindowWidget(QWidget* parent = nullptr);
    private:
        Ui::MainWindowWidget ui;
    };
}

#endif
