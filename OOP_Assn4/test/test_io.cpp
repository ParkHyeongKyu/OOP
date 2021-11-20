/** Test codes for model */

#include <QtTest/QtTest>
#include <fstream>

#include "io/seqio.h"
#include "io/songio.h"

using namespace as4::model;
using namespace as4::io;

class TestIo : public QObject
{
    Q_OBJECT
private slots:
    void ReadWriteSeq();
    void ReadWriteSong();
};

///////////////////////////////////////////////////////////////////////////
/// Problem 1-2) Make this test pass
///////////////////////////////////////////////////////////////////////////
void TestIo::ReadWriteSeq()
{
    ISeq *seq1 = new DefaultSeq;

    seq1->Put({100, 10, {0, 1}}); // C1 start:duration 100:10
    seq1->Put({0, 10, {0, 1}}); // C1 0:10
    seq1->Put({10, 10, {2, 1}}); // D1 10:10
    seq1->Put({10, 20, {5, 1}}); // F1 10:20

    // temporary output file
    std::string tmp_file_path = "TestIoReadWriteSeq.seq";

    {
        using namespace as4::io::operators;
        std::ofstream fout(tmp_file_path);
        fout << *seq1;
    }

    ISeq *seq2 = new DefaultSeq;

    {
        using namespace as4::io::operators;
        std::ifstream fin(tmp_file_path);
        fin >> *seq2;
    }
    QCOMPARE(*seq1, *seq2);
}

void TestIo::ReadWriteSong()
{
    Song song;

    song.GetMelodySeq()->Put({100, 10, {0, 1}}); // C1 start:duration 100:10
    song.GetMelodySeq()->Put({0, 10, {0, 1}}); // C1 0:10
    song.GetMelodySeq()->Put({10, 10, {2, 1}}); // D1 10:10
    song.GetMelodySeq()->Put({10, 20, {5, 1}}); // F1 10:20

    song.GetDrumSeq()->Put({90, 10, {0, 1}}); // C1 start:duration 100:10
    song.GetDrumSeq()->Put({10, 10, {0, 1}}); // C1 0:10
    song.GetDrumSeq()->Put({10, 10, {2, 1}}); // D1 10:10
    song.GetDrumSeq()->Put({10, 20, {5, 1}}); // F1 10:20

    // temporary output file
    std::string tmp_file_path = "TestIoReadWriteSong.song";

    {
        using namespace as4::io::operators;
        std::ofstream fout(tmp_file_path);
        fout << song;
    }

    Song song_recon;

    {
        using namespace as4::io::operators;
        std::ifstream fin(tmp_file_path);
        fin >> song_recon;
    }

    QCOMPARE(*song.GetMelodySeq(), *song_recon.GetMelodySeq());
    QCOMPARE(*song.GetDrumSeq(), *song_recon.GetDrumSeq());
}

QTEST_MAIN(TestIo)
#include "test_io.moc"
