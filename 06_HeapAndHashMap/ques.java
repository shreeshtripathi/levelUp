import java.util.*;
import java.util.Map.Entry;

public class ques {
    // Leetcode 378. Kth Smallest Element in a Sorted Matrix==========
    int kthSmallest(int[][] matrix, int k) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            return matrix[a[0]][a[1]] - matrix[b[0]][b[1]];
        });

        // in array==========
        // 0th index is row
        // 1st index is col
        for (int i = 0; i < matrix.length; i++) {
            pq.add(new int[] { i, 0 });
        }

        for (int i = 0; i < k - 1; i++) {
            int[] rem = pq.remove();

            int r = rem[0];
            int c = rem[1];

            if (c < matrix[0].length - 1)
                pq.add(new int[] { r, c + 1 });
        }
        return matrix[pq.peek()[0]][pq.peek()[1]];
    }

    // leetcode 786. K-th Smallest Prime Fraction=============
    public int[] kthSmallestPrimeFraction(int[] arr, int K) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            return (arr[a[0]] * arr[b[1]]) - (arr[a[1]] * arr[b[0]]);
        });

        int n = arr.length;
        for (int i = 1; i < n; i++)
            pq.add(new int[] { 0, i });

        for (int i = 1; i < K; i++) {
            int r = pq.peek()[0];
            int c = pq.peek()[1];

            pq.remove();

            if (r + 1 < c) {
                pq.add(new int[] { r + 1, c });
            }
        }

        int r = pq.peek()[0];
        int c = pq.peek()[1];
        return new int[] { arr[r], arr[c] };
    }

    // Leetcode 347. Top K Frequent Elements==========================
    private class pair implements Comparable<pair> {
        int freq;
        int val;

        pair(int freq, int val) {
            this.freq = freq;
            this.val = val;
        }

        @Override
        public int compareTo(pair o) {
            return this.freq - o.freq;
        }
    }

    public int[] topKFrequent(int[] nums, int k) {
        HashMap<Integer, Integer> map = new HashMap<>();

        for (int ele : nums)
            map.put(ele, map.getOrDefault(ele, 0) + 1);

        PriorityQueue<pair> pq = new PriorityQueue<>();

        // we can avoid entry set and can use keyset
        for (Entry<Integer, Integer> entry : map.entrySet()) {
            pq.add(new pair(entry.getValue(), entry.getKey()));
            if (pq.size() > k) {
                pq.remove();
            }
        }

        int[] res = new int[k];
        for (int i = 0; i < k; i++) {
            res[i] = pq.remove().val;
        }
        return res;
    }

    public static void main(String[] args) {

    }
}