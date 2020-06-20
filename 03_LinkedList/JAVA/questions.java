import java.util.PriorityQueue;

public class questions {
    public class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
        }
    }

    // Leetcode 876. Middle of the Linked List=============================

    public ListNode middleNode(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // Leetcode 206. Reverse Linked List================================

    public ListNode reverseList(ListNode head) {
        if (head == null)
            return head;

        ListNode prev = null;
        ListNode curr = head;
        ListNode next = head.next;

        while (next != null) {
            curr.next = prev;
            prev = curr;
            curr = next;
            next = next.next;
        }

        curr.next = prev;
        return curr;
    }

    private ListNode getMidNode2(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        return slow;
    }

    // Class Question : Reverse Data in Linked List=============================
    public ListNode reverseDataInList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        if (head.next.next == null) {
            ListNode curr = head.next;
            curr.next = head;
            head.next = null;
            return curr;
        }
        ListNode curr1 = head;

        ListNode prev = getMidNode2(curr1);

        ListNode curr2 = prev.next;
        prev.next = null;

        curr2 = reverseList(curr2);

        ListNode nhead = curr2;

        while (curr1 != null && curr2 != null) {
            // swap data
            int temp = curr1.val;
            curr1.val = curr2.val;
            curr2.val = temp;

            curr1 = curr1.next;
            curr2 = curr2.next;
        }

        nhead = reverseList(nhead);

        prev.next = nhead;

        return head;
    }

    // Leetcode 234. Palindrome Linked List=======================================
    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null)
            return true;

        ListNode curr1 = head;
        ListNode mid = getMidNode2(curr1);

        ListNode curr2 = mid.next;
        mid.next = null;

        curr2 = reverseList(curr2);

        while (curr1 != null && curr2 != null) {
            if (curr1.val != curr2.val)
                return false;
            curr1 = curr1.next;
            curr2 = curr2.next;
        }

        return true;
    }

    // Leetcode 203. Remove Linked List Elements===================================
    public ListNode removeElements(ListNode head, int val) {
        ListNode curr = new ListNode(-1);
        curr.next = head;
        head = curr;

        while (curr.next != null) {
            if (curr.next.val == val) {
                ListNode rem = curr.next;
                curr.next = rem.next;
                rem.next = null;
            } else
                curr = curr.next;
        }
        return head.next;
    }

    // Leetcode 83. Remove Duplicates from Sorted
    // List============================================
    public ListNode deleteDuplicates(ListNode head) {
        ListNode curr = new ListNode(Integer.MIN_VALUE);
        curr.next = head;
        head = curr;

        while (curr.next != null) {
            if (curr.next.val == curr.val) {
                // remove current next
                ListNode rem = curr.next;
                curr.next = rem.next;
                rem.next = null;
            } else {
                curr = curr.next;
            }
        }
        return head.next;
    }

    // Leetcode 19. Remove Nth Node From End of List================================
    public ListNode removeNthFromEnd(ListNode head, int n) {
        if (head == null)
            return null;

        ListNode temp = new ListNode(-1);
        temp.next = head;
        // get (n - 1)th node
        ListNode slow = head;
        ListNode fast = head;
        while (n > 0) {
            fast = fast.next;
            n--;
        }

        // manage if fast is equal to null, that means we have to remove first node
        if (fast == null) {
            return slow.next;
        }

        // proceed fast and slow simultaneously
        while (fast.next != null) {
            slow = slow.next;
            fast = fast.next;
        }

        ListNode rem = slow.next;
        slow.next = rem.next;
        rem.next = null;
        return temp.next;
    }

    // Leetcode 143. Reorder List===============================================
    public void reorderList(ListNode head) {
        if (head == null || head.next == null || head.next.next == null)
            return;

        ListNode mid = getMidNode2(head);
        ListNode curr1 = head;
        ListNode curr2 = mid.next;
        mid.next = null;

        curr2 = reverseList(curr2);

        while (curr1 != null && curr2 != null) {
            ListNode temp1 = curr1;
            curr1 = curr1.next;
            temp1.next = curr2;

            ListNode temp2 = curr2;
            curr2 = curr2.next;
            temp2.next = curr1;
        }
    }

    // Leetcode 21. Merge Two Sorted Lists=================================
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null) {
            return l1 == null ? l2 : l1;
        }

        ListNode head = new ListNode(-1);
        ListNode prev = head;

        ListNode curr1 = l1;
        ListNode curr2 = l2;

        while (curr1 != null && curr2 != null) {
            if (curr1.val <= curr2.val) {
                prev.next = curr1;
                prev = curr1;
                curr1 = curr1.next;
            } else {
                prev.next = curr2;
                prev = curr2;
                curr2 = curr2.next;
            }
        }

        if (curr1 != null) {
            prev.next = curr1;
        }

        if (curr2 != null) {
            prev.next = curr2;
        }
        return head.next;
    }

    // Leetcode 141. Linked List Cycle=========================================
    public boolean hasCycle(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;

            if (slow == fast)
                return true;
        }
        return false;
    }

    // Leetcode 142. Linked List Cycle II===================================
    public ListNode detectCycle(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;

            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow.next;
                    fast = fast.next;
                }
                return slow;
            }
        }
        return null;
    }

    // Leetcode 2. Add Two Numbers=========================================
    public ListNode addTwoNumbers_(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null) {
            return l1 == null ? l2 : l1;
        }
        ListNode curr1 = l1;
        ListNode curr2 = l2;

        int carry = 0;
        ListNode head = null;
        ListNode ans = head;
        while (curr1 != null && curr2 != null) {
            int val = curr1.val + curr2.val + carry;
            if (head == null) {
                head = new ListNode(val % 10);
                ans = head;
            } else {
                head.next = new ListNode(val % 10);
                head = head.next;
            }
            carry = val / 10;
            curr1 = curr1.next;
            curr2 = curr2.next;
        }

        if (curr1 != null) {
            while (curr1 != null) {
                int val = curr1.val + carry;
                head.next = new ListNode(val % 10);
                head = head.next;
                curr1 = curr1.next;
                carry = val / 10;
            }
        }

        if (curr2 != null) {
            while (curr2 != null) {
                int val = curr2.val + carry;
                head.next = new ListNode(val % 10);
                head = head.next;
                curr2 = curr2.next;
                carry = val / 10;
            }
        }
        if (carry == 1) {
            head.next = new ListNode(1);
        }
        return ans;
    }

    // Leetcode 445. Add Two Numbers
    // II===============================================
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null) {
            return l1 == null ? l2 : l1;
        }
        ListNode curr1 = reverseList(l1);
        ListNode curr2 = reverseList(l2);

        int carry = 0;
        ListNode head = null;
        ListNode ans = head;
        while (curr1 != null && curr2 != null) {
            int val = curr1.val + curr2.val + carry;
            if (head == null) {
                head = new ListNode(val % 10);
                ans = head;
            } else {
                head.next = new ListNode(val % 10);
                head = head.next;
            }
            carry = val / 10;
            curr1 = curr1.next;
            curr2 = curr2.next;
        }

        if (curr1 != null) {
            while (curr1 != null) {
                int val = curr1.val + carry;
                head.next = new ListNode(val % 10);
                head = head.next;
                curr1 = curr1.next;
                carry = val / 10;
            }
        }

        if (curr2 != null) {
            while (curr2 != null) {
                int val = curr2.val + carry;
                head.next = new ListNode(val % 10);
                head = head.next;
                curr2 = curr2.next;
                carry = val / 10;
            }
        }
        if (carry == 1) {
            head.next = new ListNode(1);
        }
        ans = reverseList(ans);
        return ans;
    }

    // Leetcode 148. Sort List==================================================
    public ListNode sortList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        ListNode mid = getMidNode2(head);

        ListNode head2 = mid.next;
        mid.next = null;

        ListNode l1 = sortList(head);
        ListNode l2 = sortList(head2);

        ListNode res = mergeTwoLists(l1, l2);
        return res;
    }

    // Leetcode 160. Intersection of Two Linked
    // Lists=====================================
    public ListNode getIntersectionNode(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null)
            return null;
        ListNode tail = l1;
        while (tail.next != null)
            tail = tail.next;

        tail.next = l1;

        ListNode node = detectCycle(l2);
        tail.next = null;
        return node;
    }

    // Date : 13 JUNE 2020==============================================

    // Leetcode 23. Merge k Sorted Lists================================
    private class Pair implements Comparable<Pair> {
        ListNode node;

        Pair(ListNode node) {
            this.node = node;
        }

        public int compareTo(Pair o) {
            return this.node.val - o.node.val;
        }
    }

    public ListNode mergeKLists(ListNode[] lists) {
        if (lists.length == 0)
            return null;

        ListNode head = new ListNode(-1);
        ListNode curr = head;
        PriorityQueue<Pair> pq = new PriorityQueue<>();

        for (int i = 0; i < lists.length; i++) {
            if (lists[i] != null)
                pq.add(new Pair(lists[i]));
        }

        while (pq.size() > 0) {
            Pair rem = pq.remove();
            curr.next = rem.node;

            if (rem.node.next != null) {
                pq.add(new Pair(rem.node.next));
            }
            curr = curr.next;
        }
        return head.next;
    }

}