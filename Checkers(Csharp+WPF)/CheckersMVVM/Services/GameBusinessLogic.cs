using CheckersMVVM.MVVM.Model;
using CheckersMVVM.MVVM.ViewModel;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Windows;
using System.IO;

namespace CheckersMVVM.Services
{
    class GameBusinessLogic
    {
        public ObservableCollection<ObservableCollection<Cell>> cells { get; set; }
        public GameBoardVM boardVM;
        public GameBusinessLogic(ObservableCollection<ObservableCollection<Cell>> cells)
        {
            this.cells = cells;
        }
        private void UnselectCells()
        {
            foreach (ObservableCollection<Cell> lineCells in cells)
                foreach (Cell cell in lineCells)
                {
                    if (cell.BackGround == Cell.BackGroundColor.PossibleMove)
                    {
                        cell.IsClickable = false;
                        cell.BackGround = Cell.BackGroundColor.Brown;
                    }
                    if (cell.BackGround == Cell.BackGroundColor.PossibleJump)
                    {
                        cell.IsClickable = false;
                        cell.BackGround = Cell.BackGroundColor.Brown;
                    }
                    if (cell.BackGround == Cell.BackGroundColor.Selected)
                        cell.BackGround = Cell.BackGroundColor.Brown;
                }
        }
        private ObservableCollection<Cell> IsPossibleMovesUp(Cell currentCell)
        {
            ObservableCollection<Cell> movesUp = new ObservableCollection<Cell>();
            if (currentCell.X > 0 && currentCell.Y > 0 && cells[currentCell.X - 1][currentCell.Y - 1].Piece == Cell.PieceState.None)
                movesUp.Add(cells[currentCell.X - 1][currentCell.Y - 1]);
            if (currentCell.X > 0 && currentCell.Y < 7 && cells[currentCell.X - 1][currentCell.Y + 1].Piece == Cell.PieceState.None)
                movesUp.Add(cells[currentCell.X - 1][currentCell.Y + 1]);

            if (movesUp.Count == 0)
                return null;
            return movesUp;
        }
        private ObservableCollection<Cell> IsPossibleMovesDown(Cell currentCell)
        {
            ObservableCollection<Cell> movesDown = new ObservableCollection<Cell>();
            if (currentCell.X < 7 && currentCell.Y > 0 && cells[currentCell.X + 1][currentCell.Y - 1].Piece == Cell.PieceState.None)
                movesDown.Add(cells[currentCell.X + 1][currentCell.Y - 1]);
            if (currentCell.X < 7 && currentCell.Y < 7 && cells[currentCell.X + 1][currentCell.Y + 1].Piece == Cell.PieceState.None)
                movesDown.Add(cells[currentCell.X + 1][currentCell.Y + 1]);

            if (movesDown.Count == 0)
                return null;
            return movesDown;
        }
        private ObservableCollection<Cell> IsPossibleJumpsUp(Cell currentCell)
        {
            Cell.PieceState enemy1 = Cell.PieceState.None;
            Cell.PieceState enemy2 = Cell.PieceState.None;
            switch (currentCell.Piece)
            {
                case Cell.PieceState.Red:
                    {
                        enemy1 = Cell.PieceState.Black;
                        enemy2 = Cell.PieceState.BlackKing;
                    }
                    break;
                case Cell.PieceState.RedKing:
                    {
                        enemy1 = Cell.PieceState.Black;
                        enemy2 = Cell.PieceState.BlackKing;
                    }
                    break;
                case Cell.PieceState.BlackKing:
                    {
                        enemy1 = Cell.PieceState.Red;
                        enemy2 = Cell.PieceState.RedKing;
                    }
                    break;
                default: break;
            }

            ObservableCollection<Cell> jumpsUp = new ObservableCollection<Cell>();
            if (enemy1 != Cell.PieceState.None || enemy2 != Cell.PieceState.None)
            {
                if (currentCell.X > 1 && currentCell.Y > 1 &&
                    cells[currentCell.X - 2][currentCell.Y - 2].Piece == Cell.PieceState.None &&
                    (cells[currentCell.X - 1][currentCell.Y - 1].Piece == enemy1 ||
                    cells[currentCell.X - 1][currentCell.Y - 1].Piece == enemy2))
                    jumpsUp.Add(cells[currentCell.X - 2][currentCell.Y - 2]);

                if (currentCell.X > 1 && currentCell.Y < 6
                    && cells[currentCell.X - 2][currentCell.Y + 2].Piece == Cell.PieceState.None &&
                   (cells[currentCell.X - 1][currentCell.Y + 1].Piece == enemy1 ||
                   cells[currentCell.X - 1][currentCell.Y + 1].Piece == enemy2))
                    jumpsUp.Add(cells[currentCell.X - 2][currentCell.Y + 2]);

            }

            if (jumpsUp.Count == 0)
                return null;
            return jumpsUp;
        }
        private ObservableCollection<Cell> IsPossibleJumpsDown(Cell currentCell)
        {
            Cell.PieceState enemy1 = Cell.PieceState.None;
            Cell.PieceState enemy2 = Cell.PieceState.None;
            switch (currentCell.Piece)
            {
                case Cell.PieceState.Black:
                    {
                        enemy1 = Cell.PieceState.Red;
                        enemy2 = Cell.PieceState.RedKing;
                    }
                    break;
                case Cell.PieceState.RedKing:
                    {
                        enemy1 = Cell.PieceState.Black;
                        enemy2 = Cell.PieceState.BlackKing;
                    }
                    break;
                case Cell.PieceState.BlackKing:
                    {
                        enemy1 = Cell.PieceState.Red;
                        enemy2 = Cell.PieceState.RedKing;
                    }
                    break;
                default: break;
            }

            ObservableCollection<Cell> jumpsDown = new ObservableCollection<Cell>();
            if (enemy1 != Cell.PieceState.None || enemy2 != Cell.PieceState.None)
            {
                if (currentCell.X < 6 && currentCell.Y > 1 &&
                  cells[currentCell.X + 2][currentCell.Y - 2].Piece == Cell.PieceState.None &&
                  (cells[currentCell.X + 1][currentCell.Y - 1].Piece == enemy1 ||
                  cells[currentCell.X + 1][currentCell.Y - 1].Piece == enemy2))
                    jumpsDown.Add(cells[currentCell.X + 2][currentCell.Y - 2]);

                if (currentCell.X < 6 && currentCell.Y < 6
                    && cells[currentCell.X + 2][currentCell.Y + 2].Piece == Cell.PieceState.None &&
                   (cells[currentCell.X + 1][currentCell.Y + 1].Piece == enemy1 ||
                   cells[currentCell.X + 1][currentCell.Y + 1].Piece == enemy2))
                    jumpsDown.Add(cells[currentCell.X + 2][currentCell.Y + 2]);
            }

            if (jumpsDown.Count == 0)
                return null;
            return jumpsDown;
        }
        private void ShowMovesOrJumps(ObservableCollection<Cell> selectedCells, Cell.BackGroundColor color)
        {
            foreach (Cell cellPosition in selectedCells)
            {
                cells[cellPosition.X][cellPosition.Y].BackGround = color;
                cells[cellPosition.X][cellPosition.Y].IsClickable = true;
            }

        }
        private void ExecuteJump(Cell currentCell, int player)
        {
            Cell moveCell = cells[currentCell.X][currentCell.Y];
            Cell pieceCell = cells[Helper.PreviousCell.X][Helper.PreviousCell.Y];
            Cell attackedCell = cells[(currentCell.X + Helper.PreviousCell.X) / 2][(currentCell.Y + Helper.PreviousCell.Y) / 2];
            moveCell.BackGround = Cell.BackGroundColor.Brown;

            if (player == 1)
            {
                if (moveCell.X == 0)
                    moveCell.Piece = Cell.PieceState.RedKing;
                else
                    moveCell.Piece = pieceCell.Piece;
            }
            else
            {
                if (moveCell.X == 7)
                    moveCell.Piece = Cell.PieceState.BlackKing;
                else
                    moveCell.Piece = pieceCell.Piece;
            }

            moveCell.IsClickable = true;
            attackedCell.Piece = Cell.PieceState.None;
            pieceCell.IsClickable = false;
            pieceCell.Piece = Cell.PieceState.None;
            Helper.PreviousCell = null;
        }
        private void ExecuteMove(Cell currentCell, int player)
        {
            Cell moveCell = cells[currentCell.X][currentCell.Y];
            Cell pieceCell = cells[Helper.PreviousCell.X][Helper.PreviousCell.Y];
            moveCell.BackGround = Cell.BackGroundColor.Brown;

            if (player == 1)
            {
                if (moveCell.X == 0)
                    moveCell.Piece = Cell.PieceState.RedKing;
                else
                    moveCell.Piece = pieceCell.Piece;
            }
            else
            {
                if (moveCell.X == 7)
                    moveCell.Piece = Cell.PieceState.BlackKing;
                else
                    moveCell.Piece = pieceCell.Piece;
            }

            moveCell.IsClickable = true;
            pieceCell.IsClickable = false;
            pieceCell.Piece = Cell.PieceState.None;
            Helper.PreviousCell = null;
        }
        private void ShowKingMoves(ObservableCollection<Cell> movesUp, ObservableCollection<Cell> movesDown, ObservableCollection<Cell> jumpsUp, ObservableCollection<Cell> jumpsDown)
        {
            if (jumpsUp != null)
                ShowMovesOrJumps(jumpsUp, Cell.BackGroundColor.PossibleJump);
            if (jumpsDown != null)
                ShowMovesOrJumps(jumpsDown, Cell.BackGroundColor.PossibleJump);

            if (jumpsUp == null && jumpsDown == null)
            {
                if (movesUp != null)
                    ShowMovesOrJumps(movesUp, Cell.BackGroundColor.PossibleMove);
                if (movesDown != null)
                    ShowMovesOrJumps(movesDown, Cell.BackGroundColor.PossibleMove);
            }
        }

