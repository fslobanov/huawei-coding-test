/*
 * \author: Lobanov F.S.
 * \date: 10/14/22
 * \time: 3:47 PM
 * \brief: 
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace common {

using InputStream = std::istream;
using OutputStream = std::ostream;

/**
 * @brief Parses num of cases from stream
 * @throw If parsing failed or cases number precondition is not met
 */
[[nodiscard]] inline std::uint32_t parse_integer(InputStream &stream,
                                                 std::uint32_t min,
                                                 std::uint32_t max) noexcept(false)
{
	std::string buf;
	stream >> buf;

	if(stream.fail()) {
		throw std::invalid_argument("failed to read an integer from stream");
	}

	const auto parsed = std::stoul(buf);
	if(parsed >= std::numeric_limits<std::uint32_t>::max()) {
		throw std::invalid_argument("integer does not fit into 32bit unsigned: '" + std::to_string(parsed) + "'");
	}

	const auto value{static_cast<std::uint32_t>(parsed)};

	if(value < min || value > max) {
		throw std::invalid_argument("value is out of range '" + std::to_string(value) + "'");
	}

	return value;
}
}  // namespace common