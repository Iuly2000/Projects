import java.awt.*;

public class Node {
    private int m_id;
    private int m_CoordX;
    private int m_CoordY;
    private Color m_color;

    public Node(int id,int CoordX,int CoordY)
    {
        m_id=id;
        m_CoordX=CoordX;
        m_CoordY=CoordY;
        m_color = Color.BLACK;
    }

    public int GetId() {
        return m_id;
    }

    public int GetCoordX()
    {
        return m_CoordX;
    }

    public int GetCoordY()
    {
        return m_CoordY;
    }

    public Color GetColor() {
        return m_color;
    }

    public void SetColor(Color color) {
        m_color = color;
    }

    public void SetId(int id)
    {
     m_id=id;
    }

    public void SetCoordX(int CoordX)
    {
        m_CoordX=CoordX;
    }

    public void SetCoordY(int CoordY)
    {
        m_CoordY=CoordY;
    }

    public void drawNode(Graphics g)
    {
        g.setColor(m_color);
        if(m_color==Color.GREEN)
        g.fillOval(m_CoordX,m_CoordY, 5, 5);
        else
        g.fillOval(m_CoordX,m_CoordY, 1, 1);

    }

}
