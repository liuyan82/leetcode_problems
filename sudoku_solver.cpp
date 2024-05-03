#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:

    string OutputFlag(unsigned short flag) {
        unsigned short count = flag >> 9;
        if (count == 0) {
            return "[]";
        }
        string available_number = "[";
        for (int i = 0; i < 9; ++i) {
            if ((flag & (0x1 << i)) == 0) {
                available_number.push_back('1' + i);
                available_number.push_back(',');
            }
        }
        if (available_number.size() > 1) {
            available_number.pop_back();
        }
        available_number.push_back(']');
        return available_number;
    }

    /**
     *  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
     * |    left count     |  used bits     |
     * @return -1 if the sudoku is not legal; otherwise the modified flag
     */
    unsigned short SetUsed(unsigned short flag, int used_number) {
        unsigned short left_count = flag >> 9;
        if (left_count == 0) {
            return flag;
        }

        if ((flag & (0x1 << used_number)) == 0) {
            --left_count;
            flag = (left_count << 9) | (flag & 0x1FF) | (0x1 << used_number);
        }

        return flag;
    }

    unsigned short MergeFlag(unsigned short flag1, unsigned short flag2) {
        unsigned short used_flag = (flag1 & 0x1FF) | (flag2 & 0x1FF);
        unsigned short count = 9;
        for (int i = 0; i < 9; ++i) {
            if ((used_flag & (0x1 << i)) != 0) {
                --count;
            }
        }

        return (count << 9) | used_flag;
    }

    /**
     * @brief 
     * 
     * @tparam row 
     * @tparam col 
     * @param i 
     * @param j 
     * @param num 
     * @return true if update succeeded, false if sudoku become invalid
     */
    template<size_t row, size_t col>
    bool UpdateFlagsOnNewFill(unsigned short (&flags)[row][col], int i, int j, int num) {
        if ((flags[i][j] & (0x1 << num)) != 0){
            return false;
        }
        flags[i][j] = 0;
       
        // 更新所在行、列、宫的所有格的标签
        for (int x = 0; x < 9; ++x) {
            flags[i][x] = SetUsed(flags[i][x], num);
        }
        for (int x = 0; x < 9; ++x) {
            flags[x][j] = SetUsed(flags[x][j], num);
        }
        int k = (i / 3) * 3 + (j / 3);
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                unsigned char r_index = 3 * (k / 3) + x;
                unsigned char c_index = 3 * (k % 3) + y;
                flags[r_index][c_index] = SetUsed(flags[r_index][c_index], num);
            }
        }
        return true;
    }

    template<int row, int col>
    void CalculateFlags(vector<vector<char>>& board, unsigned short (&flags)[row][col]) {
        // 按行更新标签
        for (int i = 0; i < 9; ++i) {
            int flag = 9 << 9; // 每行的flag是一样的，初始值为9种可能，每个数字的标记都为0
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }
                int num = board[i][j] - '1';
                flags[i][j] = 0; // 数已经定了，用0种可能性来标记
                flag = SetUsed(flag, num);
            }

            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    flags[i][j] = flag;
                }
            }
        }

        // 按列更新标签
        for (int j = 0; j < 9; ++j) {
            unsigned short flag = 9 << 9; // 每列flag一样，最终需要跟已经生成的flag合并
            for (int i = 0; i < 9; ++i) {
                if (board[i][j] == '.') {
                    continue;
                }
                int num = board[i][j] - '1';
                flags[i][j] = 0; // 数已经定了，用0种可能性来标记
                flag = SetUsed(flag, num);
            }

            for (int i = 0; i < 9; ++i) {
                if (board[i][j] == '.') {
                    flags[i][j] = MergeFlag(flags[i][j], flag);
                }
            }
        }

        // 按宫更新标签
        for (int k = 0; k < 9; ++k) {
            int flag = 9 << 9;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    unsigned char r_index = 3 * (k / 3) + i;
                    unsigned char c_index = 3 * (k % 3) + j;
                    if (board[r_index][c_index] == '.') {
                        continue;
                    }
                    int num = board[r_index][c_index] - '1';
                    flags[r_index][c_index] = 0; // 数已经定了，用0种可能性来标记
                    flag = SetUsed(flag, num);
                }
            }

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    unsigned char r_index = 3 * (k / 3) + i;
                    unsigned char c_index = 3 * (k % 3) + j;
                    if (board[r_index][c_index] == '.') {
                        flags[r_index][c_index] = MergeFlag(flags[r_index][c_index], flag);
                    }
                }
            }
        }
    }

    /**
     * @brief 
     * 
     * @tparam row 
     * @tparam col 
     * @param board 
     * @param all_set 
     * @param new_filled 
     * @return false if sudoku not valid after filled, ortherwise true (no new filled or valid after filled)
     */
    template<int row, int col>
    bool FillUniqCell(vector<vector<char> >& board, unsigned short (&flags)[row][col], bool& all_set, bool& new_filled) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    all_set = false;
                }
                // 只计算只剩一种可能的空位
                // 还需要从另一个角度考虑：该行、该列、该宫还缺什么数？是不是只能放在某个格里？
                if ((flags[i][j] >> 9) == 1) {
                    unsigned char num = 0;
                    for (; num < 9; ++num) {
                        if ((flags[i][j] & (0x1 << num)) == 0) {
                            break;
                        }
                    }
                    if (num < 9) {
                        // std::cout << "Fill (" << i << ", " << j << ") with " << (char)('1' + num) << std::endl;
                        board[i][j] = '1' + num;
                        flags[i][j] = 0;
                    }
                    
                    // 更新所在行、列、宫的所有格的标签
                    if (!UpdateFlagsOnNewFill(flags, i, j, num)) {
                        return false;
                    }
                    new_filled = true;
                }
            }
        }
        return true;
    }

    template<int row, int col>
    bool FillUniqNumberByRow(vector<vector<char> >& board, unsigned short (&flags)[row][col], bool& all_set, bool& new_filled) {
        // 按行考虑缺数
        for (int i = 0; i < 9; ++i) {
            int flag = 9 << 9;
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }
                flag = SetUsed(flag, board[i][j] - '1');
            }

            // 把当前行缺数的情况打出来
            // std::cout << "Lack Number In Row " << i << ": " << OutputFlag(flag) << std::endl;

            for (int k = 0; k < 9; ++k) {
                
                if ((flag >> 9) > 0 && (flag & (0x1 << k)) == 0) {
                    int target_pos = -1;
                    for (int j = 0; j < 9; ++j) {
                        if ((flags[i][j] >> 9) > 0 && (flags[i][j] & (0x1 << k)) == 0) {
                            if (target_pos == -1) {
                                target_pos = j;
                            } else {
                                target_pos = -1;
                                break;
                            }
                        }
                    }
                    if (target_pos != -1) {
                        // std::cout << "Fill-4 (" << i << ", " << target_pos << ") with " << (char)('1' + k) << std::endl;
                        board[i][target_pos] = '1' + k;
                        if (!UpdateFlagsOnNewFill(flags, i, target_pos, k)) {
                            return false;
                        }
                        new_filled = true;
                    }
                }
            }
        }
        return true;
    }

    template<int row, int col>
    bool FillUniqNumberByCol(vector<vector<char> >& board, unsigned short (&flags)[row][col], bool& all_set, bool& new_filled) {
        // 按列考虑缺数
        for (int j = 0; j < 9; ++j) {
            int flag = 9 << 9;
            for (int i = 0; i < 9; ++i) {
                if (board[i][j] == '.') {
                    continue;
                }
                flag = SetUsed(flag, board[i][j] - '1');
            }

            // 把当前列缺数的情况打出来
            // std::cout << "Lack Number In Column " << j << ": " << OutputFlag(flag) << std::endl;

            for (int k = 0; k < 9; ++k) {
                
                if ((flag >> 9) > 0 && (flag & (0x1 << k)) == 0) {
                    int target_pos = -1;
                    for (int i = 0; i < 9; ++i) {
                        if ((flags[i][j] >> 9) > 0 && (flags[i][j] & (0x1 << k)) == 0) {
                            if (target_pos == -1) {
                                target_pos = i;
                            } else {
                                target_pos = -1;
                                break;
                            }
                        }
                    }
                    if (target_pos != -1) {
                        // std::cout << "Fill-5 (" << target_pos << ", " << j << ") with " << (char)('1' + k) << std::endl;
                        board[target_pos][j] = '1' + k;
                        if (!UpdateFlagsOnNewFill(flags, target_pos, j, k)) {
                            return false;
                        }
                        new_filled = true;
                    }
                }
            }
        }
        return true;
    }

    template<int row, int col>
    bool FillUniqNumberBySqure(vector<vector<char> >& board, unsigned short (&flags)[row][col], bool& all_set, bool& new_filled) {
        // 按宫考虑缺数
        for (int k = 0; k < 9; ++k) {
            int flag = 9 << 9;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    unsigned char r_index = 3 * (k / 3) + i;
                    unsigned char c_index = 3 * (k % 3) + j;
                    if (board[r_index][c_index] != '.') {
                        flag = SetUsed(flag, board[r_index][c_index] - '1');
                    }
                }
            }

            // 打印宫缺数情况
            // std::cout << "Lack Number In Square " << k << ": " << OutputFlag(flag) << std::endl;

            for (int x = 0; x < 9; ++x) {
                if ((flag >> 9) == 0 || (flag & (0x1 << x)) != 0) {
                    continue;
                }
                int target_r = -1;
                int target_c = -1;
                bool unique_pos = true;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        unsigned char r_index = 3 * (k / 3) + i;
                        unsigned char c_index = 3 * (k % 3) + j;
                        if ((flags[r_index][c_index] >> 9) > 0 &&  (flags[r_index][c_index] & (0x1 << x)) == 0) {
                            if (target_r != -1) {
                                target_r = -1;
                                target_c = -1;
                                unique_pos = false;
                                break;
                            } else {
                                target_r = r_index;
                                target_c = c_index;
                            }
                        }
                    }
                    if (!unique_pos) {
                        break;
                    }
                }
                if (target_r >= 0 && unique_pos) {
                    // std::cout << "Fill-6 (" << target_r << ", " << target_c << ") with " << (char)('1' + x) << std::endl;
                    board[target_r][target_c] = '1' + x;
                    if (!UpdateFlagsOnNewFill(flags, target_r, target_c, x)) {
                        return false;
                    }
                    new_filled = true;
                }
            }
        }
        return true;
    }

    /**
     * @brief 使用唯一数法解决数独
     * 
     * @tparam row 
     * @tparam col 
     * @param board 
     * @return int  
     *          1: 已全部解决
     *          0: 未全部解决，未冲突； 
     *         -1: 有冲突
     */
    template<int row, int col>
    int SolveSudoku(vector<vector<char>>& board, unsigned short (&flags)[row][col]) {
        bool all_set = true;
        for(;;) {
            all_set = true;
            bool new_filled = false;
            // 按flag来计算未知位置的数字
            if (!FillUniqCell(board, flags, all_set, new_filled)) {
                return -1;
            }

            if (!FillUniqNumberByRow(board, flags, all_set, new_filled)) {
                return -1;
            }

            if (!FillUniqNumberBySqure(board, flags, all_set, new_filled)) {
                return -1;
            }

            // for (int i = 0; i < 9; ++i) {
            //     for (int j = 0; j < 9; ++j) {
            //         std::cout << board[i][j] << "\t";
            //     }
            //     std::cout << std::endl;
            // }
            // std::cout << "---------------------" << std::endl;

            // for (int i = 0; i < 9; ++i) {
            //     for (int j = 0; j < 9; ++j) {
            //         std::cout << "Available In " << i << ", " << j << " is " << OutputFlag(flags[i][j]) << std::endl;
            //     }
            // }

            if (all_set || !new_filled) {
                break;
            }
        }
        return all_set ? 1 : 0;
    }

    template<int row, int col>
    bool SolveSudokuWithGuess(vector<vector<char>>& board, unsigned short (&flags)[row][col], std::string guess_log, int level) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                int count = (flags[i][j] >> 9);
                if (count == 0) {
                    continue;
                }
                for (int k = 0; k < 9; ++k) {
                    if ((flags[i][j] & (0x1 << k)) == 0) {
                        std::string current_guess_log = guess_log + ", (";
                        current_guess_log.append(std::to_string(i)).append(", ")
                        .append(std::to_string(j)).append(") -> ").append(std::to_string(k + 1));
                        std::cout << "Guess: " << current_guess_log << std::endl;
                        vector<vector<char>> temp_board = board;
                        unsigned short temp_flags[9][9] = {0};
                        memcpy((void*)temp_flags, flags, sizeof(flags));
                        temp_board[i][j] = '1' + k;
                        if (!UpdateFlagsOnNewFill(temp_flags, i, j, k)) {
                            continue;
                        }
                        int normal_solve_result = SolveSudoku(temp_board, temp_flags);

                        if (normal_solve_result == 1) {
                            board = temp_board;
                            
                            for (int i = 0; i < 9; ++i) {
                                for (int j = 0; j < 9; ++j) {
                                    std::cout << temp_board[i][j] << "\t";
                                }
                                std::cout << std::endl;
                            }
                            return true;
                        }
                        if (normal_solve_result == -1) {
                            continue;
                        }

                        if (normal_solve_result == 0) {
                            bool succeeded = SolveSudokuWithGuess(temp_board, temp_flags, current_guess_log, level + 1);
                            for (int i = 0; i < 9; ++i) {
                                for (int j = 0; j < 9; ++j) {
                                    std::cout << temp_board[i][j] << "\t";
                                }
                                std::cout << std::endl;
                            }
                            if (succeeded) {
                                board = temp_board;
                                return true;
                            } else {
                                continue;
                            }
                        }
                    }
                }
            }
        }
        return false;
        
    }

    void solveSudoku(vector<vector<char>>& board) {
        unsigned short flags[9][9] = { 0 };
        CalculateFlags(board, flags);
        if (SolveSudoku(board, flags) == 1) {
            return;
        }
        SolveSudokuWithGuess(board, flags, "", 0);
    }
};

