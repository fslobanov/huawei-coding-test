/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 3:14 PM
 * \brief: 
 */

#include <Solver.h>

#include <limits>
#include <algorithm>
#include <cassert>
#include <stack>

namespace task_three {

Solver::Solver(common::InputStream &input, common::OutputStream &output)
    : input{input}
    , output{output}
    , current_result{kUnsolved}
{
}

void Solver::solve() noexcept(false)
{
	const auto num_cases = common::parse_integer(input, 1, 10);
	for(auto case_index{0u}; case_index < num_cases; ++case_index) {
		process_case(case_index);
	}
}

void Solver::process_case(const std::size_t) noexcept(false)
{
	// TODO: is this correct that row width is unbounded?
	const auto column_count = common::parse_integer(input, 1, std::numeric_limits<std::uint32_t>::max());
	const auto row_count = common::parse_integer(input, 0, 30);
	const auto piece_count = common::parse_integer(input, 1, 100);

	if(!column_count || !row_count) {
		print_case(kUnsolved);
		return;
	}

	print_case(complete_map(piece_count, row_count, column_count));
}

Solver::Piece::Storage Solver::parse_pieces(const std::uint32_t piece_count,
                                            const std::uint32_t rows,
                                            const std::uint32_t columns)
{
	Piece::Storage pieces;
	pieces.reserve(piece_count);

	for(auto piece_number{0u}; piece_number < piece_count; ++piece_number) {
		Piece piece{piece_number,
		            common::parse_integer(input, 0, columns),
		            common::parse_integer(input, 0, rows),
		            common::parse_integer(input, 0, columns),
		            common::parse_integer(input, 0, rows)};

		if(piece.left_column >= piece.right_column || piece.top_row >= piece.bottom_row) {
			throw std::invalid_argument("invalid piece");
		}

		pieces.emplace_back(piece);
	}

	return pieces;
}

void Solver::algorithm_x(const Matrix &original_matrix, const std::uint32_t depth)
{
	// Matrix is empty, solution found
	if(original_matrix.empty()) {
		const auto signed_depth = static_cast<int>(depth);
		// Update result, if better than existing
		current_result = (current_result != kUnsolved) ? std::min(current_result, signed_depth) : signed_depth;
		return;
	}

	// Just iterate matrix row by row
	for(auto index{0u}; index < original_matrix.size(); ++index) {
		// Deepcopy original matrix and erase current row to prevent later modifications and omit backtracking
		auto matrix = original_matrix;
		const auto current_row_it = matrix.begin() + index;
		// Extract one current row from matrix
		auto current_row = std::move(*(current_row_it));
		matrix.erase(current_row_it);

		// Iterating over selected row by columns and search for conflicting rows
		for(auto column_it = current_row.cells.begin(); column_it != current_row.cells.end(); /*unused*/) {
			const auto column_index = column_it - current_row.cells.begin();
			const auto &cell = *column_it;

			// If row cell is empty, we need to check, is there are another filled cell in this column
			if(Cell::Empty == cell) {
				const auto all_zeros =
				    std::all_of(matrix.begin(), matrix.end(), [&](const MatrixRow &matrix_row) noexcept {
					    return Cell::Empty == matrix_row.cells[column_index];
				    });
				// If column is all zeros, this matrix cannot be solved
				if(all_zeros) {
					return;
				}
				// Go to next column of current row otherwise
				++column_it;
				continue;
			}

			// Iterating over rest of rows by current column, to remove or adjust remaining rows
			for(auto rest_row_it = matrix.begin(); rest_row_it != matrix.end(); /*unused*/) {
				auto &rest_row = *rest_row_it;
				const auto cell_it = rest_row.cells.begin() + column_index;
				// If cell is filled it means conflict with current row, and rest row should be removed
				if(Cell::Filled == *cell_it) {
					rest_row_it = matrix.erase(rest_row_it);
				}
				// Not conflicting, just erase cell of this column in rest row
				else {
					rest_row.cells.erase(cell_it);
					rest_row_it = std::next(rest_row_it);
				}
			}

			// After all rest rows being iterated by current column, we may erase it
			column_it = current_row.cells.erase(column_it);
		}

		// Calling this algo again on remaining matrix copy
		algorithm_x(matrix, 1 + depth);
	}
}

Solver::Matrix Solver::make_matrix(const std::uint32_t piece_count,
                                   const std::uint32_t height,
                                   const std::uint32_t width)
{
	auto pieces = parse_pieces(piece_count, height, width);

	Matrix matrix;
	matrix.reserve(pieces.size());

	// Unrolling pieces into matrix, each row of matrix is representation of all cells of piece mapped into
	// one-dimension array, which is width*height size of map:

	// Piece 1: x0y0 x1y0 x2y0 x0y1 x1y1 x2y1 x0y2 x1y2 x2y2
	// Piece 2: x0y0 x1y0 x2y0 x0y1 x1y1 x2y1 x0y2 x1y2 x2y2

	for(const auto &piece : pieces) {
		Cells cells(width * height, Cell::Empty);
		MatrixRow matrix_row{piece, std::move(cells)};

		for(auto column{piece.left_column}; column < piece.right_column; ++column) {
			for(auto row{piece.top_row}; row < piece.bottom_row; ++row) {
				matrix_row.cells[width * row + column] = Cell::Filled;
				++matrix_row.weight;
			}
		}
		matrix.emplace_back(std::move(matrix_row));
	}

	return matrix;
}

int Solver::complete_map(const std::uint32_t piece_count,
                         const std::uint32_t height,
                         const std::uint32_t width) noexcept
{
	current_result = kUnsolved;
	algorithm_x(make_matrix(piece_count, height, width), 0);
	return current_result;
}

void Solver::print_case(int result) const noexcept
{
	output << std::to_string(result) << std::endl;
}

}  // namespace task_three