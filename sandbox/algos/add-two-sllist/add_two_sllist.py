#! /usr/bin/python

# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

    def __str__(self):

        node = self

        output = '['
        while(node):

            output = '{} {}'.format(output, node.val)
            node = node.next

        return('{} ]'.format(output))

def addTwoNumbers(l1, l2):
    """
    :type l1: ListNode
    :type l2: ListNode
    :rtype: ListNode
    """

    # init sll for sum
    sum = ListNode(0)
    cur_sum_node = sum
    carry = 0

    while(l1 or l2):

        # add l1.val and l2.val
        if l1:
            cur_sum_node.val += l1.val
            l1 = l1.next
        if l2:
            cur_sum_node.val += l2.val
            l2 = l2.next

        # calc amount to carry to next digit
        carry = int(cur_sum_node.val / 10)
        # calc current digit value
        cur_sum_node.val = cur_sum_node.val % 10

        if (carry or l1 or l2):
            cur_sum_node.next = ListNode(carry)
            cur_sum_node = cur_sum_node.next

    return sum

if __name__ == '__main__':

    l1 = ListNode(2)
    l1.next = ListNode(4)
    l1.next.next = ListNode(3)
    l1.next.next.next = ListNode(1)

    l2 = ListNode(5)
    l2.next = ListNode(6)
    l2.next.next = ListNode(4)

    my_sum = addTwoNumbers(l1, l2)

    print(my_sum)