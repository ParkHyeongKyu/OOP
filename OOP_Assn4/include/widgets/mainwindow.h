#ifndef __AS4_WIDGETS_MAINWINDOW_H
#define __AS4_WIDGETS_MAINWINDOW_H

#include <QWidget>
#include "ui_mainwindowwidget.h"
#include <QPushButton>
#include "model/song.h"
#include "model/play.h"

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
        MainWindowWidget(QWidget* parent = nullptr); //constructor
        as4::model::Note* setforput(int r, int c); //note삽입을 위해 준비해주는 메소드
    private slots:
        void on_pushButton_released(); //버튼을 클릭하고 떼었을 때 발생하는 slot

        void on_tableWidget_cellClicked(int row, int column); //tableWidget의 cell이 클릭되었을 때 발생하는 slot

        void on_tableWidget_2_cellClicked(int row, int column); //tableWidget_2의 cell이 클릭되었을 때 발생하는 slot

        void on_tabWidget_tabBarClicked(int index); //tabBar가 클릭되었을 때 발생하는 slot

        void on_tableWidget_cellPressed(int row, int column); //tableWidget의 cell이 pressed되었을 때 발생하는 slot

        void on_tableWidget_2_cellPressed(int row, int column); //tableWidget_2의 cell이 pressed되었을 때 발생하는 slot
    signals:
        void buttonreleased(); //on_pushButton_released() slot에서 작업 수행을 한 뒤 발생하는 signal
    private:
        Ui::MainWindowWidget ui;
        as4::model::Song* music; //노래를 담는 포인터
        int mode; //melody모드인지 drum모드인지 판별해줌
        as4::model::playmusic* pm; //melody모드일 때 사용하는 포인터
        as4::model::playmusic* pd; //drum모드일 때 사용하는 포인터
        int visit[16][40]; //cell의 현재 사용중(색칠) 여부를 알려주는 배열
    };
}

#endif
