/** Automatic test codes for model */

#include <QtTest/QtTest>
#include <string>
#include <tuple>

#include "model/time.h"
#include "model/pitch.h"
#include "model/seq.h"

using namespace as4::model;

class TestModel : public QObject
{
    Q_OBJECT
private slots:
    // pitch.h
    void ConstructPitch();
    void PitchToString();
    void PitchFromString();

    // time.h
    void TimeIntervalToBeats();
    void TimeIntervalToSeconds();
    void SecondsToTimeInterval();
    void BeatsToTimeInterval();

    // skipping tests for note.h

    // seq.h
    void PutNotesSeq();
    void RemoveNotesSeq();
    void GetOrderedSeq();
    void GetTimeLengthSeq();
};

///////////////////////////////////////////////////////////////////////////////
// Unit tests for pitch.h
///////////////////////////////////////////////////////////////////////////////
void TestModel::ConstructPitch()
{
    QVERIFY_EXCEPTION_THROWN(Pitch(1,-1), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(Pitch(-1,1), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(Pitch(12,1), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(Pitch(1,0), std::runtime_error);
}

void TestModel::PitchToString()
{
    const std::vector<std::tuple<std::string, int, int>> data = { 
        {"C1", 0, 1},
        {"C#1", 1, 1},
        {"B1", 11, 1},
        {"A12", 9, 12},
        {"D#4", 3, 4},
    };
    pitch::StandardPitchStringfier strf;
    for (const auto &d : data)
    {
        auto [str, pitch_class, octave] = d;
        Pitch p(pitch_class, octave);
        QCOMPARE(strf.ToString(p), str);
    }
}

void TestModel::PitchFromString()
{
    const std::vector<std::tuple<std::string, int, int>> data = { 
        {"C1", 0, 1},
        {"C#1", 1, 1},
        {"B1", 11, 1},
        {"A12", 9, 12},
        {"D#4", 3, 4},
    };

    pitch::StandardPitchStringfier strf;
    for (const auto &d : data)
    {
        auto [str, pitch_class, octave] = d;
        Pitch p = strf.FromString(str);
        QCOMPARE(p.GetPitchClass(), pitch_class);
        QCOMPARE(p.GetOctave(), octave);
    }

    const std::vector<std::string> invalid = {
        "random", "!", "~", "Z#", "Z", "Z#23", "Z2", "Z23", "B#"};
    for (size_t i=0; i<invalid.size(); i++)
    {
        QVERIFY_EXCEPTION_THROWN(strf.FromString(invalid[i]), std::runtime_error);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Unit tests for time.h
///////////////////////////////////////////////////////////////////////////////
void TestModel::TimeIntervalToBeats()
{
    TimeConfig tconfig = TimeConfig(120, 4);
    TimeInterval i1 = 0, i2 = 7, i3 = 8;

    QCOMPARE(tconfig.Beats(i1), 0);
    QCOMPARE(tconfig.Beats(i2), 1.75);
    QCOMPARE(tconfig.Beats(i3), 2.0);
}

void TestModel::TimeIntervalToSeconds()
{
    TimeConfig tconfig = TimeConfig(120, 4);
    TimeInterval i1 = 0, i2 = 480;

    QCOMPARE(tconfig.Seconds(i1), 0);
    QCOMPARE(tconfig.Seconds(i2), 60.0);
}

void TestModel::SecondsToTimeInterval()
{
    TimeConfig tconfig = TimeConfig(120, 4);
    const double seconds = 60.0;

    QCOMPARE(tconfig.IntervalFromSeconds(seconds), 480);
}

void TestModel::BeatsToTimeInterval()
{
    TimeConfig tconfig = TimeConfig(120, 4);
    const double beats = 1.75;

    QCOMPARE(tconfig.IntervalFromBeats(beats), 7);
}

///////////////////////////////////////////////////////////////////////////////
// Unit tests for seq.h
///////////////////////////////////////////////////////////////////////////////
void TestModel::PutNotesSeq()
{
    ISeq *seq = new DefaultSeq;

    seq->Put({0, 10, {0, 1}}); // C1 start:duration 0:10
    seq->Put({10, 10, {2, 1}}); // D1 10:10
    seq->Put({10, 20, {5, 1}}); // F1 10:20

    std::vector<Note*> at_0 = seq->Get(0);
    QCOMPARE(at_0.size(), 1);
    std::vector<Note*> at_10 = seq->Get(10);
    QCOMPARE(at_10.size(), 2);

    delete seq;
}

void TestModel::RemoveNotesSeq()
{
    ISeq *seq = new DefaultSeq;

    seq->Put({100, 10, {0, 1}}); // C1 start:duration 100:10
    seq->Put({0, 10, {0, 1}}); // C1 0:10
    seq->Put({10, 10, {2, 1}}); // D1 10:10
    seq->Put({10, 20, {5, 1}}); // F1 10:20

    Note *note = seq->Get(0).at(0);
    QCOMPARE(*note, Note(0,10,{0,1}));
    QVERIFY(seq->Remove(note));
    QCOMPARE(seq->Get(0).size(), 0);
    QCOMPARE(seq->GetOrdered().size(), 3);

    delete seq;
}

void TestModel::GetOrderedSeq()
{
    std::vector<Note> notes {
        {100, 10, {0, 1}},
        {0, 10, {0, 1}},
        {10, 20, {2, 1}},
        {10, 20, {5, 1}},
    };

    ISeq *seq = new DefaultSeq;

    for(size_t i=0; i<notes.size(); i++)
    {
        seq->Put(notes[i]);
    }

    std::sort(notes.begin(), notes.end(),
              [](const Note &a, const Note &b)
    {
        return a.GetStart() < b.GetStart();
    });

    std::vector<Note*> result = seq->GetOrdered();
    for(size_t i=0; i<notes.size(); i++)
    {
        QCOMPARE(*result[i], notes[i]);
    }

    delete seq;
}

void TestModel::GetTimeLengthSeq()
{
    ISeq *seq = new DefaultSeq;

    QCOMPARE(seq->GetSeqTimeLength(), 0);

    seq->Put({100, 10, {0, 1}}); // C1 start:duration 100:10
    seq->Put({0, 10, {0, 1}}); // C1 0:10
    seq->Put({10, 10, {2, 1}}); // D1 10:10
    seq->Put({10, 20, {5, 1}}); // F1 10:20

    QCOMPARE(seq->GetSeqTimeLength(), 110);

    delete seq;
}

QTEST_MAIN(TestModel)
#include "test_model.moc"
