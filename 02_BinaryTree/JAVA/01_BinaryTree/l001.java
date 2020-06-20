import java.util.*;

public class l001 {
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

    // =========================TRAVERSAL=========================

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

    // diameter=================================================
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

    // levelOrder traversal =================================================
    static void levelOrder01(Node node) {
        // Implement parent queue and child queue - addlast, removeFirst
        LinkedList<Node> queue = new LinkedList<>();

        queue.addLast(node);

        while (queue.size() != 0) {
            // remove and get
            Node rem = queue.removeFirst();
            System.out.print(rem.data + " ");

            // push in child queue
            if (rem.left != null)
                queue.addLast(rem.left);
            if (rem.right != null)
                queue.addLast(rem.right);
        }
    }

    // levelorder linewise using two queueus
    static void levelOrder02(Node node) {
        // Implement parent queue and child queue - addlast, removeFirst
        LinkedList<Node> parent = new LinkedList<>();
        LinkedList<Node> child = new LinkedList<>();

        parent.addLast(node);
        int level = 0;

        System.out.print("level " + level + " -> ");
        while (parent.size() != 0) {
            // remove and get
            Node rem = parent.removeFirst();
            System.out.print(rem.data + " ");

            // push in child queue
            if (rem.left != null)
                child.addLast(rem.left);
            if (rem.right != null)
                child.addLast(rem.right);

            if (parent.size() == 0) {
                System.out.println();
                level++;
                if (child.size() != 0)
                    System.out.print("level " + level + " -> ");

                // swap parent and child
                LinkedList<Node> temp = null;
                temp = parent;
                parent = child;
                child = temp;
            }
        }
    }

    // levelorder linewise using sinle queue (null concept)
    static void levelOrder03(Node node) {
        LinkedList<Node> queue = new LinkedList<>();
        queue.addLast(node);
        queue.add(null);

        int level = 0;
        System.out.print("level : " + level + " -> ");

        while (queue.size() != 1) {
            Node rem = queue.removeFirst();
            System.out.print(rem.data + " ");
            if (rem.left != null)
                queue.addLast(rem.left);
            if (rem.right != null)
                queue.addLast(rem.right);

            if (queue.getFirst() == null) {
                queue.removeFirst();
                queue.addLast(null);
                level++;
                if (queue.size() != 1)
                    System.out.print("\nlevel : " + level + " -> ");
            }
        }
    }

    // levelorder linewise without even using null
    static void levelOrder04(Node node) {
        LinkedList<Node> queue = new LinkedList<>();

        queue.addLast(node);
        int level = 0;
        while (queue.size() != 0) {
            System.out.print("level : " + level + " -> ");
            level++;
            int size = queue.size();

            while (size-- > 0) {
                Node rem = queue.removeFirst();
                System.out.print(rem.data + " ");
                if (rem.left != null)
                    queue.addLast(rem.left);
                if (rem.right != null)
                    queue.addLast(rem.right);
            }
            System.out.println();
        }
    }

    static void levelOrder(Node node) {
        // levelOrder01(node);
        // levelOrder02(node);
        // levelOrder03(node);
        // levelOrder04(node);
    }

    // view=================================================

    static void leftView(Node node) {
        LinkedList<Node> queue = new LinkedList<>();

        queue.addLast(node);

        while (queue.size() != 0) {
            int size = queue.size();
            System.out.println(queue.getFirst().data);

            while (size-- > 0) {
                Node rem = queue.removeFirst();
                if (rem.left != null)
                    queue.addLast(rem.left);
                if (rem.right != null)
                    queue.addLast(rem.right);
            }
        }
    }

    static void rightView(Node node) {
        LinkedList<Node> queue = new LinkedList<>();

        queue.addLast(node);

        while (queue.size() != 0) {
            int size = queue.size();
            Node prev = null;
            while (size-- > 0) {
                Node rem = queue.removeFirst();
                prev = rem;

                if (rem.left != null)
                    queue.addLast(rem.left);
                if (rem.right != null)
                    queue.addLast(rem.right);
            }
            System.out.println(prev.data);
        }
    }

    static int leftmin = 0;
    static int rightmax = 0;

    static void width(Node node, int level) {
        if (node == null)
            return;

        leftmin = Math.min(leftmin, level);
        rightmax = Math.max(rightmax, level);

        width(node.left, level - 1);
        width(node.right, level + 1);
    }

    static class voPair {
        Node node;
        int idx;

        voPair(Node node, int idx) {
            this.node = node;
            this.idx = idx;
        }
    }

