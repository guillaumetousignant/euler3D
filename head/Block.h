#ifndef EULER3D_HEAD_BLOCK_H
#define EULER3D_HEAD_BLOCK_H

#include <string>
#include <vector>

class Block
{

public:

  Block();
  ~Block();



  int n_cells_in_block_;
  int nb_face_in_wall_;

};

#endif
