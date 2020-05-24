import java.util.*;

public class btree {
    static class Node {
        int data;
        Node left = null;
        Node right = null;

        Node(int data) {
            this.data = data;
        }
    }

    static int idx = 0;

    static Node construct(int[] arr) {
        if (idx >= arr.length || arr[idx] == -1) {
            idx++;
            return null;
        }

        Node node = new Node(arr[idx++]);
        node.left = construct(arr);
        node.right = construct(arr);

        return node;
    }

    static void display(Node node) {
        if (node == null)
            return;

        String str = "";
        str += node.left == null ? ".\t" : node.left.data + "\t";
        str += "<- " + node.data + " ->";
        str += node.right == null ? "\t." : "\t" + node.right.data;

        System.out.println(str);

        display(node.left);
        display(node.right);
    }

    static int size(Node node) {
        if (node == null)
            return 0;
        return size(node.left) + size(node.right) + 1;
    }

    static int height(Node node) {
        if (node == null)
            return 0;

        return Math.max(height(node.left), height(node.right)) + 1;
    }

    static int myMax(Node node) {
        if (node == null)
            return Integer.MIN_VALUE;

        return Math.max(node.data, Math.max(myMax(node.left), myMax(node.right)));
    }

    static int myMin(Node node) {
        if (node == null)
            return Integer.MAX_VALUE;

        return Math.min(node.data, Math.min(myMin(node.left), myMin(node.right)));

    }

    static boolean find(Node node, int data) {
        if (node == null)
            return false;

        if (node.data == data)
            return true;

        return find(node.left, data) || find(node.right, data);
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~TRAVERSAL~~~~~~~~~~~~~~~~~~~~~~~~

    static void preOrder(Node node) {
        if (node == null)
            return;

        System.out.print(node.data + " ");
        preOrder(node.left);
        preOrder(node.right);
    }

    static void postOrder(Node node) {
        if (node == null)
            return;

        postOrder(node.left);
        postOrder(node.right);
        System.out.print(node.data + " ");
    }

    static void inOrder(Node node) {
        if (node == null)
            return;

        inOrder(node.left);
        System.out.print(node.data + " ");
        inOrder(node.right);
    }

    static ArrayList<Node> nodeToRootPath(Node node, int val) {
        if (node == null)
            return null;

        if (node.data == val) {
            ArrayList<Node> base = new ArrayList<>();
            base.add(node);
            return base;
        }

        ArrayList<Node> lres = nodeToRootPath(node.left, val);
        if (lres != null) {
            lres.add(node);
            return lres;
        }
        ArrayList<Node> rres = nodeToRootPath(node.right, val);
        if (rres != null) {
            rres.add(node);
            return rres;
        }
        return null;
    }

    // lca - Lowest Common Ancestor

    static int lca(Node node, int val1, int val2) {
        ArrayList<Node> path1 = nodeToRootPath(node, val1);
        ArrayList<Node> path2 = nodeToRootPath(node, val2);

        int lca = -1;

        int i = path1.size() - 1;
        int j = path2.size() - 1;

        while (i >= 0 && j >= 0 && path1.get(i) == path2.get(j)) {
            lca = path1.get(i).data;
            i--;
            j--;
        }
        return lca;
    }

    static Node lcaNode = null;

    static boolean lca2(Node node, int data1, int data2) {
        if (node == null)
            return false;

        boolean selfdone = false;
        if (node.data == data1 || node.data == data2)
            selfdone = true;

        boolean leftdone = lca2(node.left, data1, data2);
        if (lcaNode != null)
            return true;

        boolean rightdone = lca2(node.right, data1, data2);
        if (lcaNode != null)
            return true;

        if ((selfdone && leftdone) || (selfdone && rightdone) || (leftdone && rightdone)) {
            lcaNode = node;
        }

        return leftdone || rightdone || selfdone;
    }

    static void set1(Node node) {

        // ArrayList<Node> path = nodeToRootPath(node, 1000);
        // if(path != null)
        // for(Node n : path) {
        // System.out.print(n.data + " ");
        // }
        // System.out.println();

        // System.out.println(lca(node, 90, 100));

        // lca2(node, 40, 90);
        // System.out.println(lcaNode.data);

    }

    // diameter~~~~~~~~~~~~~~~~~~~~~~
    // o(n ^ 2) approach for diamter
    static int diameter1(Node node) {
        if (node == null)
            return 0;

        int lh = height(node.left);
        int rh = height(node.right);

        int ld = diameter1(node.left);
        int rd = diameter1(node.right);

        return Math.max(lh + rh, Math.max(ld, rd));
    }

    // O(n) approach for diamter using class pair
    static class diaPair {
        int ht;
        int dia;

        diaPair(int ht, int dia) {
            this.ht = ht;
            this.dia = dia;
        }

        diaPair() {

        }
    }

    static diaPair diameter2(Node node) {
        if (node == null)
            return new diaPair(0, 0);

        diaPair lpair = diameter2(node.left);
        diaPair rpair = diameter2(node.right);

        diaPair mpair = new diaPair();
        mpair.ht = Math.max(lpair.ht, rpair.ht) + 1;
        mpair.dia = Math.max(lpair.ht + rpair.ht, Math.max(lpair.dia, rpair.dia));
        return mpair;
    }

    // O(n) approach for diameter without using pair class
    static int dia = 0;

    static int diameter3(Node node) {
        if (node == null)
            return 0;

        int lh = diameter3(node.left);
        int rh = diameter3(node.right);

        dia = Math.max(dia, lh + rh);

        return Math.max(lh, rh) + 1;
    }

    static void diameter(Node node) {
        // System.out.println(diameter1(node));

        // diaPair res = diameter2(node);
        // System.out.println(res.dia);

        dia = 0;
        diameter3(node);
        System.out.println(dia);
    }

    static void solve() {
        int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100, -1, -1, -1, 70, 110, -1, -1, 120, -1,
                -1 };
        Node root = construct(arr);
        // display(root);
        // System.out.println("Height : " + height(root));
        // System.out.println("Minimum : " + myMin(root));
        // System.out.println("Maximum : " + myMax(root));
        // System.out.println("PreOrder : ");
        // preOrder(root);
        // System.out.println("PostOrder : ");
        // postOrder(root);

        // set1(root);
        diameter(root);
    }

    public static void main(String[] args) {
        solve();
    }
}