    static void verticalOrder(Node node) {
        // make leftmin and rightmax using width function
        width(node, 0);
        // make array
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();
        int n = rightmax - leftmin + 1;
        for (int i = 0; i < n; i++) {
            ans.add(new ArrayList<>());
        }
        // now apply levelOrder (OR BFS)

        LinkedList<voPair> queue = new LinkedList<>();
        queue.addLast(new voPair(node, -leftmin));

        while (queue.size() != 0) {
            int size = queue.size();
            while (size-- > 0) {
                voPair rem = queue.removeFirst();
                ans.get(rem.idx).add(rem.node.data);
                if (rem.node.left != null) {
                    queue.addLast(new voPair(rem.node.left, rem.idx - 1));
                }
                if (rem.node.right != null) {
                    queue.addLast(new voPair(rem.node.right, rem.idx + 1));
                }
            }
        }

        for (int i = 0; i < ans.size(); i++) {
            ArrayList<Integer> list = ans.get(i);
            System.out.print(i + " -> ");
            for (int val : list) {
                System.out.print(val + ", ");
            }
            System.out.println();
        }
    }

    static void verticalOrderSum(Node node) {
        // make leftmin and rightmax using width function
        width(node, 0);
        // make array
        int n = rightmax - leftmin + 1;
        int[] ans = new int[n];
        // now apply levelOrder (OR BFS)

        LinkedList<voPair> queue = new LinkedList<>();
        queue.addLast(new voPair(node, -leftmin));

        while (queue.size() != 0) {
            int size = queue.size();
            while (size-- > 0) {
                voPair rem = queue.removeFirst();
                ans[rem.idx] = ans[rem.idx] + rem.node.data;
                if (rem.node.left != null) {
                    queue.addLast(new voPair(rem.node.left, rem.idx - 1));
                }
                if (rem.node.right != null) {
                    queue.addLast(new voPair(rem.node.right, rem.idx + 1));
                }
            }
        }

        for (int i = 0; i < ans.length; i++) {
            System.out.println(i + " -> " + ans[i]);
        }
    }

    static void bottomView(Node node) {
        leftmin = rightmax = 0;
        width(node, 0);

        int[] ans = new int[rightmax - leftmin + 1];

        LinkedList<voPair> queue = new LinkedList<>();
        queue.addLast(new voPair(node, -leftmin));

        while (queue.size() != 0) {
            int size = queue.size();

            while (size-- > 0) {
                voPair rem = queue.removeFirst();
                ans[rem.idx] = rem.node.data;
                if (rem.node.left != null)
                    queue.addLast(new voPair(rem.node.left, rem.idx - 1));
                if (rem.node.right != null)
                    queue.addLast(new voPair(rem.node.right, rem.idx + 1));
            }
        }

        for (int val : ans)
            System.out.print(val + " ");
    }

    static void topView(Node node) {
        leftmin = rightmax = 0;
        width(node, 0);

        int[] ans = new int[rightmax - leftmin + 1];
        // mark the empty array with some number, suppose it is -infinity
        Arrays.fill(ans, Integer.MIN_VALUE);

        LinkedList<voPair> queue = new LinkedList<>();
        queue.addLast(new voPair(node, -leftmin));

        while (queue.size() != 0) {
            int size = queue.size();

            while (size-- > 0) {
                voPair rem = queue.removeFirst();
                if (ans[rem.idx] == Integer.MIN_VALUE)
                    ans[rem.idx] = rem.node.data;

                if (rem.node.left != null)
                    queue.addLast(new voPair(rem.node.left, rem.idx - 1));
                if (rem.node.right != null)
                    queue.addLast(new voPair(rem.node.right, rem.idx + 1));
            }
        }

        for (int val : ans)
            System.out.print(val + " ");
    }

    static int leftDmin = 0;

    static void diagonalWidth(Node node, int l) {
        if (node == null)
            return;

        leftDmin = Math.min(leftDmin, l);

        diagonalWidth(node.left, l - 1);
        diagonalWidth(node.right, l);
    }

    static void diagonalView(Node node) {
        diagonalWidth(node, 0);
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();
        int n = -leftDmin;
        for (int i = 0; i <= n; i++) {
            ans.add(new ArrayList<>());
        }

        LinkedList<voPair> queue = new LinkedList<>(); // addLast, removeFirst
        queue.addLast(new voPair(node, 0));

        while (queue.size() > 0) {
            int size = queue.size();

            while (size-- > 0) {
                voPair rem = queue.removeFirst();
                ans.get(rem.idx).add(rem.node.data);

                if (rem.node.left != null)
                    queue.addLast(new voPair(rem.node.left, rem.idx + 1));
                if (rem.node.right != null)
                    queue.addLast(new voPair(rem.node.right, rem.idx));

            }
        }

        for(ArrayList<Integer> arr : ans) {
            System.out.println(arr);
        }
    }

    static void diagonalSum(Node node) {
        diagonalWidth(node, 0);
        int n = -leftDmin;
        int[] ans = new int[n + 1];

        LinkedList<voPair> queue = new LinkedList<>(); // addLast, removeFirst
        queue.addLast(new voPair(node, 0));

        while (queue.size() > 0) {
            int size = queue.size();

            while (size-- > 0) {
                voPair rem = queue.removeFirst();
                ans[rem.idx] += rem.node.data;

                if (rem.node.left != null)
                    queue.addLast(new voPair(rem.node.left, rem.idx + 1));
                if (rem.node.right != null)
                    queue.addLast(new voPair(rem.node.right, rem.idx));

            }
        }

        for(int val : ans) {
            System.out.println(val);
        }
    }