        private void ShowRedMoves(ObservableCollection<Cell> jumpsUp, ObservableCollection<Cell> movesUp)
        {
            if (jumpsUp != null)
                ShowMovesOrJumps(jumpsUp, Cell.BackGroundColor.PossibleJump);
            else
            {
                if (movesUp != null)
                    ShowMovesOrJumps(movesUp, Cell.BackGroundColor.PossibleMove);
            }
        }
        private void ShowBlackMoves(ObservableCollection<Cell> jumpsDown, ObservableCollection<Cell> movesDown)
        {
            if (jumpsDown != null)
                ShowMovesOrJumps(jumpsDown, Cell.BackGroundColor.PossibleJump);
            else
            {
                if (movesDown != null)
                    ShowMovesOrJumps(movesDown, Cell.BackGroundColor.PossibleMove);
            }
        }

        private bool PossibleMultipleJumpRed(Cell aux, ObservableCollection<Cell> jumpsUp)
        {
            jumpsUp = IsPossibleJumpsUp(aux);
            if (jumpsUp != null)
            {
                Helper.UnclickablePieces(cells);
                ShowMovesOrJumps(jumpsUp, Cell.BackGroundColor.PossibleJump);
                aux.IsClickable = true;
                aux.BackGround = Cell.BackGroundColor.Selected;
                return true;
            }
            return false;
        }

