import java.util.*;

public class questions {

    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }

    }

    public class Node {
        int data;
        Node left;
        Node right;

        Node(int data) {
            this.data = data;
        }
    }

    // Leetcode = 863 k away from
    // node~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    private ArrayList<TreeNode> nodeToRootPath(TreeNode node, int data) {
        if (node == null)
            return null;

        if (node.val == data) {
            ArrayList<TreeNode> mres = new ArrayList<>();
            mres.add(node);
            return mres;
        }

        ArrayList<TreeNode> lres = nodeToRootPath(node.left, data);
        if (lres != null) {
            lres.add(node);
            return lres;
        }

        ArrayList<TreeNode> rres = nodeToRootPath(node.right, data);
        if (rres != null) {
            rres.add(node);
            return rres;
        }

        return null;
    }

    private void kdown(TreeNode node, TreeNode blocked, int k, List<Integer> ans) {
        if (node == null || node == blocked)
            return;

        if (k == 0) {
            ans.add(node.val);
            return;
        }

        kdown(node.left, blocked, k - 1, ans);
        kdown(node.right, blocked, k - 1, ans);
    }

    public List<Integer> distanceK(TreeNode root, TreeNode target, int k) {
        ArrayList<TreeNode> n2rp = nodeToRootPath(root, target.val);

        ArrayList<Integer> ans = new ArrayList<>();
        TreeNode block = null;
        for (int i = 0; i < n2rp.size() && k >= 0; i++) {
            kdown(n2rp.get(i), block, k, ans);
            block = n2rp.get(i);
            k--;
        }
        return ans;
    }

    // K distance with space o(1)
    public int distanceK_O1(TreeNode node, List<Integer> ans, TreeNode targ, int k) {
        if (node == null)
            return -1;
        if (node == targ) {
            kdown(node, null, k, ans);
            return 1;
        }

        int lres = distanceK_O1(node.left, ans, targ, k);
        if (lres != -1 && k - lres >= 0) {
            kdown(node, node.left, k - lres, ans);
            return lres + 1;
        }

        int rres = distanceK_O1(node.right, ans, targ, k);
        if (rres != -1 && k - rres >= 0) {
            kdown(node, node.right, k - rres, ans);
            return rres + 1;
        }

        return -1;
    }

    // Leetcode = 236 Lowest Common
    // Ancestor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    public ArrayList<TreeNode> nodeToRootPath(TreeNode node, TreeNode val) {
        if (node == null)
            return null;

        if (node == val) {
            ArrayList<TreeNode> base = new ArrayList<>();
            base.add(node);
            return base;
        }

        ArrayList<TreeNode> lres = nodeToRootPath(node.left, val);
        if (lres != null) {
            lres.add(node);
            return lres;
        }
        ArrayList<TreeNode> rres = nodeToRootPath(node.right, val);
        if (rres != null) {
            rres.add(node);
            return rres;
        }
        return null;
    }

    public TreeNode lowestCommonAncestor(TreeNode node, TreeNode p, TreeNode q) {
        ArrayList<TreeNode> path1 = nodeToRootPath(node, p);
        ArrayList<TreeNode> path2 = nodeToRootPath(node, q);

        TreeNode lcaNode = null;

        int i = path1.size() - 1;
        int j = path2.size() - 1;

        while (i >= 0 && j >= 0 && path1.get(i) == path2.get(j)) {
            lcaNode = path1.get(i);
            i--;
            j--;
        }
        return lcaNode;
    }

    // LCA in O(1) space
    private TreeNode lcaNode = null;

    public boolean lca2(TreeNode node, int data1, int data2) {
        if (node == null)
            return false;

        boolean selfdone = false;
        if (node.val == data1 || node.val == data2)
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

    // Leetcode = 543
    // diamater~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // o(n ^ 2) approach for diamter
    public int height(TreeNode node) {
        if (node == null)
            return 0;

        int lh = height(node.left);
        int rh = height(node.right);

        return Math.max(lh, rh) + 1;
    }

    public int diameter1(TreeNode node) {
        if (node == null)
            return 0;

        int lh = height(node.left);
        int rh = height(node.right);

        int ld = diameter1(node.left);
        int rd = diameter1(node.right);

        return Math.max(lh + rh, Math.max(ld, rd));
    }

    // O(n) approach for diamter using class pair
    public class diaPair {
        int ht;
        int dia;

        diaPair(int ht, int dia) {
            this.ht = ht;
            this.dia = dia;
        }

        diaPair() {

        }
    }

    public diaPair diameter2(TreeNode node) {
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
    public int dia = 0;

    public int diameter3(TreeNode node) {
        if (node == null)
            return 0;

        int lh = diameter3(node.left);
        int rh = diameter3(node.right);

        dia = Math.max(dia, lh + rh);

        return Math.max(lh, rh) + 1;
    }

    // Leetcode - 112
    // HasPathSum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    private boolean hasPathSum_(TreeNode root, int sum) {
        if (root == null) {
            return false;
        }

        if (root.left == null && root.right == null && sum - root.val == 0) {
            return true;
        }

        boolean rres = hasPathSum_(root.left, sum - root.val);

        rres = rres || hasPathSum_(root.right, sum - root.val);

        return rres;
    }

    public boolean hasPathSum(TreeNode root, int sum) {
        if (root == null) {
            return false;
        }

        return hasPathSum_(root, sum);
    }

    // Leetcode - 113
    // PathSum~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    private List<List<Integer>> res = new ArrayList<>();

    private void pathSum(TreeNode root, List<Integer> sans, int sum) {
        if (root == null) {
            return;
        }
        if (root.left == null && root.right == null && sum - root.val == 0) {
            List<Integer> base = new ArrayList<>(sans);
            base.add(root.val);
            res.add(base);
        }

        sans.add(root.val);
        pathSum(root.left, sans, sum - root.val);
        pathSum(root.right, sans, sum - root.val);
        sans.remove(sans.size() - 1);
    }

    public List<List<Integer>> pathSum(TreeNode root, int sum) {
        List<Integer> sans = new ArrayList<>();
        pathSum(root, sans, sum);
        return res;
    }

    // GeeksforGeeks - Max Path Sum
    // Link - https://practice.geeksforgeeks.org/problems/maximum-path-sum/1
    private static int ans = 0;

    private static int leaf2leaf(Node node) {
        if (node == null)
            return 0;

        int leftans = leaf2leaf(node.left);
        int rightans = leaf2leaf(node.right);

        if (node.left != null && node.right != null) {
            ans = Math.max(ans, leftans + rightans + node.data);
            return Math.max(leftans, rightans) + node.data;
        }

        return (node.left == null ? rightans : leftans) + node.data;

    }

    public static int maxPathSumGeeks(Node root) {
        ans = (int) -1e8;
        leaf2leaf(root);
        return ans;
    }

    // leetcode - 124
    // MaximumPathSum(any node to any node)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Leetcode 124.========================================================

    int max_nodeToNodeSum = (int) -1e8;

    public int maxPathSum_(TreeNode node) {
        if (node == null)
            return 0;

        int leftNodeToNodeSum = maxPathSum_(node.left);
        int rightNodeToNodeSum = maxPathSum_(node.right);

        int max_ = Math.max(leftNodeToNodeSum, rightNodeToNodeSum) + node.val;
        max_nodeToNodeSum = Math.max(Math.max(max_nodeToNodeSum, node.val),
                Math.max(leftNodeToNodeSum + node.val + rightNodeToNodeSum, max_));

        return Math.max(max_, node.val);
    }

    public int maxPathSum(TreeNode root) {
        maxPathSum_(root);
        return max_nodeToNodeSum;
    }

    // Leetcode 173 BST Iterator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class BSTIterator {

        private Stack<TreeNode> st = null;

        public BSTIterator(TreeNode root) {
            st = new Stack<>();
            push_All_left_of_right(root);
        }

        private void push_All_left_of_right(TreeNode node) {
            while (node != null) {
                st.push(node);
                node = node.left;
            }
        }

        public int next() {
            TreeNode rem = st.pop();
            push_All_left_of_right(rem.right);
            return rem.val;
        }

        public boolean hasNext() {
            return st.size() != 0;
        }
    }

    // Leetcode 105 Construct Binary Tree from Preorder and Inorder
    // Traversal~~~~~~~~~~~~~
    private TreeNode construction_PreIn(int[] pre, int pst, int pend, int[] in, int ist, int iend) {
        if (pst > pend || ist > iend)
            return null;

        TreeNode node = new TreeNode(pre[pst]);

        // find root node in INORDER
        int idx = ist;
        while (in[idx] != pre[pst])
            idx++;

        // total element
        int tele = idx - ist;
        node.left = construction_PreIn(pre, pst + 1, pst + tele, in, ist, idx - 1);
        node.right = construction_PreIn(pre, pst + tele + 1, pend, in, idx + 1, iend);

        return node;
    }

    public TreeNode buildTree_(int[] pre, int[] in) {
        return construction_PreIn(pre, 0, pre.length - 1, in, 0, in.length - 1);
    }

    // Leetcode 106 Construct Binary Tree from Inorder and Postorder Traversal
    // ~~~~~~~~~~~~~~~~
    private TreeNode construction_PostIn(int[] post, int pst, int pend, int[] in, int ist, int iend) {
        if (ist > iend || pst > pend)
            return null;

        TreeNode node = new TreeNode(post[pend]);

        int idx = ist;
        while (in[idx] != post[pend])
            idx++;

        int tele = idx - ist;
        node.left = construction_PostIn(post, pst, pst + tele - 1, in, ist, idx - 1);
        node.right = construction_PostIn(post, pst + tele, pend - 1, in, idx + 1, iend);

        return node;
    }

    public TreeNode buildTree_1(int[] in, int[] post) {
        return construction_PostIn(post, 0, post.length - 1, in, 0, in.length - 1);
    }

    // Leetcode 889 Construct Binary Tree from Preorder and Postorder
    // Traversal~~~~~~~~~~~
    private TreeNode construction_PrePost(int[] pre, int prest, int prend, int[] po, int post, int poend) {
        if (prest > prend || post > poend)
            return null;

        TreeNode node = new TreeNode(pre[prest]);

        if (prest == prend) {
            return node;
        }

        int indx = post;
        while (po[indx] != pre[prest + 1])
            indx++;

        int tele = indx - post + 1;

        node.left = construction_PrePost(pre, prest + 1, prest + tele, po, post, indx);
        node.right = construction_PrePost(pre, prest + tele + 1, prend, po, indx + 1, poend - 1);

        return node;
    }

    public TreeNode constructFromPrePost(int[] pre, int[] post) {
        return construction_PrePost(pre, 0, pre.length - 1, post, 0, post.length - 1);
    }

    // https://practice.geeksforgeeks.org/problems/construct-tree-from-inorder-and-levelorder/1
    // construction from levelorder Inorder
    Node construction_InLevel(ArrayList<Integer> level, int[] in, int ist, int iend) {
        if (ist > iend)
            return null;

        Node node = new Node(level.get(0));

        if (level.size() == 1)
            return node;

        int indx = ist;
        while (in[indx] != level.get(0))
            indx++;

        ArrayList<Integer> llevel = new ArrayList<>(); // left level
        ArrayList<Integer> rlevel = new ArrayList<>(); // right level

        HashSet<Integer> set = new HashSet<>();
        for (int i = ist; i < indx; i++)
            set.add(in[i]);

        for (int i = 1; i < level.size(); i++) {
            if (set.contains(level.get(i)) == true) { // if present then add in llevel
                llevel.add(level.get(i));
            } else { // otherwise, add in rlevel
                rlevel.add(level.get(i));
            }
        }

        node.left = construction_InLevel(llevel, in, ist, indx - 1);
        node.right = construction_InLevel(rlevel, in, indx + 1, iend);

        return node;
    }

    Node buildTree(int inord[], int l[]) {
        ArrayList<Integer> level = new ArrayList<>();

        for (int val : l)
            level.add(val);

        return construction_InLevel(level, inord, 0, inord.length - 1);
    }
}
