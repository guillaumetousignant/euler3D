#ifndef DUMMY_BLOCK_H
#define DUMMY_BLOCK_H

class DummyBlock {
    public:
        DummyBlock();
        ~DummyBlock();

        int* boundary_values_;
        void fillBlock(int i);
};
#endif