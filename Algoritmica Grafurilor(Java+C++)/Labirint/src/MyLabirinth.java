import kotlin.Pair;
import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.util.Queue;
import java.util.Vector;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.LinkedList;

public class MyLabirinth extends JPanel {

    private Vector<Vector<Integer>> Matrix;
    private DrawLabirinth draw;
    private boolean checkRoads;
    private Vector<Pair<Integer, Integer>> Positions;

    public MyLabirinth() {
        try {
            BufferedReader file = new BufferedReader(new FileReader("src/Labirinth.txt"));
            String line = file.readLine();
            int indexvector = 0;
            Matrix = new Vector<>();
            while (line != null) {
                Matrix.add(new Vector<>());
                for (int index = 0; index < line.length(); index++)
                    Matrix.elementAt(indexvector).add(Character.getNumericValue(line.charAt(index)));
                indexvector++;
                line = file.readLine();
            }
            file.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        checkRoads = false;
        repaint();
    }

    private Pair<Integer, Integer> FindStart() {
        for (int index1 = 0; index1 < Matrix.size(); index1++)
            for (int index2 = 0; index2 < Matrix.elementAt(index1).size(); index2++)
                if (Matrix.elementAt(index1).elementAt(index2) == 2) {
                    return new Pair<>(index1, index2);
                }
        return null;
    }

    private void PBF() {
        Queue<Pair<Integer, Integer>> current_positions = new LinkedList<>();
        current_positions.add(FindStart());
        checkRoads = true;
        Positions = new Vector<>();
        Matrix.elementAt(current_positions.peek().getFirst()).set(current_positions.peek().getSecond(), 4);
        while (!current_positions.isEmpty()) {
            if (current_positions.peek().getFirst() + 1 < Matrix.size())
                if (Matrix.elementAt(current_positions.peek().getFirst() + 1).elementAt(current_positions.peek().getSecond()) == 1) {
                    Matrix.elementAt(current_positions.peek().getFirst() + 1).set(current_positions.peek().getSecond(), Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond()) + 1);
                    current_positions.add(new Pair<>(current_positions.peek().getFirst() + 1, current_positions.peek().getSecond()));
                } else if (Matrix.elementAt(current_positions.peek().getFirst() + 1).elementAt(current_positions.peek().getSecond()) == 3) {
                    Positions.add(new Pair<>(current_positions.peek().getFirst(), current_positions.peek().getSecond()));
                    Matrix.elementAt(current_positions.peek().getFirst() + 1).set(current_positions.peek().getSecond(), 0);
                }

            if (current_positions.peek().getSecond() + 1 < Matrix.elementAt(0).size())
                if (Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond() + 1) == 1) {
                    Matrix.elementAt(current_positions.peek().getFirst()).set(current_positions.peek().getSecond() + 1, Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond()) + 1);
                    current_positions.add(new Pair<>(current_positions.peek().getFirst(), current_positions.peek().getSecond() + 1));
                } else if (Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond() + 1) == 3) {
                    Positions.add(new Pair<>(current_positions.peek().getFirst(), current_positions.peek().getSecond()));
                    Matrix.elementAt(current_positions.peek().getFirst()).set(current_positions.peek().getSecond() + 1, 0);
                }

            if (current_positions.peek().getFirst() - 1 >= 0)
                if (Matrix.elementAt(current_positions.peek().getFirst() - 1).elementAt(current_positions.peek().getSecond()) == 1) {
                    Matrix.elementAt(current_positions.peek().getFirst() - 1).set(current_positions.peek().getSecond(), Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond()) + 1);
                    current_positions.add(new Pair<>(current_positions.peek().getFirst() - 1, current_positions.peek().getSecond()));

                } else if (Matrix.elementAt(current_positions.peek().getFirst() - 1).elementAt(current_positions.peek().getSecond()) == 3) {
                    Positions.add(new Pair<>(current_positions.peek().getFirst(), current_positions.peek().getSecond()));
                    Matrix.elementAt(current_positions.peek().getFirst() - 1).set(current_positions.peek().getSecond(), 0);
                }
            
            if (current_positions.peek().getSecond() - 1 >= 0)
                if (Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond() - 1) == 1) {
                    Matrix.elementAt(current_positions.peek().getFirst()).set(current_positions.peek().getSecond() - 1, Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond()) + 1);
                    current_positions.add(new Pair<>(current_positions.peek().getFirst(), current_positions.peek().getSecond() - 1));

                } else if (Matrix.elementAt(current_positions.peek().getFirst()).elementAt(current_positions.peek().getSecond() - 1) == 3) {
                    Positions.add(new Pair<>(current_positions.peek().getFirst(), current_positions.peek().getSecond()));
                    Matrix.elementAt(current_positions.peek().getFirst()).set(current_positions.peek().getSecond() - 1, 0);
                }
            current_positions.remove();
        }
        repaint();
    }

    public int GetNrOfLines() {
        return Matrix.size();
    }

    public int GetNrOfColumns() {
        return Matrix.elementAt(0).size();
    }

    protected void paintComponent(Graphics g) {
        if (!checkRoads) {
            draw = new DrawLabirinth(g, Matrix);
            PBF();
        } else
            for (int index = 0; index < Positions.size(); index++)
                draw.DrawRoad(g, Positions.elementAt(index).getFirst(), Positions.elementAt(index).getSecond(), Matrix);
    }
}
