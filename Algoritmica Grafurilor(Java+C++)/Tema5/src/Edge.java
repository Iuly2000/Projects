import java.awt.*;
import java.util.ArrayList;

public class Edge {
    private int m_start;
    private int m_end;
    private int m_length;
    private Color m_color;

    public Edge(int start, int end, int length) {
        m_start = start;
        m_end = end;
        m_length = length;
        m_color = Color.BLACK;
    }

    public int GetStart() {
        return m_start;
    }

    public int GetEnd() {
        return m_end;
    }

    public int GetLength() {
        return m_length;
    }

    public Color GetColor() {
        return m_color;
    }

    public void SetColor(Color color) {
        m_color = color;
    }

    public void SetStart(int start) {
        m_start = start;
    }

    public void SetEnd(int end) {
        m_end = end;
    }

    public void SetLength(int length) {
        m_length = length;
    }

    public void drawEdge(Graphics g, ArrayList<Node> nodes) {
        g.setColor(m_color);
        g.drawLine(nodes.get(m_start).GetCoordX(), nodes.get(m_start).GetCoordY(),
                nodes.get(m_end).GetCoordX(), nodes.get(m_end).GetCoordY());
    }
}
