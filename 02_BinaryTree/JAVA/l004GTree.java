import java.util.*;

public class l004GTree {

    static class Node {
        int data;
        ArrayList<Node> children = null;

        Node(int data) {
            this.data = data;
            this.children = new ArrayList<>();
        }
    }

    static Node createGtree(int[] dlist) {
        Stack<Node> st = new Stack<>();

        for (int i = 0; i < dlist.length - 1; i++) {
            if (dlist[i] != -1) {
                Node node = new Node(dlist[i]);
                st.push(node);
            } else {
                Node node = st.pop();
                st.peek().children.add(node);
            }
        }

        return st.peek();
    }

    static void preOrder(Node root) {
        System.out.print(root.data + ", ");
        for (Node child : root.children) {
            preOrder(child);
        }
    }

    static void display(Node root) {
        System.out.print(root.data + " -> ");
        for (Node child : root.children) {
            System.out.print(child.data + ", ");
        }
        System.out.println();
        for (Node child : root.children) {
            display(child);
        }
    }

    static void levelOrder(Node root) {
        LinkedList<Node> queue = new LinkedList<>();
        queue.addLast(root);

        while (queue.size() != 0) {
            int size = queue.size();
            while (size-- > 0) {
                Node rem = queue.removeFirst();
                System.out.print(rem.data + " ");

                for (Node n : rem.children) {
                    queue.addLast(n);
                }
            }
            System.out.println();
        }
    }

    static int height(Node root) {
        int ht = 0;
        for (Node child : root.children) {
            ht = Math.max(ht, height(child));
        }
        return ht + 1;
    }

    static int size(Node root) {
        int s = 0;
        for (Node child : root.children) {
            s += size(child);
        }
        return s + 1;
    }

    static boolean find(Node root, int data) {
        if (root.data == data)
            return true;

        boolean res = false;
        for (Node child : root.children) {
            res = res || find(child, data);
        }
        return res;
    }

    static boolean nodeToRootPath(Node root, int data) {
        return false;
    }

    static boolean isMirror(Node root1, Node root2) {
        if (root1.children.size() != root2.children.size() || root1.data != root2.data)
            return false;

        boolean res = true;
        for (int i = 0, j = root1.children.size() - 1; j >= 0; i++, j--) {
            Node first = root1.children.get(i);
            Node last = root2.children.get(j);

            res = res && isMirror(first, last);
        }

        return res;
    }

    static Node linearize(Node root) {
        if (root.children.size() == 0)
            return root;

        int n = root.children.size();
        Node lastTail = linearize(root.children.get(n - 1));

        for (int i = n - 2; i >= 0; i--) {
            Node secondLastTail = linearize(root.children.get(i));

            // connection
            secondLastTail.children.add(root.children.get(i + 1));

            // remove last
            root.children.remove(root.children.size() - 1);
        }
        return lastTail;
    }

    static void flattern_(Node root, ArrayList<Node> nodes) {
        nodes.add(root);

        for (Node child : root.children) {
            flattern_(child, nodes);
        }
    }

    static Node flattern(Node root) {
        ArrayList<Node> nodes = new ArrayList<>();
        for (Node child : root.children) {
            flattern_(child, nodes);
        }

        root.children = new ArrayList<>();
        for (Node n : nodes) {
            root.children.add(n);
            n.children.clear();
        }

        return root;
    }

    static void solve() {
        int[] dlist = { 10, 20, 30, -1, 40, -1, 50, -1, -1, 60, 70, -1, 80, 90, -1, 100, -1, -1, 110, -1, -1, 120, 130,
                -1, -1, -1 };
        Node root = createGtree(dlist);
        // preOrder(root);
        display(root);
        // levelOrder(root);
        // linearize(root);
        flattern(root);
        System.out.println();
        display(root);

    }

    public static void main(String[] args) {
        solve();
    }
}