    static void view(Node node) {
        // leftView(node);
        // rightView(node);
        // verticalOrder(node);
        // verticalOrderSum(node);
        // display(node);
        // bottomView(node);
        // topView(node);
        diagonalView(node);
        diagonalSum(node);
    }

    // Iterative Traversal=================================================
    static class TPair {
        Node node = null;
        boolean self;
        boolean left;
        boolean right;

        TPair(Node node) {
            this.node = node;
            self = left = right = false;
        }
    }

    static void Itr_PreOrder(Node node) {
        Stack<TPair> st = new Stack<>();
        st.push(new TPair(node));

        while (st.size() != 0) {
            TPair top = st.peek();
            if (top.self == false) {
                top.self = true;
                System.out.print(top.node.data + " ");
            } else if (top.left == false) {
                top.left = true;
                if (top.node.left != null) {
                    st.push(new TPair(top.node.left));
                }
            } else if (top.right == false) {
                top.right = true;
                if (top.node.right != null) {
                    st.push(new TPair(top.node.right));
                }
            } else {
                st.pop();
            }
        }
        System.out.println();
    }

    static void Itr_InOrder(Node node) {
        Stack<TPair> st = new Stack<>();
        st.push(new TPair(node));

        while (st.size() != 0) {
            TPair top = st.peek();
            if (top.left == false) {
                top.left = true;
                if (top.node.left != null) {
                    st.push(new TPair(top.node.left));
                }
            } else if (top.self == false) {
                top.self = true;
                System.out.print(top.node.data + " ");
            } else if (top.right == false) {
                top.right = true;
                if (top.node.right != null) {
                    st.push(new TPair(top.node.right));
                }
            } else {
                st.pop();
            }
        }
        System.out.println();
    }

    static void Itr_PostOrder(Node node) {
        Stack<TPair> st = new Stack<>();
        st.push(new TPair(node));

        while (st.size() != 0) {
            TPair top = st.peek();
            if (top.left == false) {
                top.left = true;
                if (top.node.left != null) {
                    st.push(new TPair(top.node.left));
                }
            } else if (top.right == false) {
                top.right = true;
                if (top.node.right != null) {
                    st.push(new TPair(top.node.right));
                }
            } else if (top.self == false) {
                top.self = true;
                System.out.print(top.node.data + " ");
            } else {
                st.pop();
            }
        }
        System.out.println();
    }

    static void ItrTraversal(Node node) {
        Itr_PreOrder(node);
        // Itr_InOrder(node);
        // Itr_PostOrder(node);
    }

    // Morris
    // Traversal=================================================
    static Node rightMost_of_leftNode(Node lnode, Node curr) {
        while (lnode.right != null && lnode.right != curr) {
            lnode = lnode.right;
        }
        return lnode;
    }

    static void Morris_InOrder(Node node) {
        Node curr = node;
        while (curr != null) {
            if (curr.left == null) {
                System.out.print(curr.data + " ");
                curr = curr.right;
            } else {
                Node lnode = curr.left;
                Node rightMost = rightMost_of_leftNode(lnode, curr);
                if (rightMost.right == null) { // make a thread
                    rightMost.right = curr;
                    curr = curr.left;
                } else { // break a thread
                    rightMost.right = null;
                    System.out.print(curr.data + " ");
                    curr = curr.right;
                }
            }
        }
        System.out.println();
    }

    static void Morris_PreOrder(Node node) {
        Node curr = node;
        while (curr != null) {
            if (curr.left == null) {
                System.out.print(curr.data + " ");
                curr = curr.right;
            } else {
                Node lnode = curr.left;
                Node rightMost = rightMost_of_leftNode(lnode, curr);
                if (rightMost.right == null) { // make a thread
                    rightMost.right = curr;
                    System.out.print(curr.data + " ");
                    curr = curr.left;
                } else { // break a thread
                    rightMost.right = null;
                    curr = curr.right;
                }
            }
        }
        System.out.println();
    }

    static void morris(Node node) {
        // Morris_InOrder(node);
        Morris_PreOrder(node);
    }

    static void solve() {
        // int[] arr = { 10, 20, 40, -1, -1, 50, 80, -1, -1, 90, -1, -1, 30, 60, 100,
        // -1, -1, -1, 70, 110, -1, -1, 120, -1,
        // -1 };

        int[] arr = { 11, 6, 4, -1, 5, -1, -1, 8, -1, 10, -1, -1, 19, 17, -1, -1, 43, 30, -1, -1, 49, -1, -1 };
        Node root = construct(arr);
        display(root);
        // System.out.println("Height : " + height(root));
        // System.out.println("Minimum : " + myMin(root));
        // System.out.println("Maximum : " + myMax(root));
        // System.out.println("PreOrder : ");
        // preOrder(root);
        // System.out.println("PostOrder : ");
        // postOrder(root);

        // set1(root);
        // diameter(root);

        // levelOrder(root);

        view(root);
        // ItrTraversal(root);
        // morris(root);

    }

    public static void main(String[] args) {
        solve();
    }
}
