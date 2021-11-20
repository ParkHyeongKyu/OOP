#include "widgets/mainwindow.h"
#include "model/play.h"
#include "model/seq.h"
#include "model/pitch.h"
#include <QMouseEvent>
#include <QSoundEffect>
#include <QEventLoop>
#include <QTimer>

namespace app::widgets
{
    MainWindowWidget::MainWindowWidget(QWidget* parent)
        :QWidget(parent)
    {
        /* Put your code here */
        int x;
        ui.setupUi(this);
        music = new as4::model::Song;
        for(int i = 0; i < 16; i++) //나중에 cell을 색칠하기 위하여 각 cell들을 set해주고 visit배열을 0으로 초기화시킨다.
        {
            for(int j = 0; j < 40; j++)
            {
                ui.tableWidget->setItem(i, j, new QTableWidgetItem);
                ui.tableWidget_2->setItem(i, j, new QTableWidgetItem);
                visit[i][j] = 0;
            }
        }
        x = ui.tabWidget->currentIndex(); //x를 탭위젯이 가르키는 현재 인덱스로 나타낸다.
        if(x == 0) //x가 0이면 멜로디 모드이다.
        {
            mode = 0;
        }
        else { //x가 1이면 드럼 모드이다.
            mode = 1;
        }
    }
}

as4::model::Note* app::widgets::MainWindowWidget::setforput(int r, int c)
{
    as4::model::Note* nn = new as4::model::Note(); //삽입해줄 노트를 동적할당한다.
    as4::model::Pitch np; //노트에 사용할 피치이다.
    as4::model::pitch::StandardPitchStringfier change; //string을 피치로 바꿔주는 역할을 한다.
    std::string pc;

    switch(r) //r에 따라 pc를 정한다.
    {
    case 0: pc = "D#5";
        break;
    case 1: pc = "D5";
        break;
    case 2: pc = "C#5";
        break;
    case 3: pc = "C5";
        break;
    case 4: pc = "B4";
        break;
    case 5: pc = "A#4";
        break;
    case 6: pc = "A4";
        break;
    case 7: pc = "G#4";
        break;
    case 8: pc = "G4";
        break;
    case 9: pc = "F#4";
        break;
    case 10: pc = "F4";
        break;
    case 11: pc = "E4";
        break;
    case 12: pc = "D#4";
        break;
    case 13: pc = "D4";
        break;
    case 14: pc = "C#4";
        break;
    case 15: pc = "C4";
        break;
    }
    nn->SetStart(c); //노트에 값을 부여한다.
    np = change.FromString(pc);
    nn->SetPitch(np);
    nn->SetDuration(4);
    return nn;
}

void app::widgets::MainWindowWidget::on_pushButton_released()
{
    if (mode == 0) //멜로디 모드일 경우
    {
        pm = new as4::model::playmelody(music->GetMelodySeq());
        connect(this, SIGNAL(buttonreleased()), pm, SLOT(start())); //buttonreleased()라는 SIGNAL이 발생하면 pm에서 start() 슬롯으로 이동한다.
    }
    else //드럼 모드일 경우
    {
        pd = new as4::model::playdrum(music->GetDrumSeq());
        connect(this, SIGNAL(buttonreleased()), pd, SLOT(start())); //buttonreleased()라는 SIGNAL이 발생하면 pd에서 start() 슬롯으로 이동한다.
    }
    emit buttonreleased();
}

void app::widgets::MainWindowWidget::on_tableWidget_cellClicked(int row, int column) //클릭된 cell의 row, column값을 받아온다.
{
    as4::model::Note* nn;
    nn = setforput(row, column);
    music->GetMelodySeq()->Put(*nn); //nn을 music의 Melody에 삽입한다.
    if(column == 37) //경우에 따라 cell의 색을 칠한다.
    {
        ui.tableWidget->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
        ui.tableWidget->item(row, (column+1))->setBackground(Qt::green);
        visit[row][column + 1] = 1;
        ui.tableWidget->item(row, (column+2))->setBackground(Qt::green);
        visit[row][column + 2] = 1;
    }
    else if(column == 38)
    {
        ui.tableWidget->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
        ui.tableWidget->item(row, (column+1))->setBackground(Qt::green);
        visit[row][column + 1] = 1;
    }
    else if(column == 39)
    {
        ui.tableWidget->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
    }
    else
    {
        ui.tableWidget->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
        ui.tableWidget->item(row, (column+1))->setBackground(Qt::green);
        visit[row][column + 1] = 1;
        ui.tableWidget->item(row, (column+2))->setBackground(Qt::green);
        visit[row][column + 2] = 1;
        ui.tableWidget->item(row, (column+3))->setBackground(Qt::green);
        visit[row][column + 3] = 1;
    }
}

void app::widgets::MainWindowWidget::on_tableWidget_2_cellClicked(int row, int column) //클릭된 cell의 row, column값을 받아온다.
{
    as4::model::Note* nn;
    nn = setforput(row, column);
    music->GetDrumSeq()->Put(*nn); //nn을 music의 Drum에 삽입한다.
    if(column == 37) //경우에 따라 cell의 색을 칠한다.
    {
        ui.tableWidget_2->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
        ui.tableWidget_2->item(row, (column+1))->setBackground(Qt::green);
        visit[row][column + 1] = 1;
        ui.tableWidget_2->item(row, (column+2))->setBackground(Qt::green);
        visit[row][column + 2] = 1;
    }
    else if(column == 38)
    {
        ui.tableWidget_2->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
        ui.tableWidget_2->item(row, (column+1))->setBackground(Qt::green);
        visit[row][column + 1] = 1;
    }
    else if(column == 39)
    {
        ui.tableWidget_2->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
    }
    else
    {
        ui.tableWidget_2->item(row, column)->setBackground(Qt::green);
        visit[row][column] = 1;
        ui.tableWidget_2->item(row, (column+1))->setBackground(Qt::green);
        visit[row][column + 1] = 1;
        ui.tableWidget_2->item(row, (column+2))->setBackground(Qt::green);
        visit[row][column + 2] = 1;
        ui.tableWidget_2->item(row, (column+3))->setBackground(Qt::green);
        visit[row][column + 3] = 1;
    }
}

