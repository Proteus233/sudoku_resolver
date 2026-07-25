#include <optional>
#include <set>
#include <vector>

typedef std::vector<std::set<int>> row;
typedef std::vector<row> Matrix;

struct Pos{
    int y = 0;
    int x = 0;
};


class Resolver {
 public:
  Resolver( std::vector<std::vector<std::optional<int>>>& start_sudoku);

 private:
 void clear(Matrix& mat);

    void eliminate_square(Matrix& mat, int y, int x);
    void eliminate_row(Matrix& mat, int i, int j);
    void eliminate_column(Matrix& mat, int i, int j);
    void solve_sudoku(Matrix& mat);
    void print_matrix(Matrix& mat);

    Pos min_pos_possib(Matrix& mat);

    bool solved(Matrix& mat);
};