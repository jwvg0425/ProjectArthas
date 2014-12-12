#pragma once
#include "Macro.h"
#include "DataType.h"
#include <array>
#include <vector>
#include <queue>
#include <hash_map>
#include <stack>

template <typename IType, int ROW, int COL>
struct array2d
{
	typedef std::array<std::array<IType, COL>, ROW> type;
};

template<typename IType, int A, int B, int C>
struct array3d
{
	typedef std::array<std::array<std::array<IType, C>, B>, A> type;
};