#ifndef DATASTRUCTURE_HEAD_BOUNDARYCELLIDS_H
#define DATASTRUCTURE_HEAD_BOUNDARYCELLIDS_H


class BoundaryCellIds
{
public:
	int* cell_count_;
	int n_cell_in_boundary_;
	int* cell_ids_in_boundary_;

	virtual void updateBoundary() = 0;

	BoundaryCellIds();
	~BoundaryCellIds();
	
};

#endif
