#pragma once
#include <array>
#include <utility>
#include <vector>
#include <algorithm>

enum class Unit
{
	Unknown,
	Black,
	White
};

using Hint = std::vector<int>;

class Hints
{
	std::vector<Hint> row_hints;
	std::vector<Hint> column_hints;

public:
	//Hints (std::vector<Hint>&& rows, std::vector<Hint>&& columns) : row_hints(rows), column_hints(columns) {}
	Hints (std::vector<std::vector<int>> rows, std::vector<std::vector<int>> columns) 
			: row_hints(std::move(rows)),
			  column_hints(std::move(columns))
	{}
	Hints(const Hints& h)
		: row_hints(h.row_hints),
		  column_hints(h.column_hints)
	{}

	int maxNRow()
	{
		int biggest = -1;
		for (auto hint : row_hints)
		{
			biggest = std::max({ biggest, (int)hint.size() });
		}
		return biggest;
	}
	int maxNColumn()
	{
		int biggest = -1;
		for (auto hint : column_hints)
		{
			biggest = std::max({ biggest, (int)hint.size() });
		}
		return biggest;
	}
	

	std::tuple<Hint, Hint> getHints(int x, int y)
	{
		return std::make_tuple(column_hints[x], row_hints[y]);
	}
};

class Board
{
public:
	Board(int width, int height, Hints hints)
		: width(width),
		  height(height),
		  hints(std::move(hints))
	{
		state = std::vector<std::vector<Unit>>(width, std::vector<Unit>(height, Unit::Unknown));
	}

	Board(const Board& b) : width(b.width), height(b.height), hints(b.hints)
	{
		state = std::vector<std::vector<Unit>>(width, std::vector<Unit>(height));
		for (int i = 0; i < width; ++i)
		{
			std::copy(b.state[i].begin(), b.state[i].end(), state[i].begin());
		}
	}

	Unit& getUnit(int x, int y)
	{
		if (x < width && y < height)
		{
			return state[x][y];
		}
		else
		{
			throw std::exception("out of bound exception");
		}
	}
	void setBlack(int x, int y)
	{
		state[x][y] = Unit::Black;
	}
	void setWhite(int x, int y)
	{
		state[x][y] = Unit::White;
	}
	void setUnknown(int x, int y)
	{
		state[x][y] = Unit::Unknown;
	}

	Hints getHints ()
	{
		return hints;
	}
	
	const int width;
	const int height;
private:

	std::vector<std::vector<Unit> > state;
	Hints hints;
};
namespace std
{
	std::string to_string(Unit u)
	{
		if (u == Unit::Unknown)
		{
			return "U";
		} else if (u == Unit::Black)
		{
			return "B";
		} else if (u == Unit::White)
		{
			return "X";
		}
	}
	std::string to_string(Board b)
	{
		std::string s("");
		for (int x = 0; x < b.width; ++x)
		{
			for (int y = 0; y < b.height; ++y)
			{
				s += to_string(b.getUnit(x, y)) + " ";
			}
			s += "\n";
		}
		return s;
	}
}
