import java.util.*;

public class l002 {
    static class Node {
        int data;
        Node left = null;
        Node right = null;

        Node(int data) {
            this.data = data;
        }
    };

    static Node constructBST(int[] arr, int lo, int hi) {
        if (lo > hi)
            return null;

        int mid = (lo + hi) / 2;
        Node node = new Node(arr[mid]);
        node.left = constructBST(arr, lo, mid - 1);
        node.right = constructBST(arr, mid + 1, hi);

        return node;
    }

    static void display(Node node) {
        if (node == null)
            return;

        String str = "";
        str += node.left == null ? ".\t" : node.left.data + "\t";
        str += "<- " + node.data + " .";
        str += node.right == null ? "\t." : "\t" + node.right.data;

        System.out.println(str);

        display(node.left);
        display(node.right);
    }

    // Basic~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    static int height(Node node) {
        if (node == null)
            return 0;
        return Math.max(height(node.left), height(node.right)) + 1;
    }

    static int size(Node node) {
        if (node == null)
            return 0;

        return size(node.left) + size(node.right) + 1;
    }

    static boolean find(Node node, int data) {
        Node curr = node;
        while (curr != null) {
            if (curr.data == data)
                return true;
            else if (curr.data > data)
                curr = curr.left;
            else
                curr = curr.right;
        }
        return false;
    }

    static int min(Node node) {
        Node curr = node;

        while (curr.left != null)
            curr = curr.left;

        return curr.data;
    }

    static int max(Node node) {
        Node curr = node;

        while (curr.right != null)
            curr = curr.right;

        return curr.data;
    }

    static void basic(Node node) {
        display(node);
        // System.out.println("Find (75) : " + find(node, 75));
    }

    // return the data in range of a, b
    static void dataInRange_01(Node node, int a, int b, int[] ans) {
        if (node == null)
            return;

        dataInRange_01(node.left, a, b, ans);
        if (node.data >= a && node.data <= b) {
        }
        dataInRange_01(node.right, a, b, ans);
    }

    // oroot = original root
    static void targetSumPair_1(Node node, Node oroot, int target) {
        if (node == null)
            return;

        int val1 = node.data;
        int val2 = target - val1;

        if (val1 > val2 && find(oroot, val2) == true)
            System.out.println(val1 + " + " + val2 + " = " + (val1 + val2));

        targetSumPair_1(node.left, oroot, target);
        targetSumPair_1(node.right, oroot, target);
    }

    static void targetSumPair_2(Node node, int target) {
        // make a helper function of INORDER Traversal(In Inorder it is sorted array)
        // make two pointer and implement it for target sum
    }

    // target sum pair using two Stack
    static void insert_left_most(Node node, Stack<Node> st) {
        while (node != null) {
            st.push(node);
            node = node.left;
        }
    }

    static void insert_right_most(Node node, Stack<Node> st) {
        while (node != null) {
            st.push(node);
            node = node.right;
        }
    }

    static void targetSumPair_3(Node node, int target) {
        Stack<Node> left = new Stack<>();
        Stack<Node> right = new Stack<>();

        insert_left_most(node, left);
        insert_right_most(node, right);

        while (left.size() != 0 && right.size() != 0) {
            int val1 = left.peek().data;
            int val2 = right.peek().data;

            if (val1 >= val2) {
                left.pop();
                right.pop();
            } else if (val1 + val2 < target) {
                Node rem = left.peek();
                left.pop();
                insert_left_most(rem.right, left);
            } else if (val1 + val2 > target) {
                Node rem = right.peek();
                right.pop();
                insert_right_most(rem.left, right);
            } else {
                System.out.println(val1 + " + " + val2 + " = " + (val1 + val2));
                insert_left_most(left.peek().right, left);
                insert_right_most(right.peek().left, right);
                left.pop();
                right.pop();
            }
        }
    }

    static void targetSumPair(Node node) {
        int target = 100;
        targetSumPair_1(node, node, target);
        System.out.println("\n");
        targetSumPair_3(node, target);
    }

    static void solve() {
        int[] arr = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110 };
        Node root = constructBST(arr, 0, arr.length - 1);
        basic(root);
        // targetSumPair(root);
    }

    public static void main(String[] args) {
        solve();
    }
}