int main(int argc, const char **argv) {
    /**
     *[['.','.','9','7','4','8','.','.','.'],
     * ['7','.','.','.','.','.','.','.','.'],
     * ['.','2','.','1','.','9','.','.','.'],
     * ['.','.','7','.','.','.','2','4','.'],
     * ['.','6','4','.','1','.','5','9','.'],
     * ['.','9','8','.','.','.','3','.','.'],
     * ['.','.','.','8','.','3','.','2','.'],
     * ['.','.','.','.','.','.','.','.','6'],
     * ['.','.','.','2','7','5','9','.','.']]
     */

    char data[9][9] = {{'.','.','9','7','4','8','.','.','.'},
        {'7','.','.','.','.','.','.','.','.'},
        {'.','2','.','1','.','9','.','.','.'},
        {'.','.','7','.','.','.','2','4','.'},
        {'.','6','4','.','1','.','5','9','.'},
        {'.','9','8','.','.','.','3','.','.'},
        {'.','.','.','8','.','3','.','2','.'},
        {'.','.','.','.','.','.','.','.','6'},
        {'.','.','.','2','7','5','9','.','.'}
    };
    
    vector<vector<char> > problem;
    for (int i = 0; i < 9; ++i) {
        vector<char> row;
        for (int j = 0; j < 9; ++j) {
            row.push_back(data[i][j]);
        }
        problem.push_back(row);

    }

    Solution sol;
    sol.solveSudoku(problem);

    
    return 0;
}
