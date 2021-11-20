#ifndef __AS4_MODEL_SEQ_H
#define __AS4_MODEL_SEQ_H

#include <vector>
#include "model/note.h"
#include "model/time.h"

namespace as4::model
{
    /**
     * Abstract)
     * Abstract class for any note sequence
     *
     * Note)
     * Why would we want to use this useless class without any implementation?
     *
     * If you read "io/seqio.h" or some test codes provided with this project,
     * you'll notice that when they take any note sequence as parameters,
     * they are always using 'ISeq', not VectorSeq or something.
     *
     * As far as the method definitions of ISeq stay still, I can write any
     * code that uses note sequence, even without a single implementation.
     *
     * As a TA, this is a good thing because I can write test codes without
     * considering how you implemented details.
     *
     * In real projects, you can prepare multiple implementations for a single
     * abstract class (interface) and use different implementation for
     * different situations
     */
    class ISeq
    {
        public:
            /** Define virtual destructor for abstract class */
            virtual ~ISeq() =default;
            /**
             * Abstract)
             * Puts a new note into the sequence
             * 
             * @param note          a Note object to be put
             */
            virtual void Put(const Note &note) =0;

            /**
             * Abstract)
             * Get all notes that starts at or is playing at seeker position.
             *
             * Note)
             * There can be multiple notes to be played given a seeker position.
             * There are multiple notes with same start timestamps (Polyphony)
             *
             * Returns)
             * Pointers to Notes to be played. The lifetime of this pointers are
             * equal to this object's.
             */
            virtual std::vector<Note*> Get(const Timestamp &pos_seeker) =0;

            /**
             * Abstract)
             * Remove a note from the sequence
             *
             * Returns)
             * True if a note is removed. False if the note did not exist.
             */
            virtual bool Remove(const Note *note) =0;

            /**
             * Abstract)
             * Get ordered vector of notes.
             *
             * Note)
             * The first elements of the vector has the earliest start time.
             *
             * Returns)
             * Pointers to all notes in ascending order of start time
             */
            const virtual std::vector<Note*> GetOrdered() const =0;

            /**
             * Abstract)
             * Get time length of this sequence.
             *
             * Note)
             * Length of a sequence is defined by the max value of start time
             * plus duration of the note.
             */
            virtual TimeInterval GetSeqTimeLength() const =0;

            virtual std::vector<Note*> GetStart(const Timestamp& pos_seeker) = 0; //pos_seeker에서 시작하는 Note들의 vector을 return해주는 함수
    };

    // You can remove this default implementation if you want.
    // You might want to use different underlying implementation for ISeq
    //
    // Right now, it uses std::list of Note as container for notes
    // Is this the best way you can go with? (If it works, it doesn't matter)
    // There will be no additional credit for this change.
    //
    // Hint : std::priority_queue
    class VectorSeq : public ISeq
    {
        public:
            VectorSeq() =default;
            ~VectorSeq() override;
            // WARNING : after copying A to B, the Note* acquired from A is not
            //           compatible with B and vice versa.
            VectorSeq(const VectorSeq &other);
            VectorSeq &operator=(const VectorSeq &other);
            /**
             * There are two ways to override virtual methods
             * 
             * Given 'class A { virtual void A() =0; };'
             * 
             * 1) class B : public A { virtual void A(); };
             * 2) class B : public A { void A() override; }
             * 
             * They are effectively the same.
             * In this code, we use 2). Because it generates compile time error if
             * we try to override non-existing parent virtual method.
             */
            void Put(const Note &note) override;
            /**
             * note that this method does not allocate any new memory space for
             * Note objects. DON'T DELETE THE POINTERS RETURNED FROM THIS CALL. 
             * IT IS ONLY FOR REFERENCING!!!. 
             *
             * After this object is deleted, the pointers can't be accessed.
             *
             * Actually, there is a safer way to handle this situation.
             * Instead of raw pointers, we can return smart pointers introduced
             * in C++11. In this case, std::weak_ptr is the best in my opinion.
             *
             * If you are interested, please refer to std::shared_ptr
             * std::unique_ptr, std::weak_ptr.
             */
            std::vector<Note*> Get(const Timestamp &pos_seeker) override;

            bool Remove(const Note *note) override;

            const std::vector<Note*> GetOrdered() const override;

            TimeInterval GetSeqTimeLength() const override;

            std::vector<Note*> GetStart(const Timestamp& pos_seeker) override; //playmusic의 GetStart함수를 override함

        private:
            void Sort(std::vector <Note*> vsec);

            std::vector<Note*> m_notes;
    };

    // If you want to use your implementation in test_model.cpp and song.h,
    // change 'VectorSeq' to something else
    using DefaultSeq = VectorSeq;
}

#endif
