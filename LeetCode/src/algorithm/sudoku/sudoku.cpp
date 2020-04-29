#include "sudoku.h"

sudoku::sudoku()
{
}

sudoku::~sudoku()
{
}

void sudoku::solve(vector<vector<char>>& matrix)
{
	vector<vector<char>> possible_values;
	bool rt = pre_processor(matrix, possible_values);
	if (rt == false)
		return;
	rt = backtracking_solve(matrix, 0, possible_values);
}

bool sudoku::isInSubMatrix(char val, const matrix_index& index, const vector<vector<char>>& matrix)
{
	cell _cell = get_cell(index);
	for (int r = _cell.m_top.m_r; r <= _cell.m_bottom.m_r; ++r)
	{
		for (int c = _cell.m_top.m_c; c <= _cell.m_bottom.m_c; ++c)
		{
			if (matrix[r][c] == val)
				return true;
		}
	}
	return false;
}

bool sudoku::isInRowOrCol(char val, const matrix_index& index, const vector<vector<char>>& matrix)
{
	for (int i = 0; i < 9; ++i)
	{
		if (val == matrix[index.m_r][i])
			return true;
	}

	for (int i = 0; i < 9; ++i)
	{
		if (val == matrix[i][index.m_c])
			return true;
	}
	return false;
}

cell sudoku::get_cell(const matrix_index& index)
{
	cell _cell;
	_cell.m_top.m_r = index.m_r - index.m_r % 3;
	_cell.m_top.m_c = index.m_c - index.m_c % 3;

	_cell.m_bottom.m_r = _cell.m_top.m_r + 2;
	_cell.m_bottom.m_c = _cell.m_top.m_c + 2;

	return _cell;
}

bool sudoku::backtracking_solve(vector<vector<char>>& matrix, int index, const vector<vector<char>>& possible_values)
{
	if (index > 80)
		return true;

	bool rt = false;
	int subMatrixIndex = index / 9;
	int subMatrixDataIndex = index % 9;
	if (possible_values[index].size() > 0)
	{
		for (int i = 0; i < possible_values[index].size(); ++i)
		{
			//判断该格能否填值
			if (is_avaliable(possible_values[index][i], matrix, index) == true)
			{
				matrix[subMatrixIndex][subMatrixDataIndex] = possible_values[index][i];
				rt = backtracking_solve(matrix, index + 1, possible_values);
				if (rt == true)
					break;
				else
				{
					matrix[subMatrixIndex][subMatrixDataIndex] = '.';
				}
				continue;
			}
			else
			{
				matrix[subMatrixIndex][subMatrixDataIndex] = '.';
				rt = false;
			}
		}
		return rt;
	}
	else
	{
		return backtracking_solve(matrix, index + 1, possible_values);
	}
}

void print_matrix(const vector<vector<char>>& matrix)
{
	cout << "********************************************"<<endl;
	for (int row = 0; row < 9; ++row)
	{
		cout << "* ";
		for (int col = 0; col < 9; ++col)
		{
			cout << matrix[row][col] << " ";
		}
		cout << " *";
		cout << endl;
	}
	cout << "********************************************" << endl << endl << endl;
}
void sudoku_test()
{
	vector<vector<char>> matrix;
	char row0[9] = { '.','.','9','7','4','8','.','.','.' };
	char row1[9] = { '7','.','.','.','.','.','.','.','.' };
	char row2[9] = { '.','2','.','1','.','9','.','.','.' };
	char row3[9] = { '.','.','7','.','.','.','2','4','.' };
	char row4[9] = { '.','6','4','.','1','.','5','9','.' };
	char row5[9] = { '.','9','8','.','.','.','3','.','.' };
	char row6[9] = { '.','.','.','8','.','3','.','2','.' };
	char row7[9] = { '.','.','.','.','.','.','.','.','6' };
	char row8[9] = { '.','.','.','2','7','5','9','.','.' };
	matrix.push_back(vector<char>(row0, row0 + 9));
	matrix.push_back(vector<char>(row1, row1 + 9));
	matrix.push_back(vector<char>(row2, row2 + 9));
	matrix.push_back(vector<char>(row3, row3 + 9));
	matrix.push_back(vector<char>(row4, row4 + 9));
	matrix.push_back(vector<char>(row5, row5 + 9));
	matrix.push_back(vector<char>(row6, row6 + 9));
	matrix.push_back(vector<char>(row7, row7 + 9));
	matrix.push_back(vector<char>(row8, row8 + 9));
	print_matrix(matrix);
	sudoku _sudoku;
	_sudoku.solve(matrix);
	print_matrix(matrix);
}

bool sudoku::is_avaliable(char val, vector<vector<char>>& matrix, int index)
{
	matrix_index _matrix_index(index / 9, index % 9);
	if (isInSubMatrix(val, _matrix_index, matrix) == true)
		return false;
	if (isInRowOrCol(val, _matrix_index, matrix) == true)
		return false;
	return true;
}

bool sudoku::pre_processor(vector<vector<char>>& matrix, vector<vector<char>>& possible_values)
{
	char data[9] = { '1','2','3','4','5','6','7','8','9' };
	bool is_continue_processor = false;
	for (int index = 0; index < 81; ++index)
	{
		vector<char> values;
		matrix_index _matrix_index(index / 9, index % 9);
		if (matrix[_matrix_index.m_r][_matrix_index.m_c] == '.')
		{
			for (int i = 0; i < 9; ++i)
			{
				if (isInSubMatrix(data[i], _matrix_index, matrix) == true)
					continue;
				if (isInRowOrCol(data[i], _matrix_index, matrix) == true)
					continue;
				values.push_back(data[i]);
			}
			if (values.size() == 0)
				return false;
			if (values.size() == 1)
			{
				is_continue_processor = true;
				matrix[_matrix_index.m_r][_matrix_index.m_c] = values[0];
				values.clear();
			}
		}
		possible_values.push_back(values);
	}
	if (is_continue_processor)
	{
		possible_values.clear();
		return pre_processor(matrix, possible_values);
	}
	return true;
}