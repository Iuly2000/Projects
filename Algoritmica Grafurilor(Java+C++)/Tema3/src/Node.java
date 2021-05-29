import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

public class Node
{
	private int coordX;
	private int coordY;
	private int number;
	private Color color;
	
	public Node(int coordX, int coordY, int number)
	{
		this.coordX = coordX;
		this.coordY = coordY;
		this.number = number;
		this.color=Color.RED;
	}
	
	public int getCoordX() {
		return coordX;
	}
	public void setCoordX(int coordX) {
		this.coordX = coordX;
	}
	public int getCoordY() {
		return coordY;
	}
	public void setCoordY(int coordY) {
		this.coordY = coordY;
	}
	public int getNumber() {
		return number;
	}
	public void setNumber(int number) {
		this.number = number;
	}
	public Color getColor() {
		return color;
	}
	public void setColor(Color color) {
		this.color = color;
	}

	private Integer NumberofDigits(Integer number) {
		Integer cnumber = number, nr = 0;
		while (cnumber != 0) {
			nr++;
			cnumber /= 10;
		}
		return nr;
	}

	public void drawNode(Graphics g, int node_diam)
	{
		Integer digits= NumberofDigits(number);
		g.setColor(color);
		g.setFont(new Font("TimesRoman", Font.BOLD, 15));
        g.fillOval(coordX, coordY, node_diam+digits*digits, node_diam+digits*digits);
        g.setColor(Color.WHITE);
        g.drawOval(coordX, coordY, node_diam+digits*digits, node_diam+digits*digits);
        	g.drawString(((Integer)number).toString(), coordX+(node_diam+digits*digits)/2-4*digits, coordY+(node_diam+digits*digits)/2+5);

	}
}
