import java.awt.Color;
import java.awt.Graphics;
import java.util.Vector;

public class DrawLabirinth {

    public DrawLabirinth(Graphics g, Vector<Vector<Integer>> Matrix) {
        for (int index1 = 0; index1 < Matrix.size(); index1++)
            for (int index2 = 0; index2 < Matrix.elementAt(index1).size(); index2++)
                if (Matrix.elementAt(index1).elementAt(index2) == 0) {
                    g.setColor(Color.BLACK);
                    g.fillRect(70 * index2, 70* index1, 70, 70);
                    g.setColor(Color.BLACK);
                    g.drawRect(70 * index2, 70* index1, 70, 70);
                } else if (Matrix.elementAt(index1).elementAt(index2) == 1) {
                    g.setColor(Color.WHITE);
                    g.fillRect(70 * index2, 70* index1, 70, 70);
                    g.setColor(Color.BLACK);
                    g.drawRect(70 * index2, 70* index1, 70, 70);
                } else if (Matrix.elementAt(index1).elementAt(index2) == 3) {
                    g.setColor(Color.RED);
                    g.fillRect(70 * index2, 70* index1, 70, 70);
                    g.setColor(Color.BLACK);
                    g.drawRect(70 * index2, 70* index1, 70, 70);
                } else if (Matrix.elementAt(index1).elementAt(index2) == 2) {
                    g.setColor(Color.BLUE);
                    g.fillRect(70 * index2, 70* index1, 70, 70);
                    g.setColor(Color.BLACK);
                    g.drawRect(70 * index2, 70* index1, 70, 70);
                }

    }

    void DrawRoad(Graphics g, Integer index1, Integer index2, Vector<Vector<Integer>> Matrix) {
        Integer currentPoint = Matrix.elementAt(index1).elementAt(index2);
        boolean check;
        while (currentPoint != 4) {
            g.setColor(Color.GREEN);
            g.fillRect(70 * index2, 70* index1, 70, 70);
            g.setColor(Color.BLACK);
            g.drawRect(70 * index2, 70* index1, 70, 70);
            check=false;
            if(index1 - 1>=0)
            if (Matrix.elementAt(index1 - 1).elementAt(index2) == Matrix.elementAt(index1).elementAt(index2) - 1) {
                currentPoint = Matrix.elementAt(index1 - 1).elementAt(index2);
                index1--;
                check=true;
            }
                if(index2+1<Matrix.elementAt(0).size()&&!check)
                if (Matrix.elementAt(index1).elementAt(index2 + 1) == Matrix.elementAt(index1).elementAt(index2) - 1) {
                currentPoint = Matrix.elementAt(index1).elementAt(index2 + 1);
                index2++;
                check=true;
            }
                if(index1+1<Matrix.size()&&!check)
                if (Matrix.elementAt(index1 + 1).elementAt(index2) == Matrix.elementAt(index1).elementAt(index2) - 1) {
                currentPoint = Matrix.elementAt(index1 + 1).elementAt(index2);
                index1++;
                check=true;
            }
                if(index2-1>=0&&!check)
                if (Matrix.elementAt(index1).elementAt(index2 - 1) == Matrix.elementAt(index1).elementAt(index2) - 1) {
                currentPoint = Matrix.elementAt(index1).elementAt(index2 - 1);
                index2--;
            }
        }
    }
}
