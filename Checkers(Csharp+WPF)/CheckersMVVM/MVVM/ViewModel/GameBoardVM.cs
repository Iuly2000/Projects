using CheckersMVVM.Commands;
using CheckersMVVM.MVVM.Model;
using CheckersMVVM.Services;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Windows.Input;
using System.Windows;
using System.IO;
using System;

namespace CheckersMVVM.MVVM.ViewModel
{
    class GameBoardVM : ObservableObject
    {

        public GameBoardVM()
        {
            visibilityInGame = false;
            string[] lines = System.IO.File.ReadAllLines(Helper.Statistics);
            playersStatistics = new Tuple<int, int>(int.Parse(lines[0]), int.Parse(lines[1]));
            player1 = "Transparent";
            player2 = "Transparent";
        }

        private GameBusinessLogic bl;
        private string player1;
        public string Player1
        {
            get
            {
                return player1;
            }
            set
            {
                player1 = value;
                NotifyPropertyChanged("Player1");
            }
        }
        private string player2;
        public string Player2
        {
            get
            {
                return player2;
            }
            set
            {
                player2 = value;
                NotifyPropertyChanged("Player2");
            }
        }

        private bool multipleJumps;
        public bool MultipleJumps
        {
            get
            {
                return multipleJumps;
            }
            set
            {
                multipleJumps = value;
                if (multipleJumps)
                    stringMultipleJumps = "MultipleJumps:ON";
                else
                    stringMultipleJumps = "MultipleJumps:OFF";
                NotifyPropertyChanged("MultipleJumps");
                NotifyPropertyChanged("StringMultipleJumps");
            }
        }
        private string stringMultipleJumps;
        public string StringMultipleJumps
        {
            get
            {
                return stringMultipleJumps;
            }
        }

        private bool visibilityInGame;
        public bool VisibilityInGame
        {
            get
            {
                return visibilityInGame;
            }
            set
            {
                visibilityInGame = value;
                NotifyPropertyChanged("VisibilityInGame");
            }
        }
        private Tuple<int, int> playersStatistics;
        public Tuple<int, int> PlayersStatistics
        {
            get
            {
                return playersStatistics;
            }
            set
            {
                playersStatistics = value;
            }
        }
        private ObservableCollection<ObservableCollection<CellVM>> gameBoard;
        public ObservableCollection<ObservableCollection<CellVM>> GameBoard
        {
            get
            {
                return gameBoard;
            }
            set
            {
                gameBoard = value;
                NotifyPropertyChanged("GameBoard");
            }
        }

        private ICommand newGameCommand;
        public ICommand NewGameCommand
        {
            get
            {
                newGameCommand = new RelayCommand<object>(o =>
                {
                    Helper.gameBoard = this;
                    if (MessageBox.Show("Do you want multiple jumps on?", "Question", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.No)
                        MultipleJumps = false;
                    else
                        MultipleJumps = true;

                    ObservableCollection<ObservableCollection<Cell>> board = Helper.InitGameBoard(Helper.InitialState, true, multipleJumps);
                    bl = new GameBusinessLogic(board);
                    GameBoard = CellBoardToCellVMBoard(board);
                    bl.boardVM = this;
                    VisibilityInGame = true;
                });
                return newGameCommand;
            }
        }

        private ICommand saveGame;
        public ICommand SaveGame
        {
            get
            {
                saveGame = new RelayCommand<object>(o =>
                {
                    string filePath = Helper.SaveGameDialog();
                    if (filePath != "")
                        using (StreamWriter writer = new StreamWriter(filePath))
                        {
                            foreach (ObservableCollection<Cell> boardline in bl.cells)
                            {
                                string line = "";
                                foreach (Cell cell in boardline)
                                {
                                    line += Helper.StringToPiece(cell.Piece) + " ";
                                }
                                line = line.TrimEnd(' ');
                                writer.WriteLine(line);
                            }
                            if (Player1 == "#6600FFFF")
                                writer.WriteLine("1");
                            else
                                writer.WriteLine("2");
                            if (MultipleJumps)
                                writer.WriteLine("1");
                            else
                                writer.WriteLine("0");
                        }

                });
                return saveGame;
            }
        }

        private ICommand loadGame;
        public ICommand LoadGame
        {
            get
            {
                loadGame = new RelayCommand<object>(o =>
                {
                    Helper.gameBoard = this;
                    string loadedGame = Helper.LoadGameFileDialog();
                    if (loadedGame != "")
                    {
                        ObservableCollection<ObservableCollection<Cell>> board = Helper.InitGameBoard(loadedGame);
                        bl = new GameBusinessLogic(board);
                        GameBoard = CellBoardToCellVMBoard(board);

                        bl.boardVM = this;
                        VisibilityInGame = true;
                    }
                });
                return loadGame;
            }
        }


        private ICommand about;
        public ICommand About
        {
            get
            {
                about = new RelayCommand<object>(o =>
                  {
                      string[] info = System.IO.File.ReadAllLines(Helper.Info);
                      string infoShow = "";
                      foreach (string lines in info)
                          infoShow += lines + '\n';
                      MessageBox.Show(infoShow, "About", MessageBoxButton.OK, MessageBoxImage.Information);
                  });
                return about;
            }
        }

        private ICommand statistics;
        public ICommand Statistics
        {
            get
            {
                statistics = new RelayCommand<object>(o =>
                {
                    MessageBox.Show("Player1 won:" + playersStatistics.Item1 + " times.\nPlayer2 won:" + playersStatistics.Item2 + " times.", "Statistics", MessageBoxButton.OK, MessageBoxImage.Information);
                });
                return statistics;
            }
        }
        public ObservableCollection<ObservableCollection<CellVM>> CellBoardToCellVMBoard(ObservableCollection<ObservableCollection<Cell>> board)
        {
            ObservableCollection<ObservableCollection<CellVM>> result = new ObservableCollection<ObservableCollection<CellVM>>();
            for (int i = 0; i < board.Count; i++)
            {
                ObservableCollection<CellVM> line = new ObservableCollection<CellVM>();
                for (int j = 0; j < board[i].Count; j++)
                {
                    Cell c = board[i][j];
                    CellVM cellVM = new CellVM(c.X, c.Y, c.Piece, c.BackGround, bl);
                    cellVM.SimpleCell.IsClickable = c.IsClickable;
                    line.Add(cellVM);
                }
                result.Add(line);
            }
            return result;
        }

    }
}
