/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 3:14 PM
 * \brief: 
 */

#pragma once

#include <vector>
#include <set>

#include <common.h>
#include <ostream>

namespace task_three {

class Solver final
{
public:
	Solver(common::InputStream &input, common::OutputStream &output);
	void solve() noexcept(false);
	
private:
	constexpr static int kUnsolved = -1;
	enum class Cell : bool
	{
		Empty = false,
		Filled = true
	};
	using Cells = std::vector<Cell>;
	
	struct Piece final
	{
		std::size_t index{};
		
		std::uint32_t left_column{};
		std::uint32_t top_row{};
		std::uint32_t right_column{};
		std::uint32_t bottom_row{};

		friend std::ostream &operator<<(std::ostream &os, const Piece &piece)
		{
			os << "#" << piece.index << ": " << piece.left_column << "/" << piece.top_row << " " << piece.right_column
			   << "/" << piece.bottom_row;
			return os;
		}
	};
	
	struct MatrixRow final
	{
		Piece piece;
		Cells cells;
	};
	using Matrix = std::vector<MatrixRow>;

private:
	common::InputStream &input;
	common::OutputStream &output;
	
	std::vector<Piece> pieces;
	int current_best_result;
	
private:
	void process_case(std::size_t case_number) noexcept(false);
	void parse_pieces(std::uint32_t piece_count, std::uint32_t rows, std::uint32_t columns) noexcept(false);
	[[nodiscard]] int complete_map(std::uint32_t rows, std::uint32_t columns) noexcept;
	// https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
	void algorithm_x(const Matrix &original_matrix, std::uint32_t depth);
	void print_case(int result) const noexcept;
};

}  // namespace task_three