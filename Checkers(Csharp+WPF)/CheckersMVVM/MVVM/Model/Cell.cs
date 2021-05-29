using CheckersMVVM.Services;

namespace CheckersMVVM.MVVM.Model
{
    class Cell : ObservableObject
    {

        public Cell(int x, int y, PieceState piece, BackGroundColor backGround)
        {
            this.X = x;
            this.Y = y;
            this.Piece = piece;
            this.backGround = backGround;
            this.imagePath = PieceToString(this.piece);
            this.backGroundString =BackGroundToString(this.backGround);
            this.isClickable = false;
        }

        private int x;
        public int X
        {
            get { return x; }
            set
            {
                x = value;
                NotifyPropertyChanged("X");
            }
        }
        private int y;
        public int Y
        {
            get { return y; }
            set
            {
                y = value;
                NotifyPropertyChanged("Y");
            }
        }

        private bool isClickable;
        public bool IsClickable 
        {
            get
            {
                return isClickable;
            }
            set
            {
                isClickable = value;
                NotifyPropertyChanged("IsClickable");
            }
        }
        private PieceState piece;
        public PieceState Piece
        {
            get { return piece; }
            set
            {
                piece = value;
                imagePath = PieceToString(piece);
                NotifyPropertyChanged("Piece");
                NotifyPropertyChanged("ImagePath");
            }
        }

        private BackGroundColor backGround;
        public BackGroundColor BackGround
        {
            get
            {
                return backGround;
            }
            set
            {
                backGround = value;
                backGroundString = BackGroundToString(backGround);
                NotifyPropertyChanged("BackGround");
                NotifyPropertyChanged("BackGroundString");
            }
        }

        private string imagePath;
        public string ImagePath
        {
            get
            {
                return imagePath;
            }         

        }

        private string backGroundString;
        public string BackGroundString
        {
            get
            {
                return backGroundString;
            }          
        }

        public enum BackGroundColor
        {
            White,
            Brown,
            Selected,
            PossibleMove,
            PossibleJump
        }

        public enum PieceState
        {
            None,
            Red,
            Black,
            RedKing,
            BlackKing
        }

        public string PieceToString(PieceState piece)
        {
            switch (piece)
            {               
                case PieceState.Red: return "/CheckersMVVM;component/Images/red.png";
                case PieceState.Black:return "/CheckersMVVM;component/Images/black.png";                
                case PieceState.RedKing:return "/CheckersMVVM;component/Images/redKinged.png";
                case PieceState.BlackKing: return "/CheckersMVVM;component/Images/blackKinged.png";
                default:return null;
            }
        }

        public string BackGroundToString(BackGroundColor backGround)
        {
            switch(backGround)
            {
                case BackGroundColor.Brown:return "#FF7C4004";
                case BackGroundColor.White:return "WhiteSmoke";
                case BackGroundColor.Selected:return "Aqua";
                case BackGroundColor.PossibleMove:return "BurlyWood";
                case BackGroundColor.PossibleJump:return "PaleVioletRed";
                default:return null;
            }
        }       
    }
}
