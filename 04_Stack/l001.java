class MyStack {

    private int[] arr = null;

    private int size = 0;

    private int tos = -1;

    public MyStack(int size) {
        this.arr = new int[size];
    }

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public int top() {
        return this.arr[tos];
    }

    public void push(int data) {
        if (size > 10000) {
            System.out.println("StackOverFlow");
            return;
        }
        this.arr[size] = data;
        size++;
        tos++;
    }

    public int pop() {
        int data = this.arr[tos];
        this.arr[tos] = -1;
        size--;
        tos--;
        return data;
    }

    @Override
    public String toString() {
        String str = "[";
        int i = 0;
        for (; i < this.size - 1; i++) {
            str += this.arr[i] + ", ";
        }
        str += this.arr[i] + "]";
        return str;
    }
}

public class l001 {
    public static void main(String[] args) {
        MyStack st = new MyStack(10);

        for (int i = 0; i < 5; i++) {
            st.push(i + 10);
        }

        System.out.println(st);
        System.out.println(st.size());
        st.pop();
        System.out.println(st + "\n" + st.size());

        while (st.size() > 0) {
            int val = st.top();
            st.pop();
            System.out.println(val);
        }
    }
}