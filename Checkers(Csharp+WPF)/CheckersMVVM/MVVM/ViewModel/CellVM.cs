using CheckersMVVM.Commands;
using CheckersMVVM.MVVM.Model;
using CheckersMVVM.Services;
using System.Windows.Input;
using static CheckersMVVM.MVVM.Model.Cell;

namespace CheckersMVVM.MVVM.ViewModel
{
    class CellVM : ObservableObject
    {
        GameBusinessLogic bl;
        public CellVM(int x, int y, PieceState piece, BackGroundColor backGround, GameBusinessLogic bl)
        {
            SimpleCell = new Cell(x, y, piece, backGround);
            this.bl = bl;
        }

        private Cell simpleCell;
        public Cell SimpleCell
        {
            get { return simpleCell; }
            set
            {
                simpleCell = value;
                NotifyPropertyChanged("SimpleCell");
            }
        }


        private ICommand clickCommand;
        public ICommand ClickCommand
        {
            get
            {
                clickCommand = new RelayCommand<Cell>(bl.ClickAction);
                  

                return clickCommand;
            }
        }

    }
}
