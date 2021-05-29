import kotlin.Pair;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.*;
import java.time.LocalTime;
import java.util.*;
import javax.swing.JPanel;
import java.lang.Math;
import java.io.File;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import org.w3c.dom.*;
import javax.xml.parsers.*;



public class MyPanel extends JPanel {
    private LocalTime m_time;
    private pair m_road;
    private ArrayList<ArrayList<Edge>> adjacencyList;
    private final ArrayList<Node> m_nodesList;
    private final ArrayList<Edge> m_edgesList;
    private Vector<Edge> m_path;
    private final int m_frameWidth, m_frameHeight;

    public MyPanel(int frameWidth, int frameHeight) {
        m_nodesList = new ArrayList<>();
        m_edgesList = new ArrayList<>();
        m_frameWidth = frameWidth;
        m_frameHeight = frameHeight;
        m_time = LocalTime.now();
        m_road = new pair(null, null);
        m_path = new Vector<>();

        ReadFromFile();
        ConvertNodesToPositions();

        addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                double minDistance = Integer.MAX_VALUE;
                Node selectedNode = m_nodesList.get(0);
                for (Node node : m_nodesList) {
                    double nodedistance = Math.sqrt((node.GetCoordX() - e.getX()) * (node.GetCoordX() - e.getX()) + (node.GetCoordY() - e.getY()) * (node.GetCoordY() - e.getY()));
                    if (nodedistance < minDistance) {
                        minDistance = nodedistance;
                        selectedNode = node;
                    }
                }

                if (m_road.GetFirst() != null && m_road.GetSecond() != null) {
                    m_road = new pair(selectedNode, null);
                }
                else if (m_road.GetFirst() != null) {
                    m_road.SetSecond(selectedNode);
                    try {
                        UserChoice();
                    } catch (IOException ioException) {
                        ioException.printStackTrace();
                    }
                } else
                    m_road.SetFirst(selectedNode);
            }
        });

        CreateAdjacencyList();

        repaint();
    }

    public void UserChoice() throws IOException {
        System.out.print("Please write 1 for  Dijkstra or 2 for Bellman-Ford:");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String userInput = br.readLine();
        while (!(userInput.equals("1") || userInput.equals("2"))) {
            System.out.print("Please write 1 for  Dijkstra or 2 for Bellman-Ford:");
            userInput = br.readLine();
        }
        if (userInput.equals("1")) {
            m_time = LocalTime.now();
            System.out.print("Time before drawing the road with Dijkstra:");
            System.out.print(m_time);
            System.out.print('\n');

            Dijkstra();

            m_time = LocalTime.now();
            System.out.print("Time after drawing the road with Dijkstra:");
            System.out.print(m_time);
            System.out.print('\n');
        }
       else if (userInput.equals("2")) {
            m_time = LocalTime.now();
            System.out.print("Time before drawing the road with Bellman-Ford:");
            System.out.print(m_time);
            System.out.print('\n');

            BellmanFord();

            m_time = LocalTime.now();
            System.out.print("Time after drawing the road with Bellman-Ford:");
            System.out.print(m_time);
            System.out.print('\n');
        }
    }

    private void Dijkstra() {
        Vector<Boolean> visited = new Vector<>();
        Vector<Edge> previous = new Vector<>();
        Vector<Integer> distance = new Vector<>();
        for (int index = 0; index < m_nodesList.size(); ++index) {
            visited.add(false);
            previous.add(null);
            distance.add(Integer.MAX_VALUE);
        }
        distance.set(m_road.GetFirst().GetId(), 0);

        PriorityQueue<Pair<Integer, Integer>> pq = new PriorityQueue<>(Comparator.comparing(Pair::getSecond));
        pq.add(new Pair<>(m_road.GetFirst().GetId(), 0));

        Pair<Integer, Integer> currentNode;
        while (!pq.isEmpty()) {
            currentNode = pq.poll();
            visited.set(currentNode.getFirst(), true);
            if (distance.get(currentNode.getFirst()) < currentNode.getSecond()) continue;
            for (Edge edge : adjacencyList.get(currentNode.getFirst())) {
                if (visited.get(edge.GetEnd())) continue;
                Integer newdistance = distance.get(currentNode.getFirst()) + edge.GetLength();
                if (newdistance < distance.get(edge.GetEnd())) {
                    previous.set(edge.GetEnd(), edge);
                    distance.set(edge.GetEnd(), newdistance);
                    pq.add(new Pair<>(edge.GetEnd(), newdistance));
                }
            }
        }

        m_path = CreatePath(previous);
        for (Edge edge : m_path)
            edge.SetColor(Color.RED);
        m_road.GetFirst().SetColor(Color.GREEN);
        m_road.GetSecond().SetColor(Color.GREEN);
        repaint();
    }

    private Vector<Edge> CreatePath(Vector<Edge> previous) {
        Vector<Edge> path = new Vector<>();
        for (Integer index = m_road.GetSecond().GetId(); previous.get(index) != null; index = previous.get(index).GetStart())
            path.add(previous.get(index));
        return path;
    }


    private void BellmanFord() {
        Vector<Edge> previous = new Vector<>();
        Vector<Integer> distance = new Vector<>();
        for (int index = 0; index < m_nodesList.size(); ++index) {
            previous.add(null);
            distance.add(Integer.MAX_VALUE);
        }
        distance.set(m_road.GetFirst().GetId(), 0);
        boolean verifyChange;

        for (int index = 0; index < m_nodesList.size() - 1; ++index) {
            verifyChange = false;
           for(Edge edge:m_edgesList)
            {
                if(distance.get(edge.GetStart())==Integer.MAX_VALUE) continue;
                    Integer newdistance = distance.get(edge.GetStart()) + edge.GetLength();
                    if (newdistance < distance.get(edge.GetEnd())) {
                        previous.set(edge.GetEnd(), edge);
                        distance.set(edge.GetEnd(), newdistance);
                        verifyChange = true;
                    }
                }
            if (!verifyChange)
                break;
        }

        m_path = CreatePath(previous);
        for (Edge edge : m_path)
            edge.SetColor(Color.RED);
        m_road.GetFirst().SetColor(Color.GREEN);
        m_road.GetSecond().SetColor(Color.GREEN);
        repaint();
    }

    void CreateAdjacencyList() {
        adjacencyList = new ArrayList<ArrayList<Edge>>();
        for (int index = 0; index < m_nodesList.size(); ++index)
            adjacencyList.add(new ArrayList<>());

        for (int index = 0; index < m_edgesList.size(); ++index) {
            Edge edge = m_edgesList.get(index);
            adjacencyList.get(edge.GetStart()).add(edge);
        }

    }

    private void ReadFromFile() {
        try {

            System.out.print("Time before reading from file:");
            System.out.print(m_time);
            System.out.print('\n');

            File inputFile = new File("map2.xml");
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document doc = builder.parse(inputFile);

            m_time = LocalTime.now();
            System.out.print("Time after loading the xml file:");
            System.out.print(m_time);
            System.out.print('\n');

            NodeList nList = doc.getElementsByTagName("node");
            int size = nList.getLength();
            for (int index = 0; index < size; ++index) {
                Element element = (Element) nList.item(index);
                int id = Integer.parseInt(element.getAttribute("id"));
                int longitude = Integer.parseInt(element.getAttribute("longitude"));
                int latitude = Integer.parseInt(element.getAttribute("latitude"));
                m_nodesList.add(new Node(id, latitude, longitude));
            }

            m_time = LocalTime.now();
            System.out.print("Time after reading the nodes:");
            System.out.print(m_time);
            System.out.print('\n');

            NodeList aList = doc.getElementsByTagName("arc");
            size = aList.getLength();
            for (int index = 0; index < size; ++index) {
                Element element = (Element) aList.item(index);
                int start = Integer.parseInt(element.getAttribute("from"));
                int end = Integer.parseInt(element.getAttribute("to"));
                int length = Integer.parseInt(element.getAttribute("length"));
                m_edgesList.add(new Edge(start, end, length));
            }

            m_time = LocalTime.now();
            System.out.print("Time after reading the edges:");
            System.out.print(m_time);
            System.out.print('\n');

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    private int GetMaxLatitude() {
        int max = 0;
        for (Node node : m_nodesList)
            if (node.GetCoordX() > max)
                max = node.GetCoordX();
        return max;
    }

    private int GetMaxLongitude() {
        int max = 0;
        for (Node node : m_nodesList)
            if (node.GetCoordY() > max)
                max = node.GetCoordY();
        return max;
    }

    private int GetMinLatitude() {
        int min = m_nodesList.get(0).GetCoordX();
        for (Node node : m_nodesList)
            if (node.GetCoordX() < min)
                min = node.GetCoordX();
        return min;
    }

    private int GetMinLongitude() {
        int min = m_nodesList.get(0).GetCoordY();
        for (Node node : m_nodesList)
            if (node.GetCoordY() < min)
                min = node.GetCoordY();
        return min;
    }

    private void ConvertNodesToPositions() {
        int minlongitude = GetMinLongitude();
        int minlatitude = GetMinLatitude();
        int longitudeRatio = (GetMaxLongitude() - minlongitude) / (m_frameHeight - 41);
        int latitudeRatio = (GetMaxLatitude() - minlatitude) / (m_frameWidth - 18);
        for (Node node : m_nodesList) {
            node.SetCoordX(((node.GetCoordX() - minlatitude) / latitudeRatio));
            node.SetCoordY(m_frameHeight - 41 - ((node.GetCoordY() - minlongitude) / longitudeRatio));
        }

        m_time = LocalTime.now();
        System.out.print("Time after Converting the nodes to XY coordinates:");
        System.out.print(m_time);
        System.out.print('\n');
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (Node node : m_nodesList) {
            node.drawNode(g);
        }

        for (Edge edge : m_edgesList)
            edge.drawEdge(g, m_nodesList);

        if (!m_path.isEmpty()) {
            for (Edge edge : m_path)
                edge.drawEdge(g, m_nodesList);

            m_road.GetFirst().drawNode(g);
            m_road.GetSecond().drawNode(g);
        }

    }

}