        private bool PossibleMultipleJumpKing(Cell aux, ObservableCollection<Cell> jumpsUp, ObservableCollection<Cell> jumpsDown)
        {
            jumpsUp = IsPossibleJumpsUp(aux);
            jumpsDown = IsPossibleJumpsDown(aux);
            if (jumpsUp != null || jumpsDown != null)
            {
                Helper.UnclickablePieces(cells);
                if (jumpsUp != null)
                    ShowMovesOrJumps(jumpsUp, Cell.BackGroundColor.PossibleJump);
                if (jumpsDown != null)
                    ShowMovesOrJumps(jumpsDown, Cell.BackGroundColor.PossibleJump);
                aux.IsClickable = true;
                aux.BackGround = Cell.BackGroundColor.Selected;
                return true;
            }
            return false;
        }

        private bool PossibleMultipleJumpBlack(Cell aux, ObservableCollection<Cell> jumpsDown)
        {
            jumpsDown = IsPossibleJumpsDown(aux);
            if (jumpsDown != null)
            {
                Helper.UnclickablePieces(cells);
                ShowMovesOrJumps(jumpsDown, Cell.BackGroundColor.PossibleJump);
                aux.IsClickable = true;
                aux.BackGround = Cell.BackGroundColor.Selected;
                return true;
            }
            return false;
        }

