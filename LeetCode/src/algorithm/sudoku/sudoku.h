#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>
#include <iostream>
#include <deque>
using namespace std;

struct matrix_index
{
	inline matrix_index(int r, int c)
		: m_r(r)
		, m_c(c)
	{
	}
	inline matrix_index()
		: m_r(-1)
		, m_c(-1)
	{}
	int m_r;
	int m_c;
};

struct cell
{
	matrix_index m_top;
	matrix_index m_bottom;
};

class sudoku
{
public:
	sudoku();
	~sudoku();

public:
	/*
	matrix 是9x9的矩阵
	一个数独的解法需遵循如下规则：
	数字 1-9 在每一行只能出现一次。
	数字 1-9 在每一列只能出现一次。
	数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
	空白格用 '.' 表示
	*/
	void solve(vector<vector<char>>& matrix);

private:
	//判断是否出现在九宫格内
	bool isInSubMatrix(char val, const matrix_index& index, const vector<vector<char>>& matrix);

	//判断在所在的行与列上是否出现了该数字
	bool isInRowOrCol(char val, const matrix_index& index, const vector<vector<char>>& matrix);

	cell get_cell(const matrix_index& index);

	//判断一个值在指定位置是否可用
	bool is_avaliable(char val, vector<vector<char>>& matrix, int index);

	//对矩阵进行预处理，将只有一个数字可用的空格填充上，并返回其他空格的可用填充数字
	bool pre_processor(vector<vector<char>>& matrix, vector<vector<char>>& possible_values);

	bool backtracking_solve(vector<vector<char>>& matrix, int index, const vector<vector<char>>& possible_values);
};
void sudoku_test();

#endif //SUDOKU_H
