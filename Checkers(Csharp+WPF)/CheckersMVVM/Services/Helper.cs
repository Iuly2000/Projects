using CheckersMVVM.MVVM.Model;
using CheckersMVVM.MVVM.ViewModel;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CheckersMVVM.Services
{
    class Helper
    {
        public static Cell CurrentCell { get; set; }
        public static Cell PreviousCell { get; set; }
        public static bool GameIsFinished { get; set; }
        public static GameBoardVM gameBoard;
        public static ObservableCollection<ObservableCollection<Cell>> InitGameBoard(string file, bool newGame = false, bool multipleJumps = false)
        {
            GameIsFinished = false;
            string[] lines = System.IO.File.ReadAllLines(file);

            ObservableCollection<ObservableCollection<Cell>> board = new ObservableCollection<ObservableCollection<Cell>>();
            for (int index1 = 0; index1 < lines.Count() - 2; ++index1)
            {
                ObservableCollection<Cell> boardLine = new ObservableCollection<Cell>();
                string[] pieces = lines[index1].Split(' ');
                for (int index2 = 0; index2 < pieces.Count(); ++index2)
                {
                    if (index1 % 2 == 1)
                        if (index2 % 2 == 0)
                            boardLine.Add(new Cell(index1, index2, StringToPiece(pieces[index2]), Cell.BackGroundColor.Brown));
                        else
                            boardLine.Add(new Cell(index1, index2, StringToPiece(pieces[index2]), Cell.BackGroundColor.White));
                    else
                        if (index2 % 2 == 0)
                        boardLine.Add(new Cell(index1, index2, StringToPiece(pieces[index2]), Cell.BackGroundColor.White));
                    else
                        boardLine.Add(new Cell(index1, index2, StringToPiece(pieces[index2]), Cell.BackGroundColor.Brown));
                }


                board.Add(boardLine);
            };

            if (lines[lines.Count() - 2] == "1")
            {
                gameBoard.Player1 = "#6600FFFF";
                gameBoard.Player2 = "Transparent";
            }
            else if (lines[lines.Count() - 2] == "2")
            {
                gameBoard.Player1 = "Transparent";
                gameBoard.Player2 = "#6600FFFF";
            }

            if (newGame)
                gameBoard.MultipleJumps = multipleJumps;
            else
            {
                if (lines[lines.Count() - 1] == "1")
                    gameBoard.MultipleJumps = true;
                else
                    gameBoard.MultipleJumps = false;
            }

            ClickablePlayerPieces(board);

            return board;
        }

        public static void ClickablePlayerPieces(ObservableCollection<ObservableCollection<Cell>> board)
        {
            foreach (ObservableCollection<Cell> lineBoard in board)
                foreach (Cell cell in lineBoard)
                {
                    if (gameBoard.Player1 == "#6600FFFF" && (cell.Piece == Cell.PieceState.Red || cell.Piece == Cell.PieceState.RedKing))
                        cell.IsClickable = true;
                    else
                        if (gameBoard.Player2 == "#6600FFFF" && (cell.Piece == Cell.PieceState.Black || cell.Piece == Cell.PieceState.BlackKing))
                        cell.IsClickable = true;
                    else
                        cell.IsClickable = false;
                }

        }

        public static void UnclickablePieces(ObservableCollection<ObservableCollection<Cell>> board)
        {
            foreach (ObservableCollection<Cell> lineBoard in board)
                foreach (Cell cell in lineBoard)
                    cell.IsClickable = false;
        }

        private static Cell.PieceState StringToPiece(string str)
        {
            switch (str)
            {
                case "1": return Cell.PieceState.Red;
                case "2": return Cell.PieceState.Black;
                case "3": return Cell.PieceState.RedKing;
                case "4": return Cell.PieceState.BlackKing;
                default: return Cell.PieceState.None;
            }
        }

        public static string StringToPiece(Cell.PieceState piece)
        {
            switch (piece)
            {
                case Cell.PieceState.Red: return "1";
                case Cell.PieceState.Black: return "2";
                case Cell.PieceState.RedKing: return "3";
                case Cell.PieceState.BlackKing: return "4";
                default: return "0";
            }
        }

        public static string LoadGameFileDialog()
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.ShowReadOnly = true;
            fileDialog.Multiselect = true;
            fileDialog.Filter = "TXT files|*.txt|All files|*.*";
            fileDialog.DefaultExt = ".txt";
            Nullable<bool> OKdialog = fileDialog.ShowDialog();

            if (OKdialog == true)
            {
                string sFileNames = "";
                foreach (string sFileName in fileDialog.FileNames)
                {
                    sFileNames += ";" + sFileName;
                }
                sFileNames = sFileNames.Substring(1);
                return sFileNames;
            }

            return "";
        }

        public static string SaveGameDialog()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "TXT files|*.txt|All files|*.*";
            saveFileDialog.DefaultExt = ".txt";
            if (saveFileDialog.ShowDialog() == true)
            {
                string sFileNames = "";
                foreach (string sFileName in saveFileDialog.FileNames)
                {
                    sFileNames += ";" + sFileName;
                }
                sFileNames = sFileNames.Substring(1);
                return sFileNames;
            }
            return "";
        }

        public static string InitialState
        {
            get { return @"..\..\Resources\InitialState\InitialState.txt"; }
        }
        public static string Info
        {
            get { return @"..\..\Resources\About\Info.txt"; }
        }
        public static string Statistics
        {
            get { return @"..\..\Resources\Statistics\PlayersStatistics.txt"; }
        }



    }


}