        private void UpdateWinner(int player)
        {
            if (player == 1)
            {
                MessageBox.Show("Player1 Won!", "Winner", MessageBoxButton.OK, MessageBoxImage.Warning);
                boardVM.PlayersStatistics = new System.Tuple<int, int>(boardVM.PlayersStatistics.Item1 + 1, boardVM.PlayersStatistics.Item2);
            }
            else
            {
                MessageBox.Show("Player2 Won!", "Winner", MessageBoxButton.OK, MessageBoxImage.Warning);
                boardVM.PlayersStatistics = new System.Tuple<int, int>(boardVM.PlayersStatistics.Item1, boardVM.PlayersStatistics.Item2 + 1);
            }

            using (StreamWriter writer = new StreamWriter(Helper.Statistics))
            {
                writer.WriteLine(boardVM.PlayersStatistics.Item1.ToString());
                writer.WriteLine(boardVM.PlayersStatistics.Item2.ToString());
            }
            boardVM.VisibilityInGame = false;
        }

        private void SwitchPlayer(int player)
        {
            if (player == 1)
            {
                boardVM.Player1 = "Transparent";
                boardVM.Player2 = "#6600FFFF";
            }
            else
            {
                boardVM.Player1 = "#6600FFFF";
                boardVM.Player2 = "Transparent";
            }

            Helper.ClickablePlayerPieces(cells);
            if (GameIsFinished())
            {
                Helper.GameIsFinished = true;
                Helper.UnclickablePieces(cells);
            }
        }
        private void RunGamePlayer1(Cell currentCell)
        {
            ObservableCollection<Cell> movesUp, movesDown, jumpsUp, jumpsDown = new ObservableCollection<Cell>();
            movesUp = IsPossibleMovesUp(currentCell);
            movesDown = IsPossibleMovesDown(currentCell);
            jumpsUp = IsPossibleJumpsUp(currentCell);
            jumpsDown = IsPossibleJumpsDown(currentCell);
            bool moveOrJumpHappened = false;

            switch (currentCell.Piece)
            {
                case Cell.PieceState.Red: ShowRedMoves(jumpsUp, movesUp); break;
                case Cell.PieceState.RedKing: ShowKingMoves(movesUp, movesDown, jumpsUp, jumpsDown); break;
                default: break;
            }

            switch (currentCell.BackGround)
            {
                case Cell.BackGroundColor.PossibleMove:
                    {
                        ExecuteMove(currentCell, 1);
                        moveOrJumpHappened = true;
                    }
                    break;

                case Cell.BackGroundColor.PossibleJump:
                    {
                        ExecuteJump(currentCell, 1);
                        if (!boardVM.MultipleJumps)
                            moveOrJumpHappened = true;
                        else
                        {
                            Cell aux = cells[currentCell.X][currentCell.Y];
                            switch (aux.Piece)
                            {
                                case Cell.PieceState.Red: if (!PossibleMultipleJumpRed(aux, jumpsUp)) moveOrJumpHappened = true; break;
                                case Cell.PieceState.RedKing: if (!PossibleMultipleJumpKing(aux, jumpsUp, jumpsDown)) moveOrJumpHappened = true; break;
                            }
                        }
                    }
                    break;
                default: break;
            }

            if (!moveOrJumpHappened)
                Helper.PreviousCell = currentCell;
            else
                SwitchPlayer(1);

            boardVM.GameBoard = boardVM.CellBoardToCellVMBoard(cells);
            if (Helper.GameIsFinished)
                UpdateWinner(1);
        }
        private void RunGamePlayer2(Cell currentCell)
        {
            bool moveOrJumpHappened = false;
            ObservableCollection<Cell> movesUp, movesDown, jumpsUp, jumpsDown = new ObservableCollection<Cell>();
            movesUp = IsPossibleMovesUp(currentCell);
            movesDown = IsPossibleMovesDown(currentCell);
            jumpsUp = IsPossibleJumpsUp(currentCell);
            jumpsDown = IsPossibleJumpsDown(currentCell);

            switch (currentCell.Piece)
            {
                case Cell.PieceState.Black: ShowBlackMoves(jumpsDown, movesDown); break;
                case Cell.PieceState.BlackKing: ShowKingMoves(movesUp, movesDown, jumpsUp, jumpsDown); break;
                default: break;
            }

            switch (currentCell.BackGround)
            {
                case Cell.BackGroundColor.PossibleMove:
                    {
                        ExecuteMove(currentCell, 2);
                        moveOrJumpHappened = true;
                    }
                    break;

                case Cell.BackGroundColor.PossibleJump:
                    {
                        ExecuteJump(currentCell, 2);
                        if (!boardVM.MultipleJumps)
                            moveOrJumpHappened = true;
                        else
                        {
                            Cell aux = cells[currentCell.X][currentCell.Y];
                            switch (aux.Piece)
                            {
                                case Cell.PieceState.Black: if (!PossibleMultipleJumpBlack(aux, jumpsDown)) moveOrJumpHappened = true; break;
                                case Cell.PieceState.BlackKing: if (!PossibleMultipleJumpKing(aux, jumpsUp, jumpsDown)) moveOrJumpHappened = true; break;
                            }
                        }
                    }
                    break;
                default: break;
            }

            if (!moveOrJumpHappened)
                Helper.PreviousCell = currentCell;
            else
                SwitchPlayer(2);

            boardVM.GameBoard = boardVM.CellBoardToCellVMBoard(cells);
            if (Helper.GameIsFinished)
                UpdateWinner(2);
        }
        private bool GameIsFinished()
        {
            foreach (ObservableCollection<Cell> cellLine in cells)
                foreach (Cell cell in cellLine)
                    if (cell.IsClickable)
                        switch (cell.Piece)
                        {
                            case Cell.PieceState.Red:
                                {
                                    if (IsPossibleJumpsUp(cell) != null || IsPossibleMovesUp(cell) != null)
                                        return false;
                                }
                                break;
                            case Cell.PieceState.Black:
                                {
                                    if (IsPossibleJumpsDown(cell) != null || IsPossibleMovesDown(cell) != null)
                                        return false;
                                }
                                break;
                            default:
                                {
                                    if (IsPossibleJumpsDown(cell) != null || IsPossibleJumpsUp(cell) != null ||
                                        IsPossibleMovesDown(cell) != null || IsPossibleMovesUp(cell) != null)
                                        return false;
                                }
                                break;
                        }
            return true;
        }
        public void ClickAction(Cell obj)
        {
            Helper.CurrentCell = obj;
            if (Helper.PreviousCell != null && Helper.CurrentCell.X == Helper.PreviousCell.X && Helper.CurrentCell.Y == Helper.PreviousCell.Y)
            {
                Helper.PreviousCell = null;
                UnselectCells();
                boardVM.GameBoard = boardVM.CellBoardToCellVMBoard(cells);
            }
            else
            {
                Cell cell = cells[Helper.CurrentCell.X][Helper.CurrentCell.Y];
                Cell.BackGroundColor bg = cell.BackGround;
                UnselectCells();
                cell.BackGround = bg;
                if (cell.Piece != Cell.PieceState.None)
                    cell.BackGround = Cell.BackGroundColor.Selected;
                Helper.CurrentCell.BackGround = cell.BackGround;
                if (boardVM.Player1 == "#6600FFFF")
                    RunGamePlayer1(Helper.CurrentCell);
                else
                    RunGamePlayer2(Helper.CurrentCell);
            }
        }
    }
}
