import java.util.*;

public class questions {
    public static void main(String[] args) {

    }

    // DATE : 20th June 2020=========================================
    // Leetcode 84. Largest Rectangle in Histogram===================
    public int largestRectangleArea(int[] hts) {
        int n = hts.length;
        Stack<Integer> st = new Stack<>();
        int res = 0;
        st.push(-1);

        for (int i = 0; i < n; i++) {
            while (st.peek() != -1 && hts[st.peek()] >= hts[i]) {
                int ht = hts[st.pop()];
                int area = ht * (i - st.peek() - 1);
                res = Math.max(res, area);
            }
            st.push(i);
        }

        while (st.peek() != -1) {
            int ht = hts[st.pop()];
            int area = ht * (n - st.peek() - 1);
            res = Math.max(res, area);
        }
        return res;
    }

    // Leetcode 85. Maximal Rectangle================================
    public int maximalRectangle(char[][] matrix) {
        if (matrix.length == 0 || matrix[0].length == 0)
            return 0;

        // make a dummy array to iterate every time on largest area histogram
        int[] hts = new int[matrix[0].length];
        int res = 0;

        for (int r = 0; r < matrix.length; r++) {
            for (int c = 0; c < matrix[0].length; c++) {
                int ch = matrix[r][c] - '0';
                if (ch == 0)
                    hts[c] = 0;
                else
                    hts[c] += ch;
            }
            // call to largest rectangle area
            res = Math.max(res, largestRectangleArea(hts));
        }

        return res;
    }

    // Leetcode 42. Trapping Rain Water=================================

    // In O(1) space
    public int trap_01(int[] arr) {
        if (arr.length == 0)
            return 0;
        int lmax = arr[0];
        int lmi = 0;
        int len = arr.length;

        int temp = 0;
        int water = 0;

        for (int i = 1; i < len; i++) {
            if (arr[i] >= lmax) {
                lmax = arr[i];
                lmi = i;
                temp = 0;
            } else {
                water += (lmax - arr[i]);
                temp += (lmax - arr[i]);
            }
        }
        if (lmi < len - 1) {
            water -= temp;
            int rmax = arr[len - 1];
            for (int i = len - 1; i >= lmi; i--) {
                if (arr[i] >= rmax) {
                    rmax = arr[i];
                } else {
                    water += (rmax - arr[i]);
                }
            }
        }
        return water;
    }

    // In O(n) space
    public int trap_02(int[] ht) {
        int n = ht.length;
        if (n == 0)
            return 0;
        int water = 0;

        int[] lg = new int[n]; // left greater
        int[] rg = new int[n];

        // set left greater element
        lg[0] = ht[0];
        for (int i = 0; i < n; i++) {
            lg[i] = Math.max(lg[i - 1], ht[i]);
        }

        // set right greater element
        rg[n - 1] = ht[n - 1];
        for (int i = n - 1; i >= 0; i--) {
            rg[i] = Math.max(rg[i + 1], ht[i]);
        }

        for (int i = 0; i < n; i++) {
            water += Math.min(lg[i], rg[i]) - ht[i];
        }
        return water;
    }

    // Rain water using stack
    public int trap_03(int[] hts) {
        if (hts.length == 0)
            return 0;

        int water = 0;

        return water;
    }

    // two pointer approach
    public int trap(int[] hts) {
        if (hts.length == 0)
            return 0;

        int li = 0;
        int lmax = hts[li];
        int ri = hts.length - 1;
        int rmax = hts[ri];

        int water = 0;

        while (ri >= li) {
            if (lmax > rmax) {
                rmax = Math.max(rmax, hts[ri]);
                water += rmax - hts[ri];
                ri--;
            } else {
                lmax = Math.max(lmax, hts[li]);
                water += lmax - hts[li];
                li++;
            }
        }

        return water;
    }

    // Leetcode 155. Min Stack==========================================
    // using single stack
    class MinStack {

        /** initialize your data structure here. */
        private Stack<Long> st = null;
        private int msf;

        public MinStack() {
            st = new Stack<>();
            msf = 0;
        }

        public void push(int x) {
            Long val = (long) x;
            if (st.size() == 0) {
                st.push(val);
                msf = x;
            } else if (msf <= val) {
                st.push(val);
            } else {
                st.push(val + val - msf);
                msf = x;
            }
        }

        public void pop() {
            if (st.peek() >= msf) {
                st.pop();
            } else {
                msf = (2 * msf) - (int) (long) st.peek();
                st.pop();
            }
        }

        public int top() {
            if (st.peek() >= msf) {
                return (int) (long) st.peek();
            } else {
                return msf;
            }
        }

        public int getMin() {
            return msf;
        }
    }

    // Leetcode 921. Minimum Add to Make Parentheses Valid==============
    public int minAddToMakeValid(String S) {
        Stack<Character> st = new Stack<>();

        for (int i = 0; i < S.length(); i++) {
            if (S.charAt(i) == '(') {
                st.push(S.charAt(i));
            } else if (S.charAt(i) == ')' && !st.empty() && st.peek() == '(') {
                st.pop();
            } else {
                st.push(S.charAt(i));
            }
        }
        return st.size();
    }

    // Leetcode 1249. Minimum Remove to Make Valid Parentheses============
    public String minRemoveToMakeValid(String str) {
        int n = str.length();
        boolean[] marked = new boolean[n];

        Stack<Integer> st = new Stack<>();
        st.push(-1);

        for (int i = 0; i < n; i++) {
            if (st.peek() != -1 && str.charAt(i) == ')' && str.charAt(st.peek()) == '(') {
                int val = st.peek();
                st.pop();
                marked[i] = marked[val] = true;
            } else if (str.charAt(i) == '(') {
                st.push(i);
            } else if (str.charAt(i) != ')') {
                marked[i] = true;
            }
        }
        String ans = "";
        for (int i = 0; i < n; i++) {
            if (marked[i]) {
                ans += str.charAt(i);
            }
        }
        return ans;
    }

    // Leetcode 402. Remove K Digits=============================
    public String removeKdigits(String num, int k) {
        if (num.length() == 0)
            return "0";

        Stack<Character> st = new Stack<>();

        for (int i = 0; i < num.length(); i++) {
            char ch = num.charAt(i);
            while (!st.isEmpty() && st.peek() > ch && k > 0) {
                st.pop();
                k--;
            }
            st.push(ch);
        }

        while (k-- > 0) {
            st.pop();
        }

        String revans = "";

        while (!st.isEmpty())
            revans += st.pop();

        while (revans.length() != 0) {
            if (revans.charAt(revans.length() - 1) != '0')
                break;
            revans = revans.substring(0, revans.length() - 1);
        }

        String ans = "";

        for (int i = revans.length() - 1; i >= 0; i--) {
            ans += revans.charAt(i);
        }

        return ans.length() != 0 ? ans : "0";
    }
}