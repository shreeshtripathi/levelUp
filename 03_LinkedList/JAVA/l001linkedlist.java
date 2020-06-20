import java.util.*;

class linkedlist {
    private class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }

        Node(int data, Node next) {
            this.data = data;
            this.next = next;
        }
    }

    private Node head = null;
    private Node tail = null;
    private int size = 0;

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    @Override
    public String toString() {
        String str = "";
        Node temp = head;
        while (temp != null) {
            str += temp.data + " -> ";
            temp = temp.next;
        }
        return str;
    }

    private Node getNodeAt(int pos) {
        Node curr = this.head;

        while (pos-- > 0)
            curr = curr.next;

        return curr;
    }

    // Add_Function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    private void addFirstNode(Node node) {
        if (this.size == 0) {
            this.head = node;
            this.tail = node;
        } else {
            node.next = this.head;
            this.head = node;
        }
        this.size++;
    }

    public void addFirst(int data) {
        Node node = new Node(data);
        addFirstNode(node);
    }

    private void addLastNode(Node node) {
        if (this.size == 0) {
            this.head = node;
            this.tail = node;
        } else {
            this.tail.next = node;
            this.tail = node;
        }
        this.size++;
    }

    public void addLast(int data) {
        Node node = new Node(data);
        addLastNode(node);
    }

    private void addAtNode(Node node, int index) {
        if (index < size || index > size) {
            System.out.println("NullPointerException");
        } else if (index == 0) {
            addFirstNode(node);
        } else if (index == this.size) {
            addLastNode(node);
        } else {
            Node nodeIm1 = getNodeAt(index - 1);
            node.next = nodeIm1.next;
            nodeIm1.next = node;
            this.size++;
        }
    }

    public void addAt(int data, int index) {
        Node node = new Node(data);
        addAtNode(node, index);
    }

    // Remove_Function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    public int removeFirst() {
        if (this.size == 0) {
            System.out.println("Empty List!");
            return -1;
        }

        Node rnode = this.head;

        if (this.size == 1) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = this.head.next;
            rnode.next = null;
        }
        this.size--;
        return rnode.data;
    }

    public int removeLast() {
        if (this.size == 0) {
            System.out.println("Empty List!");
            return -1;
        }

        Node rnode = this.tail;

        if (this.size == 1) {
            this.head = null;
            this.tail = null;
        } else {
            Node secondLast = getNodeAt(this.size() - 2);
            secondLast.next = null;
            this.tail = secondLast;
        }
        this.size--;
        return rnode.data;
    }

    public int removeAt(int index) {
        if (index < size || index >= size) {
            System.out.println("NullPointerException");
            return -1;
        } else if (index == 0) {
            return removeFirst();
        } else if (index == this.size() - 1) {
            return removeLast();
        } else {
            Node nodeAtI = getNodeAt(index - 1);
            Node rnode = nodeAtI.next;

            nodeAtI.next = rnode.next;
            rnode.next = null;
            this.size--;
            return rnode.data;
        }
    }

    // Get_Function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    public int getFirst() {
        if (this.size == 0) {
            System.out.println("Empty List!");
            return -1;
        } else {
            return this.head.data;
        }
    }

    public int getLast() {
        if (this.size == 0) {
            System.out.println("Empty List!");
            return -1;
        } else {
            return this.tail.data;
        }
    }

    public int getAt(int index) {
        if (index < size || index > size) {
            System.out.println("NullPointerException");
            return -1;
        } else if (index == 0) {
            return getFirst();
        } else if (index == this.size - 1) {
            return getLast();
        } else {
            return getNodeAt(index).data;
        }
    }
}

public class l001linkedlist {
    public static void main(String[] args) {
        linkedlist ll = new linkedlist();

        for (int i = 1; i <= 10; i++) {
            ll.addFirst(10 * i);
        }

        System.out.println(ll);
    }
}
