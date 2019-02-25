#ifndef SOLVERSKELETON_HEAD_BLOCK_H
#define SOLVERSKELETON_HEAD_BLOCK_H


class Block
{
	public:
		int test_block_;

		int n_cells_in_block_;
		int nb_face_in_wall_;

		Block(int test_block);
		~Block();


};


#endif