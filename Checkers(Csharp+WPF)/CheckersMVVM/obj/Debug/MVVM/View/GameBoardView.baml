   M S B A M L   `   `   `  ����G  CCheckersMVVM, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullI)clr-namespace:CheckersMVVM.MVVM.ViewModelCheckersMVVM.MVVM.ViewModel  5   	   +clr-namespace:CheckersMVVMCheckersMVVM  5   	   *    $CheckersMVVM.MVVM.View.GameBoardView   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   ?	viewModel)clr-namespace:CheckersMVVM.MVVM.ViewModel     5   	   ,localclr-namespace:CheckersMVVM     5   	   $	��665��5   	   $	��770��6     � 
ResizeMode$  NoResize=�5	   	    � WindowStartupLocation$ CenterScreen=�5
   	    � Title$ Checkers��5   	    � Icon$1 +pack://application:,,,/Images/GameIcon.jfif��5   	    � 	Resources 5         	BoolToVis��%   &	        �� 5   
   6'   5       � DataContext 5      -  'CheckersMVVM.MVVM.ViewModel.GameBoardVM  5   
   .��5      �� ���	#FFAAA7A8._�5   
   �  � ColumnDefinitions 5      �� 5      $	��200 �6#   �� 5       � RowDefinitions 5      �� 5      $��75 �6    �� 5       .+�5#      �� $��0��6   $��0��5$      
���   �$��2q�5&      ._�5'      �� $��Checkers��5(      $��45(�5)      
�������$��Center=�5+      $��Center=�5,      5-      5.      �� 50      $��1��6   $��0��51      
���   �$��2q�53      55      �� 56      $��1��6   $��0��57      
���   �$��2q�59      ._�5:      �� -   5        $��player1Label��5;      $��Player1��5<      $
��Left=�5=      $��Center=�5>      $��35(�5?      $��	110,0,0,0q�5@      
���  ��y�5A      �� *VisibilityInGame+ �� 	Converter# [  ��5B      �� *	Player1+	 J� Effect	 5D      3  -System.Windows.Media.Effects.DropShadowEffect  5E      5G      5H      �� 5J      -   5        $��player2Label��5L      $��1��5J      $��0��5K      $��Player2��5M      $��Center=�5N      $��Center=�5O      $��35(�5P      $��	140,0,0,0q�5Q      
���   �y�5R      �� *VisibilityInGame+# [  ��5S      �� *	Player2+	 5U        5V      5X      �� 5Z      $��1��6   $��0��5[      
���   �$��2q�5]      
���   �._�5_      �� .+�5a      �� -   5        
 ��Name$
 newGame��5a      $��New Game��5b      $��50��5c      
����� �$��22(�5e        MenuButtonTheme#��[ 5f      ��5g      �� *NewGameCommand+�� 5h      -   5        $

 save��5h      $
��Save��5i      $��50��5j      
����� �$��22(�5l      #��[ 5o      {�5m      �� *VisibilityInGame+��5n      �� *
SaveGame+5o      �� 5q      -   5        $
 loadGame��5q      $��	Load Game��5r      $��50��5s      
����� �$��22(�5u      #��[ 5w      ��5v      �� *
LoadGame+5w      �� 5y      -   5        $
 
statistics��5y      $��
Statistics��5z      $��50��5{      
����� �$��22(�5}      #��[ 5      ��5~      �� *
Statistics+5      �� 5�      -   5        $
 about��5�      $��About��5�      $��50��5�      
����� �$��22(�5�      #��[ 5�      ��5�      �� *About+5�      �� 5�      -   5        $
 multipleJumps��5�      $��50��5�      
����� �$��22(�5�       J� IsHitTestVisible .  #��[ 5�      ��5�      �� *StringMultipleJumps+y�5�      �� *VisibilityInGame+# [  5�      5�      5�      �� 5�      $��1��6   $��1��5�      
���   �$��2q�5�      ._�5�      �� -	   5        $
��grid��5�      $��	10 10 0 0q�5�      ��5�      �� *	GameBoard+��5�      �� 5�      .R�5�      �� ��6+   �� ��5�   "   �� 5�   &   .R�5�   *   ��  �� Orientation$ 
Horizontal=�65   5�   '   ��5�   "   �� 5�   &   .R�5�   *   �� $��66��61   $��66��6<   $��2q�6H   ���#000000._�5�   .   �� ��65   �� *ClickCommand+��6V   �� *
SimpleCell+��6   �� *SimpleCell.BackGroundString+ 6�   �� *SimpleCell.IsClickable+��5�   2   �� 5�   6   $
��Fill=�6}   ��6<   �� *SimpleCell.ImagePath+ �� TargetNullValue Z� 6}   5�   /   5�   +   5�   '   5�      5�      5�      5�      5�      5�      5�      