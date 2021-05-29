
public class pair {
    private Node m_first;
    private Node m_second;
    public pair(Node first,Node second)
    {
       m_first=first;
       m_second=second;
    }

    public Node GetFirst() {
        return m_first;
    }

    public Node GetSecond()
    {
        return m_second;
    }


    public void SetFirst(Node first)
    {
        m_first=first;
    }

    public void SetSecond(Node second)
    {
        m_second=second;
    }
}
