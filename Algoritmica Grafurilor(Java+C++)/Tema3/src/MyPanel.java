import kotlin.Pair;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.*;
import java.util.*;
import javax.swing.BorderFactory;
import javax.swing.JPanel;
import java.lang.Math;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.*;
import java.lang.Math;


public class MyPanel extends JPanel {
    private int nodeNr = 0;
    private int node_diam = 30;
    private Vector<Node> listaNoduri;
    private Vector<Arc> listaArce;
    private ArrayList<Point> Positions;
    private ArrayList<ArrayList<Integer>> adiacenta, StrongComponents;
    private JButton sort;
    private JButton connected;
    private JButton strongconnected;
    private JButton reset;
    private Point pointStart = null;
    private Point pointEnd = null;
    private boolean isDragging = false, paintNewEdges = false;
    private int indexRight = -1;

    public MyPanel(JButton psort, JButton pconnected, JButton pstrongconnected, JButton preset) throws IOException {
        listaNoduri = new Vector<Node>();
        listaArce = new Vector<Arc>();
        adiacenta = new ArrayList<ArrayList<Integer>>();
        sort = psort;
        connected = pconnected;
        strongconnected = pstrongconnected;
        reset = preset;

        reset.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                listaArce.clear();
                listaNoduri.clear();
                adiacenta.clear();
                nodeNr = 0;
                repaint();
            }
        });
        sort.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                TopologicalSort();
            }
        });
        connected.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ConnectedComponents();
            }
        });
        strongconnected.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                SConnectedComponents();
            }
        });

        String file = "src/adiacenta.txt";
        // borderul panel-ului
        setBorder(BorderFactory.createLineBorder(Color.black));
        addMouseListener(new MouseAdapter() {
            //evenimentul care se produce la apasarea mousse-ului
            public void mousePressed(MouseEvent e) {
                pointStart = e.getPoint();
                if (SwingUtilities.isRightMouseButton(e))
                    for (int index = 0; index < listaNoduri.size(); index++)
                        if ((pointStart.x >= listaNoduri.elementAt(index).getCoordX() && pointStart.x <= listaNoduri.elementAt(index).getCoordX() + node_diam) && (pointStart.y >= listaNoduri.elementAt(index).getCoordY() && pointStart.y <= listaNoduri.elementAt(index).getCoordY() + node_diam))
                            indexRight = index;
            }

            //evenimentul care se produce la eliberarea mousse-ului
            public void mouseReleased(MouseEvent e) {
                if (SwingUtilities.isLeftMouseButton(e) && e.getX() > 170) {
                    if (!isDragging) {
                        boolean var = false;
                        for (int index = 0; index < listaNoduri.size(); index++) {
                            if (Math.sqrt((listaNoduri.elementAt(index).getCoordX() - e.getX()) * (listaNoduri.elementAt(index).getCoordX() - e.getX()) + (listaNoduri.elementAt(index).getCoordY() - e.getY()) * (listaNoduri.elementAt(index).getCoordY() - e.getY())) < node_diam * 1.3)
                                var = true;
                        }
                        if (!var) {
                            adiacenta.add(new ArrayList<Integer>());
                            for (int index = 0; index < adiacenta.size() - 1; index++) {
                                adiacenta.get(index).add(0);
                                adiacenta.get(nodeNr).add(0);
                            }
                            adiacenta.get(nodeNr).add(0);
                            addNode(e.getX(), e.getY());
                            Write(file);
                        }
                    } else {
                        boolean var1 = false, var2 = false, var3 = false;
                        int pointer1 = 0, pointer2 = 0;
                        for (int index = 0; index < listaNoduri.size(); index++) {
                            if ((pointStart.x >= listaNoduri.elementAt(index).getCoordX() && pointStart.x <= listaNoduri.elementAt(index).getCoordX() + node_diam + 2) && (pointStart.y >= listaNoduri.elementAt(index).getCoordY() && pointStart.y <= listaNoduri.elementAt(index).getCoordY() + node_diam)) {
                                var1 = true;
                                pointer1 = index;
                            }
                            if ((pointEnd.x >= listaNoduri.elementAt(index).getCoordX() && pointEnd.x <= listaNoduri.elementAt(index).getCoordX() + node_diam + 2) && (pointEnd.y >= listaNoduri.elementAt(index).getCoordY() && pointEnd.y <= listaNoduri.elementAt(index).getCoordY() + node_diam)) {
                                var2 = true;
                                pointer2 = index;
                            }
                        }
                        if (var1 && var2 && pointer1 != pointer2) {
                            for (int index = 0; index < listaArce.size(); index++) {
                                if (Math.sqrt((listaArce.elementAt(index).GetStartcoordX() - pointStart.x) * (listaArce.elementAt(index).GetStartcoordX() - pointStart.x) + (listaArce.elementAt(index).GetStartcoordY() - pointStart.y) * (listaArce.elementAt(index).GetStartcoordY() - pointStart.y)) < node_diam * 1.5
                                        && (Math.sqrt((listaArce.elementAt(index).GetEndcoordX() - pointEnd.x) * (listaArce.elementAt(index).GetEndcoordX() - pointEnd.x) + (listaArce.elementAt(index).GetEndcoordY() - pointEnd.y) * (listaArce.elementAt(index).GetEndcoordY() - pointEnd.y)) < node_diam * 1.5))
                                    var3 = true;
                            }
                            if (!var3) {
                                Arc arc = new Arc(pointStart, pointEnd);
                                listaArce.add(arc);
                                adiacenta.get(pointer1).set(pointer2, 1);
                                Write(file);
                            }
                        }


                    }
                    pointStart = null;
                    isDragging = false;
                }
                indexRight = -1;
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            //evenimentul care se produce la drag&drop pe mousse
            public void mouseDragged(MouseEvent e) {
                pointEnd = e.getPoint();
                isDragging = true;
                if (SwingUtilities.isRightMouseButton(e) && indexRight != -1 && e.getX() > 170) {
                    for (int index = 0; index < listaArce.size(); index++) {
                        if ((listaArce.elementAt(index).GetStartcoordX() >= listaNoduri.elementAt(indexRight).getCoordX()) && (listaArce.elementAt(index).GetStartcoordX() <= listaNoduri.elementAt(indexRight).getCoordX() + node_diam) && (listaArce.elementAt(index).GetStartcoordY() >= listaNoduri.elementAt(indexRight).getCoordY()) && (listaArce.elementAt(index).GetStartcoordY() <= listaNoduri.elementAt(indexRight).getCoordY() + node_diam)) {
                            listaArce.elementAt(index).SetStartcoordX(e.getX() + node_diam / 2);
                            listaArce.elementAt(index).SetStartcoordY(e.getY() + node_diam / 2);
                        }
                        if ((listaArce.elementAt(index).GetEndcoordX() >= listaNoduri.elementAt(indexRight).getCoordX()) && (listaArce.elementAt(index).GetEndcoordX() <= listaNoduri.elementAt(indexRight).getCoordX() + node_diam) && (listaArce.elementAt(index).GetEndcoordY() >= listaNoduri.elementAt(indexRight).getCoordY()) && (listaArce.elementAt(index).GetEndcoordY() <= listaNoduri.elementAt(indexRight).getCoordY() + node_diam)) {
                            listaArce.elementAt(index).SetEndcoordX(e.getX() + node_diam / 2);
                            listaArce.elementAt(index).SetEndcoordY(e.getY() + node_diam / 2);
                        }
                    }
                    listaNoduri.elementAt(indexRight).setCoordX(e.getX());
                    listaNoduri.elementAt(indexRight).setCoordY(e.getY());
                    repaint();
                } else if (SwingUtilities.isLeftMouseButton(e))
                    repaint();
            }
        });
    }

    //metoda care se apeleaza la eliberarea mouse-ului
    private void addNode(int x, int y) {
        nodeNr++;
        Node node = new Node(x, y, nodeNr);
        listaNoduri.add(node);
        repaint();

    }

    public void SConnectedComponents() {
        ArrayList<ArrayList<Integer>> Graph = CreateList();
        Stack<Integer> depth;
        depth = PTDFGraph();
        InversionGraph(Graph);
        PTDFGraphInverted(Graph, depth);
        AddnewNodes();
        AddnewEdges();
        repaint();
    }

    private void AddnewNodes() {
        listaNoduri.clear();
        listaArce.clear();
        nodeNr = 0;
        for (int index1 = 0; index1 < StrongComponents.size(); ++index1) {
            double number = 0;
            for (int index2 = 0; index2 < StrongComponents.get(index1).size(); ++index2) {
                number = number * Math.pow(10, NumberofDigits(StrongComponents.get(index1).get(index2))) + StrongComponents.get(index1).get(index2);
            }

            Node node = new Node(Positions.get(index1).x, Positions.get(index1).y, (int) Math.round(number));
            listaNoduri.add(node);
        }

    }

    private void AddnewEdges() {
        paintNewEdges = true;
        ArrayList<ArrayList<Integer>> Graph = CreateList();
        for (int index1 = 0; index1 < StrongComponents.size(); ++index1) {
            for (int index2 = 0; index2 < StrongComponents.get(index1).size(); ++index2) {
                Integer node = StrongComponents.get(index1).get(index2);
                for (int index3 = 0; index3 < Graph.get(node - 1).size(); ++index3)
                    if (!StrongComponents.get(index1).contains(Graph.get(node - 1).get(index3) + 1)) {
                        Arc arc = new Arc(new Point(Positions.get(index1)),new Point(Positions.get(SearchComponents
                                (Graph.get(node - 1).get(index3) + 1))));
                        if (!listaArce.contains(arc)) {
                            listaArce.add(arc);
                        }
                    }

            }
        }
    }

    private Integer SearchComponents(Integer node) {
        for (int index1 = 0; index1 < StrongComponents.size(); ++index1)
            for (int index2 = 0; index2 < StrongComponents.get(index1).size(); ++index2) {
                if (node == StrongComponents.get(index1).get(index2))
                    return index1;
            }
        return -1;
    }

    private Integer NumberofDigits(Integer number) {
        Integer cnumber = number, nr = 0;
        while (cnumber != 0) {
            nr++;
            cnumber /= 10;
        }
        return nr;
    }

    private void PTDFGraphInverted(ArrayList<ArrayList<Integer>> Graph, Stack<Integer> depth) {
        Integer start = depth.peek(), NrComp = 1;
        SortedSet<Integer> Unvisited = new TreeSet<>();
        Stack<Integer> Visited = new Stack<>();
        ArrayList<Integer> SComponents = new ArrayList<>();
        StrongComponents = new ArrayList<ArrayList<Integer>>();
        Positions = new ArrayList<Point>();
        Visited.add(start);
        SComponents.add(start + 1);
        for (int index = 0; index < listaNoduri.size(); ++index) {
            if (index == start)
                continue;
            else
                Unvisited.add(index);
        }

        while (!depth.isEmpty()) {
            depth.pop();
            Positions.add(new Point(listaNoduri.get(start).getCoordX(), listaNoduri.get(start).getCoordY()));
            while (!Visited.isEmpty()) {
                Integer currentnode = Visited.peek();
                if (Graph.get(currentnode).size() != 0) {
                    int count = 0;
                    for (int index = 0; index < Graph.get(currentnode).size(); ++index) {
                        Integer visitednode = Graph.get(currentnode).get(index);
                        if (Unvisited.contains(visitednode)) {
                            Unvisited.remove(visitednode);
                            Visited.add(visitednode);
                            depth.remove(visitednode);
                            SComponents.add(visitednode + 1);
                            break;
                        } else {
                            ++count;
                            continue;
                        }
                    }

                    if (count == Graph.get(currentnode).size()) {
                        Visited.remove(currentnode);
                    }

                } else {
                    Visited.remove(currentnode);
                }

            }
            System.out.print(NrComp);
            System.out.print(".");
            for (Integer value : SComponents)
                System.out.print(value);
            System.out.print("\n");

            if (!depth.isEmpty())
                start = depth.peek();

            StrongComponents.add(new ArrayList<>());
            for (int index = 0; index < SComponents.size(); ++index)
                StrongComponents.get(StrongComponents.size() - 1).add(SComponents.get(index));
            Unvisited.remove(start);
            Visited.add(start);
            NrComp++;
            SComponents.clear();
            SComponents.add(start + 1);
        }
    }

    private void InversionGraph(ArrayList<ArrayList<Integer>> Graph) {
        ArrayList<ArrayList<Integer>> CopyGraph = new ArrayList<ArrayList<Integer>>();
        Vector<Integer> size = new Vector<>();
        for (int index1 = 0; index1 < Graph.size(); index1++) {
            CopyGraph.add(new ArrayList<Integer>());
            size.add(Graph.get(index1).size());
            for (int index2 = 0; index2 < Graph.get(index1).size(); index2++) {
                CopyGraph.get(index1).add(Graph.get(index1).get(index2));
            }
        }

        for (int index1 = 0; index1 < CopyGraph.size(); ++index1)
            for (int index2 = 0; index2 < CopyGraph.get(index1).size(); ++index2) {
                Graph.get(Graph.get(index1).get(index2)).add(index1);
            }

        for (int index1 = 0; index1 < Graph.size(); ++index1)
            for (int index3 = 0; index3 < size.get(index1); ++index3)
                Graph.get(index1).remove(0);
    }

    private Stack<Integer> PTDFGraph() {
        Integer start = 0;
        SortedSet<Integer> Unvisited = new TreeSet<>();
        Stack<Integer> Visited = new Stack<>();
        Stack<Integer> depth = new Stack<>();
        ArrayList<ArrayList<Integer>> Graph = CreateList();
        Visited.add(start);
        for (int index = 1; index < listaNoduri.size(); ++index) {
            Unvisited.add(index);
        }

        while (listaNoduri.size() != depth.size()) {
            while (!Visited.isEmpty()) {
                Integer currentnode = Visited.peek();
                if (Graph.get(currentnode).size() != 0) {
                    int count = 0;
                    for (int index = 0; index < Graph.get(currentnode).size(); ++index) {
                        Integer visitednode = Graph.get(currentnode).get(index);
                        if (Unvisited.contains(visitednode)) {
                            Unvisited.remove(visitednode);
                            Visited.add(visitednode);
                            break;
                        } else {
                            ++count;
                            continue;
                        }
                    }

                    if (count == Graph.get(currentnode).size()) {
                        Visited.remove(currentnode);
                        depth.add(currentnode);
                    }

                } else {
                    Visited.remove(currentnode);
                    depth.add(currentnode);
                }

            }
            if (Unvisited.size() > 0)
                start = Unvisited.first();
            Unvisited.remove(start);
            Visited.add(start);
        }

        return depth;

    }

    public void ConnectedComponents() {
        Integer start = 0, nrComp = 1;
        SortedSet<Integer> Unvisited = new TreeSet<>();
        Stack<Integer> Visited = new Stack<>();
        Set<Integer> Marked = new LinkedHashSet<>();
        ArrayList<ArrayList<Integer>> Graph = CreateListNonOriented();
        Vector<Integer> Components = new Vector<Integer>();

        Components.add(start);
        Visited.add(start);
        for (int index = 1; index < listaNoduri.size(); ++index) {
            Unvisited.add(index);
        }
        while (listaNoduri.size() != Marked.size()) {
            while (!Visited.isEmpty()) {
                Integer currentnode = Visited.peek();
                if (Graph.get(currentnode).size() != 0) {
                    int count = 0;
                    for (int index = 0; index < Graph.get(currentnode).size(); ++index) {
                        Integer visitednode = Graph.get(currentnode).get(index);
                        if (Unvisited.contains(visitednode)) {
                            Unvisited.remove(visitednode);
                            Visited.add(visitednode);
                            Components.add(visitednode);
                            break;
                        } else {
                            ++count;
                            continue;
                        }
                        }
                    if (count == Graph.get(currentnode).size()) {
                        Visited.remove(currentnode);
                        Marked.add(currentnode);
                    }
                } else {
                    Visited.remove(currentnode);
                    Marked.add(currentnode);
                }
            }


            for (Integer value : Components)
                listaNoduri.get(value).setColor(ComponentColor(nrComp));
            if (Unvisited.size() > 0)
                start = Unvisited.first();


            Unvisited.remove(start);
            Visited.add(start);
            nrComp++;
            Components.clear();
            Components.add(start);
        }

        repaint();
    }

    private ArrayList<ArrayList<Integer>> CreateList() {

        ArrayList<ArrayList<Integer>> Graph = new ArrayList<ArrayList<Integer>>();
        for (int index1 = 0; index1 < adiacenta.size(); index1++) {
            Graph.add(new ArrayList<>());
            for (int index2 = 0; index2 < adiacenta.size(); index2++)
                if (adiacenta.get(index1).get(index2) == 1)
                    Graph.get(index1).add(index2);
        }

        return Graph;
    }

    private ArrayList<ArrayList<Integer>> CreateListNonOriented() {

        ArrayList<ArrayList<Integer>> Graph = new ArrayList<ArrayList<Integer>>();
        ArrayList<ArrayList<Integer>> Copyadiacenta = new ArrayList<ArrayList<Integer>>();
        for (int index1 = 0; index1 < adiacenta.size(); index1++) {
            Copyadiacenta.add(new ArrayList<Integer>());
            for (int index2 = 0; index2 < adiacenta.size(); index2++) {
                Copyadiacenta.get(index1).add(adiacenta.get(index1).get(index2));
            }
        }
        for (int index1 = 0; index1 < Copyadiacenta.size(); index1++) {
            for (int index2 = 0; index2 < Copyadiacenta.size(); index2++)
                if (Copyadiacenta.get(index1).get(index2) == 1) {
                    Copyadiacenta.get(index2).set(index1, 1);
                }
        }

        for (int index1 = 0; index1 < Copyadiacenta.size(); index1++) {
            Graph.add(new ArrayList<>());
            for (int index2 = 0; index2 < Copyadiacenta.size(); index2++)
                if (Copyadiacenta.get(index1).get(index2) == 1) {
                    Graph.get(index1).add(index2);
                }
        }

        return Graph;
    }

    public void TopologicalSort() {
        ArrayList<ArrayList<Integer>> Graph = CreateList();
        ArrayList<Integer> listsort = new ArrayList<>();
        Vector<Integer> Nodes = Indegree0(Graph);
        Stack<Integer> stackIndegree = new Stack<>();

        for (int index = 0; index < Nodes.size(); ++index)
            if (Nodes.get(index) == 0)
                stackIndegree.add(index);

        if (!stackIndegree.isEmpty()) {
            while (!stackIndegree.isEmpty()) {
                Integer node = stackIndegree.peek();
                if (!listsort.contains(node + 1))
                    listsort.add(node + 1);
                if (Graph.get(node).size() != 0) {
                    Integer visitednode = Graph.get(node).get(0);
                    Graph.get(node).remove(visitednode);
                    if (Indegree0(Graph).get(visitednode) == 0)
                        stackIndegree.add(visitednode);
                } else
                    stackIndegree.pop();
            }

            boolean acyclic = false;
            for (int index1 = 0; index1 < Graph.size(); index1++)
                if (Graph.get(index1).size() != 0) {
                    System.out.print("The graph is not acyclic!");
                    acyclic = true;
                    break;
                }
            if (!acyclic)
                for (int index = 0; index < listsort.size(); ++index) {
                    System.out.print(listsort.get(index));
                    System.out.print(" ");
                }
        } else
            System.out.print("The graph is not acyclic!");
    }

    private Vector<Integer> Indegree0(ArrayList<ArrayList<Integer>> Graph) {
        Vector<Integer> Nodes;
        Nodes = new Vector<>();
        for (int index = 0; index < Graph.size(); ++index)
            Nodes.add(0);

        for (int index1 = 0; index1 < Graph.size(); index1++)
            for (int index2 = 0; index2 < Graph.get(index1).size(); index2++)
                Nodes.setElementAt(1, Graph.get(index1).get(index2));
        return Nodes;
    }

    private Color ComponentColor(int numberComponent) {
        switch (numberComponent) {
            case 1:
                return Color.BLACK;
            case 2:
                return Color.GREEN;
            case 3:
                return Color.CYAN;
            case 4:
                return Color.MAGENTA;
            case 5:
                return Color.ORANGE;
            case 6:
                return Color.YELLOW;
            case 7:
                return Color.GRAY;
            case 8:
                return Color.BLUE;
            case 9:
                return Color.DARK_GRAY;
            case 10:
                return Color.PINK;

        }
        return Color.RED;
    }


    public void Write(String filename) {
        try (FileWriter file = new FileWriter(filename)) {
            file.write(Integer.toString(nodeNr));
            file.write("\n");
            ArrayList<ArrayList<Integer>> Graph = CreateList();
            for (int index1 = 0; index1 < adiacenta.size(); index1++) {
                for (int index2 = 0; index2 < adiacenta.size(); index2++)
                    file.write(Integer.toString(adiacenta.get(index1).get((index2))));
                file.write("\n");
            }
            file.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    //se executa atunci cand apelam repaint()
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);//apelez metoda paintComponent din clasa de baza
        g.drawString("This is my Graph!", 10, 20);

        //deseneaza arcele existente in lista
        if (!paintNewEdges)
            for (Arc a : listaArce) {
                a.drawArc(g);
            }
        else
            for (Arc a : listaArce) {
                a.SetStartcoordX(a.GetStartcoordX() + node_diam / 2);
                a.SetStartcoordY(a.GetStartcoordY() + node_diam / 2);
                a.SetEndcoordX(a.GetEndcoordX() + node_diam / 2);
                a.SetEndcoordY(a.GetEndcoordY() + node_diam / 2);
                a.drawArc(g);
            }


        //deseneaza lista de noduri
        for (int i = 0; i < listaNoduri.size(); i++) {
            listaNoduri.elementAt(i).drawNode(g, node_diam);
        }

        //deseneaza arcul curent; cel care e in curs de desenare
        if (pointStart != null && indexRight == -1) {
            g.setColor(Color.RED);
            g.drawLine(pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);
        }

        sort.repaint();
        connected.repaint();
        strongconnected.repaint();
        reset.repaint();
    }
}
