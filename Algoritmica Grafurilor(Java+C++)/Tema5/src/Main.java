import javax.swing.*;
import java.io.IOException;

public class Main {
    private static void initUI() throws IOException {
            JFrame frame=new JFrame("Harta Luxembourg");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(600, 735);
        frame.add(new MyPanel(frame.getWidth(),frame.getHeight()));
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(new Runnable()
        {
            public void run()
            {

                try {
                    initUI();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
