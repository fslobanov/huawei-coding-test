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
    , current_best_result{kUnsolved}
{
	pieces.reserve(100);
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

	parse_pieces(piece_count, row_count, column_count);
	print_case(complete_map(row_count, column_count));
}

void Solver::parse_pieces(const std::uint32_t piece_count, const std::uint32_t rows, const std::uint32_t columns)
{
	pieces.clear();

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
}

void Solver::algorithm_x(const Matrix &original_matrix, std::uint32_t depth)
{
	if(original_matrix.empty()) {
		std::cout << "SOLVED " << depth << std::endl;
		const auto signed_depth = static_cast<int>(depth);
		current_best_result =
		    (current_best_result != kUnsolved) ? std::min(current_best_result, signed_depth) : signed_depth;
		return;
	}

	for(auto index{0u}; index < original_matrix.size(); ++index) {
		auto matrix = original_matrix;
		const auto row_it = matrix.begin() + index;
		auto row = std::move(*(row_it));
		matrix.erase(row_it);

		for(auto column_it = row.cells.begin(); column_it != row.cells.end(); /**/) {
			const auto column_index = column_it - row.cells.begin();
			const auto &cell = *column_it;

			if(Cell::Empty == cell) {
				const auto all_zeros = std::all_of(matrix.begin(), matrix.end(), [&](const MatrixRow &matrix_row) {
					return Cell::Empty == matrix_row.cells[column_index];
				});
				if(all_zeros) {
					return;
				}
				++column_it;
				continue;
			}

			for(auto remaining_row_it = matrix.begin(); remaining_row_it != matrix.end();) {
				auto &rest_row = *remaining_row_it;
				const auto cell_it = rest_row.cells.begin() + column_index;
				if(Cell::Filled == *cell_it) {
					remaining_row_it = matrix.erase(remaining_row_it);
				} else {
					rest_row.cells.erase(cell_it);
					remaining_row_it = std::next(remaining_row_it);
				}
			}

			column_it = row.cells.erase(column_it);
		}

		algorithm_x(matrix, 1 + depth);
		/*row_it = matrix.insert(row_it, std::move(row));
		++row_it;*/
	}
}

int Solver::complete_map(std::uint32_t rows, std::uint32_t columns) noexcept
{
	std::cout << "#######################################" << std::endl;
	current_best_result = kUnsolved;

	Matrix matrix;
	matrix.reserve(pieces.size());

	for(const auto &piece : pieces) {
		std::cout << "# PIECE " << piece << std::endl;
		Cells cells(rows * columns, Cell::Empty);
		MatrixRow matrix_row{piece, std::move(cells)};

		for(auto column{piece.left_column}; column < piece.right_column; ++column) {
			for(auto row{piece.top_row}; row < piece.bottom_row; ++row) {
				matrix_row.cells[columns * row + column] = Cell::Filled;
			}
		}
		matrix.emplace_back(std::move(matrix_row));
	}

	algorithm_x(std::move(matrix), 0);
	return current_best_result;
}

void Solver::print_case(int result) const noexcept
{
	output << std::to_string(result) << std::endl;
}

}  // namespace task_three