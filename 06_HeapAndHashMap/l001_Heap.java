import java.util.ArrayList;

class Heap {
    // Heap===========================================================
    private ArrayList<Integer> arr = null;
    private boolean isMaxHeap = true;

    public Heap(int[] data, boolean isMaxHeap) {
        arr = new ArrayList<>();

        int n = data.length;
        this.isMaxHeap = isMaxHeap;

        for (int i = 0; i < n; i++)
            arr.add(data[i]);

        // Here we can create Heap(i.e. Parenbt is max then child)
        // in O(n) time complexity
        for (int i = n - 1; i >= 0; i--)
            downHeapify(i, n);
    }

    private void swap(int a, int b) {
        int val1 = arr.get(a);
        int val2 = arr.get(b);

        arr.set(a, val2);
        arr.set(b, val1);
    }

    private void downHeapify(int pi, int n) {
        if (pi >= n)
            return;

        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;
        int maxIndx = pi;

        if (lci < n && compareTo(lci, maxIndx))// arr.get(lci) > arr.get(maxIndx))
            maxIndx = lci;
        if (rci < n && compareTo(rci, maxIndx))// arr.get(rci) > arr.get(maxIndx))
            maxIndx = rci;

        if (pi != maxIndx) {
            swap(pi, maxIndx);
            downHeapify(maxIndx, n);
        }
    }

    private void upHeapify(int ci) {
        int pi = (ci - 1) / 2;
        int minIndx = ci;

        if (pi >= 0 && compareTo(pi, ci))// this.arr.get(pi) < this.arr.get(ci))
            minIndx = pi;

        if (minIndx != ci) {
            swap(pi, ci);
            upHeapify(minIndx);
        }
    }

    public boolean compareTo(int x, int y) {
        if (isMaxHeap)
            return this.arr.get(x) > this.arr.get(y);
        else
            return this.arr.get(x) < this.arr.get(y);
    }

    // User's Function================================================
    public boolean isEmpty() {
        return this.arr.size() == 0;
    }

    public int size() {
        return this.arr.size();
    }

    public int top() {
        if (this.arr.size() == 0)
            return -1;

        return this.arr.get(0);
    }

    public void pop() {
        if (this.arr.size() == 0)
            return;

        swap(0, this.arr.size() - 1);
        this.arr.remove(this.arr.size() - 1);

        downHeapify(0, this.arr.size());
    }

    public void add(int val) {
        this.arr.add(val);
        upHeapify(this.arr.size() - 1);
    }
}

public class l001_Heap {

    public static int height(int[] arr, int indx) {
        if (indx >= arr.length)
            return 0;

        int lh = height(arr, 2 * indx + 1);
        int rh = height(arr, 2 * indx + 2);

        return Math.max(lh, rh) + 1;
    }

    public static int size(int[] arr, int indx) {
        if (indx >= arr.length)
            return 0;

        int ls = size(arr, 2 * indx + 1);
        int rs = size(arr, 2 * indx + 2);

        return ls + rs + 1;
    }

    public static void main(String[] args) {
        int[] arr = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13, 50 };
        Heap hp = new Heap(arr, true);

        while (hp.size() != 0) {
            System.out.print(hp.top() + " ");
            hp.pop();
        }
    }
}