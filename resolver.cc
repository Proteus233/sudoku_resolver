#include "resolver.hh"

#include <cassert>
#include <iostream>
#include <optional>
#include <set>
#include <vector>

Resolver::Resolver(std::vector<std::vector<std::optional<int>>>& start_sudoku) {
  Matrix aux_mat(9, row(9));
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (start_sudoku[i][j].has_value()) {
        aux_mat[i][j] = {(start_sudoku[i][j].value())};
      } else {
        aux_mat[i][j] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
      }
    }
  }
  clear(aux_mat);
  clear(aux_mat);
  if (solve_sudoku(aux_mat)){
    //the sudooku is solved
  }else{
    //the sudoku const be solverd
  }
  print_matrix(aux_mat);
  Pos min = min_pos_possib(aux_mat);
  std::cout << "min possibilities at y:" << min.y << " x:" << min.x
            << std::endl;
}

void Resolver::clear(Matrix& mat) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (mat[i][j].size() == 1) {
        eliminate_square(mat, i, j);
        eliminate_row(mat, i, j);
        eliminate_column(mat, i, j);
      }
    }
  }
}

void Resolver::eliminate_square(Matrix& mat, int y, int x) {
  assert(!mat[y][x].empty());
  int start_i = (y / 3) * 3;
  int start_j = (x / 3) * 3;
  int val = *mat[y][x].begin();
  for (int i = start_i; i < start_i + 3; ++i) {
    for (int j = start_j; j < start_j + 3; ++j) {
      if (!(i == y && j == x)) {
        mat[i][j].erase(val);
      }
    }
  }
}

void Resolver::eliminate_row(Matrix& mat, int y, int x) {
  assert(!mat[y][x].empty());
  int val = *mat[y][x].begin();
  for (int i = 0; i < 9; i++) {
    if (!(i == x)) {
      mat[y][i].erase(val);
    }
  }
}

void Resolver::eliminate_column(Matrix& mat, int y, int x) {
  assert(!mat[y][x].empty());
  int val = *mat[y][x].begin();
  for (int i = 0; i < 9; i++) {
    if (!(i == y)) {
      mat[i][x].erase(val);
    }
  }
}

void Resolver::print_matrix(Matrix& mat) {
  for (int l1 = 0; l1 < 11; l1++) {
    std::cout << "-";
  };
  std::cout << std::endl;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      auto poss = mat[i][j];
      for (auto p : poss) {
        std::cout << p << " ";
      }
      std::cout << ", ";
    }
    std::cout << std::endl;
  }
}

Pos Resolver::min_pos_possib(Matrix& mat) {
  int min_possib = 9;
  Pos result = {0, 0};
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (mat[i][j].size() > 1 && mat[i][j].size() < min_possib) {
        min_possib = mat[i][j].size();
        result = {i, j};
        if (min_possib == 2) {
          return result;
        }
      }
    }
  }
  return result;
}

bool Resolver::solved(Matrix& mat) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (mat[i][j].size() > 1) {
        return false;
      }
    }
  }
  return true;
}


bool Resolver::correct(Matrix& mat){
  return true;
}

bool Resolver::solve_sudoku(Matrix& mat) {
  auto aux_mat = mat;
  clear(aux_mat);

  // cas base, es incompatible
    if (incompatible(aux_mat)){
    return false;
  }

  // cas base: esta solucionat: retorna la matriu solucionada
  if (solved(aux_mat)) {
    mat = aux_mat;
    return true;
  }

  //if we are here at least one set has multiple options
  Pos min_pos = min_pos_possib(aux_mat);
  auto poss = aux_mat[min_pos.y][min_pos.x];
  for (auto p : poss) {
    //std::cout << p << " ";

    aux_mat[min_pos.y][min_pos.x] = {p};

    if (solve_sudoku(aux_mat)){
      mat = aux_mat;
      return true; //the sudoku is completed
    }
    else{
      if (poss.size() == 1){
        //the only option left in the set is not compatible
        return false;
      }
      poss.erase(p); //caution, might leave an empty set
      aux_mat[min_pos.y][min_pos.x] = poss;

    }
  }
  return false;
  //if we are here there are no possibilities possible
  //there si an edge case if neither of the possibilities are poissible
}