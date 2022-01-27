from sys import maxsize
from dataclasses import dataclass
from node import Node
from typing import Optional


@dataclass
class CircularSingleLinkedList:
    pass


    def __post_init__(self):
        self.__head: Node = None
        self.__tail: Node = None
        self.__count: int = 0


    @property
    def head(self) -> Node:
        """Gets the property of the head of the circular singly linked list."""
        return self.__head


    @property
    def tail(self) -> Node:
        """Gets the property of the tail of the circular singly linked list."""
        return self.__tail


    @property
    def count(self) -> int:
        """Gets the number of items in the list"""
        return self.__count


    def __len__(self) -> int:
        """Returns the count of nodes in the circular singly linked list."""
        return self.__count


    def __str__(self) -> str:
        """Returns the string representation of the circular singly linked list."""
        return f'CircularSinglyLinkedList(head={self.__head}, tail={self.__tail}, count={self.__count})'


    def __existance_of_elements(self):
        """Asserts if there is any node in the list."""
        ## Evaluate the existence of the single linked list
        assert self.head, 'There are no elements in the circular singly linked list. Use the add or append method.'


    def __iter__(self):
        """Iterates through the all nodes of the circular singly linked list."""
        ## If there is not head
        self.__existance_of_elements()

        ## Iterate through all nodes of the circular single linked list
        probe: Node = self.head

        for _ in range(self.count):
            yield probe
            probe = probe.next


    def display(self):
        """Display all nodes values of the circular singly linked list."""
        for node in self.__iter__():
            print(node.value)


    def __verify_index(self, index: int):
        """Verifies the index of the input."""
        if not(-1 <= index < self.count):
            raise IndexError(f'The index value: {index} is out of range in the circular singly linked list.')


    def push(self, value: int):
        """Adds a new node to the begging of the circular singly linked list."""

        self.__head = Node(value, self.__head)

        if not self.tail:
            self.__tail = self.head
        else:
            self.__tail.next = self.head

        self.__count += 1


    def append(self, value: int):
        """Appends new node to the end of the circular singly linked list."""

        if self.tail:
            self.__tail.next = Node(value)
            self.__tail = self.__tail.next
            self.__tail.next = self.head
        else:
            self.__head = self.__tail = Node(value)

        self.__count += 1


    def insert(self, index: int, value: int):
        """Inserts a new node in function of the index."""
        ## Check if the list exist
        self.__existance_of_elements()
        ## Verify if list is empty
        self.__verify_index(index)

        ## Inserts on the index
        if index == 0:
            ## Add the beginning
            self.push(value)
        elif index in [-1, self.count-1]:
            ## Add the end of the single linked list
            self.append(value)
        else:
            probe: Node = self.head
            temp: Node = None

            for _ in range(index):
                temp = probe
                probe = probe.next

            temp.next = Node(value, probe)
            self.__count += 1


    def before_value(self, before_value: int, value: int):
        """Inserts a new node before the first appearance of a given value."""
        ## Evaluate if the single linked list is empty
        self.__existance_of_elements()

        ## Evaluate the insertion
        if self.head.value == before_value:
            self.push(value)
        else:
            probe: Node = self.head
            temp: Node = None

            while temp != self.tail and probe.value != before_value:
                temp = probe
                probe = probe.next

            if probe != self.head:
                temp.next = Node(value, probe)
                self.__count += 1


    def after_value(self, after_value: int, value: int):
        """Inserts a new node after the first appearance of given value."""
        ## Evaluate the existance
        self.__existance_of_elements()

        if self.count == 1 and self.head.value == after_value:
            self.append(value)
        else:
            probe: Node = self.head
            temp: Node = self.head.next

            while temp != self.tail and probe.value != after_value:
                probe = temp
                temp = temp.next

            if temp == self.tail and temp.value <= after_value:
                self.append(value)
            elif probe.value <= after_value:
                probe.next = Node(value, temp)
                self.__count += 1


    def insert_sorted(self, value: int):
        """Insert a new element in a sorted in the circular singly linked list."""
        self.__existance_of_elements()

        if self.head.value >= value:
            self.push(value)
        elif self.tail.value <= value:
            self.append(value)
        else:
            probe: Node = self.head
            temp: Node = self.head.next

            while temp != self.tail and probe.value <= value and not(temp.value > value):
                probe = temp
                temp = temp.next

            probe.next = Node(value, temp)
            self.__count += 1



    def index(self, value: int) -> list[int]:
        """Search for the index of the given value and return the list of indixes"""
        return [
            i for i, node in enumerate(self.__iter__()) if node.value == value
        ]


    def clear(self):
        """Deletes the circular singly linked list."""
        self.__head = None
        self.__tail = None
        self.__count = 0


    def pop(self):
        """Deletes the last node of the circular singly linked list."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        ## Evaluates the number of nodes in the list
        if self.count == 1:
            self.clear()
            return

        ## Iterate to the node before the last
        probe: Node = self.head
        temp: Node = self.head.next

        while temp != self.tail:
            probe = temp
            temp = temp.next

        probe.next = self.head
        self.__tail = probe
        self.__count -= 1


    def shift(self):
        """Deletes the first node of the circular singly linked list."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        if self.count == 1:
            self.clear()
            return

        self.__head = self.head.next
        self.__tail.next = self.head
        self.__count -= 1


    def delete(self, index: int):
        """Deletes a node by a given index."""
        self.__existance_of_elements()
        ## Verify the index
        self.__verify_index(index)

        ## Verify the index corners
        if index == 0:
            self.shift()
        elif index in [-1, self.count-1]:
            self.pop()
        else:
            probe: Node = self.head
            temp: Node = None

            for _ in range(index):
                temp = probe
                probe = probe.next

            temp.next = probe.next
            self.__count -= 1


    def remove(self, value: int):
        """Deletes the first appearance of the given value."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        ## In case it's the first element
        if self.head.value == value:
            self.shift()
            return

        probe: Node = self.head
        temp: Node = None

        while probe != self.tail and probe.value != value:
            temp = probe
            probe = probe.next

        if probe == self.tail and probe.value == value:
            self.__tail = temp
            temp.next = self.head
            self.__count -= 1
        elif probe.value == value and probe != self.tail:
            temp.next = probe.next
            self.__count -= 1


    def unique_sorted(self):
        """Remove the duplicate values from the circular singly linked list."""
        ## Check the existence of the list
        self.__existance_of_elements()

        probe: Node = self.head
        temp: Node = self.head.next

        while temp != self.tail:
            if probe.value != temp.value:
                probe = temp
                temp = temp.next
            else:
                probe.next = temp.next
                self.__count -= 1
                temp = probe.next

        if temp == self.tail and probe.value == temp.value:
            self.__tail = probe
            probe.next = self.head
            self.__count -= 1


    def replace(self, old_value: int,value: int, entire: bool = False):
        """Replaces the first occurrence of the given value with new one or all apperances. By default replace the first appearance."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        ## Iterate through all the elements in case the all entire parameter is true
        for node in self.__iter__():
            if node.value == old_value:
                node.value = value
                if not entire:
                    break


    def update(self, index: int, value: int):
        """Updates a value in the list by a given index."""
        self.__existance_of_elements()
        ## Evaluates the correct index
        self.__verify_index(index)

        probe: Node = self.head

        for _ in range(index):
            probe = probe.next
        
        ## Updates the value
        probe.value = value


    def reverse(self):
        """Reverse the circular singly linked list backwards."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        next_node: Node = None
        prev_node: Node = None
        probe: Node = self.head

        for _ in range(self.count):
            next_node = probe.next ## Keep the next node of the original list
            probe.next = prev_node ## Join the next property with the previous node
            prev_node = probe ## Move the previous as the current
            probe = next_node ## Move to the next node of the original list

        self.__head = prev_node
        self.__tail = probe
        probe.next = self.head


    def check_sort(self) -> bool:
        """Check if the circular singly linked list is sorted."""
        self.__existance_of_elements()

        probe: Node = self.head
        x: int = -maxsize - 1

        for _ in range(self.count):
            if probe.value < x:
                return False

            x = probe.value
            probe = probe.next

        return True


    def search(self, value: int) -> Optional[Node]:
        """Returns the a node if the value is in the list."""
        self.__existance_of_elements()

        ## Check the extremes
        if self.head.value == value:
            return self.head
        elif self.tail.value == value:
            return self.tail

        probe: Node = self.head
        temp: Node = None

        for _ in range(self.count):

            if probe.value == value:
                temp.next = probe.next
                probe.next = self.head
                self.__head = probe
                self.__tail.next = self.head
                return probe

            temp = probe
            probe = probe.next

        return None