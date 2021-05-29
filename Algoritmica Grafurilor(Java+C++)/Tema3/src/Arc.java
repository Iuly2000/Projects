import java.awt.*;
import java.awt.geom.AffineTransform;

public class Arc
{
	private Point start;
	private Point end;

	public int GetStartcoordX()
    {
        return start.x;
    }
    public int GetStartcoordY()
    {
        return start.y;
    }
    public int GetEndcoordX()
    {
        return end.x;
    }
    public int GetEndcoordY()
    {
        return end.y;
    }
    public void SetStartcoordX(int x){
	    start.x=x;
	}
    public void SetStartcoordY(int y){
        start.y=y;
    }
    public void SetEndcoordX(int x){
	    end.x=x;
    }
    public void SetEndcoordY(int y){
	    end.y=y;
	};
	public Arc(Point start, Point end)
	{
		this.start = start;
		this.end = end;
	}
	public void drawArrow(Graphics g,int x1,int y1,int x2,int y2)
    {
        Graphics2D g1=(Graphics2D) g.create();
        double dx=x2-x1,dy=y2-y1;
        int lenght= (int) Math.sqrt(dx*dx+dy*dy);
        double angle=Math.atan2(dy,dx);
        AffineTransform to=AffineTransform.getTranslateInstance(x1,y1);
        to.concatenate(AffineTransform.getRotateInstance(angle));
        g1.transform(to);
        g1.drawLine(0,0,lenght,0);
        int ArrrowSize=8;
        g1.fillPolygon(new int[] {lenght-15,lenght-ArrrowSize-20,lenght-ArrrowSize-20}, new int[] {0, -ArrrowSize,ArrrowSize},3);
    }
	public void drawArc(Graphics g)
	{
		if (start != null)
		{
            g.setColor(Color.blue);
            drawArrow(g,start.x, start.y, end.x, end.y);
        }
	}
}
