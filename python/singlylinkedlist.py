from sys import maxsize
from typing import Optional
from dataclasses import dataclass
from node import Node


@dataclass
class SingleLinkedList:
    pass


    def __post_init__(self):
        self.__head: Node = None
        self.__tail: Node = None
        self.__count: int = 0


    @property
    def head(self) -> Node:
        """Gets the property of the head of the singly linked list."""
        return self.__head
    
    
    @property
    def tail(self) -> Node:
        """Gets the property of the tail of the singly linked list."""
        return self.__tail


    @property
    def count(self) -> int:
        """Gets the number of items in the list"""
        return self.__count


    def __len__(self) -> int:
        """Returns the count of nodes in the singly linked list."""
        return self.__count
    

    def __str__(self) -> str:
        """Returns the string representation of the singly linked list."""
        return f'SinglyinkedList(head={self.__head}, tail={self.__tail}, count={self.__count})'
    

    def __existance_of_elements(self):
        """Asserts if there is any node in the list."""
        ## Evaluate the existence of the single linked list
        assert self.head, 'There are no elements in the singly linked list. Use the add or append method.'


    def __iter__(self):
        """Iterates through the all nodes of the singly linked list."""
        ## If there is not head
        self.__existance_of_elements()

        ## Iterate until the last element of the list
        probe: Node = self.head
        while probe:
            yield probe
            probe = probe.next


    def display(self):
        """Display all nodes values of the singly linked list."""
        for node in self.__iter__():
            print(node.value)        


    def __verify_index(self, index: int):
        """Verifies the index of the input."""
        if not(-1 <= index < self.count):
            raise IndexError(f'The index value: {index} is out of range in the circular singly linked list.')


    def push(self, value: int):
        """Adds a node to the begging of the singly linked list."""

        self.__head = Node(value, self.head)

        if self.__tail is None:
            self.__tail = self.head

        self.__count += 1
        

    def append(self, value: int):
        """Appends node to the end of the single linked list."""

        if self.tail:
            self.__tail.next = Node(value)
            self.__tail = self.__tail.next
        else:
            self.__head = self.__tail = Node(value)

        self.__count += 1


    def insert(self, index: int, value: int):
        """Inserts a new node in function of the index."""
        ## Verify the existance of the list
        self.__existance_of_elements()

        ## Verify the range of the index
        self.__verify_index(index)

        ## Inserts on the index
        if index == 0:
            ## Add the beginning
            self.push(value)
        elif index in [-1, self.count-1]:
            ## Add the end of the single linked list
            self.append(value)
        else:
            ## Iterate through the desired index
            probe: Node = self.head

            while index > 1:
                probe = probe.next
                index -= 1

            ## Add a new node
            probe.next = Node(value, probe.next)
            self.__count += 1


    def insert_sorted(self, value: int):
        """Insert a new element if the singly linked list is sorted."""
        ## Check the list existence
        self.__existance_of_elements()

        ## Check if the new value is less than the head
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

            while probe != self.tail and probe.value != before_value:
                temp = probe
                probe = probe.next

            if probe.value == before_value:
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

            if temp == self.tail and temp.value == after_value:
                self.append(value)
            elif probe.value <= after_value:
                probe.next = Node(value, temp)
                self.__count += 1


    def index(self, value: int) -> list[int]:
        """Search for the index of the given value and return the list of indixes"""
        return [
            i for i, node in enumerate(self.__iter__()) if node.value == value
        ]


    def clear(self):
        """Deletes the single linked list."""
        self.__head = None
        self.__tail = None
        self.__count = 0


    def pop(self):
        """Deletes the last node of the singly linked list."""
        self.__existance_of_elements()

        if self.count == 1:
            self.clear()
            return

        probe: Node = self.head

        while probe.next != self.tail:
            probe = probe.next

        self.__tail = probe
        probe.next = None
        self.__count -= 1


    def shift(self):
        """Deletes the first node of the singly linked list."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        if self.count == 1:
            self.clear()
            return

        self.__head = self.__head.next
        self.__count -= 1


    def delete(self, index: int):
        """Deletes and element by an index."""
        ## Verify the index
        self.__verify_index(index)

        ## If there is only one element in the list
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

        ## In case its the first element
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
            temp.next = None
            self.__count -= 1
        elif probe != self.tail and probe.value == value:
            temp.next = probe.next
            self.__count -= 1


    def remove_duplicates_sorted(self):
        """Remove the duplicates values from the singly linked list."""
        ## Check the existence of the list
        self.__existance_of_elements()

        probe: Node = self.head
        temp: Node = self.head.next

        while temp:
            if probe.value != temp.value:
                probe = temp
                temp = temp.next
            else:
                probe.next = temp.next
                self.__count -= 1
                temp = probe.next


    def check_sort(self) -> bool:
        """Check if the singly linked list is sorted."""
        ## Check the existence of the list
        self.__existance_of_elements()

        probe: Node = self.__head
        x: int = -maxsize - 1

        while probe:
            if probe.value < x:
                return False
            
            x = probe.value
            probe = probe.next

        return True


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
        ## Evaluates if the list is empty
        self.__existance_of_elements()
        ## Evaluates the correct index
        self.__verify_index(index)

        ## Iterate until the given index is reached
        probe: Node = self.__head

        for _ in range(index):
            probe = probe.next

        ## Updates the value
        probe.value = value


    def reverse(self):
        """Reverse the singly linked list backwards."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        ## Iterate to reverse the list
        prev_node: Node = None
        next_node: Node = None
        probe: Node = self.head
        self.__tail = self.head

        while probe:
            next_node = probe.next
            probe.next = prev_node
            prev_node = probe
            probe = next_node

        self.__head = prev_node


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
                return probe

            temp = probe
            probe = probe.next

        return None