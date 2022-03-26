package test;

import java.util.Stack;

public class SolutionSudoku {
    /**
     * 37.解数独 思路 用三张表分别标记行列以及小块内数字的种类，然后找出可能性最少的空尝试填上数字，再迭代尝试，如果失败回退上一个尝试的数字再继续往下尝试。通过函数嵌套的方式实现回退。
     */
    private static final class NinePalaceGrid {
        private final char[] numbers = new char[]{'1','2','3','4','5','6','7','8','9'};
        private final boolean[][] lines = new boolean[9][9];
        private final boolean[][] columns = new boolean[9][9];
        private final boolean[][][] blocks = new boolean[3][3][9];

        private void indexTrue(int line,int column,int number) {
            lines[line][number] = true;
            columns[column][number] = true;
            blocks[line/3][column/3][number] = true;
        }

        private void indexFalse(int line,int column,int number) {
            lines[line][number] = false;
            columns[column][number] = false;
            blocks[line/3][column/3][number] = false;
        }

        private boolean writeNumber(int line,int column,int number) {
            return !(lines[line][number] || columns[column][number] || blocks[line/3][column/3][number]);
        }

        private int[] leastLikely(char[][] board) {
            int[] index = new int[2];
            int min = 10;
            for (int i=0;i<board.length;i++) {
                for (int j=0;j<board[i].length;j++) {
                    if(board[i][j] == '.') {
                        int likelyNumber = likely(i,j);
                        if(likelyNumber < min) {
                            index[0] = i;
                            index[1] = j;
                            min = likelyNumber;
                        }
                    }
                }
            }
            return index;
        }

        private int likely(int x,int y) {
            int number=9;
            for (int i=0;i<9;i++) {
                if (lines[x][i] || columns[y][i] || blocks[x/3][y/3][i]) {
                    number--;
                }
            }
            return number;
        }

        public int statistics(char[][] board) {
            int number = 0;
            for (int i=0;i<board.length;i++) {
                for (int j=0;j<board[i].length;j++) {
                    if(board[i][j] >= 49 && board[i][j] <= 57) {
                        indexTrue(i,j,board[i][j]-49);
                    } else if(board[i][j] == '.') {
                        number++;
                    }
                }
            }
            return number;
        }

        public boolean solve(char[][] board,int number) {
            if(number == 0) {
                return true;
            }
            int[] index = leastLikely(board);
            int x = index[0];
            int y = index[1];
            for (int i=0;i<9;i++) {
                if(writeNumber(x,y,i)) {
                    indexTrue(x,y,i);
                    board[x][y] = numbers[i];
                    if(solve(board,number-1)) {
                        return true;
                    }
                    board[x][y] = '.';
                    indexFalse(x,y,i);
                }
            }
            return false;
        }

        public boolean solveStack(char[][] board, int number) {
            class Message {
                private int line;
                private int column;
                private int number;

                Message(int x,int y,int n) {
                    line = x;
                    column = y;
                    number = n;
                }
            }
            Stack<Message> stack = new Stack();
            for (;;) {
                if (number == 0) {
                    return true;
                }
                int[] index = leastLikely(board);
                int x = index[0];
                int y = index[1];

                int i = 0;
                for (;i<9;i++) {
                    if(writeNumber(x,y,i)) {
                        indexTrue(x,y,i);
                        board[x][y] = numbers[i];
                        stack.push(new Message(x,y,i));
                        number--;
                        break;
                    }
                }
                if (i == 9 && !stack.empty()) {
                    number++;
                    board[x][y] = '.';
                    Message pop = stack.pop();
                    indexFalse(pop.line,pop.column,pop.number);
                } else if (i == 9 && stack.empty()) {
                    return false;
                }
            }
        }
    }

    public static void main(String[] args) {
        char[][] d = new char[][] {
                {'5','3','.','.','7','.','.','.','.'},
                {'6','.','.','1','9','5','.','.','.'},
                {'.','9','8','.','.','.','.','6','.'},
                {'8','.','.','.','6','.','.','.','3'},
                {'4','.','.','8','.','3','.','.','1'},
                {'7','.','.','.','2','.','.','.','6'},
                {'.','6','.','.','.','.','2','8','.'},
                {'.','.','.','4','1','9','.','.','5'},
                {'.','.','.','.','8','.','.','7','9'}};

        NinePalaceGrid sudoku = new NinePalaceGrid();
        int statistics = sudoku.statistics(d);
        if(sudoku.solveStack(d,statistics)) {
            for (int i=0;i<d.length;i++) {
                for (int j=0;j<d[i].length;j++) {
                    System.out.print(d[i][j]);
                    if (j < 8) {
                        System.out.print("\t");
                    }
                }
                System.out.println();
            }
        }
    }
}
