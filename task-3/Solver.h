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
	constexpr static auto kUnsolved{-1};

	enum class Cell : bool
	{
		Empty = false,
		Filled = true
	};
	using Cells = std::vector<Cell>;

	struct Piece final
	{
		using Storage = std::vector<Piece>;

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
		std::size_t weight{0};
	};
	using Matrix = std::vector<MatrixRow>;

private:
	common::InputStream &input;
	common::OutputStream &output;

	int current_result;

private:
	/**
	 * @brief Simply processes case
	 */
	void process_case(std::size_t case_number) noexcept(false);
	/**
	 * @brief Parses pieces	from input stream
	 * @throw std::exception If any piece is broken
	 */
	[[nodiscard]] Piece::Storage parse_pieces(std::uint32_t piece_count,
	                                          std::uint32_t rows,
	                                          std::uint32_t columns) noexcept(false);
	/**
	 * @brief Completes treasure map
	 * @return Min number of pieces to cover map
	 */
	[[nodiscard]] int complete_map(std::uint32_t piece_count, std::uint32_t height, std::uint32_t width) noexcept;
	/**
	 * @brief Creates matrix of mapped pieces
	 * @details Each row in matrix represents Piece. Row contains bitmap for all coordinates which are covered by Piece
	 */
	[[nodiscard]] Matrix make_matrix(std::uint32_t piece_count, std::uint32_t height, std::uint32_t width);
	/**
	 * @brief Donald Knuth AlgoritmX implementation for Exact Cover problem solving
	 * @link https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
	 */
	void algorithm_x(const Matrix &original_matrix, std::uint32_t depth);
	/**
	 * @brief Simply prints result
	 */
	void print_case(int result) const noexcept;
};

}  // namespace task_three