void app::widgets::MainWindowWidget::on_tabWidget_tabBarClicked(int index) //클릭된 tabBar의 index를 받아온다
{
    if(index == 0) //index가 0일 경우 melody모드이다.
        mode = 0;
    else { //index가 1일 경우 drum모드이다.
        mode = 1;
    }
}

void app::widgets::MainWindowWidget::on_tableWidget_cellPressed(int row, int column)
{
    int cc;
    std::vector<as4::model::Note*> sub;
    int arr[12] = {3, 2, 1, 0, 11, 10, 9, 8, 7, 6, 5, 4}; //피아노 판의 row가 작은 순서대로 해당하는 pitch_class의 번호를 배열로 지정한다.
    int calc = arr[row]; //삭제하고 싶은 note의 pitch_class를 calc로 정한다.

    if(visit[row][column] != 1) //cellPressed는 마우스 왼쪽, 오른쪽 클릭을 모두 입력받는다. 우리는 색칠된 곳에서만 마우스 오른쪽 입력을 적용시킬 것이기 때문에 visit이 0이면 return시킨다.
    {
        return;
    }
    else {
        sub = music->GetMelodySeq()->Get(column); //sub를 melodyseq중 column의 pos에 재생되고 있는 Note* vector로 정한다.
        for(unsigned long long i = 0; i < sub.size(); i++)
        {
            if(calc == sub[i]->GetPitch().GetPitchClass()) //삭제할 Note를 찾는다.
            {
                cc = sub[i]->GetStart(); //삭제할 Note의 시작시간을 cc로 정한다.
                if(music->GetMelodySeq()->Remove(sub[i])) //실제 삭제하고 싶은 Note의 삭제가 제대로 이루어졌다면
                { //경우에 따라 색을 삭제하고 visit배열을 0으로 바꾼다.
                    if(sub[i]->GetStart() == 37)
                    {
                        ui.tableWidget->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                        ui.tableWidget->item(row, cc + 1)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 1] = 0;
                        ui.tableWidget->item(row, cc + 2)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 2] = 0;
                    }
                    else if(column == 38)
                    {
                        ui.tableWidget->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                        ui.tableWidget->item(row, cc + 1)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 1] = 0;
                    }
                    else if(column == 39)
                    {
                        ui.tableWidget->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                    }
                    else
                    {
                        ui.tableWidget->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                        ui.tableWidget->item(row, cc + 1)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 1] = 0;
                        ui.tableWidget->item(row, cc + 2)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 2] = 0;
                        ui.tableWidget->item(row, cc + 3)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 3] = 0;
                    }
                }
            }
        }
    }
}

void app::widgets::MainWindowWidget::on_tableWidget_2_cellPressed(int row, int column)
{
    int cc;
    std::vector<as4::model::Note*> sub;
    int arr[12] = {3, 2, 1, 0, 11, 10, 9, 8, 7, 6, 5, 4}; //피아노 판의 row가 작은 순서대로 해당하는 pitch_class의 번호를 배열로 지정한다.
    int calc = arr[row]; //삭제하고 싶은 note의 pitch_class를 calc로 정한다.

    if(visit[row][column] != 1) //cellPressed는 마우스 왼쪽, 오른쪽 클릭을 모두 입력받는다. 우리는 색칠된 곳에서만 마우스 오른쪽 입력을 적용시킬 것이기 때문에 visit이 0이면 return시킨다.
    {
        return;
    }
    else {
        sub = music->GetDrumSeq()->Get(column); //sub를 drumseq중 column의 pos에 재생되고 있는 Note* vector로 정한다.
        for(unsigned long long i = 0; i < sub.size(); i++)
        {
            if(calc == sub[i]->GetPitch().GetPitchClass()) //삭제할 Note를 찾는다.
            {
                cc = sub[i]->GetStart(); //삭제할 Note의 시작시간을 cc로 정한다.
                if(music->GetDrumSeq()->Remove(sub[i])) //실제 삭제하고 싶은 Note의 삭제가 제대로 이루어졌다면
                { //경우에 따라 색을 삭제하고 visit배열을 0으로 바꾼다.
                    if(sub[i]->GetStart() == 37)
                    {
                        ui.tableWidget_2->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                        ui.tableWidget_2->item(row, cc + 1)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 1] = 0;
                        ui.tableWidget_2->item(row, cc + 2)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 2] = 0;
                    }
                    else if(column == 38)
                    {
                        ui.tableWidget_2->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                        ui.tableWidget_2->item(row, cc + 1)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 1] = 0;
                    }
                    else if(column == 39)
                    {
                        ui.tableWidget_2->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                    }
                    else
                    {
                        ui.tableWidget_2->item(row, cc)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart()] = 0;
                        ui.tableWidget_2->item(row, cc + 1)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 1] = 0;
                        ui.tableWidget_2->item(row, cc + 2)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 2] = 0;
                        ui.tableWidget_2->item(row, cc + 3)->setBackground(Qt::white);
                        visit[row][sub[i]->GetStart() + 3] = 0;
                    }
                }
            }
        }
    }
}
