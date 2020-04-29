/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef TABLE_PRINTER_H
#define TABLE_PRINTER_H

#include "core.hpp"

class Table_printer
{
public:

	void add_row(std::vector<String> cells)
	{
		rows.push_back(cells);
	}

	String to_string()
	{
		std::vector<uint> column_widths;
		for (std::vector<String> row_cells : rows)
		{
			for (uint i = 0; i < row_cells.size(); i++)
			{
				String_ref cell = row_cells[i];
				uint width = cell.size();
				if (i == column_widths.size())
				{
					column_widths.push_back(width);
				}
				else
				{
					if (width > column_widths[i])
					{
						column_widths[i] = width;
					}
				}
			}
		}

		String result;
		for (std::vector<String> row_cells : rows)
		{
			if (result != "")
				result += "\n";
			for (uint i = 0; i < row_cells.size(); i++)
			{
				String_ref cell = row_cells[i];
				String new_cell = cell;
				while (new_cell.size() < column_widths[i])
					new_cell += ' ';
				if (i > 0)
					result += ' ';
				result += new_cell;
			}
		}

		return result;
	}

	void clear()
	{
		rows.clear();
	}

private:

	std::vector<std::vector<String> > rows;

};

#endif /* TABLE_PRINTER_H */

