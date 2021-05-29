import javax.swing.SwingUtilities;
import javax.swing.*;

public class Main {
    private static void initUI() {
        JFrame f=new JFrame("Labirinth");
        MyLabirinth labirinth=new MyLabirinth();
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.add(labirinth);
        f.setSize(labirinth.GetNrOfColumns()*70+17,labirinth.GetNrOfLines()*70+40);
        f.setResizable(false);
        f.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Main::initUI);
    }
}
