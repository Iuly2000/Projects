import javax.swing.*;
import java.io.IOException;

public class Graf
{	
	private static void initUI() throws IOException {
        JFrame f = new JFrame("Algoritmica Grafurilor");
        JButton sort=new JButton("TopologicSort");
        JButton connected=new JButton("CComponents");
        JButton strongconnected=new JButton("SCComponents");
        JButton reset=new JButton("ResetGraph");
        //sa se inchida aplicatia atunci cand inchid fereastra
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //imi creez ob MyPanel
        sort.setBounds(20,100,150,30);
        connected.setBounds(20,160,150,30);
        strongconnected.setBounds(20,220,150,30);
        reset.setBounds(350,20,120,30);
        f.add(sort);
        f.add(connected);
        f.add(strongconnected);
        f.add(reset);
        sort.setVisible(true);
        connected.setVisible(true);
        strongconnected.setVisible(true);
        reset.setVisible(true);
        //setez dimensiunea ferestrei
        f.setSize(850, 500);
        f.add(new MyPanel(sort,connected,strongconnected,reset));
        //fac fereastra vizibila
        f.setVisible(true);
    }

	public static void main(String[] args)
	{
		//pornesc firul de executie grafic
		//fie prin implementarea interfetei Runnable, fie printr-un ob al clasei Thread
		SwingUtilities.invokeLater(new Runnable() //new Thread()
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
